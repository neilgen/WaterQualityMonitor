#ifndef PROCESSSETWIDGET_H
#define PROCESSSETWIDGET_H

#include <QWidget>

#include "datas.h"

namespace Ui {
class ProcessSetWidget;
}

class ProcessSetWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ProcessSetWidget(QWidget *parent = 0);
    ~ProcessSetWidget();
    
private:
    Ui::ProcessSetWidget *ui;
};

#endif // PROCESSSETWIDGET_H
