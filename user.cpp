#include "user.h"

User::User(QString username, QString password):username(username),password(password)
{
    id = ++nextID;
    admin = false;
}

User::User()
{
    id = ++nextID;
    admin = false;
}

int User::nextID = 0;

bool User::compareUsername(QString username)
{
    if(this->username == username)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool User::comparePassword(QString password)
{
    if(this->password == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString User::getUsername()
{
    return username;
}

QString User::getPassword()
{
    return password;
}

QString User::printUser()
{
    QString temp;
    temp =  "ID: " + QString::number(id) + "." +
            "\nUsername: " + username +
            "\nPassword: " + password +
            "\nAdmin: " + QString::number(admin);
    if(borrowedBooksID.size()>0)
    {
        temp += "\nBooks: ";
        for(auto x : borrowedBooksID)
        {
            temp += QString::number(x.first) + "." + QString::number(x.second) + ", ";
        }
    }
    if(borrowedGamesID.size()>0)
    {
        temp += "\nGames: ";
        for(auto x : borrowedGamesID)
        {
            temp += QString::number(x.first) + "." + QString::number(x.second) + ", ";
        }
    }
    if(borrowedMoviesID.size()>0)
    {
        temp += "\nMovies: ";
        for(auto x : borrowedMoviesID)
        {
            temp += QString::number(x.first) + "." + QString::number(x.second) + ", ";
        }
    }
    temp += "\n%\n";
    return temp;
}

void User::loadUser(QString userString)
{
    QString temp;
    QTextStream stream(&userString);
    stream >> temp;
    while(temp != '%' && !stream.atEnd())
    {
        if(temp == "ID:")
        {
            stream >> id;
            nextID = id;
            stream.read(1);
        }
        else if(temp == "Admin:")
        {
            stream >> temp;
            if(temp == '1')
            {
                admin = true;
            }
        }
        else if(temp == "Username:")
        {
            stream >> username;
        }
        else if(temp == "Password:")
        {
            stream >> password;
        }
        else if(temp == "Books:")
        {
            stream >> temp;
            while(temp != '\n')
            {

            }
        }
        else if(temp == "Games:")
        {

        }
        else if(temp == "Movies:")
        {

        }
        stream >> temp;
    }
}



