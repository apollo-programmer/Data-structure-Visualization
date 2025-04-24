#ifndef AVLSTATE_H
#define AVLSTATE_H

#include <random>
#include <AVL/AVLCode.h>
#include <AVL/AVL.h>
#include <AVL/AVLPanel.h>
#include <GUI/CodeBlock.h>
#include <GUI/inputBox.h>
#include <GUI/Slider.h>

enum class AVLAnimationMode{
    IDLE, INSERT, REMOVE, SEARCH, UPDATE, UPDATEINS
};

class AVLState {   
    public: 
        AVLState();

        void updateTheme();

        void update();
        void draw();

        void saveInsertState(int value);
        void saveRemoveState(int value);
        void saveSearchState(int value);

        void animateInsert(int value);
        void animateRemove(int value);
        void animateSearch(int value);

        int getBalanceFactor(AVLNode* root);

        void resetBox();
        std::string getRandomInput();
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
        AVL AVLTree;
        AVLPanel panel;
        Slider speedSlider;
        
        InputBox createBox;
        InputBox valueBox;
        InputBox initialValue;
        InputBox finalValue;

        Button Random;
        Button LoadFile;
        Button Apply;

        CodeBlock code;

        AVLAnimationMode animationState=AVLAnimationMode::IDLE;

        bool isPlaying = false;
        bool isPaused = false;
        int currentStep = 0;
        bool isStateSaved=false;

        struct AnimationStep{
            AVL* AVLTree;
            AVLAnimationMode animationState;
            CodeBlock code;
        };

        std::vector<AnimationStep*> stateList;

        std::string createText;
        std::string valueText;
        std::string initialValueText;
        std::string finalValueText;
};

#endif