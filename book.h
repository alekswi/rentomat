#ifndef BOOK_H
#define BOOK_H

#include <QApplication>
#include "article.h"

class Book: public Article
{
public:
    Book();
    ~Book();
    bool compare(QString name);
    bool compare(QString name, QString author, QString category, int releaseFrom, int releaseTo);
    QString getAuthor();
    int getPages();
    void setID(int id);
    QString printBook();
    void loadBook(QString gameString);
protected:
    QString author;
    static int nextID;
    int pages;
    friend class AddBookDialog;
};

#endif // BOOK_H
