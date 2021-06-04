#ifndef CONFIRMBORROW_H
#define CONFIRMBORROW_H

#include <QDialog>

namespace Ui {
class ConfirmBorrow;
}

class ConfirmBorrow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmBorrow(QWidget *parent = nullptr);
    ~ConfirmBorrow();

public slots:
    void getName(QString name);

private slots:
    void on_borrowButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ConfirmBorrow *ui;
};

#endif // CONFIRMBORROW_H
