#ifndef SEARCHEDMODINFOCARD_H
#define SEARCHEDMODINFOCARD_H

#include <QWidget>

namespace Ui {
class SearchedModInfoCard;
}

class SearchedModInfoCard : public QWidget
{
    Q_OBJECT

public:
    void modName(const QString &text);
    void modAuthorName(const QString &text);
    explicit SearchedModInfoCard(QWidget *parent = nullptr);
    ~SearchedModInfoCard();

private slots:
    void on_AddMod_Button_clicked();

private:
    Ui::SearchedModInfoCard *ui;
};

#endif // SEARCHEDMODINFOCARD_H
