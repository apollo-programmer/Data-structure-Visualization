#ifndef SHORTESTPATHSTATE_H
#define SHORTESTPATHSTATE_H

#include <random>
#include <ShortestPath/ShortestPath.h>
#include <ShortestPath/STPanel.h>
#include <ShortestPath/ShortestPathCode.h>
#include <GUI/CodeBlock.h>
#include <GUI/inputBox.h>
#include <GUI/Slider.h>

enum class STAnimationMode {
    IDLE, CREATE, DIJKSTRA
};

class ShortestPathState{
    public:
        ShortestPathState();

        void updateTheme();
        
        void update();
        void draw();

        void saveDijkstraState(int startNode);
        
        void animateFruchtermanReingold();
        void animateDijkstra(int startNode);

        void resetBox();
        bool isBackPressed();

        void play();
        void pause();
        void resume();
        void nextStep();
        void prevStep();
        void restart();
        void moveEnd();
        void moveStart();
        void saveState();
        void applyState();
        void clearState();

    private:
        ShortestPath ST;
        STPanel panel;
        Slider speedSlider;

        InputBox NodesBox;
        InputBox EdgesBox;
        InputBox StartNodesBox;

        Button Random;
        Button LoadFile;
        Button Apply;
        
        Button Weighted;
        Button Directed;
        Button Unweighted;
        Button Undirected;

        CodeBlock code;

        STAnimationMode animationState=STAnimationMode::IDLE;

        bool isPlaying = false;
        bool isPaused = false;
        int currentStep = 0;
        bool isStateSaved=false;

        int findSmall=-1;
        int  minCost =  INT_MAX;

        struct AnimationStep{
            ShortestPath* ST;
            STAnimationMode animationState;
            CodeBlock code;
        };

        std::vector<AnimationStep*> stateList;

        std::string startNodeText;
        std::string nodesText;
        std::string edgesText;
        bool isLoadFile=false;
};

#endif