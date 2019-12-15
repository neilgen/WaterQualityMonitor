#ifndef LOGACTORWIDGET_H
#define LOGACTORWIDGET_H

#include <QWidget>
#include "datas.h"

namespace Ui {
class LogActorWidget;
}

class LogActorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LogActorWidget(QWidget *parent = 0);
    ~LogActorWidget();

public:
    void refresh();
    
private:
    void refreshUI(const QList<Log> logs);

private slots:
    void slotSearch();  //查询
    void slotExport();  //导出

private:
    Ui::LogActorWidget *ui;
};

#endif // LOGACTORWIDGET_H
