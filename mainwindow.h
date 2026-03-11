#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    AboutDialog *aboutDialog;
};
#endif // MAINWINDOW_H
