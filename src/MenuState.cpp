#include <MenuState.h>
#include <MenuState.h>

MenuState::MenuState(){
    this->background = LoadTexture("button.png");
    this->title = "Data Structure Visualization";

    this->SLL.setText("Singly Linked List",menuButtonFontSize);
    this->SLL.setSize(menuButtonSize);
    this->SLL.setPosition({400,550});
    
    this->LinearHT.setText("Linear Hashing Table",menuButtonFontSize);
    this->LinearHT.setSize(menuButtonSize);
    this->LinearHT.setPosition({800 ,550});

    this->Tree234.setText("2-3-4 Tree",menuButtonFontSize);
    this->Tree234.setSize(menuButtonSize);
    this->Tree234.setPosition({1200 ,550});

    this->AVLTree.setText("AVL Tree",menuButtonFontSize);
    this->AVLTree.setSize(menuButtonSize);
    this->AVLTree.setPosition({400 ,700});

    this->MinSpanningTree.setText("Minimum Spanning Tree",menuButtonFontSize);
    this->MinSpanningTree.setSize(menuButtonSize);
    this->MinSpanningTree.setPosition({800, 700});

    this->ShortestPath.setText("Shortest Path",menuButtonFontSize);
    this->ShortestPath.setSize(menuButtonSize);
    this->ShortestPath.setPosition({1200 ,700});
}

void MenuState::draw(){
    DrawTexture(this->background, 0, 0, WHITE);
    DrawText(this->title, GetScreenWidth()/2.0f - MeasureText(this->title, appTitleFontSize)/2.0f, 350, 40, appTitleColor);

    this->SLL.drawRectangleRounded(70);
    this->LinearHT.drawRectangleRounded(70);
    this->Tree234.drawRectangleRounded(70);
    this->AVLTree.drawRectangleRounded(70);
    this->MinSpanningTree.drawRectangleRounded(70);
    this->ShortestPath.drawRectangleRounded(70);

    this->SLL.drawText();
    this->LinearHT.drawText();
    this->Tree234.drawText();
    this->AVLTree.drawText();
    this->MinSpanningTree.drawText();
    this->ShortestPath.drawText();

    this->SLL.drawOutlineRounded(70, 100, 5);
    this->LinearHT.drawOutlineRounded(70, 100, 5);
    this->Tree234.drawOutlineRounded(70, 100, 5);
    this->AVLTree.drawOutlineRounded(70, 100, 5);
    this->MinSpanningTree.drawOutlineRounded(70, 100, 5);
    this->ShortestPath.drawOutlineRounded(70, 100, 5);
}

void MenuState::update(){
    if(this->SLL.isPressed()){
        currentSelection=MenuSelection::SLL;
    }
    else if(this->LinearHT.isPressed()){
        currentSelection=MenuSelection::LINEAR_HT;
    }
    else if(this->Tree234.isPressed()){
        currentSelection=MenuSelection::TREE_234;
    }
    else if(this->AVLTree.isPressed()){
        currentSelection=MenuSelection::AVL_TREE;
    }
    else if(this->MinSpanningTree.isPressed()){
        currentSelection=MenuSelection::MIN_SPANNING_TREE;
    }
    else if(this->ShortestPath.isPressed()){
        currentSelection=MenuSelection::SHORTEST_PATH;
    }
    this->SLL.update();
    this->LinearHT.update();
    this->Tree234.update();
    this->AVLTree.update();
    this->MinSpanningTree.update();
    this->ShortestPath.update();
}