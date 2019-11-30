#ifndef LOGDATA_H
#define LOGDATA_H

#include <QObject>
#include "logstruct.h"
#include "waterdb.h"

class LogData : public QObject
{
    Q_OBJECT
private:
    explicit LogData(QObject *parent = 0);

public:
    static LogData * getIns();

    //添加日志
    void addLog(const LOG_TYPE t, const QString de, const QString notes = QString());

    //获取日志
    QList<Log> getLog(const LOG_TYPE t) const;
    QList<Log> getLogBefore(const LOG_TYPE t, const QDateTime dt) const;
    QList<Log> getLogAfter(const LOG_TYPE t, const QDateTime dt) const;
    QList<Log> getLog(const LOG_TYPE t, const QDateTime beginDt, const QDateTime endDt) const;

private:
    void initDBTable();

private:

};

#endif // LOGDATA_H
