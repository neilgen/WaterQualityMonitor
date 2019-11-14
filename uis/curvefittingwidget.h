#ifndef CURVEFITTINGWIDGET_H
#define CURVEFITTINGWIDGET_H

#include <QWidget>

namespace Ui {
class CurveFittingWidget;
}

class CurveFittingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CurveFittingWidget(QWidget *parent = 0);
    ~CurveFittingWidget();
    
private:
    Ui::CurveFittingWidget *ui;
};

#endif // CURVEFITTINGWIDGET_H
