#include "varsettable.h"
#include "ui_varsettable.h"

VarSetTable::VarSetTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VarSetTable)
{
    ui->setupUi(this);

    connect(ui->pushButton_add, SIGNAL(clicked()),this,SLOT(onAdd()));
    connect(ui->pushButton_remove, SIGNAL(clicked()),this,SLOT(onRemove()));
    connect(ui->pushButton_cancel, SIGNAL(clicked()),this,SLOT(onCancel()));
    connect(ui->pushButton_apply, SIGNAL(clicked()),this,SLOT(onApply()));

    readConf();
}

VarSetTable::~VarSetTable()
{
    delete ui;
}

void VarSetTable::onAdd()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void VarSetTable::onRemove()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0) return ;

    ui->tableWidget->removeRow(row);
}

void VarSetTable::onCancel()
{
    readConf();
}

void VarSetTable::onApply()
{
    writeConf();
}

void VarSetTable::readConf()
{
    //读取配置
}

void VarSetTable::writeConf()
{
    //保存配置
}
