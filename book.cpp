#include "book.h"

Book::Book(QString name, QString author)
{
    id= ++nextID;
    this->name = name;
    this->author = author;
    year = rand() % 220 + 1800;
    pages = rand() % 500 + 100;
}

int Book::nextID = 0;

bool Book::compare(QString name)
{
    if(this->name == name)
        return true;
    return false;
}

QString Book::printBook()
{
    QString temp;
    temp =  "ID: " + QString::number(id) + "." +
            "\nName: " + name +
            "\nAuthor: " + author +
            "\nCategory: " + category +
            "\nIntroduction: " + introduction +
            "\nDate: " + QString::number(day) + "-" + QString::number(month) + "-" + QString::number(year) +
            "\nPages: " + QString::number(pages) +
            "\nStock:";
    for(auto x:stock)
    {
        temp += " " + x.printStock();
    }
    return temp;
}

void Book::addStock()
{
    QString temp = typeid(this).name();
    Stock x(temp);
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
            stream.read(1);
        }
        else if(temp == "Author:")
        {
            author = stream.readLine();
        }
        else if(temp == "Pages:")
        {
            stream >> pages;
        }
        else if(temp == "Name:")
        {
            name = stream.readLine();
        }
        else if(temp == "Category:")
        {
            category = stream.readLine();
        }
        else if(temp == "Introduction:")
        {
            introduction = stream.readLine();
        }
        else if(temp == "Stock:")
        {

        }
    }
}
