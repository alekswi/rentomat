#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <userdatabase.h>
#include <articledatabase.h>
#include "deletedialog.h"

namespace Ui {
class Application;
}

class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = nullptr);
    ///Sets current user as given
    void login(QString username, QString password);
    ///Sets current user to nullptr
    void logout();
    ~Application();

private slots:
    void on_books_clicked();

    void on_games_clicked();

    void on_movies_clicked();

    void on_account_clicked();

    void on_signUp_clicked();

    void on_signIn_clicked();

    void on_deleteUser_clicked();

    void on_logout_clicked();

signals:
    void sendUser(QString username, QString password);

private:
    Ui::Application *ui;
    UserDatabase userDB;
    ArticleDatabase articleDB;
    bool logged;
    User* current;
    DeleteDialog *deleteDialog;
};

#endif // APPLICATION_H
