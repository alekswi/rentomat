#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    ui->stackedWidget->setCurrentIndex(0);
}

Application::~Application()
{
    delete ui;
}

void Application::on_books_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    setWindowTitle("Rentomat: Books");
}

void Application::on_movies_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    setWindowTitle("Rentomat: Movies");
}

void Application::on_games_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    setWindowTitle("Rentomat: Games");
}

void Application::on_account_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    setWindowTitle("Rentomat");
}
