#include "userdata.h"
#include <QDesktopServices>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QApplication>
#include <QDate>

UserData::UserData(QObject *parent) :
    QObject(parent)
{
    parse();

    //需要将timer更改为系统空闲时间
    timer = new QTimer(this);
    timer->setInterval(3600*1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
}

UserData *UserData::getIns()
{
    static UserData ud;
    return &ud;
}

QString UserData::login(QString name, QString passwd)
{
    QString res;
    if(name.isEmpty())
    {
        res = QString("用户名为空");
        return res;
    }

    //用户匹配
    User matchUser;
    for(int i = 0; i < users.count(); i++)
    {
        User u = users.at(i);
        if(u.name.compare(name, Qt::CaseSensitive) == 0)
        {
            matchUser = u;
            break;
        }
    }
    if(matchUser.id <= 0 || matchUser.name.isEmpty())
    {
        res = QString("不存在该用户");
        return res;
    }

    //密码匹配
    if(matchUser.encryption == USER_ENCRYPTION_NULL)
    {
        curUser = matchUser;
        sigUserChanged();
    }
    else if(matchUser.encryption == USER_ENCRYPTION_FIXED)
    {
        if(matchUser.passwd.compare(passwd) == 0)
        {
            curUser = matchUser;
            sigUserChanged();
        }
        else
        {
            res = QString("密码不匹配");
        }
    }
    else if(matchUser.encryption == USER_ENCRYPTION_DATE)
    {
        QString date = QDate::currentDate().toString("MMdd");
        if(date.compare(passwd) == 0)
        {
            curUser = matchUser;
            sigUserChanged();
        }
        else
        {
            res = QString("密码不匹配");
        }
    }
    else if(matchUser.encryption == USER_ENCRYPTION_RANDOM)
    {
        //先设置成123456，后面修改成随机密码
        if(passwd.compare("123456") == 0)
        {
            curUser = matchUser;
            sigUserChanged();
        }
        else
        {
            res = QString("密码不匹配");
        }
    }
    else
    {
        res = QString("加密方式无法识别");
    }

    //登录成功开始计算超时
    timer->start();
    return res;
}

void UserData::logout()
{
    curUser = User();
    sigUserChanged();
}

bool UserData::checkUserPermission(USER_PERMISSION_TYPE type) const
{
    if((int)type < 0 || (int)type >= (int)USER_PERMISSION_TYPE_COUNT)
    {
        return false;
    }
    if((int)curUser.permission >= (int)type)
    {
        return true;
    }
    return false;
}

QList<User> UserData::getUsers() const
{
    QList<User> us;
    for(int i = 0; i < users.count(); i++)
    {
        User u = users.at(i);
        if(this->checkUserPermission(u.permission))
        {
            us.append(u);
        }
    }
    return us;
}

void UserData::setUsers(const QList<User> us)
{
    for(int i = 0; i < us.count(); i++)
    {
        User u = us.at(i);
        if(this->checkUserPermission(u.permission))
        {
            if(users.contains(u))
            {
                users.replace(users.indexOf(u), u);
            }
        }
    }
}

void UserData::parse()
{
    QString path = getConfigPath();
    QFile file(path);
    if(!file.open(QIODevice::ReadWrite))
    {
        file.close();
        return;
    }

    QDomDocument doc("userconfig");
    QString errmsg;
    if(doc.setContent(&file,&errmsg))
    {
        users.clear();
        QDomElement root = doc.documentElement();
        QDomElement userEle = root.firstChildElement("user");
        while(!userEle.isNull())
        {
            User u;
            u.id = userEle.attribute("id").toInt();
            u.name = userEle.attribute("name");
            u.encryption = (USER_ENCRYPTION_TYPE)userEle.attribute("encryption").toInt();
            u.permission = (USER_PERMISSION_TYPE)userEle.attribute("permission").toInt();
            if(u.encryption == USER_ENCRYPTION_FIXED)
            {
                QDomElement pdEle = userEle.firstChildElement("passwd");
                if(!pdEle.isNull())
                {
                    u.passwd = pdEle.attribute("content");
                }
            }
            users.append(u);
            userEle = userEle.nextSiblingElement("user");
        }
    }
    else
    {
        qDebug() << errmsg;
    }

    file.close();
}

void UserData::save()
{
    QString path = getConfigPath();
    QFile file(path);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        file.close();
        return;
    }

    QDomDocument doc("userconfig");
    QDomElement root = doc.createElement("users");
    doc.appendChild(root);
    for(int i = 0; i < users.count(); i++)
    {
        User u = users.at(i);
        QDomElement userEle = doc.createElement("user");
        userEle.setAttribute("id", u.id);
        userEle.setAttribute("name", u.name);
        userEle.setAttribute("encryption", (int)u.encryption);
        userEle.setAttribute("permission", (int)u.permission);
        if(u.encryption == USER_ENCRYPTION_FIXED)
        {
            QDomElement pdEle = doc.createElement("passwd");
            pdEle.setAttribute("content",u.passwd);
            userEle.appendChild(pdEle);
        }
        root.appendChild(userEle);
    }

    file.write(doc.toByteArray());
    file.close();
}

QString UserData::getConfigPath()
{
    QString path = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
    path = path + "/.config/" + QApplication::applicationName() + "/users.xml";
    if(!QDir(path).exists())
    {
        QDir dir(QDesktopServices::storageLocation(QDesktopServices::HomeLocation));
        dir.mkdir(".config");
        dir.cd(".config");
        dir.mkdir(QApplication::applicationName());
        dir.cd(QApplication::applicationName());

        QFile::copy(":/res/config/users.xml",path);

        //这样直接拷贝过去的文件没有写的权限，加上写权限
        QString cmd("/bin/chmod 666 ");
        cmd += path;
        system(cmd.toLatin1().data());
    }
    return path;
}

void UserData::slotTimeout()
{
    this->logout();
    if(timer->isActive())
    {
        timer->stop();
    }
}


