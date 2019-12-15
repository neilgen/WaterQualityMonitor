#include "waterdb.h"
#include <QDir>
#include <QDesktopServices>
#include <QApplication>
#include <QDebug>

WaterDB::WaterDB(QObject *parent) :
    QObject(parent)
{
    initDB();
}

WaterDB *WaterDB::getIns()
{
    static WaterDB wdb;
    return &wdb;
}

QSqlDatabase *WaterDB::getDB()
{
    if(!db.isValid())
    {
        return 0;
    }
    if(!db.isOpen())
    {
        db.open();
    }
    return &db;
}

void WaterDB::initDB()
{
    QString dbpath = getDBPath();
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");
    //db.setPort(3306);
    db.setDatabaseName(dbpath);
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open())
    {
        qDebug() << "打开数据库文件失败";
    }
}

QString WaterDB::getDBPath()
{
    QString path = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
    path = path + "/.config/" + QApplication::applicationName() + "/water.db";
    if(!QDir(path).exists())
    {
        QDir dir(QDesktopServices::storageLocation(QDesktopServices::HomeLocation));
        dir.mkdir(".config");
        dir.cd(".config");
        dir.mkdir(QApplication::applicationName());
        dir.cd(QApplication::applicationName());
    }
    return path;
}
