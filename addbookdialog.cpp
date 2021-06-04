#include "addbookdialog.h"
#include "ui_addbookdialog.h"

AddBookDialog::AddBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());
    setWindowTitle("Add new book");

    connect(this,SIGNAL(sendBook(Book*)),parent,SLOT(getBook(Book*)));
}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}

void AddBookDialog::getUnusedBooksID(QVector<int> unusedBooksID)
{
    this->unusedBooksID = unusedBooksID;
}

void AddBookDialog::on_addBook_clicked()
{
    Book *newBook = new Book();
    if(unusedBooksID.size()>0)
    {
        newBook->setID(unusedBooksID.front());
        unusedBooksID.erase(0);
    }
    QString name = ui->bookName->text();
    QString author = ui->bookAuthor->text();
    QString category = ui->bookCategory->currentText();
    QString introduction = ui->bookIntroduction->text();
    newBook->pages = ui->bookPages->text().toInt();
    newBook->year = ui->bookRelease->text().toInt();
    if(name != "")
    {
        newBook->name = name;
    }
    if(author != "")
    {
        newBook->author = author;
    }
    if(category != "")
    {
        newBook->category = category;
    }
    if(introduction != "")
    {
        newBook->introduction = introduction;
    }
    emit sendBook(newBook);
    this->close();
}

void AddBookDialog::on_cancelAction_clicked()
{
    this->close();
}

