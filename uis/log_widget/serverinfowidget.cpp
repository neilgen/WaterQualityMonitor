#include "serverinfowidget.h"
#include "ui_serverinfowidget.h"

ServerInfoWidget::ServerInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerInfoWidget)
{
    ui->setupUi(this);
}

ServerInfoWidget::~ServerInfoWidget()
{
    delete ui;
}
