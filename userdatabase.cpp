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
        auto stringsList = fileString.split("%\n");
        for(auto record : stringsList)
        {
            if(record.left(2)=="ID")
            {
                User *temp = new User;
                temp->loadUser(record);
                users.push_back(temp);
            }
            else if(record.left(12)=="Unused ids: ")
            {
                record = record.mid(12);
                auto idList = record.split(" ");
                for(auto id : idList)
                {
                    unusedID.push_back(id.toInt());
                }
            }
        }
    }
}

void UserDatabase::saveDatabase()
{
    std::sort(users.begin(), users.end(), [](User* left, User* right) {
        return left->getID() < right->getID();});
    QFile file;
    file.setFileName("userDB.txt");
    file.open(QIODevice::WriteOnly);
    if(file.exists())
    {
        QTextStream out(&file);
        for(auto user : users)
        {
            out << user->printUser();
        }
        out << "Unused ids:";
        for(auto id : unusedID)
        {
            out << " " << id;
        }
        out << "\n";
    }
}

void UserDatabase::addUser(QString username, QString password)
{
    if(unusedID.size()==0)
    {
        User *temp = new User(username, password);
        this->users.push_back(temp);
    }
    else
    {
        User *temp = new User(username, password, unusedID[0]);
        this->users.insert((unusedID.front()-1), temp);
        unusedID.erase(unusedID.begin());
    }
}

int UserDatabase::findUser(QString username)
{
    int i = 0;
    for(auto user:users)
    {
        if(user->compareUsername(username))
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
        if(users.at(pos)->comparePassword(password))
        {
            return users.at(pos);
        }
    }
    return nullptr;
}

void UserDatabase::deleteUser(QString username)
{
    int pos = findUser(username);
    if(pos < users.size())
    {
        unusedID.push_back(users.at(pos)->getID());
    }
    if(unusedID.size()>1)
    {
        std::sort(unusedID.begin(),unusedID.end());
    }
    users.removeAt(pos);
}
