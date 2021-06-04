#ifndef STOCKLOCATIONDIALOG_H
#define STOCKLOCATIONDIALOG_H

#include <QDialog>
#include "stock.h"

namespace Ui {
class StockLocationDialog;
}

class StockLocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockLocationDialog(QWidget *parent = nullptr);
    ~StockLocationDialog();

public slots:
    void getItem(QString name, QString type);

private slots:
    void on_addButton_clicked();

    void on_cancelButton_clicked();

signals:
    void sendLocation(QString location);

    void sendStock(Stock *newStock);

private:
    Ui::StockLocationDialog *ui;
    QString type;
};

#endif // STOCKLOCATIONDIALOG_H
