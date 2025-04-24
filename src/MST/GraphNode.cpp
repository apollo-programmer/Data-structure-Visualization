#include "MST/GraphNode.h"
#include "MST/GraphEdge.h"

GraphNode::GraphNode(int data, std::vector<GraphEdge*> edge, Vector2 position)
    : data(data), edge(edge), finalPos(position) {
    this->colorChosen = nodeColor;
    this->colorNormal = nodeHighlightColor;
    this->colorCurrent = this->colorNormal;
    this->textNor = nodeTextColor;
    this->textCho = nodeHighlightTextColor;
    this->textCur = this->textNor;
    this->size = 50.0f;
    this->position = {800, 450};
}

void GraphNode::DrawNode() {
    if (this == nullptr) return;

    if(this->isVisited){
        DrawCircleV(position, size / 2, nodeHighlightColor);

        char text[16];
        snprintf(text, sizeof(text), "%d", data);
        int fontSize = 20;
        Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
        Vector2 textPos = { position.x - textSize.x / 2, position.y - textSize.y / 2 };
        DrawText(text, textPos.x, textPos.y, fontSize, nodeHighlightTextColor);
    }
    else{
        DrawCircleV(position, size / 2, nodeColor);

        char text[16];
        snprintf(text, sizeof(text), "%d", data);
        int fontSize = 20;
        Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
        Vector2 textPos = { position.x - textSize.x / 2, position.y - textSize.y / 2 };
        DrawText(text, textPos.x, textPos.y, fontSize, nodeTextColor);
    }
}

void GraphNode::UpdatePosition() {
    Vector2 mousePos = GetMousePosition();
    bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool mouseReleased = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

    float distance = Vector2Distance(mousePos, position);

    if (mousePressed && distance <= size / 2) {
        isDragging = true;
        dragOffset = Vector2Subtract(position, mousePos);
        colorCurrent = colorChosen;
    }

    if (isDragging) {
        position = Vector2Add(mousePos, dragOffset);
    }

    if (mouseReleased) {
        isDragging = false;
        //finalPos = position;
        colorCurrent = colorNormal;
    }
}