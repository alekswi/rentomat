#ifndef DELETEUSERDIALOG_H
#define DELETEUSERDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteUserDialog;
}

class DeleteUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteUserDialog(QWidget *parent = nullptr);
    bool ifDeleted();
    ~DeleteUserDialog();

public slots:
    void setUser(QString username, QString password);

private slots:
    void on_Delete_clicked();

    void on_Cancel_clicked();

private:
    Ui::DeleteUserDialog *ui;
    QString username;
    QString password;
    bool check;
};

#endif // DELETEUSERDIALOG_H
