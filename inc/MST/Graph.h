#pragma once

#include "GraphNode.h"
#include "GUI/ColorTheme.h"
#include <vector>

class Graph {
public:
    std::vector<GraphNode*> vertices;
    std::vector<GraphEdge*> edges;

    Graph();
    Graph(std::vector<GraphNode*> vertices, std::vector<GraphEdge*> edges);
    Graph(Graph * graph);
    ~Graph();

    void createGraph(int numOfVer);
    void CreateGraphFromInput(std::vector<std::vector<int>> input);
    void DrawGraph();
    void Draw();
    void Update();
};