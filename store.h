#ifndef STORE_H
#define STORE_H

#include<QApplication>

class Store
{
public:
    Store();
private:
    int id;
    QString location;
    QVector<std::pair<int,int>> books;
    QVector<std::pair<int,int>> games;
    QVector<std::pair<int,int>> movie;
};

#endif // STORE_H
