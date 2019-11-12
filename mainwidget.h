#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = NULL);
    ~MainWidget();
public slots:
    void onPopMenu();
    void onOtherActionTriggered();
    void onLogActionTriggered();
    void onGuardActionTriggered();
    void onInstrumentActionTriggered();
    void onReviewActionTriggered();
    void onFlowActionTriggered();
    void onCurveActionTriggered();
    void onVarActionTriggered();

protected:
    void resizeEvent(QResizeEvent * event);
private:
    Ui::MainWidget *ui;

    void initConnect();
};
#endif // MAINWIDGET_H
