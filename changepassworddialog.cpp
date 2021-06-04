#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePasswordDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());
    setWindowTitle("Change password");
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;

}

void ChangePasswordDialog::reset()
{
    ui->passwordLabel->setText("");
    ui->newPasswordLabel->setText("");
    ui->repeatNewPasswordLabel->setText("");
}

void ChangePasswordDialog::getUser(User *user)
{
    this->user = user;
}

void ChangePasswordDialog::on_Confirm_clicked()
{
    if(user->comparePassword(ui->passwordLabel->text()))
    {
        if(ui->newPasswordLabel->text().size() < 8)
        {
            QMessageBox::warning(this, "Warning", "Please enter password with at least 8 characters");
        }
        else if(ui->newPasswordLabel->text()==ui->repeatNewPasswordLabel->text())
        {
            user->setPassword(ui->newPasswordLabel->text());
            QMessageBox::about(this, "Done", "Password changed");
            reset();
            this->close();
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Passwords don't match");
        }
    }
}


void ChangePasswordDialog::on_Cancel_clicked()
{
    reset();
    this->close();
}

