#ifndef CHANGEUSERNAMEDIALOG_H
#define CHANGEUSERNAMEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "userdatabase.h"

namespace Ui {
class ChangeUsernameDialog;
}

class ChangeUsernameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeUsernameDialog(QWidget *parent = nullptr);
    void reset();
    ~ChangeUsernameDialog();

public slots:
    void getInfo(User *user, UserDatabase userDB);

private slots:
    void on_Confirm_clicked();

    void on_Cancel_clicked();

private:
    Ui::ChangeUsernameDialog *ui;
    UserDatabase userDB;
    User *user;
};

#endif // CHANGEUSERNAMEDIALOG_H
