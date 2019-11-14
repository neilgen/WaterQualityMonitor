#ifndef EXAMINETESTWIDGET_H
#define EXAMINETESTWIDGET_H

#include <QWidget>

namespace Ui {
class ExamineTestWidget;
}

class ExamineTestWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ExamineTestWidget(QWidget *parent = 0);
    ~ExamineTestWidget();
    
private:
    Ui::ExamineTestWidget *ui;
};

#endif // EXAMINETESTWIDGET_H
