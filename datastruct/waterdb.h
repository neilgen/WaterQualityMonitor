#ifndef WATERDB_H
#define WATERDB_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>

#define DATETIME_FORMAT "yyyy-MM-dd hh:mm:ss"

//数据库
class WaterDB : public QObject
{
    Q_OBJECT
private:
    explicit WaterDB(QObject *parent = 0);
    
public:
    static WaterDB* getIns();
    QSqlDatabase * getDB();

private:
    void initDB();
    QString getDBPath();

private:
    QSqlDatabase db;
};

#endif // WATERDB_H
