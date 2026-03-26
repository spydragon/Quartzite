#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "installedmodinfocard.h"
#include "searchedmodinfocard.h"
#include "colorThemes.h"
#include "QDesktopServices"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // create settings window with the main window as parent
    settings = new Settings(this);
    // create dialog window with the main window as parent
    aboutDialog = new AboutDialog(this);
    // connect edit menu entries
    QObject::connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(openSettings()));
    // connect help menu entries
    QObject::connect(ui->actionReport, SIGNAL(triggered()), this, SLOT(openBugReport()));
    QObject::connect(ui->actionDiscord, SIGNAL(triggered()), this, SLOT(openDiscord()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAboutDialog()));
    // force all menus to be properly drawn on all operating systems
    for (QWidget *w : QApplication::topLevelWidgets())
    {
        if (QMenu *menu = qobject_cast<QMenu*>(w))
        {
            menu->setAttribute(Qt::WA_TranslucentBackground);
            menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
        }
    }
    ui->profileChoice->setMenu(new BetterMenu(this));

    initProfiles();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSettings()
{
    settings->show();
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

void MainWindow::initProfiles()
{
    // make it so that clicking on the button opens the profile list
    QObject::connect(ui->profileChoice, SIGNAL(clicked()), ui->profileChoice, SLOT(showMenu()));
    addProfileEntry("Default"); // TODO read from config file
}

void MainWindow::addProfileEntry(QString name)
{
    QAction *action = ui->profileChoice->menu()->addAction(name);
    // when the entry is selected by the user, trigger profile switching
    QObject::connect(action, &QAction::triggered, this, [this, name]()
                     {
                         switchProfile(name);
                     });
}

void MainWindow::switchProfile(QString name)
{
    ui->profileChoice->setText(name);
}

void MainWindow::on_PinnedModsShelf_Button_clicked()
{
    static int originalHeight = -1;

    QScrollArea* PinnedModsShelf = ui->PinnedModsShelf_Scroll;

    if (originalHeight == -1) {
        originalHeight = PinnedModsShelf->height();
    }

    if (PinnedModsShelf->height() == 0) {
        PinnedModsShelf->setFixedHeight(originalHeight);
    } else {
        PinnedModsShelf->setFixedHeight(0);
    }

}

 void MainWindow::AddNewModToList()
{
    InstalledModInfoCard *ModCard = new InstalledModInfoCard(this);
    ModCard->setAttribute(Qt::WA_StyledBackground);
    ui->InstalledModList_Box->layout()->addWidget(ModCard);
}

void MainWindow::AddSearchedModResult()
{
    SearchedModInfoCard *ModCard = new SearchedModInfoCard(this);
    ModCard->setAttribute(Qt::WA_StyledBackground);
    ui->SearchedModList_Box->layout()->addWidget(ModCard);
}

void MainWindow::on_pushButton_clicked()
{
    AddSearchedModResult();
    AddNewModToList();
}

