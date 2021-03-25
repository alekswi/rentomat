#include "user.h"

User::User(QString x, QString y):username(x),password(y)
{
    id = 0;
    admin = false;
}

bool User::compare(QString username)
{
    if(this->username == username)
        return true;
    else
        return false;
}

QString User::printUser()
{
    QString temp;
    temp = QString::number(id) + ". " + QString::number(admin) + " " + username + " " + password + "\n";
    for(auto x : borrowedBooksID)
    {
        temp += QString::number(x.first) + "." + QString::number(x.second) + ", ";
    }
    temp += "\n";
    for(auto x : borrowedGamesID)
    {
        temp += QString::number(x.first) + "." + QString::number(x.second) + ", ";
    }
    temp += "\n";
    for(auto x : borrowedMoviesID)
    {
        temp += QString::number(x.first) + "." + QString::number(x.second) + ", ";
    }
    temp += "\n%";
    return temp;
}

void User::readUser(QFile file)
{
    QString temp;

}



