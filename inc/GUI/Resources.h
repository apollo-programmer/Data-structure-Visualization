#ifndef RESOURCES_H
#define RESOURCES_H

#include <raylib.h>
#include <GUI/ColorTheme.h>


extern int speed;
extern float delayTime;
extern float tempSpeed;
const int defaultSpeed = 200;
const float defaultDelayTime = 0.5f;

//Font
//const Font fontNumber = LoadFontEx("../resources/Ubuntu-Bold.ttf");
//

//Menu
const int appTitleFontSize(40);
const Vector2 menuButtonSize({300,50});
const int menuButtonFontSize(26);

//Panel
const int dataTitleFontSize = 32;
const Vector2 dataTitleSize({400,50});
const Vector2 dataTitlePosition({800,15+dataTitleSize.y/2.0f});

const Vector2 panelButtonSize({80, 40});//Create, Add, Remove ...
const int panelButtonFontSize(18);

const Vector2 backSize({60,60});

//InputBox
const int inputBoxFontSize(24);
const int inputBoxNameFontSize(20);

//CodeBlock
const Rectangle codeBlockRec({1200,700,400,200});
const int codeBlockFontSize(18);
const Vector2 codePosition({codeBlockRec.x+15,codeBlockRec.y});

//ColorTheme Manager
const Vector2 themeButtonSize({80, 80});
const int themeButtonFontSize(18);

//SLL
const Vector2 SLLNodeSize({50,50});
const Vector2 SLLposition({150,250});
const int SLLNodeFontSize(24);

const Vector2 SLLBoxSize({260,40});
const int SLLBoxFontSize(24);
const int SLLButtonFontSize(18);

const int SLLLabelFontSize(16);

//AVL
const Vector2 AVLPosition({800,150});
const Vector2 AVLNodeSize({40,40});
const int AVLLeafSpace = 5;
const int AVLNodeFontSize(24);
const int AVLLevelSpace = 60;

const Vector2 AVLBoxSize({260,40});
const int AVLBoxFontSize(24);
const int AVLButtonFontSize(18);

//Shortest Path
const float centerX=800, centerY=350;
const float rangeX=1400,rangeY=500;

const Vector2 STNodeSize({40,40});
const int STNodeCostFontSize(16);
const int STNodeIDFontSize(24);

const Vector2 STBoxSize({260,40});
const int STBoxFontSize(24);
const int STButtonFontSize(18);

//Arrow
const int ArrowLength = 40;

//Controller
const Vector2 controllerButtonSize({60,60});
const Vector2 controllerPosition({800,860});
const Vector2 controllerSize({400,2*(900-controllerPosition.y)});

//sound 
namespace Resource {
    extern Sound clickSound;

    void InitResource();

    void UnloadResource() ;
};

#endif