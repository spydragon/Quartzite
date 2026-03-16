#ifndef INSTALLEDMODINFOCARD_H
#define INSTALLEDMODINFOCARD_H

#include <QWidget>

namespace Ui {
class InstalledModInfoCard;
}

class InstalledModInfoCard : public QWidget
{
    Q_OBJECT

public:
    explicit InstalledModInfoCard(QWidget *parent = nullptr);
    ~InstalledModInfoCard();

private:
    Ui::InstalledModInfoCard *ui;
};

#endif // INSTALLEDMODINFOCARD_H
