#ifndef COLORTHEMES_H
#define COLORTHEMES_H

#include <vector>
#include <utility>
#include <QString>
#include <QMap>
#include <QMenu>

#define defaultTheme "Dark Rock"

struct Theme {
    std::vector<std::pair<QString, QString>> colors; // color definitions
};

static const Theme darkRock = {
    {
        {"COLOR_TEXT", "#ffffff"},
        {"COLOR_BACKGROUND1", "#1f100d"},
        {"COLOR_BACKGROUND2", "#471a0a"},
        {"COLOR_ACCENT_NORMAL", "#471a0a"},
        {"COLOR_ACCENT_HOVER", "#732a10"},
        {"COLOR_ACCENT_TEXT_HOVER", "#ffffff"},
        {"COLOR_ACCENT_BORDER", "#732a10"},
        {"COLOR_PLAY_NORMAL", "#008800"},
        {"COLOR_PLAY_HOVER", "#00bb00"},
        {"COLOR_PLAY_BORDER", "#00bb00"},
        {"COLOR_PLAY_TEXT_NORMAL", "#ffffff"},
        {"COLOR_PLAY_TEXT_HOVER", "#ffffff"},
    }
};

static const Theme lightRock = {
    {
        {"COLOR_TEXT", "#301e0f"},
        {"COLOR_BACKGROUND1", "#e3daca"},
        {"COLOR_BACKGROUND2", "#9c9491"},
        {"COLOR_ACCENT_NORMAL", "#9c9491"},
        {"COLOR_ACCENT_HOVER", "#b7b1ae"},
        {"COLOR_ACCENT_TEXT_HOVER", "#301e0f"},
        {"COLOR_ACCENT_BORDER", "#9c9491"},
        {"COLOR_PLAY_NORMAL", "#32cc32"},
        {"COLOR_PLAY_HOVER", "#54ee54"},
        {"COLOR_PLAY_BORDER", "#54ee54"},
        {"COLOR_PLAY_TEXT_NORMAL", "#000000"},
        {"COLOR_PLAY_TEXT_HOVER", "#000000"},
    }
};

static const Theme console = {
    {
        {"COLOR_TEXT", "#ffffff"},
        {"COLOR_BACKGROUND1", "#000000"},
        {"COLOR_BACKGROUND2", "#ffffff"},
        {"COLOR_ACCENT_NORMAL", "#000000"},
        {"COLOR_ACCENT_HOVER", "#ffffff"},
        {"COLOR_ACCENT_TEXT_HOVER", "#000000"},
        {"COLOR_ACCENT_BORDER", "#ffffff"},
        {"COLOR_PLAY_NORMAL", "#ffffff"},
        {"COLOR_PLAY_HOVER", "#000000"},
        {"COLOR_PLAY_BORDER", "#ffffff"},
        {"COLOR_PLAY_TEXT_NORMAL", "#000000"},
        {"COLOR_PLAY_TEXT_HOVER", "#ffffff"},
    }
};

static const Theme watermelon = {
    {
        {"COLOR_TEXT", "#ffffff"},
        {"COLOR_BACKGROUND1", "#072907"},
        {"COLOR_BACKGROUND2", "#0d7a0d"},
        {"COLOR_ACCENT_NORMAL", "#0d7a0d"},
        {"COLOR_ACCENT_HOVER", "#880000"},
        {"COLOR_ACCENT_TEXT_HOVER", "#ffffff"},
        {"COLOR_ACCENT_BORDER", "#0d7a0d"},
        {"COLOR_PLAY_NORMAL", "#880000"},
        {"COLOR_PLAY_HOVER", "#cc0000"},
        {"COLOR_PLAY_BORDER", "#cc0000"},
        {"COLOR_PLAY_TEXT_NORMAL", "#ffffff"},
        {"COLOR_PLAY_TEXT_HOVER", "#ffffff"},
     }
};

const QMap<QString, Theme> availableThemes = {
    {"Dark Rock", darkRock},
    {"Light Rock", lightRock},
    {"Console", console},
    {"Watermelon", watermelon},
};

class BetterMenu : public QMenu
{
public:
    explicit BetterMenu(QWidget *parent = nullptr)
        : QMenu(parent)
    {
        setAttribute(Qt::WA_TranslucentBackground);
        setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    }
};

#endif // COLORTHEMES_H
