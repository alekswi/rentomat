#include "changeusernamedialog.h"
#include "ui_changeusernamedialog.h"

ChangeUsernameDialog::ChangeUsernameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeUsernameDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());
    setWindowTitle("Change username");
}

ChangeUsernameDialog::~ChangeUsernameDialog()
{
    delete ui;
}

void ChangeUsernameDialog::reset()
{
    ui->passwordLabel->setText("");
    ui->usernameLabel->setText("");
}

void ChangeUsernameDialog::getInfo(User *user, UserDatabase userDB)
{
    this->user = user;
    this->userDB = userDB;
}

void ChangeUsernameDialog::on_Confirm_clicked()
{
    if(user->comparePassword(ui->passwordLabel->text()))
    {
        if(userDB.findUser(ui->usernameLabel->text())==-1)
        {
            user->setUsername(ui->usernameLabel->text());
            QMessageBox::about(this, "Done", "Username changed");
            reset();
            accept();
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Username already taken");
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Incorrect password");
    }
}


void ChangeUsernameDialog::on_Cancel_clicked()
{
    reset();
    reject();
}

