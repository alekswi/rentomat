#include "application.h"
#include "ui_application.h"
#include <QMessageBox>

Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    deleteDialog = new DeleteDialog;
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    ui->stackedWidget->setCurrentIndex(0);
    logged = false;
    connect(this,SIGNAL(sendUser(QString,QString)),deleteDialog,SLOT(setUser(QString,QString)));
    userDB.readDatabase();
}

Application::~Application()
{
    userDB.saveDatabase();
    delete deleteDialog;
    delete ui;
}

void Application::login(QString username, QString password)
{
    current = userDB.returnUser(username,password);
    logged = true;
    setWindowTitle("Rentomat: " + current->getUsername());
    ui->stackedWidget->setCurrentIndex(4);
}

void Application::logout()
{
    current = nullptr;
    logged = false;
    setWindowTitle("Rentomat");
    ui->stackedWidget->setCurrentIndex(0);
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
    if(logged==true)
    {
        ui->stackedWidget->setCurrentIndex(4);
        setWindowTitle("Rentomat: " + current->getUsername());
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
        setWindowTitle("Rentomat");
    }
}

void Application::on_signUp_clicked()
{
    QString username = ui->usernameRegister->text();
    if(userDB.findUser(username)==-1)
    {
        if(ui->passwordRegister->text().size() < 8)
        {
            QMessageBox::warning(this, "Warning", "Please enter password with at leas 8 characters");
        }
        else if(ui->passwordRegister->text()==ui->passwordRegisterRepeat->text())
        {
            QString password = ui->passwordRegister->text();
            userDB.addUser(username,password);
            QMessageBox::about(this, "Done", "Account created");
            login(username, password);
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Passwords don't match");
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Username already taken");
    }
}

void Application::on_signIn_clicked()
{
    QString username = ui->usernameLogin->text();
    QString password = ui->passwordLogin->text();
    int pos = userDB.findUser(username);
    if(pos!=-1)
    {
        QMessageBox::about(this, "Login","Login succesful");
        login(username, password);
    }
    else
    {
        QMessageBox::warning(this, "Login","Username or password incorect");
    }
}

void Application::on_deleteUser_clicked()
{
    deleteDialog->setModal(true);
    emit sendUser(current->getUsername(), current->getPassword());
    deleteDialog->exec();
    if(deleteDialog->ifDeleted())
    {
        userDB.deleteUser(current->getUsername());
        logout();
    }
}

void Application::on_logout_clicked()
{
    QMessageBox::about(this, "Logout","Logout succesful");
    logout();
}
