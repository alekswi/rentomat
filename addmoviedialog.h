#ifndef ADDMOVIEDIALOG_H
#define ADDMOVIEDIALOG_H

#include <QDialog>
#include "movie.h"

namespace Ui {
class AddMovieDialog;
}

class AddMovieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMovieDialog(QWidget *parent = nullptr);
    ~AddMovieDialog();

signals:
    ///Sends new movie to connected class
    void sendMovie(Movie *newMovie);

public slots:
    ///Receives new movie to from connected class
    void getUnusedMoviesID(QVector<int> unusedMoviesID);

private slots:
    ///Action on addMovie button clicked
    void on_addMovie_clicked();

    ///Action on cancelAction button clicked
    void on_cancelAction_clicked();

private:
    Ui::AddMovieDialog *ui;
    QVector<int> unusedMoviesID;
};

#endif // ADDMOVIEDIALOG_H
