#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "installedmodinfocard.h"
#include "searchedmodinfocard.h"
#include "colorThemes.h"
#include "QDesktopServices"
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include <unistd.h>
#include <QImage>
#include <QLabel>

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
    // mod search debouncer
    modSearchManager = new QNetworkAccessManager(this);

    QTimer* debounceTimer = new QTimer(this);
    debounceTimer->setSingleShot(true);
    debounceTimer->setInterval(750);
    QObject::connect(ui->ThunderstoreSearch, &QLineEdit::textEdited, this, [=]() {
        debounceTimer->start();
    });
    QObject::connect(debounceTimer, &QTimer::timeout, this, [this]() {
        SearchForMods();
    });

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

QNetworkReply* MainWindow::GetApi(QString apiType) {
    if (apiType == "Search") {
        QString searchURL = "https://thunderstore.io/api/cyberstorm/listing/rumble/";
        if (ui->ThunderstoreSearch->text() != "")
        {
            searchURL = searchURL + "?q=" + ui->ThunderstoreSearch->text();
        }
        QNetworkRequest request{QUrl(searchURL)};
        return modSearchManager->get(request);
    }
}

void MainWindow::UrlImageToLabel(QString url, QLabel *label) {
    QNetworkRequest imageRequest{QUrl(url)};
    QNetworkReply *imageReply = modSearchManager->get(imageRequest);
    QObject::connect(imageReply, &QNetworkReply::finished, this, [=]() {
        QByteArray imageData = imageReply->readAll();
        QPixmap icon;
        icon.loadFromData(imageData);
        imageReply->deleteLater();
        label->setPixmap(icon);
    });
}

void MainWindow::SearchForMods()
{
    QNetworkReply *result = GetApi("Search");
    QObject::connect(result, &QNetworkReply::finished, this, [=]() {
        QByteArray resultData = result->readAll();
        QJsonParseError error;
        QJsonDocument jsonData = QJsonDocument::fromJson( resultData, &error);
        QJsonObject resultJson = jsonData.object();
        AddSearchedModResults(resultJson);
        result->deleteLater();
    });
}

void MainWindow::AddSearchedModResults(QJsonObject modSearchJson)
{
    // I had to ask AI how to delete elements. this is not human code
    QLayout *layout = ui->SearchedModList_Box->layout();
    if (layout) {
        for (int i = layout->count() - 1; i >= 0; --i) {
            QLayoutItem *item = layout->itemAt(i);

            if (item->spacerItem() || item->widget() == ui->PinnedModsShelf_Scroll) {
                continue;
            }

            if (QWidget *widget = item->widget()) {
                layout->removeItem(item);
                widget->deleteLater();
                delete item;
            }
        }
    }


    QJsonArray results = modSearchJson["results"].toArray();
    int resultLength = results.size();
    double resultCount = modSearchJson["count"].toDouble();
    qDebug() << resultCount;
    for (int index = 0; index < resultLength; index++) {
        QString name = modSearchJson["results"][index]["name"].toString();
        QString authorName = modSearchJson["results"][index]["namespace"].toString();
        QString imageURL = modSearchJson["results"][index]["icon_url"].toString();
        QString description = modSearchJson["results"][index]["description"].toString();
        SearchedModInfoCard *ModCard = new SearchedModInfoCard(this);
        QLabel* imageLabel = ModCard->GetLabel();
        ModCard->modName(name);
        ModCard->modAuthorName(authorName);
        ModCard->modImage(imageURL, imageLabel);
        ModCard->modDescription(description);
        ModCard->setAttribute(Qt::WA_StyledBackground);
        imageLabel->setScaledContents(true);
        ui->SearchedModList_Box->layout()->addWidget(ModCard);
    };
}

