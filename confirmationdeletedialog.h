#ifndef CONFIRMATIONDELETEDIALOG_H
#define CONFIRMATIONDELETEDIALOG_H

#include <QDialog>

namespace Ui {
class ConfirmationDeleteDialog;
}

class ConfirmationDeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmationDeleteDialog(QWidget *parent = nullptr);
    ~ConfirmationDeleteDialog();

public slots:
    void getItem(QString name);

private slots:
    void on_deleteButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ConfirmationDeleteDialog *ui;
};

#endif // CONFIRMATIONDELETEDIALOG_H
