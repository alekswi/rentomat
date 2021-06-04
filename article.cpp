#include "article.h"

Article::Article()
{
    year = rand() % 11 + 1;
}

Article::~Article()
{

}

QString Article::getName()
{
    return name;
}

QString Article::getCategory()
{
    return category;
}

QString Article::getIntroduction()
{
    return introduction;
}

int Article::getID()
{
    return id;
}

int Article::getYear()
{
    return year;
}

void Article::addStock(Stock *stock)
{
    stocks.push_back(stock);
}

void Article::deleteStock(int idIn)
{
    int temp = 0;
    for(Stock *stock : stocks)
    {
        if(stock->getID()==idIn)
        {
            break;
        }
        temp++;
    }
    stocks.removeAt(temp);
}

void Article::borrowStock(int stockID, int studentID)
{
    for(auto stock : stocks)
    {
        if(stock->getID()==stockID)
        {
            stock->borrow(studentID);
//            QPair <int,int> temp(stockID,studentID);
//            borrowed.push_back(temp);
        }
    }
}

void Article::returnStock(int stockID)
{
    for(auto stock : stocks)
    {
        if(stock->getID()==stockID)
        {
            stock->returnStock();
        }
    }
//    int i = 0;
//    for(auto temp : borrowed)
//    {
//        if(temp.first==stockID)
//        {
//            borrowed.removeAt(i);
//        }
//        i++;
//    }
}

Stock* Article::findStock(int stockID)
{
    Stock *temp = stocks.front();
    for(auto stock : stocks)
    {
        if(stock->getID()==stockID)
        {
            temp = stock;
            break;
        }
    }
    return temp;
}

//QString Article::printBorrowed()
//{
//    QString temp = "Borrowed:";
//    for(auto borrowedRecord : borrowed)
//    {
//    temp += " " + QString::number(borrowedRecord.first) + "," + QString::number(borrowedRecord.second);
//    }
//    return temp;
//}

QVector<Stock*> Article::getStocksDB()
{
    return stocks;
}
