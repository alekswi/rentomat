#ifndef STOCK_H
#define STOCK_H

#include <QApplication>

class Stock
{
public:
    Stock();
    Stock(QString type, QString locationIn);
    ~Stock();
    ///Sets stock to borrowed and which student borrowed it
    void borrow(int studentID);
    void returnStock();
    QString getLocation();
    int getID();
    bool ifBorrowed();
    int getStudentID();
    ///Prints information about stock
    QString printStock();
    ///Loads information about stock
    void loadStock(QString stockString, int type);
private:
    QString location;
    int id;
    bool borrowed;
    int studentID;
    static int nextBookID;
    static int nextGameID;
    static int nextMovieID;
};

#endif // STOCK_H
