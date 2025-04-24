#pragma once
#include "raylib.h"
#include "raymath.h"
#include "234tree/TreeNode.h"
#include "GUI/CodeBlock.h"
#include <string>
#include <algorithm>
#include <vector>

class Operation {
public:
    enum OperationType {
        NORMAL = 1,
        HIGHLIGHT = 2,
        INSERT_EDGE = 3,
        MOVE_NODE = 4,
        SPLIT_NODE = 5,
        MERGE_KEY_TO_PARENT = 6,
        INSERT_TO_LEAF = 7,
        MOVE_TO_FINPOS = 8,
        MOVE_TO_CHILDREN_NODE = 9,
        MERGE_TO_CHILDREN = 10,
        REMOVE_LEAF = 11,
        CHANGE_KEY = 12,
        RESET_CURRENT = 13
    };
    float& speed;
    TreeNode*& node;
    TreeNode *& root;
    OperationType type; // Sửa int thành OperationType
    float curAnimation;
    int key, newKey;

    CodeBlock & codeBlock;
    bool& isSplit;
    
    Operation(float& speed, TreeNode*& node, TreeNode *& root, bool& isSplit, CodeBlock & codeBlock);
    void SetKey(int key) { this->key = key; this->newKey = key; }
    void SetNewKey(int newKey) { this->newKey = newKey; }

    bool DrawNormalNode();
    bool DrawChosenNode();
    bool DrawInsertEdge();
    bool DrawMoveNode();
    bool DrawMovetoFinalPos();
    void MoveAllNodeToFinalPos(TreeNode * tree, float curAnimation);
    bool SplitNode();
    bool MergeKeyToParent(); // Đổi từ mergeKey2Par
    bool InsertToLeaf();     // Đổi từ Insert2Leaf
    bool MoveToChildrenNode();
    bool Merge2Child();
    bool RemoveLeaf();
    bool Changekey();
    bool ResetCur();

    bool DrawOperation();
};