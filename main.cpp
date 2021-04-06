#include "application.h"
#include <QApplication>
#include <stock.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Book x("nazwa","Tolkien");
    x.addStock();
    Application window;
    window.show();
    return app.exec();
}
