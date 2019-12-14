#include "measurementwidget.h"
#include "ui_measurementwidget.h"
#include "datas.h"

MeasurementWidget::MeasurementWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasurementWidget)
{
    ui->setupUi(this);

    ui->dateTimeEdit_begin->setDate(QDate::currentDate().addDays(-1));
    ui->dateTimeEdit_end->setDate(QDate::currentDate());

    //自适应显示
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->setSelectionMode(QTableWidget::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->tableWidget->verticalHeader()->hide();
    connect(ui->tableWidget, SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)),
            this, SLOT(slotTableCurSelectedChanged(QTableWidgetItem*,QTableWidgetItem*)));

    connect(ui->pushButton_home, SIGNAL(clicked()),
            this, SLOT(slotHome()));
    connect(ui->pushButton_search, SIGNAL(clicked()),
            this, SLOT(slotSearch()));
    connect(ui->pushButton_export, SIGNAL(clicked()),
            this, SLOT(slotExport()));
    connect(ui->pushButton_curve, SIGNAL(clicked()),
            this, SLOT(slotCurve()));
    connect(ui->pushButton_printall, SIGNAL(clicked()),
            this, SLOT(slotPrintAll()));
    connect(ui->pushButton_printselected, SIGNAL(clicked()),
            this, SLOT(slotPrintSelected()));
    connect(ui->pushButton_modify,SIGNAL(clicked()),
            this, SLOT(slotModify()));
    connect(ui->pushButton_delete, SIGNAL(clicked()),
            this, SLOT(slotDelete()));

    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_modify->setEnabled(false);

    //权限设置
    slotUserChanged();
    UserData *ud = UserData::getIns();
    connect(ud, SIGNAL(sigUserChanged()), this, SLOT(slotUserChanged()));

    refresh();
}

MeasurementWidget::~MeasurementWidget()
{
    delete ui;
}

void MeasurementWidget::refresh()
{
    QList<Measurement> ms = MeasurementData::getIns()->getMeasurement();

    refreshUI(ms);
}

void MeasurementWidget::slotHome()
{
}

void MeasurementWidget::slotUserChanged()
{
    UserData *ud = UserData::getIns();
    if(ud->checkUserPermission(USER_PERMISSION_MANAGER) ||
            ud->checkUserPermission(USER_PERMISSION_MAINTAIN) ||
            ud->checkUserPermission(USER_PERMISSION_SUPER))
    {
        ui->tableWidget->showColumn(8);
        ui->tableWidget->showColumn(9);
        ui->tableWidget->showColumn(10);
    }
    else
    {
        ui->tableWidget->hideColumn(8);
        ui->tableWidget->hideColumn(9);
        ui->tableWidget->hideColumn(10);
    }
    if(ud->checkUserPermission(USER_PERMISSION_SUPER))
    {
        ui->frame_super->show();
    }
    else
    {
        ui->frame_super->hide();
    }
}

void MeasurementWidget::slotSearch()
{
    QDateTime beginDt = ui->dateTimeEdit_begin->dateTime();
    QDateTime endDt = ui->dateTimeEdit_end->dateTime();
    int minR = ui->spinBox_minRange->value();
    int maxR = ui->spinBox_maxRange->value();
    MEASUREMENT_MODE_TYPE mode = (MEASUREMENT_MODE_TYPE)ui->comboBox_mode->currentIndex();

    QList<Measurement> ms = MeasurementData::getIns()->getMeasurement(
                minR, maxR, beginDt, endDt,mode);

    refreshUI(ms);
}

void MeasurementWidget::slotCurve()
{
}

void MeasurementWidget::slotExport()
{
}

void MeasurementWidget::slotPrintAll()
{
}

void MeasurementWidget::slotPrintSelected()
{
}

void MeasurementWidget::slotTableCurSelectedChanged(
        QTableWidgetItem *current, QTableWidgetItem *previous)
{
    //删除时，会发送一个空的current对象过来
    if(current)
    {
        int row = current->row();
        if(row < 0 || row >= ui->tableWidget->rowCount()) return;

        QString dt = ui->tableWidget->item(row, 1)->text();
        ui->dateTimeEdit_modify->setDateTime(QDateTime::fromString(dt, DATETIME_FORMAT));

        float consistence = ui->tableWidget->item(row, 2)->text().toFloat();
        ui->doubleSpinBox_consistence_modify->setValue(consistence);

        MEASUREMENT_MODE_TYPE mode = get_MEASUREMENT_MODE_TYPE(ui->tableWidget->item(row, 6)->text());
        ui->comboBox_mode_modify->setCurrentIndex((int)mode);

        int sign = ui->tableWidget->item(row, 7)->text().toInt();
        ui->spinBox_sign_modify->setValue(sign);

        ui->pushButton_delete->setEnabled(true);
        ui->pushButton_modify->setEnabled(true);
    }
    else
    {
        ui->dateTimeEdit_modify->setDateTime(QDateTime::currentDateTime());
        ui->doubleSpinBox_consistence_modify->setValue(0);
        ui->comboBox_mode_modify->setCurrentIndex(0);
        ui->spinBox_sign_modify->setValue(0);

        ui->pushButton_delete->setEnabled(false);
        ui->pushButton_modify->setEnabled(false);
    }
}

void MeasurementWidget::slotModify()
{
    QTableWidgetItem *item = ui->tableWidget->currentItem();
    if(!item)
    {
        return;
    }

    int row = item->row();
    int id = ui->tableWidget->item(row,0)->text().toInt();

    QDateTime dt = ui->dateTimeEdit_modify->dateTime();
    ui->tableWidget->item(row, 1)->setText(dt.toString(DATETIME_FORMAT));

    float consistence = ui->doubleSpinBox_consistence_modify->value();
    ui->tableWidget->item(row, 2)->setText(QString::number(consistence));

    MEASUREMENT_MODE_TYPE mode = (MEASUREMENT_MODE_TYPE)ui->comboBox_mode_modify->currentIndex();
    ui->tableWidget->item(row, 6)->setText(getStr_MEASUREMENT_MODE_TYPE(mode));

    int sign = ui->spinBox_sign_modify->value();
    ui->tableWidget->item(row, 7)->setText(QString::number(sign));

    MeasurementData::getIns()->modifyMeasurement(id, dt, consistence, mode, sign);
}

void MeasurementWidget::slotDelete()
{
    QTableWidgetItem *item = ui->tableWidget->currentItem();
    if(!item)
    {
        return;
    }

    int row = item->row();
    int id = ui->tableWidget->item(row,0)->text().toInt();

    ui->tableWidget->removeRow(row);

    MeasurementData::getIns()->deleteMeasurement(id);
}

void MeasurementWidget::refreshUI(const QList<Measurement> ms)
{
    while(ui->tableWidget->rowCount()){
        ui->tableWidget->removeRow(0);
    }

    for(int i = 0; i < ms.count(); i++)
    {
        Measurement m = ms.at(i);
        ui->tableWidget->insertRow(i);
        QTableWidgetItem * item = new QTableWidgetItem(QString::number(m.id));
        ui->tableWidget->setItem(i, 0, item);
        item = new QTableWidgetItem(m.datetime.toString(DATETIME_FORMAT));
        ui->tableWidget->setItem(i,1,item);
        item = new QTableWidgetItem(QString::number(m.consistence));
        ui->tableWidget->setItem(i,2,item);
        item = new QTableWidgetItem(QString::number(m.range));
        ui->tableWidget->setItem(i,3,item);
        item = new QTableWidgetItem(QString::number(m.k));
        ui->tableWidget->setItem(i,4,item);
        item = new QTableWidgetItem(QString::number(m.b));
        ui->tableWidget->setItem(i,5,item);
        item = new QTableWidgetItem(getStr_MEASUREMENT_MODE_TYPE(m.mode));
        ui->tableWidget->setItem(i,6,item);
        item = new QTableWidgetItem(QString::number(m.sign));
        ui->tableWidget->setItem(i,7,item);
        item = new QTableWidgetItem(QString::number(m.absorbance));
        ui->tableWidget->setItem(i,8,item);
        item = new QTableWidgetItem(QString::number(m.voltage));
        ui->tableWidget->setItem(i,9,item);
        item = new QTableWidgetItem(QString::number(m.voltage_ref));
        ui->tableWidget->setItem(i,10,item);
    }
}
