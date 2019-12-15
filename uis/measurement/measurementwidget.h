#ifndef MEASUREMENTWIDGET_H
#define MEASUREMENTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "datas.h"

namespace Ui {
class MeasurementWidget;
}

class MeasurementWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MeasurementWidget(QWidget *parent = 0);
    ~MeasurementWidget();

    void refresh();

private slots:
    void slotHome();
    void slotUserChanged();
    void slotSearch();
    void slotCurve();
    void slotExport();
    void slotPrintAll();
    void slotPrintSelected();

    void slotTableCurSelectedChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
    void slotModify();
    void slotDelete();

private:
    void refreshUI(const QList<Measurement> ms);

private:
    Ui::MeasurementWidget *ui;
};

#endif // MEASUREMENTWIDGET_H
