#ifndef LOGSTRUCT_H
#define LOGSTRUCT_H

#include <QString>
#include <QDateTime>

enum LOG_TYPE
{
    LOG_NULL = 0,       //一般日志
    LOG_RUNNING = 1,    //运行日志
    LOG_ACTOR = 2,      //操作日志
    LOG_FAULT = 3,      //故障日志

    LOG_TYPE_COUNT
};

struct Log
{
    int id;     //id
    LOG_TYPE type;
    QDateTime dt;       //日期时间
    QString detail;     //详细信息
    QString notes;      //批注
    Log()
    {
        id = 0;
        type = LOG_NULL;
    }
};


#endif // LOGSTRUCT_H
