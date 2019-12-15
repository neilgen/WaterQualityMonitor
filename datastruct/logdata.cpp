#include "logdata.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

LogData::LogData(QObject *parent) :
    QObject(parent)
{
    initLogTable();
}

LogData *LogData::getIns()
{
    static LogData ld;
    return &ld;
}

void LogData::addLog(const LOG_TYPE t, const QString de, const QString notes)
{
    QSqlDatabase *db = WaterDB::getIns()->getDB();
    QSqlQuery sql_query(*db);
    //查询数据库中存放的最大ID
    int id = 0;
    QString sql_id = "select max(id) from log";
    if(sql_query.exec(sql_id))
    {
        while(sql_query.next())
        {
            id = sql_query.value(0).toInt();
            qDebug()<<QString(":DB:log: max id:%1").arg(id);
            id = id + 1;
        }
    }
    else
    {
        qDebug()<<sql_query.lastError();
    }

    //
    QString sql_insert = "insert into log (id,type,datetime,detail,notes) "
            "values (%1, %2, \"%3\", \"%4\", \"%5\")";
    sql_insert = sql_insert.arg(id).arg((int)t).arg(QDateTime::currentDateTime().toString(DATETIME_FORMAT))
            .arg(de).arg(notes);
    if(sql_query.exec(sql_insert))
    {
        qDebug() << ":DB:log:table insert successed!";
    }
    else
    {
        qDebug()<<sql_query.lastError();
    }
}

QList<Log> LogData::getLog(const LOG_TYPE t) const
{
    QList<Log> logs;

    QSqlDatabase *db = WaterDB::getIns()->getDB();
    QSqlQuery sql_query(*db);
    QString sql = "select id,type,datetime,detail,notes from log where type = %1";
    sql = sql.arg((int)t);
    if(sql_query.exec(sql))
    {
        while(sql_query.next())
        {
            Log l;
            l.id = sql_query.value(0).toInt();
            l.type = (LOG_TYPE)sql_query.value(1).toInt();
            l.dt = QDateTime::fromString(sql_query.value(2).toString(), DATETIME_FORMAT);
            l.detail = sql_query.value(3).toString();
            l.notes = sql_query.value(4).toString();
            logs.append(l);
        }
    }
    else
    {
        qDebug() << ":DB:log:" << sql << "failed";
    }
    return logs;
}

QList<Log> LogData::getLogBefore(const LOG_TYPE t, const QDateTime dt) const
{
    QDateTime beginDt = QDateTime::fromTime_t(0);
    return getLog(t, beginDt, dt);
}

QList<Log> LogData::getLogAfter(const LOG_TYPE t, const QDateTime dt) const
{
    QDateTime endDt = QDateTime::fromTime_t(9999999999);//2286/11/20 9:46:39
    return getLog(t, dt, endDt);
}

QList<Log> LogData::getLog(const LOG_TYPE t, const QDateTime beginDt, const QDateTime endDt) const
{
    QList<Log> logs;
    if(beginDt.isValid() && endDt.isValid() && beginDt <= endDt)
    {
        //
        QSqlDatabase *db = WaterDB::getIns()->getDB();
        QSqlQuery sql_query(*db);
        QString sql = "select id,type,datetime,detail,notes from log where type = %1 "
                "and datetime >= \"%2\" and datetime <= \"%3\"";
        sql = sql.arg((int)t).arg(beginDt.toString(DATETIME_FORMAT)).arg(endDt.toString(DATETIME_FORMAT));
        if(sql_query.exec(sql))
        {
            while(sql_query.next())
            {
                Log l;
                l.id = sql_query.value(0).toInt();
                l.type = (LOG_TYPE)sql_query.value(1).toInt();
                l.dt = QDateTime::fromString(sql_query.value(2).toString(), DATETIME_FORMAT);
                l.detail = sql_query.value(3).toString();
                l.notes = sql_query.value(4).toString();
                logs.append(l);
            }
        }
        else
        {
            qDebug() << ":DB:log:" << sql << "failed";
        }
    }
    return logs;
}

void LogData::initLogTable()
{
    QSqlDatabase *db = WaterDB::getIns()->getDB();
    QStringList tables = db->tables(QSql::Tables);
    if(!tables.contains("log"))
    {
        qDebug() << "DB: table log is Not Exist.";
        //创建表
        QString sql = "create table log (id int primary key, type int, datetime varchar(25),"
                "detail varchar(200), notes varchar(200))";
        QSqlQuery sql_query(*db);
        if(sql_query.exec(sql))
        {
            qDebug() << ":DB:log:table created!";
        }
        else
        {
            qDebug()<<sql_query.lastError();
        }
    }
}


