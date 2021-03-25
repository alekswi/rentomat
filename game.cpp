#include "game.h"

Game::Game(QString name, QString producer, QString publisher)
{
    this->name = name;
    this->producer = producer;
    this->publisher = publisher;
}

bool Game::compare(QString name)
{
    if(this->name == name)
        return true;
    return false;
}
