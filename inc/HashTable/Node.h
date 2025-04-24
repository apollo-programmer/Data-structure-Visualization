#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "GUI/ColorTheme.h"

class Node {
public:
    int data;
    Node* next;
    Vector2 position;       
    Vector2 finalPosition;  
    Vector2 size;          
    Vector2 finalSize;      
    Vector2 arrowPos;       
    Color & colorNormal;     
    Color & colorChosen;      
    Color colorCurrent;    
    Color  colorFinal;
    Color  textCurColor, &textChosenColor, &textNorColor;       
    bool isChosen = false; 
    bool isVisual = false;

    Node(int data, Vector2 position, Vector2 size);

    Node(int data);

    Node(Node & other);

};