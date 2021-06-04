#include "addmoviedialog.h"
#include "ui_addmoviedialog.h"

AddMovieDialog::AddMovieDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMovieDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());
    setWindowTitle("Add new movie");
    connect(this,SIGNAL(sendMovie(Movie*)),parent,SLOT(getMovie(Movie*)));
}

AddMovieDialog::~AddMovieDialog()
{
    delete ui;
}

void AddMovieDialog::getUnusedMoviesID(QVector<int> unusedMoviesID)
{
    this->unusedMoviesID = unusedMoviesID;
}

void AddMovieDialog::on_addMovie_clicked()
{
    Movie *newMovie = new Movie;
    if(unusedMoviesID.size()>0)
    {
        newMovie->setID(unusedMoviesID.front());
        unusedMoviesID.erase(0);
    }
    QString name = ui->movieName->text();
    QString producer = ui->movieProducer->text();
    QString category = ui->movieCategory->currentText();
    QString introduction = ui->movieIntroduction->text();
    QString productionCompany = ui->movieProductionCompany->text();
    newMovie->year = ui->movieRelease->text().toInt();
    if(name != "")
    {
        newMovie->name = name;
    }
    if(producer != "")
    {
        newMovie->producer = producer;
    }
    if(category != "")
    {
        newMovie->category = category;
    }
    if(productionCompany != "")
    {
        newMovie->productionCompany = productionCompany;
    }
    if(introduction != "")
    {
        newMovie->introduction = introduction;
    }
    emit sendMovie(newMovie);
    this->close();
}


void AddMovieDialog::on_cancelAction_clicked()
{
    this->close();
}

