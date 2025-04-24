#pragma once
#include "raylib.h"
#include "GUI/Slider.h"
#include "GUI/Button.h"
#include <vector>
#include "HashTable/HashTable.h"
#include "234tree/TreeNode.h"

class PlaybackControl {
public:
    PlaybackControl(Vector2 position, float width, float height, float & speed);

    void UpdateHash(int& currentPresentationIndex, int& currentStateIndex, 
                std::vector<std::vector<HashTable>> historyState);
    void UpdateTree234(int& currentPresentationIndex, int& currentStateIndex,
                std::vector<std::vector<TreeNode*>> historyState);
    void Draw();
    bool IsPlaying() const;

    int typePlayBack;
    bool isPlaying = false;
    bool isSkip = false;

private:
    Vector2 position;
    float width;
    float height;
    float & speed;

    Slider historySlider;
    Button skipBackButton;
    Button stepBackButton;
    Button stepNextButton;
    Button skipNextButton;

    enum TypePlayBack{
        hash = 0,
        tree = 1, 
        spanTree = 2
    };

    //bool isPlaying;
};