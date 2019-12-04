#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton_login, SIGNAL(clicked()),
            this, SLOT(slotLoginClicked()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::slotLoginClicked()
{
    QString name= ui->lineEdit_name->text();
    QString passwd = ui->lineEdit_passwd->text();

    QString msg = UserData::getIns()->login(name, passwd);
    if(!msg.isEmpty())
    {
        ui->label_msg->setText(msg);
    }
    else
    {
        this->accept();
    }
}
