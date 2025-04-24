#ifndef COLORTHEMEMANAGER_H
#define COLORTHEMEMANAGER_H

#include <raylib.h>
#include <GUI/Button.h>
#include <GUI/ColorTheme.h>

class ColorThemeManager {
public:
    ColorThemeManager();

    void setColorTheme();
    void applyTheme(ColorTheme theme);
    void update();
    void draw();
public:
    bool isTheme = false;
    bool isUpdate = true;
private:
    Button settingTheme;
    Rectangle panel;
    Button def;
    Button sunny;
    Button rltech;
    Button lavanda;
    Button enefete;
    Button dark;
    Button cyber;
    Button candy;
    Button terminal;
    Button bluish;
};

void LoadFontsAndTextures();
void UnloadFontsAndTextures();

#endif