#include "MST/GraphEdge.h"

GraphEdge::GraphEdge(std::vector<GraphNode*> nodes, int weight)
    : nodes(nodes), weight(weight) {
    colorNormal = lineColor;
    colorChosen = nodeHighlightColor;
    colorFlur = Fade(lineColor, 0.5f);
    currentColor = colorNormal;
    thick = 3.0f;
}

void GraphEdge::DrawEdge() {    
    if (nodes.size() != 2) return;
    if(this->isChosen){
        DrawLineEx(nodes[0]->position, nodes[1]->position, thick, outlineButtonPressedColor);
        Vector2 mid = {(nodes[0]->position.x + nodes[1]->position.x) / 2, 
                    (nodes[0]->position.y + nodes[1]->position.y) / 2};
        DrawText(std::to_string(weight).c_str(), mid.x, mid.y, 20, textButtonPressed);
    }
    else if(this->isFlur){
        DrawLineEx(nodes[0]->position, nodes[1]->position, thick, Fade(outlineButtonHoveredColor, 0.5f));
        Vector2 mid = {(nodes[0]->position.x + nodes[1]->position.x) / 2, 
                    (nodes[0]->position.y + nodes[1]->position.y) / 2};
        DrawText(std::to_string(weight).c_str(), mid.x, mid.y, 20, Fade(textButtonHovered, 0.5f));
    }
    else{
        DrawLineEx(nodes[0]->position, nodes[1]->position, thick, outlineButtonColor);
        Vector2 mid = {(nodes[0]->position.x + nodes[1]->position.x) / 2, 
                    (nodes[0]->position.y + nodes[1]->position.y) / 2};
        DrawText(std::to_string(weight).c_str(), mid.x, mid.y, 20, textButtonNormal);
    }
}