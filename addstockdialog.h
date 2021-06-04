#ifndef ADDSTOCKDIALOG_H
#define ADDSTOCKDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include "articledatabase.h"
#include "stocklocationdialog.h"

namespace Ui {
class AddStockDialog;
}

class AddStockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStockDialog(QWidget *parent = nullptr);
    ~AddStockDialog();

public slots:
    ///Receives database of articles and type of new article you want to add from connected class depending on clicked button in that class
    void getDatabase(ArticleDatabase *articleDB, int type);

    ///Receives new stock from connected class
    void getStock(Stock *newStock);

private slots:
    ///Action on cancel button clicked
    void on_cancelButton_clicked();

    ///Action on double clicked item in the tree widget
    void on_itemsTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

signals:
    ///Sends name and type of new stock to add to connected class
    void sendItem(QString name, QString type);

private:
    ArticleDatabase *articleDB;
    Game gameStock;
    Movie movieStock;
    QString currentItemName;
    int type;
    Ui::AddStockDialog *ui;
    StockLocationDialog *stockLocationDialog;
};

#endif // ADDSTOCKDIALOG_H
