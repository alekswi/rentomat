#include "user.h"

User::User(QString username, QString password):username(username),password(password)
{
    id = ++nextID;
    admin = false;
}

User::User(QString username, QString password, int id):username(username),password(password)
{
    this->id = id;
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

void User::setUsername(QString username)
{
    this->username = username;
}

void User::setPassword(QString password)
{
    this->password = password;
}

void User::borrowBook(int bookID, int stockID)
{
    QPair <int,int> temp(bookID,stockID);
    borrowedBooksID.push_back(temp);
}

void User::borrowGame(int bookID, int stockID)
{
    QPair <int,int> temp(bookID,stockID);
    borrowedGamesID.push_back(temp);
}

void User::borrowMovie(int bookID, int stockID)
{
    QPair <int,int> temp(bookID,stockID);
    borrowedMoviesID.push_back(temp);
}

void User::returnBook(int bookID, int stockID)
{
    int pos = 0;
    for(auto temp : borrowedBooksID)
    {
        if(temp.first == bookID && temp.second == stockID)
        {
            break;
        }
        pos++;
    }
    borrowedBooksID.removeAt(pos);
}

void User::returnGame(int bookID, int stockID)
{
    int pos = 0;
    for(auto temp : borrowedGamesID)
    {
        if(temp.first == bookID && temp.second == stockID)
        {
            break;
        }
        pos++;
    }
    borrowedGamesID.removeAt(pos);
}

void User::returnMovie(int bookID, int stockID)
{
    int pos = 0;
    for(auto temp : borrowedMoviesID)
    {
        if(temp.first == bookID && temp.second == stockID)
        {
            break;
        }
        pos++;
    }
    borrowedMoviesID.removeAt(pos);
}

QVector<QPair<int,int>> User::getBorrowedBooksID()
{
    return borrowedBooksID;
}

QVector<QPair<int,int>> User::getBorrowedGamesID()
{
    return borrowedGamesID;
}

QVector<QPair<int,int>> User::getBorrowedMoviesID()
{
    return borrowedMoviesID;
}

bool User::addWatchedItem(Watched *watchedItem)
{
    for(auto temp : watchedItems)
    {
        if(temp->compare(watchedItem))
        {
            return false;
        }
    }
    watchedItems.push_back(watchedItem);
    return true;
}

void User::deleteWatchedItem(QString type, QString name, QString location)
{
    int pos = 0;
    for(auto temp : watchedItems)
    {
        if(temp->getType()==type && temp->getName()==name && temp->getLocation()==location)
        {
            watchedItems.removeAt(pos);
            break;
        }
        pos++;
    }
}

QVector<Watched*> User::getWatchedItems()
{
    return watchedItems;
}

QString User::getUsername()
{
    return username;
}

QString User::getPassword()
{
    return password;
}

int User::getID()
{
    return id;
}

bool User::isAdmin()
{
    return admin;
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
        temp += "\nBooks:";
        for(auto x : borrowedBooksID)
        {
            temp += " " + QString::number(x.first) + "," + QString::number(x.second);
        }
    }
    if(borrowedGamesID.size()>0)
    {
        temp += "\nGames:";
        for(auto x : borrowedGamesID)
        {
            temp += " " + QString::number(x.first) + "," + QString::number(x.second);
        }
    }
    if(borrowedMoviesID.size()>0)
    {
        temp += "\nMovies:";
        for(auto x : borrowedMoviesID)
        {
            temp += " " + QString::number(x.first) + "," + QString::number(x.second);
        }
    }
    if(watchedItems.size()>0)
    {
        temp += "\nWatched: ";
        for(auto x : watchedItems)
        {
            temp += x->getType() + "," + x->getName() + "," + x->getLocation() + "|";
        }
    }
    if(temp.at(temp.size()-1)<'0' || temp.at(temp.size()-1)>'9')
    {
        temp.chop(1);
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
            stream.read(1);
            auto borrowedString = stream.readLine().split(" ");
            if(borrowedString.front()!="")
            {
                for(auto record : borrowedString)
                {
                    auto part = record.split(",");
                    QPair <int,int> temp(part.at(0).toInt(), part.at(1).toInt());
                    borrowedBooksID.push_back(temp);
                }
            }
        }
        else if(temp == "Games:")
        {
            stream.read(1);
            auto borrowedString = stream.readLine().split(" ");
            if(borrowedString.front()!="")
            {
                for(auto record : borrowedString)
                {
                    auto part = record.split(",");
                    QPair <int,int> temp(part.at(0).toInt(), part.at(1).toInt());
                    borrowedGamesID.push_back(temp);
                }
            }
        }
        else if(temp == "Movies:")
        {
            stream.read(1);
            auto borrowedString = stream.readLine().split(" ");
            if(borrowedString.front()!="")
            {
                for(auto record : borrowedString)
                {
                    auto part = record.split(",");
                    QPair <int,int> temp(part.at(0).toInt(), part.at(1).toInt());
                    borrowedMoviesID.push_back(temp);
                }
            }
        }
        else if(temp == "Watched:")
        {
            stream.read(1);
            auto borrowedString = stream.readLine().split("|");
            if(borrowedString.front()!="")
            {
                for(auto record : borrowedString)
                {
                    auto part = record.split(",");
                    Watched *temp = new Watched(part.at(0),part.at(1),part.at(2));
                    watchedItems.push_back(temp);
                }
            }
        }
        stream >> temp;
    }
}



