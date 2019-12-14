#include "measurementdata.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

MeasurementData::MeasurementData(QObject *parent) :
    QObject(parent)
{
    initMeasurementTable();
}

MeasurementData *MeasurementData::getIns()
{
    static MeasurementData md;
    return &md;
}

void MeasurementData::addMeasurement(const Measurement &m)
{
    QSqlDatabase *db = WaterDB::getIns()->getDB();
    QSqlQuery sql_query(*db);
    //查询数据库中存放的最大ID
    int id = 0;
    QString sql_id = "select max(id) from measurement";
    if(sql_query.exec(sql_id))
    {
        while(sql_query.next())
        {
            id = sql_query.value(0).toInt();
            qDebug()<<QString(":DB:measurement: max id:%1").arg(id);
            id = id + 1;
        }
    }
    else
    {
        qDebug()<<sql_query.lastError();
    }

    //
    QString sql_insert = "insert into measurement (id, datetime,"
            "consistence,range,k,b,mode,sign,absorbance,"
            "voltage, voltage_ref) "
            "values (%1, \"%2\", %3, %4, %5, %6, %7, %8, %9, %10, %11)";
    sql_insert = sql_insert.arg(id)
            .arg(m.datetime.toString(DATETIME_FORMAT))
            .arg(m.consistence)
            .arg(m.range)
            .arg(m.k).arg(m.b)
            .arg((int)m.mode)
            .arg(m.sign)
            .arg(m.absorbance)
            .arg(m.voltage)
            .arg(m.voltage_ref);
    if(sql_query.exec(sql_insert))
    {
        qDebug() << ":DB:measurement:table insert successed!";
    }
    else
    {
        qDebug()<<sql_query.lastError();
    }
}

void MeasurementData::modifyMeasurement(
        int id, QDateTime dt, float consistence,
        MEASUREMENT_MODE_TYPE mode, int sign)
{
    QSqlDatabase *db = WaterDB::getIns()->getDB();
    QSqlQuery sql_query(*db);
    //查询ID为id的记录是否存在
    bool isExist = false;
    QString sql_id = "select * from measurement where id=%1";
    sql_id = sql_id.arg(id);
    if(sql_query.exec(sql_id))
    {
        while(sql_query.next())
        {
            isExist = true;
        }
    }
    else
    {
        qDebug() << sql_query.lastError();
    }

    if(isExist)
    {
        QString sql_update = "update measurement set datetime=\"%1\", "
                "consistence=%2,mode=%3,sign=%4 where id=%5";
        sql_update = sql_update.arg(dt.toString(DATETIME_FORMAT))
                .arg(consistence)
                .arg((int)mode)
                .arg(sign)
                .arg(id);
        if(sql_query.exec(sql_update))
        {
            qDebug() << ":DB:measurement:table update successed!";
        }
        else
        {
            qDebug()<<sql_query.lastError();
        }
    }
}

void MeasurementData::deleteMeasurement(int id)
{
    QSqlDatabase *db = WaterDB::getIns()->getDB();
    QSqlQuery sql_query(*db);
    //查询ID为id的记录是否存在
    bool isExist = false;
    QString sql_id = "select * from measurement where id=%1";
    sql_id = sql_id.arg(id);
    if(sql_query.exec(sql_id))
    {
        while(sql_query.next())
        {
            isExist = true;
        }
    }
    else
    {
        qDebug() << sql_query.lastError();
    }

    if(isExist)
    {
        QString sql_delete = "delete from measurement where id=%1";
        sql_delete = sql_delete.arg(id);
        if(sql_query.exec(sql_delete))
        {
            qDebug() << ":DB:measurement:table delete successed!";
        }
        else
        {
            qDebug()<<sql_query.lastError();
        }
    }
}

QList<Measurement> MeasurementData::getMeasurement() const
{
    QList<Measurement> ms;
    QSqlDatabase *db = WaterDB::getIns()->getDB();
    QSqlQuery sql_query(*db);
    QString sql = "select id, datetime,"
            "consistence,range,k,b,mode,sign,absorbance,"
            "voltage, voltage_ref from measurement";
    if(sql_query.exec(sql))
    {
        while(sql_query.next())
        {
            Measurement m;
            m.id = sql_query.value(0).toInt();
            m.datetime = QDateTime::fromString(sql_query.value(1).toString(), DATETIME_FORMAT);
            m.consistence = sql_query.value(2).toFloat();
            m.range = sql_query.value(3).toInt();
            m.k = sql_query.value(4).toFloat();
            m.b = sql_query.value(5).toFloat();
            m.mode = (MEASUREMENT_MODE_TYPE)sql_query.value(6).toInt();
            m.sign = sql_query.value(7).toInt();
            m.absorbance = sql_query.value(8).toFloat();
            m.voltage = sql_query.value(9).toFloat();
            m.voltage_ref = sql_query.value(10).toFloat();
            ms.append(m);
        }
    }
    else
    {
        qDebug() << ":DB:measurement:" << sql << "failed";
    }
    return ms;
}

QList<Measurement> MeasurementData::getMeasurement(
        int minRange, int maxRange,
        const QDateTime beginDt,
        const QDateTime endDt,
        MEASUREMENT_MODE_TYPE mode) const
{
    QList<Measurement> ms;
    if(minRange <= maxRange && beginDt.isValid() && endDt.isValid() && beginDt <= endDt)
    {
        //
        QSqlDatabase *db = WaterDB::getIns()->getDB();
        QSqlQuery sql_query(*db);
        QString sql = "select id, datetime,"
                "consistence,range,k,b,mode,sign,absorbance,"
                "voltage, voltage_ref from measurement where "
                "range >= %1 and range <= %2 "
                "and datetime >= \"%3\" and datetime <= \"%4\" and mode=%5";
        sql = sql.arg(minRange).arg(maxRange)
                .arg(beginDt.toString(DATETIME_FORMAT))
                .arg(endDt.toString(DATETIME_FORMAT))
                .arg((int)mode);
        if(sql_query.exec(sql))
        {
            while(sql_query.next())
            {
                Measurement m;
                m.id = sql_query.value(0).toInt();
                m.datetime = QDateTime::fromString(sql_query.value(1).toString(), DATETIME_FORMAT);
                m.consistence = sql_query.value(2).toFloat();
                m.range = sql_query.value(3).toInt();
                m.k = sql_query.value(4).toFloat();
                m.b = sql_query.value(5).toFloat();
                m.mode = (MEASUREMENT_MODE_TYPE)sql_query.value(6).toInt();
                m.sign = sql_query.value(7).toInt();
                m.absorbance = sql_query.value(8).toFloat();
                m.voltage = sql_query.value(9).toFloat();
                m.voltage_ref = sql_query.value(10).toFloat();
                ms.append(m);
            }
        }
        else
        {
            qDebug() << ":DB:measurement:" << sql << "failed";
        }
    }
    return ms;
}

void MeasurementData::initMeasurementTable()
{
    QSqlDatabase *db = WaterDB::getIns()->getDB();
    QStringList tables = db->tables(QSql::Tables);
    if(!tables.contains("measurement"))
    {
        qDebug() << "DB: table measurement is Not Exist.";
        //创建表
        QString sql = "create table measurement (id int primary key,"
                "datetime varchar(25), "
                "consistence float, range int, k float, b float,"
                "mode int, sign int, absorbance float, "
                "voltage float, voltage_ref float)";
        QSqlQuery sql_query(*db);
        if(sql_query.exec(sql))
        {
            qDebug() << ":DB:measurement:table created!";
        }
        else
        {
            qDebug()<<sql_query.lastError();
        }
    }
}
