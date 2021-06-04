#include "confirmborrow.h"
#include "ui_confirmborrow.h"

ConfirmBorrow::ConfirmBorrow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmBorrow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());
}

ConfirmBorrow::~ConfirmBorrow()
{
    delete ui;
}

void ConfirmBorrow::getName(QString name)
{
    setWindowTitle("Borrow copy of the " + name + " ?");
}

void ConfirmBorrow::on_borrowButton_clicked()
{
    accept();
    this->close();
}


void ConfirmBorrow::on_cancelButton_clicked()
{
    reject();
    this->close();
}

