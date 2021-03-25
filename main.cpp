#include "application.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Application w;
    w.show();
    return app.exec();
}
