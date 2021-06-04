#include "game.h"

Game::Game()
{
    id= ++nextID;
    name = "unknown";
    producer = "unknown";
    publisher = "unknown";
    category = "unknown";
    introduction = "Lorem ipsum";
    year = rand() % 220 + 1800;
}

int Game::nextID = 0;

bool Game::compare(QString name)
{
    if(this->name == name)
        return true;
    return false;
}

bool Game::compare(QString name, QString category, int releaseFrom, int releaseTo)
{
    if(name!="")
    {
        if(this->name != name)
        {
            return false;
        }
    }
    if(category!="")
    {
        if(this->category != category)
        {
            return false;
        }
    }
    if(releaseFrom < releaseTo)
    {
        if(this->year < releaseFrom || this->year > releaseTo)
        {
            return false;
        }
    }
    return true;
}

QString Game::getProducer()
{
    return producer;
}

QString Game::getPublisher()
{
    return publisher;
}

void Game::setID(int id)
{
    this->id = id;
    nextID = id;
}

QString Game::printGame()
{
    QString temp;
    temp =  "ID: " + QString::number(id) + "." +
            "\nName: " + name +
            "\nCategory: " + category +
            "\nProducer: " + producer +
            "\nPublisher: " + publisher +
            "\nIntroduction: " + introduction +
            "\nRelease: " + QString::number(year) +
            "\nStock: ";
    for(auto stock : stocks)
    {
        temp += stock->printStock() + "|";
    }
    temp.chop(1);
//    temp += "\n";
//    temp += printBorrowed();
    temp += "\n%\n";
    return temp;
}

void Game::loadGame(QString gameString)
{
    QString temp;
    QTextStream stream(&gameString);
    stream >> temp;
    while(temp != '%' && !stream.atEnd())
    {
        if(temp == "ID:")
        {
            stream >> id;
            nextID = id;
            stream.read(1);
        }
        else if(temp == "Name:")
        {
            stream.read(1);
            name = stream.readLine();
        }
        else if(temp == "Category:")
        {
            stream.read(1);
            category = stream.readLine();
        }
        else if(temp == "Producer:")
        {
            stream.read(1);
            producer = stream.readLine();
        }
        else if(temp == "Publisher:")
        {
            stream.read(1);
            publisher = stream.readLine();
        }
        else if(temp == "Introduction:")
        {
            stream.read(1);
            introduction = stream.readLine();
        }
        else if(temp == "Release:")
        {
            stream >> year;
        }
        else if(temp == "Stock:")
        {
            stream.read(1);
            auto stocksString = stream.readLine().split("|");
            if(stocksString.front()!="")
            {
                for(auto record : stocksString)
                {
                    Stock *temp = new Stock;
                    temp->loadStock(record,1);
                    stocks.push_back(temp);
                }
            }
        }
//        else if(temp == "Borrowed")
//        {
//            stream.read(1);
//            auto borrowedString = stream.readLine().split(" ");
//            if(borrowedString.front()!="")
//            {
//                for(auto record : borrowedString)
//                {
//                    auto part = record.split(",");
//                    QPair <int,int> temp(part.at(0).toInt(), part.at(1).toInt());
//                    borrowed.push_back(temp);
//                }
//            }
//        }
        stream >> temp;
    }
}
