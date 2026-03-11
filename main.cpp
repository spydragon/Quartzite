#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationVersion(APP_VERSION);
    MainWindow w;
    w.show();
    return a.exec();
}
