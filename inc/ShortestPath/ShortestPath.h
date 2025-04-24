#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include <sstream>
#include <ShortestPath/ShortestPathNode.h>

class ShortestPath{
    public:
        ShortestPath();
        ~ShortestPath();

        void createGraph(int numNodes, int edges);
        void createGraph(std::string input);
        void addEdge(int node1, int node2);
        void removeEdge(int node1, int node2);
        void clear();
        void clearGraph();
        void resetGraph();
        void setWeighted();
        void deWeighted();
        void setDirected();
        void deDirected();

        ShortestPath* clone() const;
        
        void update();
        void draw();
        
        Vector2 ComputeRepulsiveForce(ShortestPathNode* &v, ShortestPathNode* &u);    
        Vector2 ComputeAttractiveForce(ShortestPathNode* &v, ShortestPathNode* &u);
        
        void updateLine();
    public:
        std::vector<ShortestPathNode*> graph;
        std::vector<STArrow*> allArrows;
        ShortestPathNode* current;
        float k;
        bool isWeighted;
        bool isDirected;
        float cool;
        float deltaTime;

        int animationStep = 0;
        int findSmall = -1;  
        int minCost = INT_MAX;
        int index=0;
};

#endif