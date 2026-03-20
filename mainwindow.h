#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./settings.h"
#include "./aboutdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /*
     * Opens a pop-up box that allows the user to change the application settings.
     */
    void openSettings();

    /*
     * Opens a link to the issue tracker in the default web browser.
     */
    void openBugReport();

    /*
     * Opens an invite to the modding server in the default web browser.
     */
    void openDiscord();

    /*
     * Opens a pop-up box that displays the essential information about the application.
     */
    void openAboutDialog();

    /*
     * Switches to a specific modding profile
     */
    void switchProfile(QString name);

    /*
     * Adds new mod to install list
     */
    void AddNewModToList();

private slots:

    void on_PinnedModsShelf_Button_clicked();

    void AddSearchedModResult();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Settings *settings;
    AboutDialog *aboutDialog;

    /*
     * Initializes the list of available profiles
     */
    void initProfiles();

    /*
     * Creates a new profile entry in the drop-down menu
     */
    void addProfileEntry(QString name);
};
#endif // MAINWINDOW_H
