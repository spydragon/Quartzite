#include "searchedmodinfocard.h"
#include "./ui_searchedmodinfocard.h"
#include "mainwindow.h"

SearchedModInfoCard::SearchedModInfoCard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SearchedModInfoCard)
{
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
