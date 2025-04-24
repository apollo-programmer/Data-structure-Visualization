#pragma once
#include "SetofAnimation.h"
#include "../HashTable.h"
#include <vector>


class Presentation {
public:
    float &speed;
    HashTable & table; // Vẫn giữ tham chiếu, nhưng sẽ không gán lại
    std::vector<SetofAnimation> SetAnimations;
    //std::vector<SetofAnimation> historyOfSets;
    int currentStep;

    std::vector<std::vector<HashTable>> &historyState;
    int &currentPresentationIndex;
    int &currentStateIndex;
    //int currentIndex;

    Presentation(float &speed, HashTable& table, std::vector<std::vector<HashTable>> &historyState, int &currentPresentationIndex, int &currentStateIndex);
    void InsertNodeAnimation(int key, Node* newNode);
    void DeleteNodeAnimation(int key);
    void FindNodeAnimation(int key);
    void CreateTableAnimation(int size);
    //void UpdateAnimation(int initValue, int finalValue, Node* newNode);
    bool DrawPresentation();
    void clear();
    //void RewindStep();
};