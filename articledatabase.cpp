#include "articledatabase.h"

ArticleDatabase::ArticleDatabase()
{

}

void ArticleDatabase::readBooksDB()
{
    QFile file;
    file.setFileName("booksDB.txt");
    file.open(QIODevice::ReadOnly);
    if(file.exists())
    {
        QTextStream stream(&file);
        QString fileString = stream.readAll();
        auto stringsList = fileString.split("%\n");
        for(auto record : stringsList)
        {
            if(record.left(2)=="ID")
            {
                Book *temp = new Book;
                temp->loadBook(record);
                books.push_back(temp);
            }
            else if(record.left(12)=="Unused ids: ")
            {
                record = record.mid(12);
                auto idList = record.split(" ");
                for(auto id : idList)
                {
                    unusedBooksID.push_back(id.toInt());
                }
            }
        }
    }
}

void ArticleDatabase::readGamesDB()
{
    QFile file;
    file.setFileName("gamesDB.txt");
    file.open(QIODevice::ReadOnly);
    if(file.exists())
    {
        QTextStream stream(&file);
        QString fileString = stream.readAll();
        auto stringsList = fileString.split("%\n");
        for(auto record : stringsList)
        {
            if(record.left(2)=="ID")
            {
                Game *temp = new Game;
                temp->loadGame(record);
                games.push_back(temp);
            }
            else if(record.left(12)=="Unused ids: ")
            {
                record = record.mid(12);
                auto idList = record.split(" ");
                for(auto id : idList)
                {
                    unusedBooksID.push_back(id.toInt());
                }
            }
        }
    }
}

void ArticleDatabase::readMoviesDB()
{
    QFile file;
    file.setFileName("moviesDB.txt");
    file.open(QIODevice::ReadOnly);
    if(file.exists())
    {
        QTextStream stream(&file);
        QString fileString = stream.readAll();
        auto stringsList = fileString.split("%\n");
        for(auto record : stringsList)
        {
            if(record.left(2)=="ID")
            {
                Movie *temp = new Movie;
                temp->loadMovie(record);
                movies.push_back(temp);
            }
            else if(record.left(12)=="Unused ids: ")
            {
                record = record.mid(12);
                auto idList = record.split(" ");
                for(auto id : idList)
                {
                    unusedBooksID.push_back(id.toInt());
                }
            }
        }
    }
}

void ArticleDatabase::readDatabase()
{
    readBooksDB();
    readGamesDB();
    readMoviesDB();
}

void ArticleDatabase::saveBooksDB()
{
    std::sort(books.begin(), books.end(), [](Book* left, Book* right) {
        return left->getID() < right->getID();});
    QFile file;
    file.setFileName("booksDB.txt");
    file.open(QIODevice::WriteOnly);
    if(file.exists())
    {
        QTextStream out(&file);
        for(auto book : books)
        {
            out << book->printBook();
        }
        out << "Unused ids:";
        for(auto id : unusedBooksID)
        {
            out << " " << id;
        }
        out << "\n";
    }
}

void ArticleDatabase::saveGamesDB()
{
    std::sort(games.begin(), games.end(), [](Game* left, Game* right) {
        return left->getID() < right->getID();});
    QFile file;
    file.setFileName("gamesDB.txt");
    file.open(QIODevice::WriteOnly);
    if(file.exists())
    {
        QTextStream out(&file);
        for(auto game : games)
        {
            out << game->printGame();
        }
        out << "Unused ids:";
        for(auto id : unusedGamesID)
        {
            out << " " << id;
        }
        out << "\n";
    }
}

void ArticleDatabase::saveMoviesDB()
{
    std::sort(movies.begin(), movies.end(), [](Movie* left, Movie* right) {
        return left->getID() < right->getID();});
    QFile file;
    file.setFileName("moviesDB.txt");
    file.open(QIODevice::WriteOnly);
    if(file.exists())
    {
        QTextStream out(&file);
        for(auto movie : movies)
        {
            out << movie->printMovie();
        }
        out << "Unused ids:";
        for(auto id : unusedMoviesID)
        {
            out << " " << id;
        }
        out << "\n";
    }
}

void ArticleDatabase::saveDatabase()
{
    saveBooksDB();
    saveGamesDB();
    saveMoviesDB();
}

QVector<Book*> ArticleDatabase::getBooksDB()
{
    return books;
}

QVector<Game*> ArticleDatabase::getGamesDB()
{
    return games;
}

QVector<Movie*> ArticleDatabase::getMoviesDB()
{
    return movies;
}

QVector <int> ArticleDatabase::getUnusedBooksId()
{
    return unusedBooksID;
}

QVector <int> *ArticleDatabase::getUnusedGamesId()
{
    return &unusedGamesID;
}

QVector <int> *ArticleDatabase::getUnusedMoviesId()
{
    return &unusedMoviesID;
}

void ArticleDatabase::addBook(Book *newBook)
{
    books.push_back(newBook);
}

void ArticleDatabase::addGame(Game *newGame)
{
    games.push_back(newGame);
}

void ArticleDatabase::addMovie(Movie *newMovie)
{
    movies.push_back(newMovie);
}

void ArticleDatabase::deleteBook(QString name)
{
    int pos = 0;
    for(auto book : books)
    {
        if(book->getName()==name)
        {
            break;
        }
        pos++;
    }
    if(pos < books.size())
    {
        unusedBooksID.push_back(books.at(pos)->getID());
    }
    if(unusedBooksID.size()>1)
    {
        std::sort(unusedBooksID.begin(),unusedBooksID.end());
    }
    books.removeAt(pos);
}

void ArticleDatabase::deleteGame(QString name)
{
    int pos = 0;
    for(auto game : games)
    {
        if(game->getName()==name)
        {
            break;
        }
        pos++;
    }
    if(pos < games.size())
    {
        unusedGamesID.push_back(games.at(pos)->getID());
    }
    if(unusedGamesID.size()>1)
    {
        std::sort(unusedGamesID.begin(),unusedGamesID.end());
    }
    games.removeAt(pos);
}

void ArticleDatabase::deleteMovie(QString name)
{
    int pos = 0;
    for(auto movie : movies)
    {
        if(movie->getName()==name)
        {
            break;
        }
        pos++;
    }
    if(pos < movies.size())
    {
        unusedMoviesID.push_back(movies.at(pos)->getID());
    }
    if(unusedMoviesID.size()>1)
    {
        std::sort(unusedMoviesID.begin(),unusedMoviesID.end());
    }
    movies.removeAt(pos);
}

Book* ArticleDatabase::findBook(QString name)
{
    Book *temp = books.front();
    for(Book *book : books)
    {
        if(book->getName()==name)
        {
            temp = book;
            break;
        }
    }
    return temp;
}

Game* ArticleDatabase::findGame(QString name)
{
    auto *temp = games.front();
    for(Game* game : games)
    {
        if(game->getName()==name)
        {
            temp = game;
            break;
        }
    }
    return temp;
}

Movie* ArticleDatabase::findMovie(QString name)
{
    auto *temp = movies.front();
    for(Movie* movie : movies)
    {
        if(movie->getName()==name)
        {
            temp = movie;
            break;
        }
    }
    return temp;
}

Book* ArticleDatabase::findBook(int id)
{
    Book *temp = books.front();
    for(Book *book : books)
    {
        if(book->getID()==id)
        {
            temp = book;
            break;
        }
    }
    return temp;
}

Game* ArticleDatabase::findGame(int id)
{
    auto *temp = games.front();
    for(Game* game : games)
    {
        if(game->getID()==id)
        {
            temp = game;
            break;
        }
    }
    return temp;
}

Movie* ArticleDatabase::findMovie(int id)
{
    auto *temp = movies.front();
    for(Movie* movie : movies)
    {
        if(movie->getID()==id)
        {
            temp = movie;
            break;
        }
    }
    return temp;
}
