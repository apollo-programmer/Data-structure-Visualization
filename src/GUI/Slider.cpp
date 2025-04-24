#include <GUI/Slider.h>

int speed = 200;
float delayTime = 0.5f;

Slider::Slider(float minVal, float maxVal, float initialVal, int steps){
    this->position={400 ,controllerPosition.y-controllerSize.y/2.0f};
    this->width=controllerPosition.x-controllerSize.x/2.0f-400; 
    this->height=controllerSize.y; 
    this->box = {position.x, position.y, width, height};
    this->sliderRect = {box.x + 20, box.y+box.height/2.0f-20, box.width-40, 12}; 
    this->minVal=minVal; 
    this->maxVal=maxVal;
    this->val=initialVal;
    this->knobSize={10, sliderRect.height + 10};
    this->isDragging=false;
    this->numSteps=steps;
}

void Slider::Update(){
    Vector2 mousePos = GetMousePosition();

    // Kiểm tra nếu người dùng nhấn chuột trái vào nút kéo
    Rectangle knobRect = {sliderRect.x + (val - minVal) / (maxVal - minVal) * (width - knobSize.x), 
                            sliderRect.y - knobSize.y / 2, knobSize.x, knobSize.y};

    // Kiểm tra nhấn trực tiếp vào thanh trượt
    if (CheckCollisionPointRec(mousePos, sliderRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        float newX = mousePos.x - sliderRect.x;
        newX = std::max(0.0f, std::min(newX, width - knobSize.x)); // Giới hạn trong thanh trượt

            // Chế độ mượt mà: giá trị thay đổi liên tục
        val = minVal + (newX / (width - knobSize.x)) * (maxVal - minVal);
        speed=defaultSpeed*val;
        delayTime = defaultDelayTime/ val;
    }

    // Kiểm tra nếu người dùng nhấn chuột trái vào nút kéo để kéo
    if (CheckCollisionPointRec(mousePos, knobRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        isDragging = true;
    }

    // Cập nhật giá trị khi kéo
    if (isDragging) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isDragging = false;
        } else {
            float newX = mousePos.x - sliderRect.x;
            newX = std::max(0.0f, std::min(newX, sliderRect.width - knobSize.x));
            val = minVal + (newX / (sliderRect.width - knobSize.x)) * (maxVal - minVal);
            speed=defaultSpeed*val;
            delayTime = defaultDelayTime/ val;
        }
    }
}

void Slider::Draw(){
    DrawRectangleRounded(box, 0, 0, buttonNormal);
    DrawRectangleLinesEx(box, 3, outlineButtonColor);
    DrawRectangleRounded(sliderRect, 100, 0, outlineButtonColor);
    float knobX = sliderRect.x + (val - minVal) / (maxVal - minVal) * (sliderRect.width - knobSize.x);
    DrawRectangleRounded({knobX, sliderRect.y - knobSize.y / 4.0f, knobSize.x, knobSize.y},80,0, outlineButtonPressedColor);
    std::string defaultSpeedText = "Speed: " + std::to_string(val).substr(0, 4);
    DrawText(defaultSpeedText.c_str(), sliderRect.x, sliderRect.y + sliderRect.height + 10, 20, textButtonNormal);
}

void Slider::reset(){
    val=1;
    speed=defaultSpeed*val;
    delayTime = defaultDelayTime/ val;
}