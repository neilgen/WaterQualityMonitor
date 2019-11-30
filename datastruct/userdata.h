#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>
#include "userstruct.h"
#include <QTimer>

class UserData : public QObject
{
    Q_OBJECT
private:
    explicit UserData(QObject *parent = 0);

public:
    static UserData * getIns();

    //输入用户名和密码登录
    QString login(QString name, QString passwd);
    //登出
    void logout();

    //检测当前用户是否拥有type的权限
    bool checkUserPermission(USER_PERMISSION_TYPE type) const;

    //获取当前用户能编辑的用户列表
    QList<User> getUsers() const ;
    //更新当前用户能编辑的用户信息
    void setUsers(const QList<User> us);

signals:
    //当前用户发生变化
    void sigUserChanged();

private slots:
    void slotTimeout();

private:
    //解析配置文件的用户信息
    void parse();
    //保存为配置
    void save();
    //获取配置文件路径
    QString getConfigPath();

private:
    User curUser;   //当前用户
    QList<User> users; //所有用户
    QTimer * timer; //用户登录超时提示
};

#endif // USERDATA_H
