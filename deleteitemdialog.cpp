#include "deleteitemdialog.h"
#include "ui_deleteitemdialog.h"

DeleteItemDialog::DeleteItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteItemDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());

    ui->itemsTree->setSortingEnabled(true);
    ui->itemsTree->sortByColumn(0, Qt::AscendingOrder);

    confirmationDeleteDialog = new ConfirmationDeleteDialog;

    connect(this,SIGNAL(sendItem(QString)),confirmationDeleteDialog,SLOT(getItem(QString)));
}

DeleteItemDialog::~DeleteItemDialog()
{
    delete ui;
}

void DeleteItemDialog::printBooks()
{
    ui->itemsTree->clear();
    for(Book *book : articleDB->getBooksDB())
    {
        QTreeWidgetItem *bookItem = new QTreeWidgetItem(ui->itemsTree);
        bookItem->setText(0,QString::number(book->getID()));
        bookItem->setText(1,book->getName());
    }
}

void DeleteItemDialog::printGames()
{
    ui->itemsTree->clear();
    for(Game *game : articleDB->getGamesDB())
    {
        QTreeWidgetItem *gameItem = new QTreeWidgetItem(ui->itemsTree);
        gameItem->setText(0,QString::number(game->getID()));
        gameItem->setText(1,game->getName());
    }
}

void DeleteItemDialog::printMovies()
{
    ui->itemsTree->clear();
    for(Movie *movie : articleDB->getMoviesDB())
    {
        QTreeWidgetItem *movieItem = new QTreeWidgetItem(ui->itemsTree);
        movieItem->setText(0,QString::number(movie->getID()));
        movieItem->setText(1,movie->getName());
    }
}

void DeleteItemDialog::getDatabase(ArticleDatabase *articleDB, int typeIn)
{
    ui->itemsTree->clear();
    this->articleDB = articleDB;
    this->type = typeIn;
    if(type == 0)
    {
        setWindowTitle("Delete book");
        printBooks();
    }
    else if(type == 1)
    {
        setWindowTitle("Delete game");
        printGames();
    }
    else if(type == 2)
    {
        setWindowTitle("Delete movie");
        printMovies();
    }
}


void DeleteItemDialog::on_cancelButton_clicked()
{
    this->close();
}

void DeleteItemDialog::on_itemsTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    int flag = 0;
    if(type == 0)
    {
        currentBook = articleDB->findBook(item->text(1));
        for(Stock *stock : currentBook->getStocksDB())
        {
            if(stock->ifBorrowed())
            {
                flag=1;
                break;
            }
        }
        if(flag == 0)
        {
            confirmationDeleteDialog->setModal(true);
            emit sendItem(currentBook->getName());
            if(confirmationDeleteDialog->exec()==1)
            {
                articleDB->deleteBook(currentBook->getName());
                printBooks();
            }
        }
    }
    else if(type == 1)
    {
        currentGame = articleDB->findGame(item->text(1));
        for(Stock *stock : currentGame->getStocksDB())
        {
            if(stock->ifBorrowed())
            {
                flag=1;
                break;
            }
        }
        if(flag == 0)
        {
            confirmationDeleteDialog->setModal(true);
            emit sendItem(currentGame->getName());
            confirmationDeleteDialog->exec();
            if(confirmationDeleteDialog->exec()==1)
            {
                articleDB->deleteGame(currentGame->getName());
                printGames();
            }
        }
    }
    else if(type == 2)
    {
        currentMovie = articleDB->findMovie(item->text(1));
        for(Stock *stock : currentMovie->getStocksDB())
        {
            if(stock->ifBorrowed())
            {
                flag=1;
                break;
            }
        }
        if(flag == 0)
        {
            confirmationDeleteDialog->setModal(true);
            emit sendItem(currentMovie->getName());
            confirmationDeleteDialog->exec();
            if(confirmationDeleteDialog->exec()==1)
            {
                articleDB->deleteMovie(currentMovie->getName());
                printMovies();
            }
        }
    }
}

