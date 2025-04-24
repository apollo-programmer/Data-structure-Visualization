#include "HashTable/Node.h"

Node::Node(int data, Vector2 position, Vector2 size): colorChosen(nodeHighlightColor), colorNormal(nodeColor), textChosenColor(nodeHighlightTextColor), textNorColor(nodeTextColor){
    this->data = data;
    this->position = position;
    this->finalPosition = position;
    this->size = size;
    this->arrowPos = position;
    //this.ConcurrentModificationException = size;
    
    this->colorCurrent = nodeColor;
    this->colorFinal = colorNormal;
    this->textCurColor = nodeTextColor;
    this->next = nullptr;
    this->isChosen = false;
    this->isVisual = false;
}

Node::Node(int data):  colorChosen(nodeHighlightColor), colorNormal(nodeColor), textChosenColor(nodeHighlightTextColor), textNorColor(nodeTextColor) {
    this->data = data;
    this->next = nullptr;
    this->position = {0, 0};
    this->finalPosition = {0, 0};
    this->arrowPos = {0, 0};
    this->size = {0, 0};
    this->finalSize = {0, 0};
    this->colorCurrent = nodeColor;
    this->textCurColor = nodeTextColor;
    this->colorFinal = BLACK;
    this->isChosen = false;
    this->isVisual = false;
}

Node::Node(Node & other): data(other.data),
                            next(nullptr), // Không sao chép next, để HashTable xử lý
                            position(other.position),
                            finalPosition(other.finalPosition),
                            size(other.size),
                            finalSize(other.finalSize),
                            arrowPos(other.arrowPos),
                            colorNormal(other.colorNormal),
                            colorChosen(other.colorChosen),
                            colorCurrent(other.colorCurrent),
                            colorFinal(other.colorFinal),
                            textChosenColor(other.textChosenColor),
                            textNorColor(other.textNorColor),
                            textCurColor(other.textCurColor),
                            isChosen(other.isChosen),
                            isVisual(other.isVisual) {}

