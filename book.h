#ifndef BOOK_H
#define BOOK_H

#include <QApplication>
#include <article.h>

class Book: public Article
{
public:
    Book(QString name, QString author);
    bool compare(QString name);
protected:
    QString author;
    int pages;
};

#endif // BOOK_H
