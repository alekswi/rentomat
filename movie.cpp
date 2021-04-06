#include "movie.h"

Movie::Movie(QString name, QString producer)
{
    this->name = name;
    this->producer = producer;
    year = rand() % 30 + 1990;
}

bool Movie::compare(QString name)
{
    if(this->name == name)
        return true;
    return false;
}
