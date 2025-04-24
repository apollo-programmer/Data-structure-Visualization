#pragma once

#include "raylib.h"
#include "raymath.h"
#include "GUI/ColorTheme.h"
#include <vector>
#include <iostream>

class GraphEdge;

class GraphNode {
public:
    int data;
    std::vector<GraphEdge*> edge;

    Vector2 position, finalPos;
    float size;
    Color colorNormal, colorCurrent, colorChosen;
    Color textCur, textNor, textCho;

    bool isVisited = false;
    bool isDragging = false;
    Vector2 dragOffset = {0, 0};

    GraphNode(int data, std::vector<GraphEdge*> edge, Vector2 position);

    void DrawNode();
    void UpdatePosition();
};