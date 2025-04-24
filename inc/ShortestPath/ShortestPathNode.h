#ifndef SHORTESTPATHNODE_H
#define SHORTESTPATHNODE_H

#include <vector>
#include <algorithm>
#include <ShortestPath/STArrow.h>

class ShortestPathNode{
    public:
        ShortestPathNode(Vector2 pos);
        ShortestPathNode(int id);
        ~ShortestPathNode();
        void setID(int id);
        int getID();
        void setCost(int cost);
        int getCost();
        void setHighlight();
        void deHighlight();
        bool getHighlight();
        void setKnown();
        void deKnown();
        bool getKnown();
        Vector2 getPosition();
        void setPosition(Vector2 position);
        Vector2 getForce();
        void setForce(Vector2 force);
        void addEdge(ShortestPathNode* node);
        void removeEdge(ShortestPathNode* node);
        void clearEdges();

        void setChosen();
        bool isCollision(ShortestPathNode* other);
        void applyRepellingForce(ShortestPathNode* other);
        void boundaryCollision();
        bool getBoundaryCollision();
        bool checkMouseHovered();
        void setLine();
        void deLine();

        ShortestPathNode* clone() const;

        void update();
        void updateNode();
        void draw(bool isWeighted, bool isDirected);
        void drawNode();
    public:
        std::vector<ShortestPathNode*> adj;
        std::vector<STArrow*> arrow;
        ShortestPathNode* prev=nullptr;

    private:
        Rectangle node;
        Vector2 position;

        Vector2 force;

        bool isChosen=false;
        bool isBoundaryCollision=false;
        bool isLine=false;

        int id;
        int cost;
        bool isKnown;
        bool isHighlight;
};

#endif