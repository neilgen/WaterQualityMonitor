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
    resetTable();
}

VarSetTable::~VarSetTable()
{
    delete ui;
}

void VarSetTable::onAdd()
{
    ui->table_vars->insertRow(ui->table_vars->rowCount());
}

void VarSetTable::onRemove()
{
    int row = ui->table_vars->currentIndex().row();
    if (row < 0) return ;

    ui->table_vars->removeRow(row);

    ui->table_vars->setCurrentItem(0);
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
    vars = VarData::getIns()->getVars();
    Var v;
    v.var_name = "asda";
    v.var_desc = "hhhdddddddd";
    v.var_value = 999.998;
    vars.append(v);
    vars.append(v);
    vars.append(v);
}

void VarSetTable::writeConf()
{
    //保存配置
    VarData::getIns()->setVars(vars);
}

void VarSetTable::resetTable()
{
    while(ui->table_vars->rowCount()){
        ui->table_vars->removeRow(0);
    }

    for(int i = 0; i < vars.count(); i++)
    {
        Var v = vars.at(i);
        int row = ui->table_vars->rowCount();
        ui->table_vars->insertRow(row);

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, v.var_name);
        ui->table_vars->setItem(row,0,item);

        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, v.var_desc);
        ui->table_vars->setItem(row,1,item);

        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, v.var_value);
        ui->table_vars->setItem(row,2,item);
    }
}
