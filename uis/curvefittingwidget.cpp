#include "curvefittingwidget.h"
#include "ui_curvefittingwidget.h"

CurveFittingWidget::CurveFittingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurveFittingWidget)
{
    ui->setupUi(this);
}

CurveFittingWidget::~CurveFittingWidget()
{
    delete ui;
}
