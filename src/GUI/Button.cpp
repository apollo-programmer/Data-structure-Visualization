#include <GUI/Button.h>

Button::Button(){}

void Button::setPosition(Vector2 position){
    this->position=position;
    this->rectangle = {position.x - size.x/2,position.y-size.y/2,size.x,size.y};
}

void Button::setSize(Vector2 size){
    this->size=size;
    this->rectangle = {position.x - size.x/2,position.y-size.y/2,size.x,size.y};
}

void Button::setText(const char* text, int fontSize){
    this->text = text;
    this->fontSize=fontSize;
}

void Button::update(){
    if(this->isTexture){
        switch(currentTheme){
            case StyleTheme::DEF:
                normal=buttonTheme.DefaultNormal;
                hovered=buttonTheme.DefaultHovered;
                pressed=buttonTheme.DefaultPressed;
                break;
            case StyleTheme::SUNNY:
                normal=buttonTheme.SunnyNormal;
                hovered=buttonTheme.SunnyHovered;
                pressed=buttonTheme.SunnyPressed;
                break;
            case StyleTheme::RLTECH:
                normal=buttonTheme.RltechNormal;
                hovered=buttonTheme.RltechHovered;
                pressed=buttonTheme.RltechPressed;
                break;
            case StyleTheme::LAVANDA:
                normal=buttonTheme.LavandaNormal;
                hovered=buttonTheme.LavandaHovered;
                pressed=buttonTheme.LavandaPressed;
                break;
            case StyleTheme::ENEFETE:
                normal=buttonTheme.EnefeteNormal;
                hovered=buttonTheme.EnefeteHovered;
                pressed=buttonTheme.EnefetePressed;
                break;
            case StyleTheme::DARK:
                normal=buttonTheme.DarkNormal;
                hovered=buttonTheme.DarkHovered;
                pressed=buttonTheme.DarkPressed;
                break;
            case StyleTheme::CYBER:
                normal=buttonTheme.CyberNormal;
                hovered=buttonTheme.CyberHovered;
                pressed=buttonTheme.CyberPressed;
                break;
            case StyleTheme::CANDY:
                normal=buttonTheme.CandyNormal;
                hovered=buttonTheme.CandyHovered;
                pressed=buttonTheme.CandyPressed;
                break;
            case StyleTheme::TERMINAL:
                normal=buttonTheme.TerminalNormal;
                hovered=buttonTheme.TerminalHovered;
                pressed=buttonTheme.TerminalPressed;
                break;
            case StyleTheme::BLUISH:
                normal=buttonTheme.BluishNormal;
                hovered=buttonTheme.BluishHovered;
                pressed=buttonTheme.BluishPressed;
                break;
        }
    }
    if(this->selected){
        color=buttonPressed;
        outlineColor=outlineButtonPressedColor;
        textColor=textButtonPressed;
    }
    else if(this->isHovered()){
        if(this->isPressed()){
            color=buttonPressed;
            outlineColor=outlineButtonPressedColor;
            textColor=textButtonPressed;
        }else{
            color=buttonHovered;
            outlineColor=outlineButtonHoveredColor;
            textColor=textButtonHovered;
        }
    }
    else{
        color=buttonNormal;
        outlineColor=outlineButtonColor;
        textColor=textButtonNormal;
    }
}

void Button::update(ColorTheme theme){
    if(this->isTexture){
        switch(currentTheme){
            case StyleTheme::DEF:
                normal=buttonTheme.DefaultNormal;
                hovered=buttonTheme.DefaultHovered;
                pressed=buttonTheme.DefaultPressed;
                break;
            case StyleTheme::SUNNY:
                normal=buttonTheme.SunnyNormal;
                hovered=buttonTheme.SunnyHovered;
                pressed=buttonTheme.SunnyPressed;
                break;
            case StyleTheme::RLTECH:
                normal=buttonTheme.RltechNormal;
                hovered=buttonTheme.RltechHovered;
                pressed=buttonTheme.RltechPressed;
                break;
            case StyleTheme::LAVANDA:
                normal=buttonTheme.LavandaNormal;
                hovered=buttonTheme.LavandaHovered;
                pressed=buttonTheme.LavandaPressed;
                break;
            case StyleTheme::ENEFETE:
                normal=buttonTheme.EnefeteNormal;
                hovered=buttonTheme.EnefeteHovered;
                pressed=buttonTheme.EnefetePressed;
                break;
            case StyleTheme::DARK:
                normal=buttonTheme.DarkNormal;
                hovered=buttonTheme.DarkHovered;
                pressed=buttonTheme.DarkPressed;
                break;
            case StyleTheme::CYBER:
                normal=buttonTheme.CyberNormal;
                hovered=buttonTheme.CyberHovered;
                pressed=buttonTheme.CyberPressed;
                break;
            case StyleTheme::CANDY:
                normal=buttonTheme.CandyNormal;
                hovered=buttonTheme.CandyHovered;
                pressed=buttonTheme.CandyPressed;
                break;
            case StyleTheme::TERMINAL:
                normal=buttonTheme.TerminalNormal;
                hovered=buttonTheme.TerminalHovered;
                pressed=buttonTheme.TerminalPressed;
                break;
            case StyleTheme::BLUISH:
                normal=buttonTheme.BluishNormal;
                hovered=buttonTheme.BluishHovered;
                pressed=buttonTheme.BluishPressed;
                break;
        }
    }
    color=theme.buttonNormal;
    outlineColor=theme.outlineButtonColor;
    textColor=theme.textButtonNormal;
    if(this->selected){
        color=theme.buttonPressed;
        outlineColor=theme.outlineButtonPressedColor;
        textColor=theme.textButtonPressed;
    }
    else if(this->isHovered()){
        if(this->isPressed()){
            color=theme.buttonPressed;
            outlineColor=theme.outlineButtonPressedColor;
            textColor=theme.textButtonPressed;
        }else{
            color=theme.buttonHovered;
            outlineColor=theme.outlineButtonHoveredColor;
            textColor=theme.textButtonHovered;
        }
    }
}

void Button::drawRectangle(Vector2 recSize){
    DrawRectangle(this->position.x, this->position.y, recSize.x, recSize.y, this->color);
}

void Button::drawRectangleRounded(int roundness){
    DrawRectangleRounded(this->rectangle, roundness, 100, this->color);
}

void Button::drawOutlineRounded(int roundness, int segments, int lineThick){
    DrawRectangleRoundedLinesEx(this->rectangle, roundness, segments, lineThick, this->outlineColor);
}

void Button::setTexture(ButtonTheme theme){
    this->buttonTheme=theme;
    this->normal=theme.DefaultNormal;
    this->hovered=theme.DefaultHovered;
    this->pressed=theme.DefaultPressed;
    this->isTexture=true;
}

void Button::drawTexture(){
    if(this->selected){
        DrawTexture(this->pressed, this->position.x - this->pressed.width/2.0f, this->position.y - this->pressed.height/2.0f, WHITE);
    }
    else if(this->isHovered()){
        if(this->isPressed()){
            DrawTexture(this->pressed, this->position.x - this->pressed.width/2.0f, this->position.y - this->pressed.height/2.0f, WHITE);
        }else{
            DrawTexture(this->hovered, this->position.x - this->hovered.width/2.0f, this->position.y - this->hovered.height/2.0f, WHITE);
        }
    }
    else{
        DrawTexture(this->normal, this->position.x - this->normal.width/2.0f, this->position.y - this->normal.height/2.0f, WHITE);
    }
}

void Button::drawText(){
    Vector2 textSize = MeasureTextEx(buttonFont, this->text, this->fontSize, 0);
    Vector2 textPosition = { this->position.x - textSize.x / 2.0f, this->position.y-textSize.y/2.0f };
    DrawTextEx(buttonFont, this->text, textPosition, this->fontSize, 0, this->textColor);
}

Vector2 Button::getSize(){
    return this->size;
}

Vector2 Button::getPosition(){
    return this->position;
}

int Button::getfontSize(){
    return this->fontSize;
}

bool Button::isPressed(){
    bool ispress = isActive&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {this->position.x-this->size.x/2, this->position.y-(this->size.y/2-this->fontSize/2), this->size.x, this->size.y});
    if(ispress){
        PlaySound(Resource::clickSound);
    }
    return ispress;
}

bool Button::isHovered(){
    return isActive&&CheckCollisionPointRec(GetMousePosition(), {this->position.x-this->size.x/2, this->position.y-(this->size.y/2-this->fontSize/2), this->size.x, this->size.y});
}

bool Button::isSelected(){
    return this->selected;
}

void Button::Selected(){
    this->selected = true;
}

void Button::deSelected(){
    this->selected = false;
}

void Button::setActive(){
    isActive=true;
}

void Button::deActive(){
    isActive=false;
}