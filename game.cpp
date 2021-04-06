#include "game.h"

Game::Game(QString name, QString producer, QString publisher)
{
    this->name = name;
    this->producer = producer;
    this->publisher = publisher;
    year = rand() % 30 + 1990;
}

bool Game::compare(QString name)
{
    if(this->name == name)
        return true;
    return false;
}
