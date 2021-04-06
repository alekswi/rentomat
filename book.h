#ifndef BOOK_H
#define BOOK_H

#include <QApplication>
#include <article.h>

class Book: public Article
{
public:
    Book(QString name, QString author);
    bool compare(QString name);
    QString printBook();
    void addStock();
    void loadBook(QString userString);
protected:
    QString author;
    static int nextID;
    int pages;
};

#endif // BOOK_H
