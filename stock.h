#ifndef STOCK_H
#define STOCK_H


class Stock
{
public:
    Stock();
    void borrow(int studentID);
private:
    int id;
    bool borrowed;
    int studentID;
};

#endif // STOCK_H
