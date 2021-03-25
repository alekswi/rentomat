#ifndef MOVIE_H
#define MOVIE_H

#include <QApplication>
#include <article.h>

class Movie: public Article
{
public:
    Movie(QString name, QString producer);
    bool compare(QString name);
protected:
    QString producer;
    QString director;
    QString productionCompany;
    int duration;
    double budget;
};

#endif // MOVIE_H
