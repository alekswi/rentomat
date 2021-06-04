#include "movie.h"

Movie::Movie()
{
    id= ++nextID;
    name = "unknown";
    producer = "unknown";
    productionCompany = "unknown";
    category = "unknown";
    introduction = "Lorem ipsum";
    year = rand() % 220 + 1800;
    duration = rand() % 120 + 60;
}

int Movie::nextID = 0;

bool Movie::compare(QString name)
{
    if(this->name == name)
        return true;
    return false;
}

bool Movie::compare(QString name, QString category, int releaseFrom, int releaseTo, int durationFrom, int durationTo)
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
    if(durationFrom < durationTo)
    {
        if(this->duration < durationFrom || this->duration > durationTo)
        {
            return false;
        }
    }
    return true;
}

QString Movie::getProducer()
{
    return producer;
}

QString Movie::getProductionCompany()
{
    return productionCompany;
}

int Movie::getDuration()
{
    return duration;
}

void Movie::setID(int id)
{
    this->id = id;
    nextID = id;
}

QString Movie::printMovie()
{
    QString temp;
    temp =  "ID: " + QString::number(id) + "." +
            "\nName: " + name +
            "\nCategory: " + category +
            "\nProducer: " + producer +
            "\nProduction_Company: " + productionCompany +
            "\nIntroduction: " + introduction +
            "\nDuration: " + QString::number(duration) +
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

void Movie::loadMovie(QString movieString)
{
    QString temp;
    QTextStream stream(&movieString);
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
        else if(temp == "Production_Company:")
        {
            stream.read(1);
            productionCompany = stream.readLine();
        }
        else if(temp == "Introduction:")
        {
            stream.read(1);
            introduction = stream.readLine();
        }
        else if(temp == "Duration:")
        {
            stream >> duration;
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
                    temp->loadStock(record,2);
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
