#ifndef USERDATABASE_H
#define USERDATABASE_H

#include<QApplication>
#include<QFile>
#include<user.h>

class UserDatabase
{
public:
    UserDatabase();
    ///Reads user database from file
    void readDatabase();
    ///Saves user database to file
    void saveDatabase();
    ///Adds user to database
    void addUser(QString username, QString password);
    ///Returns pos of user with given username, if it doesn't exist returns -1
    int findUser(QString username);
    ///Returns true if logged
    User *returnUser(QString username, QString password);
    ///Deletes user from database
    void deleteUser(QString username);
private:
    QVector<User*> users;
    QVector<int> unusedID;
};

#endif // USERDATABASE_H
