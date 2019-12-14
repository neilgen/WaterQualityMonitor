#include "mainwidget.h"

#include <QApplication>
#include <QTextCodec>

//test--BEGIN----------
//#include "datastruct/logdata.h"
//#include "uis/log_widget/logwidget.h"
//#include "uis/measurement/measurementwidget.h"
//test--END------------

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("WaterQualityMonitor");
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));


    //test-----BEGIN----------

//    LogData::getIns()->addLog(LOG_RUNNING, QString::fromUtf8("运行记录日志"), QString::fromUtf8("标注内容 运行"));
//    LogData::getIns()->addLog(LOG_ACTOR, QString::fromUtf8("操作记录日志"), QString::fromUtf8("标注内容 操作"));
//    LogData::getIns()->addLog(LOG_FAULT, QString::fromUtf8("系统错误记录日志"), QString::fromUtf8("标注内容 系统错误"));
//    LogWidget logw;
//    logw.show();

//    Measurement m;
//    m.datetime = QDateTime::currentDateTime();
//    m.range = 1000;
//    MeasurementData::getIns()->addMeasurement(m);
//    MeasurementWidget mea;
//    mea.show();

    //test-----END------------

    MainWidget w;
    w.show();
    return a.exec();
}
