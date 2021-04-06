#ifndef USER_H
#define USER_H

#include <QApplication>
#include <QFile>

class User
{
public:
    User(QString username, QString password);
    User();
    ///Compares usernames
    bool compareUsername(QString username);
    ///Compares passwords
    bool comparePassword(QString password);
    ///Sets/Updates username
    bool setUsername(QString username);
    ///Sets/Updates password
    bool setPassword(QString password);
    ///Returns username
    QString getUsername();
    ///Returns password
    QString getPassword();
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
};

#endif // USER_H
