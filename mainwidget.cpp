#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMenu>
#include "uis/varsettable.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->RootWidget->move(0,0);
    initConnect();
}

MainWidget::~MainWidget()
{
    delete ui;
}
void MainWidget::initConnect()
{
    connect(ui->otherButton, SIGNAL(clicked()), this, SLOT(onPopMenu()));
}
void MainWidget::resizeEvent(QResizeEvent *event)
{

    ui->RootWidget->resize(event->size());
}
void MainWidget::onPopMenu()
{
    QMenu menu;
    QAction otherAction(QObject::tr("其他"), &menu);
    QAction logAction(QObject::tr("日志"), &menu);
    QAction guardAction(QObject::tr("仪器维护"), &menu);
    QAction instrumentAction(QObject::tr("仪器设置"), &menu);
    QAction reviewAction(QObject::tr("审核测试"), &menu);
    QAction flowAction(QObject::tr("流程设计"), &menu);
    QAction curveAction(QObject::tr("拟合曲线"), &menu);
    QAction varAction(QObject::tr("变量设计显示"), &menu);
    menu.addAction(&otherAction);
    menu.addAction(&logAction);
    menu.addAction(&guardAction);
    menu.addAction(&instrumentAction);
    menu.addAction(&reviewAction);
    menu.addAction(&flowAction);
    menu.addAction(&curveAction);
    menu.addAction(&varAction);
    connect(&otherAction, SIGNAL(triggered()), this, SLOT(onOtherActionTriggered()) );
    connect(&logAction, SIGNAL(triggered()), this, SLOT(onLogActionTriggered()) );
    connect(&guardAction, SIGNAL(triggered()), this, SLOT(onGuardActionTriggered()) );
    connect(&instrumentAction, SIGNAL(triggered()), this, SLOT(onInstrumentActionTriggered()) );
    connect(&reviewAction, SIGNAL(triggered()), this, SLOT(onReviewActionTriggered()) );
    connect(&flowAction, SIGNAL(triggered()), this, SLOT(onFlowActionTriggered()) );
    connect(&curveAction, SIGNAL(triggered()), this, SLOT(onCurveActionTriggered()) );
    connect(&varAction, SIGNAL(triggered()), this, SLOT(onVarActionTriggered()) );
    QPoint pos;
    pos.setX(0);
    pos.setY(-menu.sizeHint().height());
    menu.exec(ui->otherButton->mapToGlobal(pos));
}
void MainWidget::onOtherActionTriggered()
{
    qDebug() << "Other Actoin Triggered";
}
void MainWidget::onLogActionTriggered()
{
    qDebug() << "Other Actoin Triggered";
}
void MainWidget::onGuardActionTriggered()
{
    qDebug() << "Other Actoin Triggered";
}
void MainWidget::onInstrumentActionTriggered()
{
    qDebug() << "Other Actoin Triggered";
}
void MainWidget::onReviewActionTriggered()
{
    qDebug() << "Other Actoin Triggered";
}
void MainWidget::onFlowActionTriggered()
{
    qDebug() << "Other Actoin Triggered";
}
void MainWidget::onCurveActionTriggered()
{
    qDebug() << "Other Actoin Triggered";
}
void MainWidget::onVarActionTriggered()
{
    qDebug() << "Other Actoin Triggered";
    VarSetTable *t = new VarSetTable();
    t->show();
}
