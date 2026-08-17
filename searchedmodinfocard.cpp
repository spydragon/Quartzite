#include "searchedmodinfocard.h"
#include "./ui_searchedmodinfocard.h"
#include "mainwindow.h"

SearchedModInfoCard::SearchedModInfoCard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SearchedModInfoCard)
{
    QString description;
    QString icon;
    ui->setupUi(this);
}

SearchedModInfoCard::~SearchedModInfoCard()
{
    delete ui;
}

void SearchedModInfoCard::on_AddMod_Button_clicked()
{
    MainWindow *mainWin = qobject_cast<MainWindow*>(window());
    if (mainWin) {
        mainWin->AddNewModToList();
    }
}

void SearchedModInfoCard::modName(const QString &text) {
    ui->modName->setText(text);
}

void SearchedModInfoCard::modAuthorName(const QString &text) {
    ui->authorName->setText(text);
}