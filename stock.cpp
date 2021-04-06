#include "stock.h"
#include <book.h>
#include <game.h>
#include <movie.h>

Stock::Stock(QString x)
{
    if(x==typeid(Book*).name())
    {
        id = ++nextBookID;
    }
    else if(x==typeid(Game*).name())
    {
        id = ++nextGameID;
    }
    else if(x==typeid(Movie*).name())
    {
        id = ++nextMovieID;
    }
    borrowed = false;
    studentID = 0;
}

int Stock::nextBookID = 0;
int Stock::nextGameID = 0;
int Stock::nextMovieID = 0;

QString Stock::printStock()
{
    QString temp;
    temp = QString::number(id) + "-" + QString::number(studentID);
    return temp;
}

void Stock::loadStock(QString stockString)
{

}
