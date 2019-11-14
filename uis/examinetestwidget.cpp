#include "examinetestwidget.h"
#include "ui_examinetestwidget.h"

ExamineTestWidget::ExamineTestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamineTestWidget)
{
    ui->setupUi(this);
}

ExamineTestWidget::~ExamineTestWidget()
{
    delete ui;
}
