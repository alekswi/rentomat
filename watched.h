#ifndef WATCHED_H
#define WATCHED_H

#include <QApplication>

class Watched
{
public:
    Watched(QString type, QString name, QString location);
    bool compare(Watched *watchedItem);
    QString getType();
    QString getName();
    QString getLocation();

private:
    QString type;
    QString name;
    QString location;
};

#endif // WATCHED_H
