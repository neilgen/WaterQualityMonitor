#ifndef SERVERINFOWIDGET_H
#define SERVERINFOWIDGET_H

#include <QWidget>

namespace Ui {
class ServerInfoWidget;
}

class ServerInfoWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ServerInfoWidget(QWidget *parent = 0);
    ~ServerInfoWidget();
    
private:
    Ui::ServerInfoWidget *ui;
};

#endif // SERVERINFOWIDGET_H
