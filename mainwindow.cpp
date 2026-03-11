#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QDesktopServices"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // create dialog window with the main window as parent
    aboutDialog = new AboutDialog(this);
    // connect help menu entries
    QObject::connect(ui->actionReport, SIGNAL(triggered()), this, SLOT(openBugReport()));
    QObject::connect(ui->actionDiscord, SIGNAL(triggered()), this, SLOT(openDiscord()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAboutDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openBugReport()
{
    QDesktopServices::openUrl( QString("https://github.com/spydragon/Quartzite/issues") );
}

void MainWindow::openDiscord()
{
    QDesktopServices::openUrl( QString("https://discord.gg/fsbcnZgzfa") );
}

void MainWindow::openAboutDialog()
{
    aboutDialog->show();
}
