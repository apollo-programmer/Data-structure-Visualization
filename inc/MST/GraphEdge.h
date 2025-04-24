#pragma once
#include "raylib.h"
#include "GraphNode.h"
#include "GUI/ColorTheme.h"
#include <vector>
#include <string>

class GraphEdge {
public: 
    std::vector<GraphNode*> nodes; // Lưu con trỏ đến node
    int weight;
    Color currentColor, colorNormal, colorChosen, colorFlur;
    
    float thick;
    bool isChosen = false;
    bool isFlur = false;

    GraphEdge(std::vector<GraphNode*> nodes, int weight);
    ~GraphEdge() = default;

    void DrawEdge();
};