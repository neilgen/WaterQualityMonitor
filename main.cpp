#include "mainwidget.h"

#include <QApplication>
#include <QTextCodec>
#include "datastruct/logdata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("WaterQualityMonitor");
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));

    LogData::getIns();

    MainWidget w;
    w.show();
    return a.exec();
}
