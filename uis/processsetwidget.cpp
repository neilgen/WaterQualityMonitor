#include "processsetwidget.h"
#include "ui_processsetwidget.h"

ProcessSetWidget::ProcessSetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessSetWidget)
{
    ui->setupUi(this);
}

ProcessSetWidget::~ProcessSetWidget()
{
    delete ui;
}
