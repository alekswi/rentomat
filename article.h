#ifndef ARTICLE_H
#define ARTICLE_H

#include <QApplication>
#include <stock.h>

class Article : public QObject
{
public:
    Article();
    virtual bool compare(QString name) = 0;
protected:
    QString name;
    QString category;
    QString introduction;
    int id;
    int year;
    int month;
    int day;
    QVector<Stock> stock;
};

#endif // ARTICLE_H
