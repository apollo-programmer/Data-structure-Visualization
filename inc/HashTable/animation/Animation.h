#pragma once
#include "raylib.h"
#include "../Node.h"

class Animation {
public:
    float& speed;
    Vector2 target;
    int type;
    float curAnimation;
    Node* node;

    Animation(float &speed, Node* node);
    Animation(float &speed, Node* node, Vector2 target);

    bool DrawChosenNode();
    bool DrawNormalNode();
    bool DrawFadeInNode(); // Không cần Presentation vì không dùng pendingFadeInNode
    bool DrawFadeOutNode();
    bool DrawMoveNodeAnimation();
    bool DrawInsertEdgeAnimation();
    bool DrawDeleteEdgeAnimation();
    bool DrawAnimation();
};