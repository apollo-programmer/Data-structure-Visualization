#ifndef TREEnode_H
#define TREEnode_H

#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "raylib.h"
#include "raymath.h"
#include "../GUI/ColorTheme.h"

class TreeNode {
    public:
        std::vector<int> keys;
        std::vector<TreeNode*> children;
        TreeNode* parent;
        bool isLeaf;
        bool isChosen = false;
        Vector2 position;
        Vector2 finalPosition;
        std::vector<Vector2> arrowPos;
        Vector2 size;
        Color currentColor,colorChosen, colorNormal;
        Color textCurColor, textNorColor, textChosenColor;
        Font fontNumber;
    
        bool isEmpty = false;
    
        float width;
    
        TreeNode(std::vector<int> keys, std::vector<TreeNode*> children, Vector2 position);
        TreeNode(TreeNode * node);
        //~TreeNode();
        void DrawNode();
        void DrawArrow(Vector2 start, Vector2 end);
        void DrawLinktoChild();
    
        void CalculateWidth();
        void assignCoordinates(float x, float y);
        void calculateCoordinate(Vector2 start);
    
        TreeNode* CreateTree(int numofKey);
        TreeNode* CreateTreewithKey(std::vector<int> keys);
        TreeNode* getRoot(TreeNode* node);
        void insertKey(TreeNode*& root, int key);
        void splitNode(TreeNode* parent, int index, TreeNode* fullNode);
    
        void deleteTree(TreeNode * node);
    };
    

#endif