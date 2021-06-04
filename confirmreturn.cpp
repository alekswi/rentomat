#include "confirmreturn.h"
#include "ui_confirmreturn.h"

ConfirmReturn::ConfirmReturn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmReturn)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());
}

ConfirmReturn::~ConfirmReturn()
{
    delete ui;
}

void ConfirmReturn::getName(QString name)
{
    setWindowTitle("Return " + name + "?");
}

void ConfirmReturn::on_borrowButton_clicked()
{
    accept();
    this->close();
}


void ConfirmReturn::on_cancelButton_clicked()
{
    reject();
    this->close();
}

