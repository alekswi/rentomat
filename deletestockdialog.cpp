#include "deletestockdialog.h"
#include "ui_deletestockdialog.h"

DeleteStockDialog::DeleteStockDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteStockDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());

    ui->itemsTree->setSortingEnabled(true);
    ui->itemsTree->sortByColumn(0, Qt::AscendingOrder);
    ui->itemsTree->setColumnWidth(0,80);
    ui->itemsTree->setColumnWidth(1,240);

    confirmationDeleteDialog = new ConfirmationDeleteDialog;

    connect(this,SIGNAL(sendStock(QString)),confirmationDeleteDialog,SLOT(getItem(QString)));
}

DeleteStockDialog::~DeleteStockDialog()
{
    delete ui;
}

void DeleteStockDialog::printBooks()
{
    ui->itemsTree->clear();
    for(Book *book : articleDB->getBooksDB())
    {
        QTreeWidgetItem *bookItem = new QTreeWidgetItem(ui->itemsTree);
        bookItem->setText(0,QString::number(book->getID()));
        bookItem->setText(1,book->getName());
        for(Stock *stock : book->getStocksDB())
        {
            QTreeWidgetItem *stockItem = new QTreeWidgetItem(bookItem);
            stockItem->setText(0,QString::number(stock->getID()));
            stockItem->setText(1,stock->getLocation());
            if(stock->ifBorrowed())
            {
                stockItem->setText(2,"Borrowed");
                stockItem->setFlags(Qt::NoItemFlags);
            }
            else
            {
                stockItem->setText(2,"Available");
            }
        }
    }
}

void DeleteStockDialog::printGames()
{
    ui->itemsTree->clear();
    for(Game* game : articleDB->getGamesDB())
    {
        QTreeWidgetItem *gameItem = new QTreeWidgetItem(ui->itemsTree);
        gameItem->setText(0,QString::number(game->getID()));
        gameItem->setText(1,game->getName());
        for(Stock *stock : game->getStocksDB())
        {
            QTreeWidgetItem *stockItem = new QTreeWidgetItem(gameItem);
            stockItem->setText(0,QString::number(stock->getID()));
            stockItem->setText(1,stock->getLocation());
            if(stock->ifBorrowed())
            {
                stockItem->setText(2,"Borrowed");
                stockItem->setFlags(Qt::NoItemFlags);
            }
            else
            {
                stockItem->setText(2,"Available");
            }
        }
    }
}

void DeleteStockDialog::printMovies()
{
    ui->itemsTree->clear();
    for(Movie* movie : articleDB->getMoviesDB())
    {
        QTreeWidgetItem *movieItem = new QTreeWidgetItem(ui->itemsTree);
        movieItem->setText(0,QString::number(movie->getID()));
        movieItem->setText(1,movie->getName());
        for(Stock *stock : movie->getStocksDB())
        {
            QTreeWidgetItem *stockItem = new QTreeWidgetItem(movieItem);
            stockItem->setText(0,QString::number(stock->getID()));
            stockItem->setText(1,stock->getLocation());
            if(stock->ifBorrowed())
            {
                stockItem->setText(2,"Borrowed");
                stockItem->setFlags(Qt::NoItemFlags);
            }
            else
            {
                stockItem->setText(2,"Available");
            }
        }
    }
}

void DeleteStockDialog::getDatabase(ArticleDatabase *articleDB, int typeIn)
{
    ui->itemsTree->clear();
    this->articleDB = articleDB;
    this->type = typeIn;
    if(type == 0)
    {
        setWindowTitle("Delete copy of the book");
        printBooks();
    }
    else if(type == 1)
    {
        setWindowTitle("Delete copy of the game");
        printGames();
    }
    else if(type == 2)
    {
        setWindowTitle("Delete copy of the movie");
        printMovies();
    }
}

void DeleteStockDialog::on_cancelButton_clicked()
{
    this->close();
}

void DeleteStockDialog::on_itemsTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->text(2)=="Available")
    {
        if(type == 0)
        {
            currentBook = articleDB->findBook(item->parent()->text(1));
            confirmationDeleteDialog->setModal(true);
            emit sendStock(currentBook->getName());
            if(confirmationDeleteDialog->exec()==1)
            {
                currentBook->deleteStock(item->text(0).toInt());
                printBooks();
            }
        }
        else if(type == 1)
        {
            currentGame = articleDB->findGame(item->parent()->text(1));
            confirmationDeleteDialog->setModal(true);
            emit sendStock(currentGame->getName());
            if(confirmationDeleteDialog->exec()==1)
            {
                currentGame->deleteStock(item->text(0).toInt());
                printGames();
            }
        }
        else if(type == 2)
        {
            currentMovie = articleDB->findMovie(item->parent()->text(1));
            confirmationDeleteDialog->setModal(true);
            emit sendStock(currentMovie->getName());
            if(confirmationDeleteDialog->exec()==1)
            {
                currentMovie->deleteStock(item->text(0).toInt());
                printMovies();
            }
        }
    }
}

