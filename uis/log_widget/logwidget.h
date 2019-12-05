#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include "logactorwidget.h"
#include "logrunningwidget.h"
#include "logfaultwidget.h"
#include "deviceinfowidget.h"
#include "serverinfowidget.h"

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();
    
private slots:
    void slotActor();
    void slotRunning();
    void slotFault();
    void slotDevice();
    void slotServer();
    void slotHome();

private:
    Ui::LogWidget *ui;
    LogActorWidget * logActorWidget;
    LogRunningWidget * logRunningWidget;
    LogFaultWidget * logFaultWidget;
    DeviceInfoWidget * deviceInfoWidget;
    ServerInfoWidget * serverInfoWidget;
};

#endif // LOGWIDGET_H
