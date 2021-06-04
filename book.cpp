#include "book.h"

Book::Book()
{
    id = ++nextID;
    name = "unknown";
    author = "unknown";
    category = "unknown";
    introduction = "Lorem ipsum";
    year = rand() % 220 + 1800;
    pages = rand() % 300 + 200;
}

Book::~Book()
{

}

int Book::nextID = 0;

bool Book::compare(QString name)
{
    if(this->name == name)
        return true;
    return false;
}

bool Book::compare(QString name, QString author, QString category, int releaseFrom, int releaseTo)
{
    if(name!="")
    {
        if(this->name != name)
        {
            return false;
        }
    }
    if(author!="")
    {
        if(this->author != author)
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

QString Book::getAuthor()
{
    return author;
}

int Book::getPages()
{
    return pages;
}

void Book::setID(int id)
{
    this->id = id;
    nextID = id;
}

QString Book::printBook()
{
    QString temp;
    temp =  "ID: " + QString::number(id) + "." +
            "\nName: " + name +
            "\nAuthor: " + author +
            "\nCategory: " + category +
            "\nIntroduction: " + introduction +
            "\nRelease: " + QString::number(year) +
            "\nPages: " + QString::number(pages) +
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

void Book::loadBook(QString bookString)
{
    QString temp;
    QTextStream stream(&bookString);
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
        else if(temp == "Author:")
        {
            stream.read(1);
            author = stream.readLine();
        }
        else if(temp == "Category:")
        {
            stream.read(1);
            category = stream.readLine();
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
        else if(temp == "Pages:")
        {
            stream >> pages;
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
                    temp->loadStock(record,0);
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
