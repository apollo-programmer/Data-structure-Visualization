#pragma once

#include "raylib.h"

class Button{
    public:
        Button();
        void setTexture(const char* normal, const char* hovered, const char* pressed);
        void setPosition(Vector2 position);
        void setSize();
        void setText(const char* text);
        void update();

        void drawTexture(Vector2 position);
        void drawText(const char* text, Vector2 position, int fontSize, Color color);

        bool isPressed();
        bool isHovered();

        int measureText(const char* text, int fontSize) const;
    private:
        Texture2D texture;
        Texture2D normalTexture;
        Texture2D hoveredTexture;
        Texture2D pressedTexture;
        Vector2 position;
        Vector2 size;
        const char* text;
};
