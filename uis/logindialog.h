#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "datas.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    
private slots:
    void slotLoginClicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
