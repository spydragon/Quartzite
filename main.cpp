#include "mainwindow.h"
#include "colorThemes.h"

#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include <QStyleFactory>

void loadStyleSheet(QString path)
{
    // TODO choose theme depending on config
    const std::vector<std::pair<QString, QString>> currentTheme = dark_rock;

    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QString style = file.readAll();
        for (const auto &c : currentTheme)
        {
            style.replace("@" + c.first, c.second);
        }
        qApp->setStyle(QStyleFactory::create("Fusion"));
        qApp->setStyleSheet(style);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationVersion(APP_VERSION);
    QFontDatabase::addApplicationFont(":/resources/Sayfull.ttf");
    loadStyleSheet(":/resources/style.qss");
    MainWindow w;
    w.show();
    return a.exec();
}
