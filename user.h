#ifndef USER_H
#define USER_H

#include <QApplication>
#include "watched.h"

class User
{
public:
    User(QString username, QString password);
    User(QString username, QString password, int id);
    User();
    ///Compares usernames
    bool compareUsername(QString username);
    ///Compares passwords
    bool comparePassword(QString password);
    ///Sets/Updates username
    void setUsername(QString username);
    ///Sets/Updates password
    void setPassword(QString password);
    ///Sets book stock as borrowed and who borrowed it
    void borrowBook(int bookID, int stockID);
    ///Sets book stock as borrowed and who borrowed it
    void borrowGame(int bookID, int stockID);
    ///Sets movie stock as borrowed and who borrowed it
    void borrowMovie(int bookID, int stockID);
    void returnBook(int bookID, int stockID);
    void returnGame(int bookID, int stockID);
    void returnMovie(int bookID, int stockID);
    QVector<QPair<int,int>> getBorrowedBooksID();
    QVector<QPair<int,int>> getBorrowedGamesID();
    QVector<QPair<int,int>> getBorrowedMoviesID();
    bool addWatchedItem(Watched *watchedItem);
    void deleteWatchedItem(QString type, QString name, QString location);
    QVector<Watched*> getWatchedItems();
    ///Returns username
    QString getUsername();
    ///Returns password
    QString getPassword();
    ///Returns ID
    int getID();
    ///Checks if user is admin
    bool isAdmin();
    ///Prints informations od User to stream
    QString printUser();
    ///Read user from stream
    void loadUser(QString userString);
protected:
    QString username;
    QString password;
    static int nextID;
    int id;
    bool admin;
    QVector<std::pair<int,int>> borrowedBooksID;
    QVector<std::pair<int,int>> borrowedGamesID;
    QVector<std::pair<int,int>> borrowedMoviesID;
    QVector<Watched*> watchedItems;
};

#endif // USER_H
