#include <GUI/InputBox.h>

InputBox::InputBox(float x, float y, float width, float height, int maxLen, Color boxCol, Color txtCol)
    : box{x, y, width, height}, maxLength(maxLen), isActive(false), boxColor(boxCol), textColor(txtCol), blinkTimer(0), showCursor(true) {}

void InputBox::Update() {
    if (CheckCollisionPointRec(GetMousePosition(), box) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isActive = true;
    } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isActive = false;
    }

    if(CheckCollisionPointRec(GetMousePosition(), box)){
        isMouseonBox = true;
    }
    else{
        isMouseonBox = false;
    }

    if (isActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32 && key <= 126) && (MeasureTextEx(inputBoxFont, text.c_str(), inputBoxFontSize, 0).x + MeasureTextEx(inputBoxFont, std::string(1, key).c_str(), inputBoxFontSize, 0).x) < box.width - 10) {
                text += static_cast<char>(key);
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !text.empty()) {
            text.pop_back();
        }
    }

    if(isMouseonBox){
        boxColor = GRAY;
    }
    else{
        boxColor = LIGHTGRAY;
    }
    
    blinkTimer += GetFrameTime();
    if (blinkTimer >= 0.5f) {
        blinkTimer = 0;
        showCursor = !showCursor;
    }
}

void InputBox::Draw() {
    DrawRectangleRec(box, (isActive||text!="") ? WHITE : boxColor);
    DrawRectangleLinesEx(box, 3, outlineButtonColor);
    DrawTextEx(inputBoxFont, text.c_str(), {box.x + 5, box.y + box.height / 4.0f}, inputBoxFontSize, 0, textColor);
    DrawTextEx(inputBoxNameFont, nameBox.c_str(), {box.x, box.y - inputBoxNameFontSize}, inputBoxNameFontSize, 0, outlineButtonColor);
    if (isActive && showCursor) {
        DrawTextEx(inputBoxFont, "|", {box.x + 5 + MeasureTextEx(inputBoxFont, text.c_str(), inputBoxFontSize, 0).x, box.y + box.height / 4.0f}, inputBoxFontSize, 0, BLACK);
    }
}

std::string InputBox::GetText() const {
    return text;
}

void InputBox::resetBox(){
    text="";
}

void InputBox::setText(std::string text){
    this->text=text;
}

void InputBox::setNameBox(std::string nameBox){
    this->nameBox=nameBox;
}

void InputBox::setPosition(Vector2 position){
    box.x = position.x;
    box.y = position.y;
}

void InputBox::clearText(){
    text.clear();
}