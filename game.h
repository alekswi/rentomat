#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <article.h>

class Game: public Article
{
public:
    Game();
    bool compare(QString name);
    bool compare(QString name, QString category, int releaseFrom, int releaseTo);
    QString getProducer();
    QString getPublisher();
    void setID(int id);
    QString printGame();
    void loadGame(QString gameString);
protected:
    QString producer;
    QString publisher;
    static int nextID;
    friend class AddGameDialog;
};

#endif // GAME_H
