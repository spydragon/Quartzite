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
    explicit SearchedModInfoCard(QWidget *parent = nullptr);
    ~SearchedModInfoCard();



private slots:
    void on_AddMod_Button_clicked();

private:
    Ui::SearchedModInfoCard *ui;
};

#endif // SEARCHEDMODINFOCARD_H
