#ifndef DELETEITEMDIALOG_H
#define DELETEITEMDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include "articledatabase.h"
#include "confirmationdeletedialog.h"

namespace Ui {
class DeleteItemDialog;
}

class DeleteItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteItemDialog(QWidget *parent = nullptr);
    void printBooks();
    void printGames();
    void printMovies();
    ~DeleteItemDialog();

public slots:
    void getDatabase(ArticleDatabase *articleDB, int typeIn);

private slots:
    void on_cancelButton_clicked();

    void on_itemsTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

signals:
    void sendItem(QString name);

private:
    Ui::DeleteItemDialog *ui;
    int type;
    ArticleDatabase *articleDB;
    Book *currentBook;
    Game *currentGame;
    Movie *currentMovie;
    ConfirmationDeleteDialog *confirmationDeleteDialog;
};

#endif // DELETEITEMDIALOG_H
