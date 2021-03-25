#ifndef USERDATABASE_H
#define USERDATABASE_H

#include<QApplication>
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
    ///Deletes user from database
    void deleteUser(QString username);
private:
    QVector<User> userDatabase;
};

#endif // USERDATABASE_H
