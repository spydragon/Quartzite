#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    // make it so that the "close" button closes the dialog window
    QObject::connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(accept()));
    // set the title label to display the name and version of the application
    ui->title->setText(QString("Quartzite v")+qApp->applicationVersion());
    ui->description->setSource(QUrl("qrc:/resources/about.html"));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
