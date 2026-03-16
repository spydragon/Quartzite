#include "installedmodinfocard.h"
#include "./ui_installedmodinfocard.h"

InstalledModInfoCard::InstalledModInfoCard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InstalledModInfoCard)
{
    ui->setupUi(this);
}

InstalledModInfoCard::~InstalledModInfoCard()
{
    delete ui;
}
