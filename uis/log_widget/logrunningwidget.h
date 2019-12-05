#ifndef LOGRUNNINGWIDGET_H
#define LOGRUNNINGWIDGET_H

#include <QWidget>
#include "datas.h"

namespace Ui {
class LogRunningWidget;
}

class LogRunningWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LogRunningWidget(QWidget *parent = 0);
    ~LogRunningWidget();
    
public:
    void refresh();

private:
    void refreshUI(const QList<Log> logs);

private slots:
    void slotSearch();  //查询
    void slotExport();  //导出

private:
    Ui::LogRunningWidget *ui;
};

#endif // LOGRUNNINGWIDGET_H
