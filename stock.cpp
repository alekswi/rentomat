#include "stock.h"
#include <book.h>
#include <game.h>
#include <movie.h>

Stock::Stock()
{
    borrowed = false;
}

Stock::Stock(QString type, QString locationIn)
{
    if(type==typeid(Book*).name())
    {
        id = ++nextBookID;
    }
    else if(type==typeid(Game*).name())
    {
        id = ++nextGameID;
    }
    else if(type==typeid(Movie*).name())
    {
        id = ++nextMovieID;
    }
    location = locationIn;
    borrowed = false;
    studentID = 0;
}

Stock::~Stock()
{

}

int Stock::nextBookID = 0;
int Stock::nextGameID = 0;
int Stock::nextMovieID = 0;

void Stock::borrow(int studentID)
{
    this->studentID = studentID;
    this->borrowed = true;
}

void Stock::returnStock()
{
    this->studentID = 0;
    this->borrowed = false;
}

QString Stock::getLocation()
{
    return location;
}

int Stock::getID()
{
    return id;
}

bool Stock::ifBorrowed()
{
    if(borrowed)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Stock::getStudentID()
{
    return studentID;
}

QString Stock::printStock()
{
    QString temp;
    temp = QString::number(id) + "," + QString::number(studentID) + "," + location;
    return temp;
}

void Stock::loadStock(QString stockString, int type)
{
    auto record = stockString.split(",");
    id = record.at(0).toInt();
    studentID = record.at(1).toInt();
    if(studentID!=0)
    {
        borrowed = true;
    }
    location = record.at(2);
    if(type == 0)
    {
        nextBookID = id;
    }
    else if(type == 1)
    {
        nextGameID = id;
    }
    if(type == 2)
    {
        nextMovieID = id;
    }
}
