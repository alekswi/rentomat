#include "deleteuserdialog.h"
#include "ui_deleteuserdialog.h"
#include <QMessageBox>

DeleteUserDialog::DeleteUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteUserDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());
    check = false;
}

DeleteUserDialog::~DeleteUserDialog()
{
    delete ui;
}

void DeleteUserDialog::setUser(QString username, QString password)
{
    this->username = username;
    setWindowTitle("Delete " + username);
    this->password = password;
}

bool DeleteUserDialog::ifDeleted()
{
    return check;
}

void DeleteUserDialog::on_Delete_clicked()
{
    if(ui->passwordLabel->text()==password)
    {
        check = true;
        ui->passwordLabel->setText("");
        this->close();
    }
    else
    {
        QMessageBox::warning(this, "Delete","Password incorect");
    }
}

void DeleteUserDialog::on_Cancel_clicked()
{
    this->close();
}
