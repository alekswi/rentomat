#ifndef USER_H
#define USER_H

#include <QApplication>
#include <QFile>

class User
{
public:
    User(QString x, QString y);
    ///Compares usernames
    bool compare(QString username);
    ///Sets/Updates username
    bool setUsername(QString username);
    ///Sets/Updates password
    bool setPassword(QString password);
    ///Prints informations od User to stream
    QString printUser();
    ///Read user from file
    void readUser(QFile file);
protected:
    QString username;
    QString password;
    int id;
    bool admin;
    QVector<std::pair<int,int>> borrowedBooksID;
    QVector<std::pair<int,int>> borrowedGamesID;
    QVector<std::pair<int,int>> borrowedMoviesID;
};

#endif // USER_H
