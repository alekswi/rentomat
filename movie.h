#ifndef MOVIE_H
#define MOVIE_H

#include <QApplication>
#include <article.h>

class Movie: public Article
{
public:
    Movie();
    bool compare(QString name);
    bool compare(QString name, QString category, int releaseFrom, int releaseTo, int durationFrom, int durationTo);
    QString getProducer();
    QString getProductionCompany();
    int getDuration();
    void setID(int id);
    QString printMovie();
    void loadMovie(QString movieString);
protected:
    QString producer;
    QString productionCompany;
    int duration;
    static int nextID;
    friend class AddMovieDialog;
};

#endif // MOVIE_H
