#ifndef SETTINGS_H
#define SETTINGS_H

#include "colorThemes.h"
#include <QDialog>
#include <QSettings>
#include <QCloseEvent>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
    QSettings uiConf;

    QString currentThemeId;

    void initializeTheme();
    void applyTheme(QString themeId);

private slots:
    void onOkClicked();
    void onApplyClicked();
    void onCancelClicked();

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // SETTINGS_H
