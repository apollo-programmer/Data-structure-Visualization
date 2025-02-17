#include "Button.h"

Button::Button(){}

void Button::setTexture(const char* normal, const char* hovered, const char* pressed){
    this->normalTexture = LoadTexture(normal);
    this->hoveredTexture = LoadTexture(hovered);
    this->pressedTexture = LoadTexture(pressed);
    this->texture = this->normalTexture;
}

void Button::setPosition(Vector2 position){
    this->position = position;
}

void Button::setSize(){
    this->size.x = this->texture.width;
    this->size.y = this->texture.height;
}

void Button::setText(const char* text){
    this->text = text;
}

void Button::update(){
    if(this->isHovered()){
        if(this->isPressed()){
            this->texture = this->pressedTexture;
        }else{
            this->texture = this->hoveredTexture;
        }
    }else{
        this->texture = this->normalTexture;
    }
}

void Button::drawTexture(Vector2 position){
    DrawTexture(this->texture, position.x, position.y, WHITE);
}

void Button::drawText(const char* text, Vector2 position, int fontSize, Color color){
    DrawText(text, position.x, position.y, fontSize, color);
}

bool Button::isPressed(){
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {this->position.x, this->position.y, this->size.x, this->size.y});
}

bool Button::isHovered(){
    return CheckCollisionPointRec(GetMousePosition(), {this->position.x, this->position.y, this->size.x, this->size.y});
}

int Button::measureText(const char* text, int fontSize) const{
    return MeasureText(text, fontSize);
}