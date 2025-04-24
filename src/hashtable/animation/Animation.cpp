#include "HashTable/animation/Animation.h"

Animation::Animation(float& speed, Node* node)
    : speed(speed), node(node), curAnimation(0.0f), type(0) {}

Animation::Animation(float& speed, Node* node, Vector2 target)
    : speed(speed), node(node), target(target), curAnimation(0.0f), type(0) {}

bool Animation::DrawChosenNode() {
    if (!node) return true;
    node->isVisual = true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        // node->colorCurrent = node->colorChosen;
        // node->textCurColor = node->textChosenColor;
        node->colorCurrent = nodeHighlightColor;
        node->textCurColor = nodeHighlightTextColor;
        node->isChosen = true;
        return false;
    }
    // node->colorCurrent = node->colorNormal;
    // node->isChosen = false;
    curAnimation = 0.0f;
    return true;
}

bool Animation::DrawNormalNode(){
    if(!node) return true;
    node->isVisual = true;
    if(curAnimation < 1.0f){
        curAnimation += 1.0f;
        // node->colorCurrent = node->colorNormal;
        // node->textCurColor = node->textNorColor;
        node->colorCurrent = nodeColor;
        node->textCurColor = nodeTextColor;
        node->isChosen = false;
        return true;
    }
    return true;
}

bool Animation::DrawFadeInNode() {
    if (!node) return true;

    // Đặt isVisual = true khi bắt đầu fade in
    node->isVisual = true;

    if (curAnimation < 1.0f) {
        curAnimation += speed;
        node->colorCurrent = Fade(nodeColor, curAnimation);

        // // Tự vẽ node trong quá trình fade in
        // DrawCircle(node->position.x, node->position.y, node->size.x, node->colorCurrent);
        // DrawCircleLines(node->position.x, node->position.y, node->size.x, WHITE);
        // std::string text = std::to_string(node->data);
        // int textWidth = MeasureText(text.c_str(), 15);
        // DrawText(text.c_str(), node->position.x - textWidth / 2, node->position.y - 7, 15, WHITE);

        return false;
    }

    node->colorCurrent = nodeColor;
    return true;
}

bool Animation::DrawFadeOutNode() {
    if (!node) return true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        node->colorCurrent = Fade(nodeColor, 1.0f - curAnimation);
        return false;
    }
    node->isVisual = false; // Ẩn node sau khi fade out
    return true;
}

bool Animation::DrawMoveNodeAnimation() {
    if (!node) return true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        node->position.x = node->position.x * (1.0f - curAnimation) + node->finalPosition.x * curAnimation;
        node->position.y = node->position.y * (1.0f - curAnimation) + node->finalPosition.y * curAnimation;
        if(node->next){
            node->arrowPos = node->next->position;
        }
        else{
            node->arrowPos = node->position;
        }
        return false;
    }
    node->position = target;
    curAnimation = 0.0f;
    return true;
}

bool Animation::DrawInsertEdgeAnimation() {
    if (!node || !node->next) return true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        node->arrowPos = {node->position.x + (node->next->position.x - node->position.x) * curAnimation,
                           node->position.y + (node->next->position.y - node->position.y) * curAnimation};
        
        return false;
    }
    node->arrowPos = node->next->position;
    return true;
}

bool Animation::DrawDeleteEdgeAnimation() {
    if (!node || !node->next) return true;
    if (curAnimation > 0.0f) {
        curAnimation -= speed;
        node->arrowPos = {node->position.x + (node->next->position.x - node->position.x) * curAnimation,
                           node->position.y + (node->next->position.y - node->position.y) * curAnimation};
        
        return false;
    }
    return true;
}

bool Animation::DrawAnimation() {
    if (!node) return true;
    switch (type) {
        case 1: return DrawChosenNode();
        case 2: return DrawFadeInNode(); // DrawFadeInNode sẽ được gọi trực tiếp từ SetofAnimation
        case 3: return DrawFadeOutNode();
        case 4: return DrawMoveNodeAnimation();
        case 5: return DrawNormalNode();
        case 6: return DrawInsertEdgeAnimation();
        case 7: return DrawDeleteEdgeAnimation();
        default: return true;
    }
}