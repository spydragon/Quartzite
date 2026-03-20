#include "settings.h"
#include "ui_settings.h"
#include <QStandardPaths>
#include <QDir>
#include <QStyleFactory>
#include <QComboBox>
#include <QPushButton>
#include <QAbstractItemView>

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings)
    , uiConf( QStandardPaths::writableLocation( QStandardPaths::AppConfigLocation)+"/ui.conf", QSettings::IniFormat)
{
    ui->setupUi(this);
    QString Configdir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(Configdir);
    uiConf.setPath(QSettings::IniFormat, QSettings::UserScope, Configdir+"/ui.conf");
    initializeTheme();

    // connect the 3 buttons at the bottom
    QObject::connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(onOkClicked()));
    QObject::connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this, SLOT(onApplyClicked()));
    QObject::connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(onCancelClicked()));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::applyTheme(QString themeId)
{
    currentThemeId = themeId;
    Theme theme = availableThemes[themeId];
    QFile file(":/resources/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QString style = file.readAll();
        for (const auto &c : theme.colors)
        {
            style.replace("@" + c.first, c.second);
        }
        qApp->setStyle(QStyleFactory::create("Fusion"));
        qApp->setStyleSheet(style);
    }
    ui->themeChoice->setText(themeId);
}

void Settings::initializeTheme()
{
    ui->themeChoice->setMenu(new BetterMenu(this));
    QObject::connect(ui->themeChoice, SIGNAL(clicked()), ui->themeChoice, SLOT(showMenu()));
    for (auto option = availableThemes.constBegin(); option != availableThemes.constEnd(); ++option)
    {
        QAction *action = ui->themeChoice->menu()->addAction(option.key());
        QObject::connect(action, &QAction::triggered, this, [this, option]()
                         {
            applyTheme(option.key());
                         });
    }


    // Try to read saved theme
    QString themeId = uiConf.value("ui/theme", defaultTheme).toString();
    if (!availableThemes.contains(themeId))
    {
        themeId = defaultTheme; // use default
        uiConf.setValue("ui/theme", themeId); // save to file
        uiConf.sync();  // force immediate write
    }
    Theme currentTheme = availableThemes[themeId];
    applyTheme(themeId);
    currentThemeId = themeId;
}

void Settings::onOkClicked()
{
    applyTheme(currentThemeId);
    uiConf.setValue("ui/theme", currentThemeId);
    uiConf.sync();
}

void Settings::onApplyClicked()
{
    applyTheme(currentThemeId);
}

void Settings::onCancelClicked()
{
    // Reset combo box and theme
    QString savedThemeId = uiConf.value("ui/theme", defaultTheme).toString();
    applyTheme(savedThemeId);
    this->close();
}

void Settings::closeEvent(QCloseEvent *event)
{
    onCancelClicked();  // run the same logic as cancel
    event->accept();
}
