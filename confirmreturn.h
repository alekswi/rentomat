#ifndef CONFIRMRETURN_H
#define CONFIRMRETURN_H

#include <QDialog>

namespace Ui {
class ConfirmReturn;
}

class ConfirmReturn : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmReturn(QWidget *parent = nullptr);
    ~ConfirmReturn();

public slots:
    void getName(QString name);

private slots:
    void on_borrowButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ConfirmReturn *ui;
};

#endif // CONFIRMRETURN_H
