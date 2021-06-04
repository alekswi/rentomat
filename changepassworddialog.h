#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "user.h"

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordDialog(QWidget *parent = nullptr);
    void reset();
    ~ChangePasswordDialog();

public slots:
    void getUser(User *user);

private slots:
    void on_Confirm_clicked();

    void on_Cancel_clicked();

private:
    Ui::ChangePasswordDialog *ui;
    User *user;

};

#endif // CHANGEPASSWORDDIALOG_H
