#include "confirmationdeletedialog.h"
#include "ui_confirmationdeletedialog.h"

ConfirmationDeleteDialog::ConfirmationDeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmationDeleteDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());
}

ConfirmationDeleteDialog::~ConfirmationDeleteDialog()
{
    delete ui;
}

void ConfirmationDeleteDialog::getItem(QString name)
{
    setWindowTitle("Confirm " + name + " deletion");
}

void ConfirmationDeleteDialog::on_deleteButton_clicked()
{
    accept();
    this->close();
}


void ConfirmationDeleteDialog::on_cancelButton_clicked()
{
    reject();
    this->close();
}

