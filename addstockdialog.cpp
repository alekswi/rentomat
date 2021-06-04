#include "addstockdialog.h"
#include "ui_addstockdialog.h"

AddStockDialog::AddStockDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStockDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());

    ui->itemsTree->setColumnWidth(0, 50);
    ui->itemsTree->setSortingEnabled(true);
    ui->itemsTree->sortByColumn(0, Qt::AscendingOrder);

    stockLocationDialog = new StockLocationDialog(this);

    connect(this, SIGNAL(sendItem(QString,QString)), stockLocationDialog, SLOT(getItem(QString,QString)));
}

AddStockDialog::~AddStockDialog()
{
    delete ui;
}

void AddStockDialog::getDatabase(ArticleDatabase *articleDB, int typeIn)
{
    this->articleDB = articleDB;
    ui->itemsTree->clear();
    type = typeIn;
    if(type == 0)
    {
        setWindowTitle("Add copy of the book");
        for(Book *book : articleDB->getBooksDB())
        {
            QTreeWidgetItem *bookItem = new QTreeWidgetItem(ui->itemsTree);
            bookItem->setText(0,QString::number(book->getID()));
            bookItem->setText(1,book->getName());
        }
    }
    else if(type == 1)
    {
        setWindowTitle("Add copy of the game");
        for(Game* game : articleDB->getGamesDB())
        {
            QTreeWidgetItem *gameItem = new QTreeWidgetItem(ui->itemsTree);
            gameItem->setText(0,QString::number(game->getID()));
            gameItem->setText(1,game->getName());
        }
    }
    else if(type == 2)
    {
        setWindowTitle("Add copy of the movie");
        for(Movie* movie : articleDB->getMoviesDB())
        {
            QTreeWidgetItem *movieItem = new QTreeWidgetItem(ui->itemsTree);
            movieItem->setText(0,QString::number(movie->getID()));
            movieItem->setText(1,movie->getName());
        }
    }
}

void AddStockDialog::getStock(Stock *newStock)
{
        if(type == 0)
        {
            Book *temp = articleDB->findBook(currentItemName);
            temp->addStock(newStock);
        }
        else if(type == 1)
        {
            Game *temp = articleDB->findGame(currentItemName);
            temp->addStock(newStock);
        }
        else if(type == 2)
        {
            Movie *temp = articleDB->findMovie(currentItemName);
            temp->addStock(newStock);
        }
}

void AddStockDialog::on_cancelButton_clicked()
{
    this->close();
}

void AddStockDialog::on_itemsTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    currentItemName = item->text(1);
    stockLocationDialog->setModal(true);
    QString tempType;
    if(type == 0)
    {
        tempType = typeid(Book*).name();
    }
    else if(type == 1)
    {
        tempType = typeid(Game*).name();
    }
    else if(type == 2)
    {
        tempType = typeid(Movie*).name();
    }
    emit sendItem(currentItemName, tempType);
    stockLocationDialog->exec();
}

