#include "searchedmodinfocard.h"
#include "./ui_searchedmodinfocard.h"
#include "mainwindow.h"
#include <QLabel>

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

QLabel* SearchedModInfoCard::GetLabel() {
    return ui->Image;
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

void SearchedModInfoCard::modImage(const QString icon, QLabel* label) {
    MainWindow *mainWin = qobject_cast<MainWindow*>(window());
    mainWin->UrlImageToLabel(icon, label);
}