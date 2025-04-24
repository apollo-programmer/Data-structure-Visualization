#pragma once
#include "raylib.h"
#include <string>
#include <algorithm>
#include <cmath>
#include <GUI/Resources.h>

class Slider{
    public:
        Rectangle box;
        Rectangle sliderRect;
        Vector2 position;
        float width, height;
        float minVal, maxVal;
        float val;
        Vector2 knobSize;
        bool isDragging;
        int numSteps;

        Slider(float minVal, float maxVal, float initialVal, int steps);
        Slider(Vector2 pos, float w, float h, float minVal, float maxVal, float initialVal, int steps = 10) 
        : position(pos), width(w), height(h), minVal(minVal), maxVal(maxVal), val(initialVal), 
          knobSize({10, h + 10}), isDragging(false), numSteps(steps) {}
        void Update();
        void Draw();

        void reset();
};