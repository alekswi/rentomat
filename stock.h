#ifndef STOCK_H
#define STOCK_H

#include <QApplication>

class Stock
{
public:
    //template<typename type> Stock(type *x);
    Stock(QString type);
    void borrow(int studentID);
    QString printStock();
    void loadStock(QString stockString);
private:
    static int nextBookID;
    static int nextGameID;
    static int nextMovieID;
    int id;
    bool borrowed;
    int studentID;
};

#endif // STOCK_H
