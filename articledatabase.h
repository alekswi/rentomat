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
private:
    QVector <Book> booksDatabase;
    QVector <Game> gamesDatabase;
    QVector <Movie> moviesDatabase;
};

#endif // ARTICLEDATABASE_H
