#include "application.h"
#include <QApplication>
#include <stock.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Application window;
    window.show();
    return app.exec();
}
