#pragma once


#include "Animation.h"
#include <vector>

class SetofAnimation {
public:
    float &speed;
    std::vector<Animation> animations;

    SetofAnimation(float &speed);
    void AddAnimation(Animation animation);
    bool Draw();
};