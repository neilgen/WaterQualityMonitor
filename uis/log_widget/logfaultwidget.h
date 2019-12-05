#ifndef LOGFAULTWIDGET_H
#define LOGFAULTWIDGET_H

#include <QWidget>
#include "datas.h"

namespace Ui {
class LogFaultWidget;
}

class LogFaultWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LogFaultWidget(QWidget *parent = 0);
    ~LogFaultWidget();
    
public:
    void refresh();

private:
    void refreshUI(const QList<Log> logs);

private slots:
    void slotSearch();  //查询
    void slotExport();  //导出

private:
    Ui::LogFaultWidget *ui;
};

#endif // LOGFAULTWIDGET_H
