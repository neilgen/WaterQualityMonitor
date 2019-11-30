#include "logdata.h"
#include <QDir>
#include <QDesktopServices>
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>

LogData::LogData(QObject *parent) :
    QObject(parent)
{
    initDBTable();
}

LogData *LogData::getIns()
{
    static LogData ld;
    return &ld;
}

void LogData::addLog(const LOG_TYPE t, const QString de, const QString notes)
{
    //
}

QList<Log> LogData::getLog(const LOG_TYPE t) const
{
    QList<Log> logs;
    //
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
    }
    return logs;
}

void LogData::initDBTable()
{
//    QString create_sql = "create table log (id int primary key, name varchar(30), age int)";
//    QSqlDatabase *db = WaterDB::getIns()->getDB();
}


