#pragma once

#include "raylib.h"
#include "MST/Graph.h"
#include "MST/GraphEdge.h"
#include "MST/GraphNode.h"

class GraphOperation{
    public:
        enum GraphOperationType{
            CHOSEN_EDGE = 1,
            NORMAL_EDGE = 2,
            FLUR_EDGE = 3,
            NORMAL_NODE = 4,
            CHOSEN_NODE = 5,
            MOVE_NODE = 6,
        };

        float & speed;
        float curAnimation;
        GraphOperationType type;
        GraphNode * vertice;
        GraphEdge * edge;

        GraphOperation(float & speed, GraphNode * vertice);
        GraphOperation(float & speed, GraphEdge * edge);

        Color LerpColor(Color start, Color end, float t);
        
        bool DrawNormalNode();
        bool DrawChosenNode();
        bool DrawNormalEdge();
        bool DrawFlurEdge();
        bool DrawChosenEdge();
        bool DrawMoveNode();
        
        bool DrawGOperation();
        
};