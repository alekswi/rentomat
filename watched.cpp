#include "watched.h"

Watched::Watched(QString type, QString name, QString location)
{
    this->type = type;
    this->name = name;
    this->location = location;
}

bool Watched::compare(Watched *watchedItem)
{
    if(this->getType()==watchedItem->getType() && this->getName()==watchedItem->getName() && this->getLocation()==watchedItem->getLocation())
    {
        return true;
    }
    return false;
}

QString Watched::getType()
{
    return type;
}

QString Watched::getName()
{
    return name;
}

QString Watched::getLocation()
{
    return location;
}
