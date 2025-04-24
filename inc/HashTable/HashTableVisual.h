#ifndef HASHTABLEVISUALIZATION_H
#define HASHTABLEVISUALIZATION_H
#include "raylib.h"
#include "raymath.h"
#include "GUI/Button.h"
#include "GUI/inputBox.h"
#include "HashTable.h"
#include "animation/Presentation.h"
#include "GUI/Slider.h"
#include "GUI/PlayBackControl.h"
#include "GUI/CodeBlock.h"
#include "234tree/animation/InputPanel.h"

#define MAX_TABLE_SIZE 10
#define HASH_TABLE_WIDTH 800
#define HASH_TABLE_HEIGHT 600
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 40
#define INPUT_BOX_WIDTH 200
#define INPUT_BOX_HEIGHT 30

class HashTableVisualization {
public:
    HashTableVisualization(const bool& isLightMode, float &speed);
    //~HashTableVisualization();

    void Init(int size, int numofKey);
    void Insert(int key);
    void Delete(int key);
    bool Find(int key);
    void UpdateKey(int initValue, int finalValue);
    void Draw();
    void Update();

    bool isBackPressed();
    bool isPlaying = false;
    bool isDrawTable = true;
    bool isSkipBack = false;

    CodeBlock codeBlock;

private:
    HashTable hashTable;
    InputPanel inputPanel;
    Presentation presentations;

    Slider speedSlider;
    //Slider rewindSlider;

    std::vector<std::vector<HashTable>> historyState;
    int currentPresentationIndex;
    int currentStateIndex;

    PlaybackControl playbackControl;


    const Texture2D hollowCircle;
    const Texture2D solidCircle;
    const Texture2D arrowEdge;
    const Font fontNumber;
    const Font fontText;
    const bool isLightMode;
    
    float &speed;

    bool isInserting;
    bool isDeleting;
    bool deleting;
    bool isFinding;
    bool isInitializing;
    bool isRewindingStep; 

    int key;

    void DrawHashTable();
    void DrawNode(Node* node);
    void DrawLine(Vector2 start, Vector2 end);
    void DrawArrow(Vector2 start, Vector2 end);
    void DrawLink(Vector2 start, Vector2 end);
};
#endif