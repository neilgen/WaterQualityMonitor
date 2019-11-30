#ifndef LOGSTRUCT_H
#define LOGSTRUCT_H

#include <QString>
#include <QDateTime>

enum LOG_TYPE
{
    LOG_RUNNING = 0,    //运行日志
    LOG_ACTOR = 1,      //操作日志
    LOG_FAULT = 2,      //故障日志

    LOG_TYPE_COUNT
};

struct Log
{
    int id;     //id
    QDateTime dt;       //日期时间
    QString detail;     //详细信息
    QString notes;      //批注
    Log()
    {
        id = 0;
    }
};


#endif // LOGSTRUCT_H
