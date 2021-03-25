#include "book.h"

Book::Book(QString name, QString author)
{
    this->name = name;
    this->author = author;
}

bool Book::compare(QString name)
{
    if(this->name == name)
        return true;
    return false;
}
