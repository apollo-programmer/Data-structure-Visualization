#ifndef AVLNODE_H
#define AVLNODE_H

#include <algorithm>
#include <AVL/AVLArrow.h>

class AVLNode{
    public:
        AVLNode();
        ~AVLNode();

        void setValue(int value);
        void setPosition(Vector2 position);
        void setTargetPosition(Vector2 targetPos);
        void setHeight(int value);
        void setDepth(int value);
        void setHighlight();
        void deHighlight();

        Vector2 getOrigin();
        Vector2 getTargetPosition();
        int getValue();
        int getHeight();
        int getDepth();
        bool isLeaf();

        void updateHeight();

        void updateNode();
        void updateCur();
        void drawCur();

        void setDestinationLeft(Vector2 targetDes);
        void setDestinationRight(Vector2 targetDes);
        void setTargetDestinationLeft(Vector2 targetDes);
        void setTargetDestinationRight(Vector2 targetDes);

        Vector2 getDestinationLeft();
        Vector2 getDestinationRight();

        AVLNode* clone() const;

        int getLeftNumNodes();
        int getRightNumNodes();
        void setLeftNumNodes(int value);
        void setRightNumNodes(int value);
        int getTotalNumNodes();
    public:
        AVLNode* left;
        AVLNode* right;
        AVLNode* parent;
    private:
        Rectangle node;

        AVLArrow* leftPointer;
        AVLArrow* rightPointer;

        Vector2 position;
        Vector2 targetPosition; 
        int value;
        int height;
        int depth;
        int leftNumNodes;
        int rightNumNodes;

        bool isHighlight;
};

#endif