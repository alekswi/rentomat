#include "addgamedialog.h"
#include "ui_addgamedialog.h"

AddGameDialog::AddGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGameDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/logo.ico"));
    setFixedSize(size());
    setWindowTitle("Add new game");
    connect(this,SIGNAL(sendGame(Game*)),parent,SLOT(getGame(Game*)));
}

AddGameDialog::~AddGameDialog()
{
    delete ui;
}

void AddGameDialog::getUnusedGamesID(QVector<int> unusedGamesID)
{
    this->unusedGamesID = unusedGamesID;
}

void AddGameDialog::on_addGame_clicked()
{
    Game *newGame = new Game;
    if(unusedGamesID.size()>0)
    {
        newGame->setID(unusedGamesID.front());
        unusedGamesID.erase(0);
    }
    QString name = ui->gameName->text();
    QString producer = ui->gameProducer->text();
    QString category = ui->gameCategory->currentText();
    QString introduction = ui->gameIntroduction->text();
    QString publisher = ui->gamePublisher->text();
    newGame->year = ui->gameRelease->text().toInt();
    if(name != "")
    {
        newGame->name = name;
    }
    if(producer != "")
    {
        newGame->producer = producer;
    }
    if(category != "")
    {
        newGame->category = category;
    }
    if(publisher != "")
    {
        newGame->publisher = publisher;
    }
    if(introduction != "")
    {
        newGame->introduction = introduction;
    }
    emit sendGame(newGame);
    this->close();
}

void AddGameDialog::on_cancelAction_clicked()
{
    this->close();
}

