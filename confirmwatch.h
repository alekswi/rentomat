#ifndef CONFIRMWATCH_H
#define CONFIRMWATCH_H

#include <QDialog>

namespace Ui {
class ConfirmWatch;
}

class ConfirmWatch : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmWatch(QWidget *parent = nullptr);
    ~ConfirmWatch();

public slots:
    void getInfo(QString name, QString location);

private slots:
    void on_watchButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ConfirmWatch *ui;
};

#endif // CONFIRMWATCH_H
