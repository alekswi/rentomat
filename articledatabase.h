#ifndef ARTICLEDATABASE_H
#define ARTICLEDATABASE_H

#include <QApplication>
#include <QFile>
#include <book.h>
#include <game.h>
#include <movie.h>

class ArticleDatabase
{
public:
    ArticleDatabase();
    void readDatabase();
    void readBooksDB();
    void readGamesDB();
    void readMoviesDB();
    void saveDatabase();
    void saveBooksDB();
    void saveGamesDB();
    void saveMoviesDB();
    QVector <Book*> getBooksDB();
    QVector <Game*> getGamesDB();
    QVector <Movie*> getMoviesDB();
    QVector <int> getUnusedBooksId();
    QVector <int> *getUnusedGamesId();
    QVector <int> *getUnusedMoviesId();
    void addBook(Book *newBook);
    void addGame(Game *newGame);
    void addMovie(Movie *newMovie);
    void deleteBook(QString name);
    void deleteGame(QString name);
    void deleteMovie(QString name);
    Book* findBook(QString name);
    Game* findGame(QString name);
    Movie* findMovie(QString name);
    Book* findBook(int id);
    Game* findGame(int id);
    Movie* findMovie(int id);

private:
    QVector <Book*> books;
    QVector <int> unusedBooksID;
    QVector <Game*> games;
    QVector <int> unusedGamesID;
    QVector <Movie*> movies;
    QVector <int> unusedMoviesID;
};

#endif // ARTICLEDATABASE_H
