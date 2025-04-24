#pragma once

#include "GraphSetofOperation.h"
#include "MST/Graph.h"
#include <algorithm>
#include <queue>

class GraphPresentation{
    public:
        float & speed;
        Graph * graph;
        std::vector<GraphSetofOperation> SetOperations;
        int currentStep;
        std::vector<std::vector<Graph*>> & historyState;
        int & currentPresentationIndex;
        int & currentStateIndex;
        std::vector<int> parent;
        std::vector<int> rank;

        GraphPresentation(float & speed, Graph * graph,
                            std::vector<std::vector<Graph*>> & historyState, int & currentPresentationIndex, int & currentStateIndex);

        void CreateGraph(int numofNode);
        void Kruskal();
        void initDisjointSet(int n);
        int find(int x);
        bool unionSets(int x, int y);
        void Prim();


        bool DrawPresentation();
};