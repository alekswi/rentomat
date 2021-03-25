#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <article.h>

class Game: public Article
{
public:
    Game(QString name, QString producer, QString publisher);
    bool compare(QString name);
protected:
    QString producer;
    QString publisher;
};

#endif // GAME_H
