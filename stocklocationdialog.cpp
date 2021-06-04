#include "stocklocationdialog.h"
#include "ui_stocklocationdialog.h"

StockLocationDialog::StockLocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockLocationDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());

    //connect(this,SIGNAL(sendLocation(QString)),parent,SLOT(getLocation(QString)));
    connect(this,SIGNAL(sendStock(Stock*)),parent,SLOT(getStock(Stock*)));
}

StockLocationDialog::~StockLocationDialog()
{
    delete ui;
}

void StockLocationDialog::getItem(QString name, QString typeIn)
{
    type = typeIn;
    setWindowTitle("New copy of " + name);
    ui->locationLabel->setText("Please enter location of " + name + ":");
}


void StockLocationDialog::on_addButton_clicked()
{
    Stock *newStock = new Stock(type, ui->locationBox->currentText());
    emit sendStock(newStock);
    this->close();
}


void StockLocationDialog::on_cancelButton_clicked()
{
    this->close();
}

