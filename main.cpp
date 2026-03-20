#include "mainwindow.h"
#include "colorThemes.h"

#include <QApplication>
#include <QFontDatabase>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationVersion(APP_VERSION);
    QFontDatabase::addApplicationFont(":/resources/Sayfull.ttf");
    //loadStyleSheet(":/resources/style.qss");
    MainWindow w;
    w.show();
    return a.exec();
}
