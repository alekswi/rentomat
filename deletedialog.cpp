#include "deletedialog.h"
#include "ui_deletedialog.h"
#include <QMessageBox>

DeleteDialog::DeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    check = false;
}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}

void DeleteDialog::setUser(QString username, QString password)
{
    this->username = username;
    setWindowTitle("Delete " + username);
    this->password = password;
}

bool DeleteDialog::ifDeleted()
{
    return check;
}

void DeleteDialog::on_Delete_clicked()
{
    if(ui->passwordLabel->text()==password)
    {
        check = true;
        this->close();
    }
    else
    {
        QMessageBox::warning(this, "Delete","Password incorect");
    }
}

void DeleteDialog::on_Cancel_clicked()
{
    this->close();
}
