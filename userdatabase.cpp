#include "userdatabase.h"

UserDatabase::UserDatabase()
{

}

void UserDatabase::readDatabase()
{

}

void UserDatabase::saveDatabase()
{
    QFile file;
    file.setFileName("userDB.txt");
    file.open(QIODevice::WriteOnly);
    if(file.exists())
    {
        QTextStream out(&file);
        for(auto x : userDatabase)
        {
            out << x.printUser();
        }
    }
}

void UserDatabase::addUser(QString username, QString password)
{
    for(auto x: userDatabase)
        if(x.compare(username))
        {
            //Pop-up window

        }
    User temp(username, password);
    this->userDatabase.push_back(temp);
}

void UserDatabase::deleteUser(QString username)
{

}
