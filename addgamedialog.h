#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

#include <QDialog>
#include "game.h"

namespace Ui {
class AddGameDialog;
}

class AddGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGameDialog(QWidget *parent = nullptr);
    ~AddGameDialog();

signals:
    ///Sends new game to connected class
    void sendGame(Game *newGame);

public slots:
    ///Receives vector of unused games ids from connected class
    void getUnusedGamesID(QVector<int> unusedGamesID);

private slots:
    ///Action on addGame button clicked
    void on_addGame_clicked();

    ///Action on cancelAction button clicked
    void on_cancelAction_clicked();

private:
    Ui::AddGameDialog *ui;
    QVector<int> unusedGamesID;
};

#endif // ADDGAMEDIALOG_H
