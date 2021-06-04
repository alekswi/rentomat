#ifndef DELETESTOCKDIALOG_H
#define DELETESTOCKDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include "articledatabase.h"
#include "confirmationdeletedialog.h"

namespace Ui {
class DeleteStockDialog;
}

class DeleteStockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteStockDialog(QWidget *parent = nullptr);
    void printBooks();
    void printGames();
    void printMovies();
    ~DeleteStockDialog();

public slots:
    void getDatabase(ArticleDatabase *articleDB, int typeIn);

private slots:
    void on_cancelButton_clicked();

    void on_itemsTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

signals:
    void sendStock(QString name);

private:
    Ui::DeleteStockDialog *ui;
    int type;
    ArticleDatabase *articleDB;
    Book *currentBook;
    Game *currentGame;
    Movie *currentMovie;
    ConfirmationDeleteDialog *confirmationDeleteDialog;
};

#endif // DELETESTOCKDIALOG_H
