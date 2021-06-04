#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <QTreeWidget>
#include <userdatabase.h>
#include <articledatabase.h>
#include "deleteuserdialog.h"
#include "deleteitemdialog.h"
#include "deletestockdialog.h"
#include "addbookdialog.h"
#include "addgamedialog.h"
#include "addmoviedialog.h"
#include "addstockdialog.h"
#include "confirmborrow.h"
#include "confirmreturn.h"
#include "confirmwatch.h"
#include "changepassworddialog.h"
#include "changeusernamedialog.h"

namespace Ui {
class Application;
}

class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = nullptr);
    ///Adds bookItem to database
    void addBookItem(Book *bookItem);
    ///Prints every book in the tree widget
    void printBookTree();
    ///Prints every stock of currentBook in the tree widget
    void printBookStock();
    ///Adds gameItem to database
    void addGameItem(Game *gameItem);
    ///Prints every game in the tree widget
    void printGameTree();
    ///Prints every stock of currentGame in the tree widget
    void printGameStock();
    ///Adds movieItem to database
    void addMovieItem(Movie *movieItem);
    ///Prints every movie in the tree widget
    void printMovieTree();
    ///Prints every stock of currentMovie in the tree widget
    void printMovieStock();
    ///Prints every borrowe book/game/movie of currentUser in the tree widget
    void printBorrowedItemsTree();
    ///Prints every watched book/game/movie of currentUser in the tree widget
    void printWatchedItemsTree();
    ///Sets current user as given username and sets logged flag to true
    void login(QString username, QString password);
    ///Sets current user to nullptr and sets logged flag to false
    void logout();
    ~Application();

public slots:
    ///Receives and adds new book to database from addbookdialog
    void getBook(Book *newBook);
    ///Receives and adds new game to database from addgamedialog
    void getGame(Game *newGame);
    ///Receives and adds new movie to database from addmoviedialog
    void getMovie(Movie *newMovie);

private slots:
    void on_books_clicked();

    void on_games_clicked();

    void on_movies_clicked();

    void on_account_clicked();

    void on_signUp_clicked();

    void on_signIn_clicked();

    void on_deleteUser_clicked();

    void on_logout_clicked();

    void on_addBook_clicked();

    void on_deleteBook_clicked();

    void on_addGame_clicked();

    void on_deleteGame_clicked();

    void on_deleteMovie_clicked();

    void on_addMovie_clicked();

    void on_addBookStock_clicked();

    void on_addGameStock_clicked();

    void on_addMovieStock_clicked();

    void on_searchBook_clicked();

    void on_searchGame_clicked();

    void on_searchMovie_clicked();

    void on_deleteMovieStock_clicked();

    void on_deleteGameStock_clicked();

    void on_deleteBookStock_clicked();

    void on_booksTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_moviesTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_gamesTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_bookStockTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_gameStockTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_movieStockTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_returnItemButton_clicked();

    void on_unwatchButton_clicked();

    void on_changeUsername_clicked();

    void on_changePassword_clicked();

signals:
    void sendUser(QString username, QString password);

    void sendName(QString name);

    void sendInfo(QString name, QString location);

    void sendUser(User *user);

    void sendUserDB(User *user, UserDatabase userDB);

    void sendUnusedBooksID(QVector<int> unusedBooksID);

    void sendUnusedGamesID(QVector<int> *unusedGamesID);

    void sendUnusedMoviesID(QVector<int> *unusedmoviesID);

    void sendAddStockArticleDB(ArticleDatabase *articleDB, int type);

    void sendDeleteStockArticleDB(ArticleDatabase *articleDB, int type);

    void sendDeleteItemArticleDB(ArticleDatabase *articleDB, int type);

private:
    void resetLoginLabel();
    void resetRegisterLabel();
    QVector <QTreeWidgetItem> *bookRoot;
    QTreeWidgetItem *gameRoot;
    QTreeWidgetItem *movieRoot;
    Book *currentBook;
    Game *currentGame;
    Movie *currentMovie;
    Ui::Application *ui;
    UserDatabase userDB;
    ArticleDatabase *articleDB;
    bool logged;
    User* current;
    AddBookDialog *addBookDialog;
    AddGameDialog *addGameDialog;
    AddMovieDialog *addMovieDialog;
    AddStockDialog *addStockDialog;
    DeleteUserDialog *deleteUserDialog;
    DeleteItemDialog *deleteItemDialog;
    DeleteStockDialog *deleteStockDialog;
    ConfirmBorrow *confirmBorrow;
    ConfirmReturn *confirmReturn;
    ConfirmWatch *confirmWatch;
    ChangeUsernameDialog *changeUsernameDialog;
    ChangePasswordDialog *changePasswordDialog;
};

#endif // APPLICATION_H
