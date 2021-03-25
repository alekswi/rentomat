#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>

namespace Ui {
class Application;
}

class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = nullptr);
    ~Application();

private slots:
    void on_books_clicked();

    void on_games_clicked();

    void on_movies_clicked();

    void on_account_clicked();

private:
    Ui::Application *ui;
};

#endif // APPLICATION_H
