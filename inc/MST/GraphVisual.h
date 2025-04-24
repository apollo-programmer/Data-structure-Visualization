#pragma once
#include "Graph.h"
#include "GUI/ColorTheme.h"
#include "GUI/Slider.h"
#include "MST/Animation/GraphPresentation.h"
#include "MST/Animation/GraphInputPanel.h"


class GraphVisual {
public:
    Graph* graph; // Con trỏ thô
    float &speed;
    GraphPresentation presentation;

    bool isPlaying = false;
    bool isDrawGraph = true;
    bool isSkipBack = false;
    bool isRewinding = false;

    std::vector<std::vector<Graph*>> historyState;
    int currentPresentationIndex;
    int currentStateIndex;

    GraphInputPanel inputPanel;

    Slider speedSlider;

    GraphVisual(float &speed);
    ~GraphVisual(); // Thêm destructor để giải phóng graph

    void Draw();
    void CreateGraph(int numOfVer);
    void CreateGraphFromInput(std::vector<std::vector<int>> input);
    void KruskalAlgo();
    void PrimAlgo();
    void Update();
};