#include "logwidget.h"
#include "ui_logwidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);

    logActorWidget = new LogActorWidget(this);
    logRunningWidget = new LogRunningWidget(this);
    logFaultWidget = new LogFaultWidget(this);
    deviceInfoWidget = new DeviceInfoWidget(this);
    serverInfoWidget = new ServerInfoWidget(this);

    ui->stackedWidget->addWidget(logActorWidget);
    ui->stackedWidget->addWidget(logRunningWidget);
    ui->stackedWidget->addWidget(logFaultWidget);
    ui->stackedWidget->addWidget(deviceInfoWidget);
    ui->stackedWidget->addWidget(serverInfoWidget);

    ui->stackedWidget->setCurrentWidget(logActorWidget);
    logActorWidget->refresh();

    connect(ui->pushButton_actor, SIGNAL(clicked()),
            this, SLOT(slotActor()));
    connect(ui->pushButton_device,SIGNAL(clicked()),
            this, SLOT(slotDevice()));
    connect(ui->pushButton_fault, SIGNAL(clicked()),
            this, SLOT(slotFault()));
    connect(ui->pushButton_home, SIGNAL(clicked()),
            this, SLOT(slotHome()));
    connect(ui->pushButton_running,SIGNAL(clicked()),
            this, SLOT(slotRunning()));
    connect(ui->pushButton_server, SIGNAL(clicked()),
            this, SLOT(slotServer()));
}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::slotActor()
{
    if(ui->stackedWidget->currentWidget() != logActorWidget)
    {
        ui->stackedWidget->setCurrentWidget(logActorWidget);
        logActorWidget->refresh();
    }
}

void LogWidget::slotRunning()
{
    if(ui->stackedWidget->currentWidget() != logRunningWidget)
    {
        ui->stackedWidget->setCurrentWidget(logRunningWidget);
        logRunningWidget->refresh();
    }
}

void LogWidget::slotFault()
{
    if(ui->stackedWidget->currentWidget() != logFaultWidget)
    {
        ui->stackedWidget->setCurrentWidget(logFaultWidget);
        logFaultWidget->refresh();
    }
}

void LogWidget::slotDevice()
{
    if(ui->stackedWidget->currentWidget() != deviceInfoWidget)
    {
        ui->stackedWidget->setCurrentWidget(deviceInfoWidget);
//        deviceInfoWidget->refresh();
    }
}

void LogWidget::slotServer()
{
    if(ui->stackedWidget->currentWidget() != serverInfoWidget)
    {
        ui->stackedWidget->setCurrentWidget(serverInfoWidget);
//        serverInfoWidget->refresh();
    }
}

void LogWidget::slotHome()
{
}
