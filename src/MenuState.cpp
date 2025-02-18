#include "MenuState.h"

MenuState::MenuState(){
    this->background = LoadTexture("button.png");
    this->title = "Data Structure Visualization";

    this->exit.setTexture("button.png", "button.png", "buttonPress.png");
    this->exit.setPosition({1400, 800});
    this->exit.setSize();

    this->SLL.setTexture("button.png", "button.png", "buttonPress.png");
    this->SLL.setPosition({600, 500});
    this->SLL.setSize();

    this->LinearHT.setTexture("button.png", "button.png", "buttonPress.png");
    this->LinearHT.setPosition({800, 500});
    this->LinearHT.setSize();

    this->Tree234.setTexture("button.png", "button.png", "buttonPress.png");
    this->Tree234.setPosition({1000, 500});
    this->Tree234.setSize();

    this->RBTree.setTexture("button.png", "button.png", "buttonPress.png");
    this->RBTree.setPosition({600, 700});
    this->RBTree.setSize();

    this->MinSpanningTree.setTexture("button.png", "button.png", "buttonPress.png");
    this->MinSpanningTree.setPosition({800, 700});
    this->MinSpanningTree.setSize();

    this->ShortestPath.setTexture("button.png", "button.png", "buttonPress.png");
    this->ShortestPath.setPosition({1000, 700});
    this->ShortestPath.setSize();
}

void MenuState::draw(){
    DrawTexture(this->background, 0, 0, WHITE);
    DrawText(this->title, 800 - MeasureText(this->title, 40)/2, 350, 40, BLACK);
    this->exit.drawTexture({1500,800});
    this->exit.drawText("Exit", {1500.0f - exit.measureText("Exit",20) ,800}, 20, BLACK);
    this->SLL.drawTexture({600,500});
    this->SLL.drawText("Singly Linked List", {500.0f - SLL.measureText("Singly Linked List",20)/2 ,550}, 20, BLACK);
    this->LinearHT.drawTexture({800,500});
    this->LinearHT.drawText("Linear Hash Table", {800.0f - LinearHT.measureText("Linear Hash Table",20)/2 ,550}, 20, BLACK);
    this->Tree234.drawTexture({1000,500});
    this->Tree234.drawText("2-3-4 Tree", {1100.0f - Tree234.measureText("2-3-4 Tree",20)/2 ,550}, 20, BLACK);
    this->RBTree.drawTexture({600,700});
    this->RBTree.drawText("Red-Black Tree", {500.0f - RBTree.measureText("Red-Black Tree",20)/2 ,700}, 20, BLACK);
    this->MinSpanningTree.drawTexture({800,700});
    this->MinSpanningTree.drawText("Minimum Spanning Tree", {800.0f - MinSpanningTree.measureText("Minimum Spanning Tree",20)/2 ,700}, 20, BLACK);
    this->ShortestPath.drawTexture({1000,700});
    this->ShortestPath.drawText("Shortest Path", {1100.0f - ShortestPath.measureText("Shortest Path",20)/2 ,700}, 20, BLACK);
}

void MenuState::update(){
    if(this->exit.isPressed()){
        CloseWindow();
    }
    if(this->SLL.isPressed()){
        this->isSLL = true;
        this->isStarted = true;
    }
    else if(this->LinearHT.isPressed()){
        this->isLinearHT = true;
        this->isStarted = true;
    }
    else if(this->Tree234.isPressed()){
        this->isTree234 = true;
        this->isStarted = true;
    }
    else if(this->RBTree.isPressed()){
        this->isRBTree = true;
        this->isStarted = true;
    }
    else if(this->MinSpanningTree.isPressed()){
        this->isMinSpanningTree = true;
        this->isStarted = true;
    }
    else if(this->ShortestPath.isPressed()){
        this->isShortestPath = true;
        this->isStarted = true;
    }
    this->exit.update();
    this->SLL.update();
    this->LinearHT.update();
    this->Tree234.update();
    this->RBTree.update();
    this->MinSpanningTree.update();
    this->ShortestPath.update();
}