#include "searchedmodinfocard.h"
#include "./ui_searchedmodinfocard.h"
#include "mainwindow.h"
#include <QLabel>

SearchedModInfoCard::SearchedModInfoCard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SearchedModInfoCard)
{
    QString description;
    QString icon;
    ui->setupUi(this);
}

SearchedModInfoCard::~SearchedModInfoCard()
{
    delete ui;
}

QLabel* SearchedModInfoCard::GetLabel() {
    return ui->Image;
}

void SearchedModInfoCard::on_AddMod_Button_clicked()
{
    MainWindow *mainWin = qobject_cast<MainWindow*>(window());
    if (mainWin) {
        mainWin->AddNewModToList();
    }
}

void SearchedModInfoCard::modName(const QString &text) {
    QString name = formatCapitalizedString(text);
    ui->modName->setText(name);
}

void SearchedModInfoCard::modAuthorName(const QString &text) {
    ui->authorName->setText(text);
}

void SearchedModInfoCard::modImage(const QString icon, QLabel* label) {
    MainWindow *mainWin = qobject_cast<MainWindow*>(window());
    mainWin->UrlImageToLabel(icon, label);
}

void SearchedModInfoCard::modDescription(const QString &text) {
    ui->descriptionBlock->setText(text);
}

// this function is completely vibe coded. I didn't want to try and work out how to apply the logic for spaces before caps.
QString SearchedModInfoCard::formatCapitalizedString(const QString &input) {
    QString result;
    int n = input.length();

    // Optional optimization: reserve roughly the space we'll need
    result.reserve(n + n / 4);

    for (int i = 0; i < n; ) {
        // When we find a capital letter, identify the full sequence of capitals
        if (input.at(i).isUpper()) {
            int j = i;
            while (j < n && input.at(j).isUpper()) {
                j++;
            }

            int seqLength = j - i;
            bool isAtEnd = (j == n);

            if (isAtEnd) {
                // RULE 3: Sequence of capitals at the very end of the string
                // Add a space before the first one (unless it's the start of the string)
                if (i != 0 && !result.endsWith(' ')) {
                    result.append(' ');
                }
                // Ignore all previous rules: append the rest without any spaces
                for (int k = i; k < j; ++k) {
                    result.append(input.at(k));
                }
            }
            else if (seqLength >= 3) {
                // RULE 2: 3 or more capital letters next to each other
                // Add a space before the first capital
                if (i != 0 && !result.endsWith(' ')) {
                    result.append(' ');
                }

                // Append all capitals up to the second-to-last one
                for (int k = i; k < j - 1; ++k) {
                    result.append(input.at(k));
                }

                // Add a space before the last capital in the sequence
                if (!result.endsWith(' ')) {
                    result.append(' ');
                }
                result.append(input.at(j - 1));
            }
            else {
                // RULE 1: 1 or 2 capital letters next to each other
                // Add a space before EVERY capital in this sequence
                for (int k = i; k < j; ++k) {
                    if (k != 0 && !result.endsWith(' ')) {
                        result.append(' ');
                    }
                    result.append(input.at(k));
                }
            }

            // Move the main index past this uppercase sequence
            i = j;
        }
        else {
            // Lowercase letters (or existing spaces/symbols) are appended as-is
            result.append(input.at(i));
            i++;
        }
    }

    return result;
}