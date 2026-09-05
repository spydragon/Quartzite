#ifndef SEARCHEDMODINFOCARD_H
#define SEARCHEDMODINFOCARD_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class SearchedModInfoCard;
}

class SearchedModInfoCard : public QWidget
{
    Q_OBJECT

public:
    void modName(const QString &text);
    void modAuthorName(const QString &text);
    void modImage(const QString icon, QLabel* label);
    void modDescription(const QString &text);
    explicit SearchedModInfoCard(QWidget *parent = nullptr);
    ~SearchedModInfoCard();
    QLabel* GetLabel();

private slots:
    void on_AddMod_Button_clicked();

private:
    Ui::SearchedModInfoCard *ui;
    QString formatCapitalizedString(const QString &input);
};

#endif // SEARCHEDMODINFOCARD_H
