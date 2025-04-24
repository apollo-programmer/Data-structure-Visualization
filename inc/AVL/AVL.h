#ifndef AVL_H
#define AVL_H

#include <sstream>
#include <AVL/AVLNode.h>

class AVL{
    public:
        AVL();
        ~AVL();

        void createTree(std::string text);
        void insertNode(int value);
        void balanceTree();
        void balanceTree(AVLNode*& root);
        int getBalanceFactor(AVLNode* root);
        void rotateRight(AVLNode*& root);
        void rotateLeft(AVLNode*& root);
        void rotateRightLeft(AVLNode*& root);
        void rotateLeftRight(AVLNode*& root);
        void clear();
        void clearTree();
        void clearTree(AVLNode*& root);

        void calculateHeight();
        void calculateHeight(AVLNode* root);
        void setCreatePosition();
        void setCreatePosition(AVLNode* root);
        void setPosition();
        void setPosition(AVLNode* root);
        void setTargetPosition();
        void setTargetPosition(AVLNode* root);
        void resetHighlight();
        void resetHighlight(AVLNode* root);
        void setArrowDestination();
        void setArrowDestination(AVLNode* root);

        bool checkPosition();
        bool checkPosition(AVLNode* root);
        bool checkArrowDestination();
        bool checkArrowDestination(AVLNode* root);

        AVL* clone() const;
        AVLNode* clone(AVLNode* root, AVLNode* curNode, AVLNode* &cloneCurNode) const;

        void update();
        void update(AVLNode* root);
        void draw();
        void draw(AVLNode* root);
    public:
        AVLNode* root;
        AVLNode* curNode;
        AVLNode* temp;

        int animationStep;
};

#endif