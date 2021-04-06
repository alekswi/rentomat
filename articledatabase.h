#ifndef ARTICLEDATABASE_H
#define ARTICLEDATABASE_H

#include <QApplication>
#include <book.h>
#include <game.h>
#include <movie.h>

class ArticleDatabase
{
public:
    ArticleDatabase();

signals:
    void ta();

private:
    QVector <Book> books;
    QVector <Game> games;
    QVector <Movie> movies;
};

#endif // ARTICLEDATABASE_H
