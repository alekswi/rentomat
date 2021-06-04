#include "confirmwatch.h"
#include "ui_confirmwatch.h"

ConfirmWatch::ConfirmWatch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmWatch)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());
}

ConfirmWatch::~ConfirmWatch()
{
    delete ui;
}

void ConfirmWatch::getInfo(QString name, QString location)
{
    setWindowTitle("Watch " + name + " at " + location +"?");
}

void ConfirmWatch::on_watchButton_clicked()
{
    accept();
    this->close();
}


void ConfirmWatch::on_cancelButton_clicked()
{
    reject();
    this->close();
}
