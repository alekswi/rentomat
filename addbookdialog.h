#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include "book.h"

namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent = nullptr);
    ~AddBookDialog();

signals:
    ///Sends new book to application
    void sendBook(Book *newBook);

public slots:
    void getUnusedBooksID(QVector<int> unusedBooksID);

private slots:
    void on_addBook_clicked();

    void on_cancelAction_clicked();

private:
    Ui::AddBookDialog *ui;
    QVector<int> unusedBooksID;
};

#endif // ADDBOOKDIALOG_H
