#include "application.h"
#include "ui_application.h"
#include <QMessageBox>
#include <QPixmap>

Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());


    articleDB = new ArticleDatabase;
    addBookDialog = new AddBookDialog(this);
    addGameDialog = new AddGameDialog(this);
    addMovieDialog = new AddMovieDialog(this);
    addStockDialog = new AddStockDialog(this);
    deleteUserDialog = new DeleteUserDialog(this);
    deleteItemDialog = new DeleteItemDialog(this);
    deleteStockDialog = new DeleteStockDialog(this);
    confirmBorrow = new ConfirmBorrow(this);
    confirmReturn = new ConfirmReturn(this);
    confirmWatch = new ConfirmWatch(this);
    changeUsernameDialog = new ChangeUsernameDialog(this);
    changePasswordDialog = new ChangePasswordDialog(this);
    bookRoot = nullptr;
    gameRoot = nullptr;
    movieRoot = nullptr;
    logged = false;

    QPixmap bookPix(":/img/book.png");
    QPixmap gamePix(":/img/game.png");
    QPixmap moviePix(":/img/movie.png");
    ui->bookImage->setPixmap(bookPix.scaled(ui->bookImage->width(),ui->bookImage->height(),Qt::KeepAspectRatio));
    ui->gameImage->setPixmap(gamePix.scaled(ui->gameImage->width(),ui->gameImage->height(),Qt::KeepAspectRatio));
    ui->movieImage->setPixmap(moviePix.scaled(ui->movieImage->width(),ui->movieImage->height(),Qt::KeepAspectRatio));

    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidgetBook->setCurrentIndex(0);
    ui->stackedWidgetGame->setCurrentIndex(0);
    ui->stackedWidgetMovie->setCurrentIndex(0);
    ui->stackedWidgetAccount->setCurrentIndex(1);

    connect(this,SIGNAL(sendUser(QString,QString)),deleteUserDialog,SLOT(setUser(QString,QString)));
    connect(this,SIGNAL(sendName(QString)),confirmBorrow,SLOT(getName(QString)));
    connect(this,SIGNAL(sendName(QString)),confirmReturn,SLOT(getName(QString)));
    connect(this,SIGNAL(sendInfo(QString,QString)),confirmWatch,SLOT(getInfo(QString,QString)));
    connect(this,SIGNAL(sendUnusedBooksID(QVector<int>unusedBooksID)),addBookDialog,SLOT(getUnusedBooksID(QVector<int>unusedBooksID)));
    connect(this,SIGNAL(sendUnusedGamesID(QVector<int>*unusedGamesID)),addGameDialog,SLOT(getUnusedGamesID(QVector<int>*unusedGamesID)));
    connect(this,SIGNAL(sendUnusedMoviesID(QVector<int>*unusedMoviesID)),addMovieDialog,SLOT(getUnusedMoviesID(QVector<int>*unusedMoviesID)));
    connect(this,SIGNAL(sendAddStockArticleDB(ArticleDatabase*,int)),addStockDialog,SLOT(getDatabase(ArticleDatabase*,int)));
    connect(this,SIGNAL(sendDeleteItemArticleDB(ArticleDatabase*,int)),deleteItemDialog,SLOT(getDatabase(ArticleDatabase*,int)));
    connect(this,SIGNAL(sendDeleteStockArticleDB(ArticleDatabase*,int)),deleteStockDialog,SLOT(getDatabase(ArticleDatabase*,int)));
    connect(this,SIGNAL(sendUserDB(User*,UserDatabase)),changeUsernameDialog,SLOT(getInfo(User*,UserDatabase)));
    connect(this,SIGNAL(sendUser(User*)),changePasswordDialog,SLOT(getUser(User*)));

    userDB.readDatabase();
    articleDB->readDatabase();
    for(int i = 0; i < 5; i++)
    {
        ui->booksTree->setColumnWidth(i,134);
        ui->gamesTree->setColumnWidth(i,134);
    }
    for(int i = 0; i < 6; i++)
    {
        ui->moviesTree->setColumnWidth(i,111);
    }
    printBookTree();
    printGameTree();
    printMovieTree();
    ui->booksTree->setSortingEnabled(true);
    ui->booksTree->sortByColumn(0, Qt::AscendingOrder);
    ui->bookStockTree->setSortingEnabled(true);
    ui->bookStockTree->sortByColumn(0, Qt::AscendingOrder);
    ui->gamesTree->setSortingEnabled(true);
    ui->gamesTree->sortByColumn(0, Qt::AscendingOrder);
    ui->gameStockTree->setSortingEnabled(true);
    ui->gameStockTree->sortByColumn(0, Qt::AscendingOrder);
    ui->moviesTree->setSortingEnabled(true);
    ui->moviesTree->sortByColumn(0, Qt::AscendingOrder);
    ui->movieStockTree->setSortingEnabled(true);
    ui->movieStockTree->sortByColumn(0, Qt::AscendingOrder);

    ui->borrowedItemsTree->setColumnWidth(0, 30);
    ui->borrowedItemsTree->setColumnWidth(1, 110);
    ui->borrowedItemsTree->setColumnWidth(2, 60);
    ui->borrowedItemsTree->setColumnWidth(3, 50);

    ui->watchedItemsTree->setColumnWidth(0, 30);
    ui->watchedItemsTree->setColumnWidth(1, 150);
}

Application::~Application()
{
    userDB.saveDatabase();
    articleDB->saveDatabase();
    delete deleteUserDialog;
    delete ui;
}

//------------------------------------ Navigation bar ------------------------------------

void Application::on_books_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidgetBook->setCurrentIndex(0);
    printBookTree();
    setWindowTitle("Rentomat: Books");
}

void Application::on_games_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidgetGame->setCurrentIndex(0);
    printGameTree();
    setWindowTitle("Rentomat: Games");
}

void Application::on_movies_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->stackedWidgetMovie->setCurrentIndex(0);
    printMovieTree();
    setWindowTitle("Rentomat: Movies");
}

void Application::on_account_clicked()
{
    if(logged==true)
    {
        ui->stackedWidget->setCurrentIndex(4);
        setWindowTitle("Rentomat: " + current->getUsername());
        printBorrowedItemsTree();
        printWatchedItemsTree();
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
        setWindowTitle("Rentomat");
    }
}

//------------------------------------ Login/register page ------------------------------------

void Application::resetLoginLabel()
{
    ui->usernameLogin->setText("");
    ui->passwordLogin->setText("");
}

void Application::resetRegisterLabel()
{
    ui->usernameRegister->setText("");
    ui->passwordRegister->setText("");
    ui->passwordRegisterRepeat->setText("");
}

void Application::login(QString username, QString password)
{
    resetLoginLabel();
    resetRegisterLabel();
    current = userDB.returnUser(username,password);
    logged = true;
    if(current->isAdmin())
    {
        setWindowTitle("Rentomat: " + current->getUsername());
        ui->stackedWidgetAccount->setCurrentIndex(1);
    }
    else
    {
        setWindowTitle("Rentomat: " + current->getUsername());
        ui->stackedWidgetAccount->setCurrentIndex(0);
        printBorrowedItemsTree();
        printWatchedItemsTree();

    }
    ui->stackedWidget->setCurrentIndex(4);
}

void Application::on_signUp_clicked()
{
    QString username = ui->usernameRegister->text();
    if(userDB.findUser(username)==-1)
    {
        if(ui->passwordRegister->text().size() < 8)
        {
            QMessageBox::warning(this, "Warning", "Please enter password with at least 8 characters");
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
    auto temp = userDB.returnUser(username, password);
    if(temp!=nullptr)
    {
        QMessageBox::about(this, "Login","Login succesful");
        login(username, password);
    }
    else
    {
        QMessageBox::warning(this, "Login","Username or password incorect");
    }
}

//------------------------------------ Books page ------------------------------------

void Application::addBookItem(Book *book)
{
    QTreeWidgetItem *bookItem = new QTreeWidgetItem(ui->booksTree);
    bookItem->setText(0,book->getName());
    bookItem->setText(1,book->getAuthor());
    bookItem->setText(2,book->getCategory());
    bookItem->setText(3,QString::number(book->getPages()));
    bookItem->setText(4,QString::number(book->getYear()));
}

void Application::printBookTree()
{
    ui->booksTree->clear();
    for(Book *book : articleDB->getBooksDB())
    {
        QTreeWidgetItem *bookItem = new QTreeWidgetItem(ui->booksTree);
        bookItem->setText(0,book->getName());
        bookItem->setText(1,book->getAuthor());
        bookItem->setText(2,book->getCategory());
        bookItem->setText(3,QString::number(book->getPages()));
        bookItem->setText(4,QString::number(book->getYear()));
    }
}

void Application::on_searchBook_clicked()
{
    ui->booksTree->clear();
    QString tempName = ui->bookNameSearch->text();
    QString tempAuthor = ui->bookAuthorSearch->text();
    QString tempCategory = ui->bookCategorySearch->currentText();
    int tempReleaseFrom = ui->bookReleaseFrom->text().toInt();
    int tempReleaseTo = ui->bookReleaseTo->text().toInt();
    for(Book *book : articleDB->getBooksDB())
    {
        if(book->compare(tempName,tempAuthor,tempCategory,tempReleaseFrom,tempReleaseTo))
        {
            QTreeWidgetItem *bookItem = new QTreeWidgetItem(ui->booksTree);
            bookItem->setText(0,book->getName());
            bookItem->setText(1,book->getAuthor());
            bookItem->setText(2,book->getCategory());
            bookItem->setText(3,QString::number(book->getPages()));
            bookItem->setText(4,QString::number(book->getYear()));
        }
    }
}

void Application::printBookStock()
{
    ui->bookStockTree->clear();
    for(Stock *stock : currentBook->getStocksDB())
    {
        QTreeWidgetItem *bookStock = new QTreeWidgetItem(ui->bookStockTree);
        bookStock->setText(0,QString::number(stock->getID()));
        bookStock->setText(1,stock->getLocation());
        if(stock->ifBorrowed())
        {
            bookStock->setText(2,"Borrowed");
            bookStock->setFlags(Qt::NoItemFlags);
        }
        else
        {
            bookStock->setText(2,"Available");
        }
    }
}

void Application::on_booksTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    currentBook = articleDB->findBook(item->text(0));
    ui->bookNameLabel->setText(currentBook->getName());
    ui->bookAuthorLabel->setText(currentBook->getAuthor());
    ui->bookCategoryLabel->setText(currentBook->getCategory());
    ui->bookIntroductionLabel->setText(currentBook->getIntroduction());
    ui->bookPagesLabel->setText(QString::number(currentBook->getPages()));
    ui->bookReleaseLabel->setText(QString::number(currentBook->getYear()));
    ui->stackedWidgetBook->setCurrentIndex(1);
    setWindowTitle(currentBook->getName());
    printBookStock();
}

void Application::on_bookStockTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(logged && !current->isAdmin())
    {
        if(!currentBook->findStock(item->text(0).toInt())->ifBorrowed())
        {
            confirmBorrow->setModal(true);
            emit sendName(currentBook->getName());
            if(confirmBorrow->exec())
            {
                current->borrowBook(currentBook->getID(),item->text(0).toInt());
                articleDB->findBook(currentBook->getName())->borrowStock(item->text(0).toInt(),current->getID());
                printBookStock();
            }
        }
        else
        {
            confirmWatch->setModal(true);
            emit sendInfo(currentBook->getName(),item->text(1));
            if(confirmWatch->exec())
            {
                Watched *watchedItem = new Watched("Book",currentBook->getName(),item->text(1));
                if(!current->addWatchedItem(watchedItem))
                {
                    QMessageBox::warning(this, "Warning", "Already watchin " + currentBook->getName() + " at " + item->text(1));
                }
            }
        }
    }
}

//------------------------------------ Games page ------------------------------------

void Application::addGameItem(Game *game)
{
    QTreeWidgetItem *gameItem = new QTreeWidgetItem(ui->gamesTree);
    gameItem->setText(0,game->getName());
    gameItem->setText(1,game->getCategory());
    gameItem->setText(2,game->getProducer());
    gameItem->setText(3,game->getPublisher());
    gameItem->setText(4,QString::number(game->getYear()));
}

void Application::printGameTree()
{
    ui->gamesTree->clear();
    for(Game *game : articleDB->getGamesDB())
    {
        QTreeWidgetItem *gameItem = new QTreeWidgetItem(ui->gamesTree);
        gameItem->setText(0,game->getName());
        gameItem->setText(1,game->getCategory());
        gameItem->setText(2,game->getProducer());
        gameItem->setText(3,game->getPublisher());
        gameItem->setText(4,QString::number(game->getYear()));
    }
}

void Application::on_searchGame_clicked()
{
    ui->gamesTree->clear();
    QString tempName = ui->gameNameSearch->text();
    QString tempCategory = ui->gameCategorySearch->currentText();
    int tempReleaseFrom = ui->gameReleaseFrom->text().toInt();
    int tempReleaseTo = ui->gameReleaseTo->text().toInt();
    for(Game *game : articleDB->getGamesDB())
    {
        if(game->compare(tempName,tempCategory,tempReleaseFrom,tempReleaseTo))
        {
            QTreeWidgetItem *gameItem = new QTreeWidgetItem(ui->gamesTree);
            gameItem->setText(0,game->getName());
            gameItem->setText(1,game->getCategory());
            gameItem->setText(2,game->getProducer());
            gameItem->setText(3,game->getPublisher());
            gameItem->setText(4,QString::number(game->getYear()));
        }
    }
}

void Application::printGameStock()
{
    ui->gameStockTree->clear();
    for(Stock *stock : currentGame->getStocksDB())
    {
        QTreeWidgetItem *gameStock = new QTreeWidgetItem(ui->gameStockTree);
        gameStock->setText(0,QString::number(stock->getID()));
        gameStock->setText(1,stock->getLocation());
        if(stock->ifBorrowed())
        {
            gameStock->setText(2,"Borrowed");
            gameStock->setFlags(Qt::NoItemFlags);
        }
        else
        {
            gameStock->setText(2,"Available");
        }
    }
}

void Application::on_gamesTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    currentGame = articleDB->findGame(item->text(0));
    ui->gameNameLabel->setText(currentGame->getName());
    ui->gameProducerLabel->setText(currentGame->getProducer());
    ui->gameCategoryLabel->setText(currentGame->getCategory());
    ui->gameIntroductionLabel->setText(currentGame->getIntroduction());
    ui->gamePublisherLabel->setText(currentGame->getPublisher());
    ui->gameReleaseLabel->setText(QString::number(currentGame->getYear()));
    ui->stackedWidgetGame->setCurrentIndex(1);
    setWindowTitle(currentGame->getName());
    printGameStock();
}

void Application::on_gameStockTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(logged && !current->isAdmin())
    {
        if(!currentGame->findStock(item->text(0).toInt())->ifBorrowed())
        {
            confirmBorrow->setModal(true);
            emit sendName(currentGame->getName());
            if(confirmBorrow->exec())
            {
                current->borrowGame(currentGame->getID(),item->text(0).toInt());
                articleDB->findGame(currentGame->getName())->borrowStock(item->text(0).toInt(),current->getID());
                printGameStock();
            }
        }
        else
        {
            confirmWatch->setModal(true);
            emit sendInfo(currentGame->getName(),item->text(1));
            if(confirmWatch->exec())
            {
                Watched *watchedItem = new Watched("Game",currentGame->getName(),item->text(1));
                if(!current->addWatchedItem(watchedItem))
                {
                    QMessageBox::warning(this, "Warning", "Already watchin " + currentGame->getName() + " at " + item->text(1));
                }
            }
        }
    }
}

//------------------------------------ Movies page ------------------------------------

void Application::addMovieItem(Movie *movie)
{
    QTreeWidgetItem *movieItem = new QTreeWidgetItem(ui->moviesTree);
    movieItem->setText(0,movie->getName());
    movieItem->setText(1,movie->getCategory());
    movieItem->setText(2,QString::number(movie->getDuration()));
    movieItem->setText(3,movie->getProducer());
    movieItem->setText(4,movie->getProductionCompany());
    movieItem->setText(5,QString::number(movie->getYear()));
}

void Application::printMovieTree()
{
    ui->moviesTree->clear();
    for(Movie *movie : articleDB->getMoviesDB())
    {
        QTreeWidgetItem *movieItem = new QTreeWidgetItem(ui->moviesTree);
        movieItem->setText(0,movie->getName());
        movieItem->setText(1,movie->getCategory());
        movieItem->setText(2,QString::number(movie->getDuration()));
        movieItem->setText(3,movie->getProducer());
        movieItem->setText(4,movie->getProductionCompany());
        movieItem->setText(5,QString::number(movie->getYear()));
    }
}

void Application::on_searchMovie_clicked()
{
    ui->moviesTree->clear();
    QString tempName = ui->movieNameSearch->text();
    QString tempCategory = ui->movieCategorySearch->currentText();
    int tempReleaseFrom = ui->movieReleaseFrom->text().toInt();
    int tempReleaseTo = ui->movieReleaseTo->text().toInt();
    int tempDurationFrom = ui->movieDurationFrom->text().toInt();
    int tempDurationTo = ui->movieDurationTo->text().toInt();
    for(Movie *movie : articleDB->getMoviesDB())
    {
        if(movie->compare(tempName,tempCategory,tempReleaseFrom,tempReleaseTo,tempDurationFrom,tempDurationTo))
        {
            QTreeWidgetItem *movieItem = new QTreeWidgetItem(ui->moviesTree);
            movieItem->setText(0,movie->getName());
            movieItem->setText(1,movie->getCategory());
            movieItem->setText(2,QString::number(movie->getDuration()));
            movieItem->setText(3,movie->getProducer());
            movieItem->setText(4,movie->getProductionCompany());
            movieItem->setText(5,QString::number(movie->getYear()));
        }
    }
}

void Application::printMovieStock()
{
    ui->movieStockTree->clear();
    for(Stock *stock : currentMovie->getStocksDB())
    {
        QTreeWidgetItem *movieStock = new QTreeWidgetItem(ui->movieStockTree);
        movieStock->setText(0,QString::number(stock->getID()));
        movieStock->setText(1,stock->getLocation());
        if(stock->ifBorrowed())
        {
            movieStock->setText(2,"Borrowed");
            movieStock->setFlags(Qt::NoItemFlags);
        }
        else
        {
            movieStock->setText(2,"Available");
        }
    }
}

void Application::on_moviesTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    currentMovie = articleDB->findMovie(item->text(0));
    ui->movieNameLabel->setText(currentMovie->getName());
    ui->movieProducerLabel->setText(currentMovie->getProducer());
    ui->movieCategoryLabel->setText(currentMovie->getCategory());
    ui->movieIntroductionLabel->setText(currentMovie->getIntroduction());
    ui->movieProductionCompanyLabel->setText(currentMovie->getProductionCompany());
    ui->movieDurationLabel->setText(QString::number(currentMovie->getDuration()));
    ui->movieReleaseLabel->setText(QString::number(currentMovie->getYear()));
    ui->stackedWidgetMovie->setCurrentIndex(1);
    setWindowTitle(currentMovie->getName());
    printMovieStock();
}

void Application::on_movieStockTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(logged && !current->isAdmin())
    {
        if(!currentMovie->findStock(item->text(0).toInt())->ifBorrowed())
        {
            confirmBorrow->setModal(true);
            emit sendName(currentMovie->getName());
            if(confirmBorrow->exec())
            {
                current->borrowMovie(currentMovie->getID(),item->text(0).toInt());
                articleDB->findMovie(currentMovie->getName())->borrowStock(item->text(0).toInt(),current->getID());
                printMovieStock();
            }

        }
        else
        {
            confirmWatch->setModal(true);
            emit sendInfo(currentMovie->getName(),item->text(1));
            if(confirmWatch->exec())
            {
                Watched *watchedItem = new Watched("Movie",currentMovie->getName(),item->text(1));
                if(!current->addWatchedItem(watchedItem))
                {
                    QMessageBox::warning(this, "Warning", "Already watchin " + currentMovie->getName() + " at " + item->text(1));
                }
            }
        }
    }
}

//------------------------------------ Account page ------------------------------------

void Application::logout()
{
    current = nullptr;
    logged = false;
    setWindowTitle("Rentomat");
    ui->stackedWidget->setCurrentIndex(0);
}

void Application::on_deleteUser_clicked()
{
    if(current->getBorrowedBooksID().size()>0 || current->getBorrowedGamesID().size()>0 || current->getBorrowedMoviesID().size()>0)
    {
        QMessageBox::warning(this, "Warning", "Please return all items first");
    }
    else
    {
        deleteUserDialog->setModal(true);
        emit sendUser(current->getUsername(), current->getPassword());
        deleteUserDialog->exec();
        if(deleteUserDialog->ifDeleted())
        {
            userDB.deleteUser(current->getUsername());
            logout();
        }
    }
}

void Application::on_logout_clicked()
{
    QMessageBox::about(this, "Logout","Logout succesful");
    logout();
}

void Application::printBorrowedItemsTree()
{
    ui->borrowedItemsTree->clear();
    QTreeWidgetItem *booksParent = new QTreeWidgetItem(ui->borrowedItemsTree);
    booksParent->setText(1,"Books:");
    for(auto temp : current->getBorrowedBooksID())
    {
        QTreeWidgetItem *booksChild = new QTreeWidgetItem(booksParent);
        booksChild->setText(0, QString::number(temp.first));
        booksChild->setText(1, articleDB->findBook(temp.first)->getName());
        booksChild->setText(2, articleDB->findBook(temp.first)->findStock(temp.second)->getLocation());
        booksChild->setText(3, QString::number(temp.second));
    }
    QTreeWidgetItem *gamesParent = new QTreeWidgetItem(ui->borrowedItemsTree);
    gamesParent->setText(1,"Games:");
    for(auto temp : current->getBorrowedGamesID())
    {
        QTreeWidgetItem *gamesChild = new QTreeWidgetItem(gamesParent);
        gamesChild->setText(0, QString::number(temp.first));
        gamesChild->setText(1, articleDB->findGame(temp.first)->getName());
        gamesChild->setText(2, articleDB->findGame(temp.first)->findStock(temp.second)->getLocation());
        gamesChild->setText(3, QString::number(temp.second));
    }
    QTreeWidgetItem *moviesParent = new QTreeWidgetItem(ui->borrowedItemsTree);
    moviesParent->setText(1,"Movies:");
    for(auto temp : current->getBorrowedMoviesID())
    {
        QTreeWidgetItem *moviesChild = new QTreeWidgetItem(moviesParent);
        moviesChild->setText(0, QString::number(temp.first));
        moviesChild->setText(1, articleDB->findMovie(temp.first)->getName());
        moviesChild->setText(2, articleDB->findMovie(temp.first)->findStock(temp.second)->getLocation());
        moviesChild->setText(3, QString::number(temp.second));
    }
}

void Application::printWatchedItemsTree()
{
    ui->watchedItemsTree->clear();
    QTreeWidgetItem *booksParent = new QTreeWidgetItem(ui->watchedItemsTree);
    booksParent->setText(1,"Books:");
    QTreeWidgetItem *gamesParent = new QTreeWidgetItem(ui->watchedItemsTree);
    gamesParent->setText(1,"Games:");
    QTreeWidgetItem *moviesParent = new QTreeWidgetItem(ui->watchedItemsTree);
    moviesParent->setText(1,"Movies:");
    for(auto temp : current->getWatchedItems())
    {
        if(temp->getType()=="Book")
        {
            QTreeWidgetItem *bookChild = new QTreeWidgetItem(booksParent);
            bookChild->setText(1,temp->getName());
            bookChild->setText(2,temp->getLocation());
        }
        else if(temp->getType()=="Game")
        {
            QTreeWidgetItem *gameChild = new QTreeWidgetItem(gamesParent);
            gameChild->setText(1,temp->getName());
            gameChild->setText(2,temp->getLocation());
        }
        else if(temp->getType()=="Movie")
        {
            QTreeWidgetItem *movieChild = new QTreeWidgetItem(moviesParent);
            movieChild->setText(1,temp->getName());
            movieChild->setText(2,temp->getLocation());
        }
    }
}

void Application::on_returnItemButton_clicked()
{
    auto temp = ui->borrowedItemsTree->currentItem();
    if(temp->text(0)!="" && temp->text(2)!="")
    {
        confirmReturn->setModal(true);
        emit sendName(temp->text(1));
        if(confirmReturn->exec())
        {
            if(temp->parent()->text(1)=="Books:")
            {
                current->returnBook(temp->text(0).toInt(),temp->text(3).toInt());
                articleDB->findBook(temp->text(1))->returnStock(temp->text(3).toInt());
            }
            else if(temp->parent()->text(1)=="Games:")
            {
                current->returnGame(temp->text(0).toInt(),temp->text(3).toInt());
                articleDB->findGame(temp->text(1))->returnStock(temp->text(3).toInt());
            }
            else if(temp->parent()->text(1)=="Movies:")
            {
                current->returnMovie(temp->text(0).toInt(),temp->text(3).toInt());
                articleDB->findMovie(temp->text(1))->returnStock(temp->text(3).toInt());
            }
            printBorrowedItemsTree();
        }
    }
}

void Application::on_unwatchButton_clicked()
{
    auto temp = ui->watchedItemsTree->currentItem();
    if(temp->text(2)!="")
    {
        if(temp->parent()->text(1)=="Books:")
        {
            current->deleteWatchedItem("Book",temp->text(1),temp->text(2));
        }
        else if(temp->parent()->text(1)=="Games:")
        {
            current->deleteWatchedItem("Game",temp->text(1),temp->text(2));
        }
        else if(temp->parent()->text(1)=="Movies:")
        {
            current->deleteWatchedItem("Movie",temp->text(1),temp->text(2));
        }
        printWatchedItemsTree();
    }
}

//------------------------------------ Admin page ------------------------------------

void Application::getBook(Book *newBook)
{
    articleDB->addBook(newBook);
    addBookItem(newBook);
}

void Application::getGame(Game *newGame)
{
    articleDB->addGame(newGame);
    addGameItem(newGame);
}

void Application::getMovie(Movie *newMovie)
{
    articleDB->addMovie(newMovie);
    addMovieItem(newMovie);
}

void Application::on_addBook_clicked()
{
    addBookDialog->setModal(true);
    emit sendUnusedBooksID(articleDB->getUnusedBooksId());
    addBookDialog->exec();
}

void Application::on_deleteBook_clicked()
{
    deleteItemDialog->setModal(true);
    emit sendDeleteItemArticleDB(articleDB, 0);
    deleteItemDialog->exec();
}

void Application::on_addGame_clicked()
{
    addGameDialog->setModal(true);
    emit sendUnusedGamesID(articleDB->getUnusedGamesId());
    addGameDialog->exec();
}

void Application::on_deleteGame_clicked()
{
    deleteItemDialog->setModal(true);
    emit sendDeleteItemArticleDB(articleDB, 1);
    deleteItemDialog->exec();
}

void Application::on_addMovie_clicked()
{
    addMovieDialog->setModal(true);
    emit sendUnusedMoviesID(articleDB->getUnusedMoviesId());
    addMovieDialog->exec();
}

void Application::on_deleteMovie_clicked()
{
    deleteItemDialog->setModal(true);
    emit sendDeleteItemArticleDB(articleDB, 2);
    deleteItemDialog->exec();
}

void Application::on_addBookStock_clicked()
{
    addStockDialog->setModal(true);
    emit sendAddStockArticleDB(articleDB, 0);
    addStockDialog->exec();
}

void Application::on_addGameStock_clicked()
{
    addStockDialog->setModal(true);
    emit sendAddStockArticleDB(articleDB, 1);
    addStockDialog->exec();
}

void Application::on_addMovieStock_clicked()
{
    addStockDialog->setModal(true);
    emit sendAddStockArticleDB(articleDB, 2);
    addStockDialog->exec();
}

void Application::on_deleteBookStock_clicked()
{
    deleteStockDialog->setModal(true);
    emit sendDeleteStockArticleDB(articleDB, 0);
    deleteStockDialog->exec();
}

void Application::on_deleteGameStock_clicked()
{
    deleteStockDialog->setModal(true);
    emit sendDeleteStockArticleDB(articleDB, 1);
    deleteStockDialog->exec();
}

void Application::on_deleteMovieStock_clicked()
{
    deleteStockDialog->setModal(true);
    emit sendDeleteStockArticleDB(articleDB, 2);
    deleteStockDialog->exec();
}

void Application::on_changeUsername_clicked()
{
    changeUsernameDialog->setModal(true);
    emit sendUserDB(current, userDB);
    if(changeUsernameDialog->exec())
    {
        setWindowTitle("Rentomat: " + current->getUsername());
    }
}

void Application::on_changePassword_clicked()
{
    changePasswordDialog->setModal(true);
    emit sendUser(current);
    changePasswordDialog->exec();
}

