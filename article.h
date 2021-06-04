#ifndef ARTICLE_H
#define ARTICLE_H

#include <QApplication>
#include <stock.h>

class Article
{
public:
    Article();
    ~Article();
    ///Returns true if this
    bool compare(QString name);
    QString getName();
    QString getCategory();
    QString getIntroduction();
    int getID();
    int getYear();
    void addStock(Stock *newStock);
    void deleteStock(int idIn);
    void borrowStock(int stockID, int studentID);
    void returnStock(int stockID);
    Stock* findStock(int stockID);
    QString printBorrowed();
    QVector<Stock*> getStocksDB();
protected:
    QString name;
    QString category;
    QString introduction;
    int id;
    int year;
    QVector <Stock*> stocks;
};

#endif // ARTICLE_H
