#include "userdatabase.h"

UserDatabase::UserDatabase()
{

}

void UserDatabase::readDatabase()
{
    QFile file;
    file.setFileName("userDB.txt");
    file.open(QIODevice::ReadOnly);
    if(file.exists())
    {
        QTextStream stream(&file);
        QString fileString = stream.readAll();
        auto usersList = fileString.split("%\n");
        for(auto user: usersList)
        {
            if(user!="")
            {
                User temp;
                temp.loadUser(user);
                users.push_back(temp);
            }
        }
    }
}

void UserDatabase::saveDatabase()
{
    QFile file;
    file.setFileName("userDB.txt");
    file.open(QIODevice::WriteOnly);
    if(file.exists())
    {
        QTextStream out(&file);
        for(auto x : users)
        {
            out << x.printUser();
        }
    }
}

void UserDatabase::addUser(QString username, QString password)
{
    User temp(username, password);
    this->users.push_back(temp);
}

int UserDatabase::findUser(QString username)
{
    int i = 0;
    for(auto x:users)
    {
        if(x.compareUsername(username))
        {
            return i;
        }
        i++;
    }
    return -1;
}

User* UserDatabase::returnUser(QString username, QString password)
{
    int pos = findUser(username);
    if(pos!=-1)
    {
        if(users[pos].comparePassword(password))
        {
            return &users[pos];
        }
    }
    return nullptr;
}

void UserDatabase::deleteUser(QString username)
{
    int pos = findUser(username);
    users.removeAt(pos);
}
