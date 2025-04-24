#ifndef COLORTHEME_H
#define COLORTHEME_H

#include <raylib.h>

enum class StyleTheme {
    DEF, SUNNY, RLTECH, LAVANDA, ENEFETE, DARK, CYBER, CANDY, TERMINAL, BLUISH
};

extern StyleTheme currentTheme;

struct ColorTheme {
    Color appTitleColor;
    Color backgroundColor;
    
    Color dataTitleColor;
    Color dataTitleTextColor;

    Color buttonNormal;
    Color buttonHovered;
    Color buttonPressed;

    Color textButtonNormal;
    Color textButtonHovered;
    Color textButtonPressed;

    Color outlineButtonColor;
    Color outlineButtonHoveredColor;
    Color outlineButtonPressedColor;

    Color codeBlockTextColor;
    Color codeBlockHighlightColor;

    Color nodeColor;
    Color nodeTextColor;
    Color nodeHighlightColor;
    Color nodeHighlightTextColor;

    Color nodeCostColor;
    Color nodeKnownColor;
    Color nodeKnownTextColor;
    Color lineColor;
    Color lineTextColor;

    Color boxColor;
    Color boxTextColor;
};

const ColorTheme Default{
    BLACK,                                // appTitleColor
    WHITE,                               //BackgroudColor

    {201,201,201,255},                   // dataTitleColor
    {119,119,119,255},                   // dataTitleTextColor
    {201,201,201,255},                   // buttonNormal
    {201, 239, 254,255},                 // buttonHovered
    {151, 232, 255,255},                 // buttonPressed
    {119,119,119,255},                   // textNormal
    {76, 171, 213,255},                   // textHovered
    {0, 136, 194, 255},                   // textPressed
    {119,119,119,255},                   // outlineButtonColor
    {76, 171, 213,255},                  // outlineButtonHoveredColor
    {0, 136, 194, 255},                  // outlineButtonPressedColor

    BLACK,                               // codeBlockTextColor
    {151, 232, 255,255},                    // codeBlockHighlightColor
    
    {201,201,201,255},                   // nodeColor
    BLACK,                               // nodeTextColor
    {0, 136, 194, 255},                  // nodeHighlightColor
    {255,255,255,255},                   // nodeHighlightTextColor

    {0,0,0,255},                         // nodeCostColor
    {201, 239, 254,255},                 // nodeKnownColor
    {0,0,0,255},                         // nodeKnownTextColor
    {0, 136, 194, 255},                  // lineColor
    {255,255,255,255},                   // lineTextColor

    LIGHTGRAY,                           // boxColor
    BLACK                                // boxTextColor
};

const ColorTheme Sunny{
    BLACK,                                // appTitleColo
    {245, 210, 129, 255},                   //BackgroudColor

    {247, 242, 193,255},                   // dataTitleColor
    {84, 73, 12,255},                   // dataTitleTextColor
    {247, 242, 193,255},                   // buttonNormal
    {245, 243, 209,255},                 // buttonHovered
    {89, 64, 6,255},                 // buttonPressed
    {84, 73, 12,255},                   // textNormal
    {244, 202, 9,255},                   // textHovered
    {234, 193, 31, 255},                   // textPressed
    {84, 73, 12,255},                   // outlineButtonColor
    {244, 202, 9,255},                  // outlineButtonHoveredColor
    {234, 193, 31, 255},                  // outlineButtonPressedColor

    {89, 64, 6,255},                  // codeBlockTextColor
    {244, 205, 25,255},                  // codeBlockHighlightColor


    {247, 242, 193,255},                         // nodeColor
    {89, 64, 6,255},                   // nodeTextColor
    {244, 205, 25,255},                       // nodeHighlightColor
    {89, 64, 6,255},                   // nodeHighlightTextColor

    {89, 64, 6,255},                         // nodeCostColor
    {152, 115, 10,255},                       // nodeKnownColor
    {247, 242, 193,255},                         // nodeKnownTextColor
    {193, 169, 98, 255},                       // lineColor
    {247, 242, 193,255},                         // lineTextColor

    LIGHTGRAY,                           // boxColor
    BLACK                                 // boxTextColor
};

const ColorTheme RLTech{
    BLACK,                                // appTitleColo
    WHITE,                               //BackgroudColor

    {245, 245, 245,255},                   // dataTitleColor
    {0,0,0,255},                   // dataTitleTextColor
    {245,245,245,255},                   // buttonNormal
    {255,255,255,255},                 // buttonHovered
    {15, 15, 15,255},                 // buttonPressed
    {0, 0, 0,255},                   // textNormal
    {238, 22, 22,255},                   // textHovered
    {246, 25, 25, 255},                   // textPressed
    {0, 0, 0,255},                   // outlineButtonColor
    {238, 22, 22,255},                  // outlineButtonHoveredColor
    {246, 25, 25, 255},                  // outlineButtonPressedColor

    BLACK,                               // codeBlockTextColor
    {246, 25, 25,255},                    // codeBlockHighlightColor


    {201,201,201,255},                         // nodeColor
    {0,0,0,255},                   // nodeTextColor
    {246, 25, 25,255},                       // nodeHighlightColor
    {255,255,255,255},                   // nodeHighlightTextColor

    {0,0,0,255},                         // nodeCostColor
    {244, 167, 167,255},                       // nodeKnownColor
    {0,0,0,255},                         // nodeKnownTextColor
    {246, 25, 25,255},                       // lineColor
    {255,255,255,255},                         // lineTextColor

    LIGHTGRAY,                           // boxColor
    BLACK                                 // boxTextColor
};

const ColorTheme Lavanda{
    WHITE,                                // appTitleColor
    {91, 91, 129,255},                    //BackgroudColor

    {62, 67, 80,255},                   // dataTitleColor
    {244, 183, 199,255},                   // dataTitleTextColor
    {62, 67, 80,255},                   // buttonNormal
    {244, 183, 199,255},                 // buttonHovered
    {150, 110, 192,255},                 // buttonPressed
    {174, 157, 214,255},                   // textNormal
    {238, 132, 160,255},                   // textHovered
    {223, 210, 226, 255},                   // textPressed
    {174, 157, 214,255},                   // outlineButtonColor
    {238, 132, 160,255},                  // outlineButtonHoveredColor
    {223, 210, 226, 255},                  // outlineButtonPressedColor

    {223, 210, 226,255},                 // codeBlockTextColor
    {150, 110, 192,255},                    // codeBlockHighlightColor


    {62, 67, 80,255},                         // nodeColor
    {255,255,255,255},                   // nodeTextColor
    {150, 110, 192,255},                       // nodeHighlightColor
    {0,0,0,255},                   // nodeHighlightTextColor

    {255,255,255,255},                         // nodeCostColor
    {244, 183, 199,255},                       // nodeKnownColor
    {0,0,0,255},                         // nodeKnownTextColor
    {212, 199, 219,255},                       // lineColor
    {150, 110, 192,255},                         // lineTextColor

    LIGHTGRAY,                           // boxColor
    BLACK                                 // boxTextColor
};

const ColorTheme EneFete{
    {30, 75, 118,255},                                // appTitleColo
    {41, 201, 229,255},                               //BackgroudColor

    {77, 243, 235,255},                   // dataTitleColor
    {30, 75, 118,255},                   // dataTitleTextColor
    {77, 243, 235,255},                   // buttonNormal
    {35, 212, 221,255},                 // buttonHovered
    {234, 102, 217,255},                 // buttonPressed
    {10, 43, 82,255},                   // textNormal
    {247, 227, 249,255},                   // textHovered
    {159, 0, 187, 255},                   // textPressed
    {22, 118, 211,255},                   // outlineButtonColor
    {247, 227, 249,255},                  // outlineButtonHoveredColor
    {92, 7, 160, 255},                  // outlineButtonPressedColor

    {10, 43, 82,255},                               // codeBlockTextColor
    {234, 102, 217,255},                    // codeBlockHighlightColor


    {77, 243, 235,255},                         // nodeColor
    {10, 43, 82,255},                   // nodeTextColor
    {102, 7, 161,255},                       // nodeHighlightColor
    {240, 241, 241,255},                   // nodeHighlightTextColor

    {10, 43, 82,255},                         // nodeCostColor
    {234, 102, 217,255},                       // nodeKnownColor
    {240, 241, 241,255},                         // nodeKnownTextColor
    {242, 163, 232,255},                       // lineColor
    {10, 43, 81,255},                         // lineTextColor

    LIGHTGRAY,                           // boxColor
    BLACK                                 // boxTextColor
};

const ColorTheme Dark{
    {195, 195, 195,255},                                // appTitleColo
    {119, 119, 119,255},                               //BackgroudColor

    {44, 44, 44,255},                   // dataTitleColor
    {240, 241, 241,255},                   // dataTitleTextColor
    {44, 44, 44,255},                   // buttonNormal
    {132, 132, 132,255},                 // buttonHovered
    {239, 239, 239,255},                 // buttonPressed
    {149, 149, 149,255},                   // textNormal
    {36, 36, 36,255},                   // textHovered
    {30, 30, 30, 255},                   // textPressed
    {149, 149, 149,255},                   // outlineButtonColor
    {220, 220, 220,255},                  // outlineButtonHoveredColor
    {30, 30, 30, 255},                  // outlineButtonPressedColor

    {239, 239, 239,255},                               // codeBlockTextColor
    {132, 132, 132,255},                    // codeBlockHighlightColor


    {44, 44, 44,255},                         // nodeColor
    {239, 239, 239,255},                   // nodeTextColor
    {239, 239, 239,255},                       // nodeHighlightColor
    {30,30,30,255},                   // nodeHighlightTextColor

    {44, 44, 44,255},                         // nodeCostColor
    {167, 167, 167,255},                       // nodeKnownColor
    {30,30,30,255},                         // nodeKnownTextColor
    {239, 239, 239,255},                       // lineColor
    {30, 30, 30,255},                   // lineTextColor

    LIGHTGRAY,                           // boxColor
    BLACK                                 // boxTextColor
};

const ColorTheme Cyber{
    {179, 222, 231,255},                                // appTitleColo
    {0, 34, 43,255},                               //BackgroudColor

    {2, 70, 88,255},                   // dataTitleColor
    {179, 222, 231,255},                   // dataTitleTextColor
    {2, 70, 88,255},                   // buttonNormal
    {201, 239, 254,255},                 // buttonHovered
    {255, 188, 81,255},                 // buttonPressed
    {122, 183, 198,255},                   // textNormal
    {182, 225, 234,255},                   // textHovered
    {216, 111, 54, 255},                   // textPressed
    {52, 123, 141,255},                   // outlineButtonColor
    {133, 208, 228,255},                  // outlineButtonHoveredColor
    {216, 111, 54, 255},                  // outlineButtonPressedColor

    {182, 225, 234,255},                               // codeBlockTextColor
    {255, 188, 81,255},                    // codeBlockHighlightColor


    {2, 70, 88,255},                         // nodeColor
    {182, 225, 234,255},                   // nodeTextColor
    {255, 188, 81,255},                       // nodeHighlightColor
    {216, 111, 54,255},                   // nodeHighlightTextColor

    {182, 225, 234,255},                         // nodeCostColor
    {201, 239, 254,255},                       // nodeKnownColor
    {0, 34, 43,255},                         // nodeKnownTextColor
    {255, 188, 81,255},                       // lineColor
    {216, 111, 54, 255},                         // lineTextColor

    LIGHTGRAY,                           // boxColor
    BLACK                                 // boxTextColor
};

const ColorTheme Candy{
    {226, 147, 83,255},                                // appTitleColo
    {255, 245, 225,255},                               //BackgroudColor

    {254, 218, 150,255},                   // dataTitleColor
    {226, 147, 83,255},                   // dataTitleTextColor
    {254, 218, 150,255},                   // buttonNormal
    {252, 216, 91,255},                 // buttonHovered
    {235, 114, 114,255},                 // buttonPressed
    {236, 167, 137,255},                   // textNormal
    {252, 98, 85,255},                   // textHovered
    {171, 58, 59, 255},                   // textPressed
    {236, 167, 137,255},                   // outlineButtonColor
    {252, 98, 85,255},                  // outlineButtonHoveredColor
    {171, 58, 59, 255},                  // outlineButtonPressedColor

    {252, 88, 68,255},                               // codeBlockTextColor
    {194, 163, 122,255},                    // codeBlockHighlightColor


    {254, 218, 150,255},                         // nodeColor
    {148, 121, 93,255},                   // nodeTextColor
    {235, 114, 114,255},                       // nodeHighlightColor
    {255, 245, 225,255},                   // nodeHighlightTextColor

    {236, 167, 137,255},                         // nodeCostColor
    {194, 163, 122,255},                       // nodeKnownColor
    {255, 245, 225,255},                         // nodeKnownTextColor
    {188, 91, 91,255},                       // lineColor
    {255, 245, 225,255},                         // lineTextColor

    LIGHTGRAY,                           // boxColor
    BLACK                                 // boxTextColor
};

const ColorTheme Terminal{
    {56, 246, 32,255},                                // appTitleColo
    {12, 21, 5,255},                               //BackgroudColor

    {22, 19, 19,255},                   // dataTitleColor
    {47, 198, 26,255},                   // dataTitleTextColor
    {22, 19, 19,255},                   // buttonNormal
    {67, 191, 46,255},                 // buttonHovered
    {67, 255, 40,255},                 // buttonPressed
    {56, 246, 32,255},                   // textNormal
    {188, 248, 189,255},                   // textHovered
    {34, 126, 23, 255},                   // textPressed
    {56, 246, 32,255},                   // outlineButtonColor
    {188, 248, 189,255},                  // outlineButtonHoveredColor
    {34, 126, 23, 255},                  // outlineButtonPressedColor

    {47, 198, 26,255},                               // codeBlockTextColor
    {34, 126, 23,255},                    // codeBlockHighlightColor


    {123, 255, 105,255},                         // nodeColor
    {34, 126, 23, 255},                   // nodeTextColor
    {237, 253, 237,255},                       // nodeHighlightColor
    {12, 21, 5,255},                   // nodeHighlightTextColor

    {230, 252, 227,255},                         // nodeCostColor
    {36, 62, 37,255},                       // nodeKnownColor
    {188, 248, 189,255},                         // nodeKnownTextColor
    {237, 253, 237,255},                       // lineColor
    {12, 21, 5,255},                         // lineTextColor

    LIGHTGRAY,                           // boxColor
    BLACK                                 // boxTextColor
};

const ColorTheme Bluish{
    {85, 137, 131,255},                                // appTitleColo
    {232, 238, 241,255},                               //BackgroudColor

    {180, 232, 243,255},                   // dataTitleColor
    {85, 137, 131,255},                   // dataTitleTextColor
    {180, 232, 243,255},                   // buttonNormal
    {205, 239, 247,255},                 // buttonHovered
    {234, 255, 255,255},                 // buttonPressed
    {92, 149, 146,255},                   // textNormal
    {95, 136, 147,255},                   // textHovered
    {54, 87, 91, 255},                   // textPressed
    {92, 149, 146,255},                   // outlineButtonColor
    {95, 136, 147,255},                  // outlineButtonHoveredColor
    {54, 87, 91, 255},                  // outlineButtonPressedColor

    {54, 87, 91,255},                               // codeBlockTextColor
    {255, 255, 255,255},                    // codeBlockHighlightColor


    {205, 239, 247,255},                         // nodeColor
    {95, 136, 147,255},                   // nodeTextColor
    {255, 255, 255,255},                       // nodeHighlightColor
    {54, 87, 91,255},                   // nodeHighlightTextColor

    {54, 87, 91, 255},                         // nodeCostColor
    {200, 215, 217,255},                       // nodeKnownColor
    {143, 164, 166,255},                         // nodeKnownTextColor
    {255, 255, 255,255},                       // lineColor
    {54, 87, 91, 255},                         // lineTextColor

    LIGHTGRAY,                           // boxColor
    BLACK                                 // boxTextColor
};


//Menu
extern Color appTitleColor;
extern Color backgroundColor;

//button
extern Color dataTitleColor;
extern Color dataTitleTextColor;

extern Color buttonNormal;
extern Color buttonHovered;
extern Color buttonPressed;
extern Color textButtonNormal;
extern Color textButtonHovered;
extern Color textButtonPressed;
extern Color outlineButtonColor;
extern Color outlineButtonHoveredColor;
extern Color outlineButtonPressedColor;

//CodeBlock
extern Color codeBlockTextColor;
extern Color codeBlockHighlightColor;

//Data
extern Color nodeColor;
extern Color nodeTextColor;

extern Color nodeHighlightColor;
extern Color nodeHighlightTextColor;

//Shortest Path
extern Color nodeCostColor;
extern Color nodeKnownColor;
extern Color nodeKnownTextColor;
extern Color lineColor;
extern Color lineTextColor;

extern Color boxColor;
extern Color boxTextColor;

struct ButtonTheme{
    Texture2D DefaultNormal;
    Texture2D DefaultHovered;
    Texture2D DefaultPressed;
    Texture2D SunnyNormal;
    Texture2D SunnyHovered;
    Texture2D SunnyPressed;
    Texture2D RltechNormal;
    Texture2D RltechHovered;
    Texture2D RltechPressed;
    Texture2D LavandaNormal;
    Texture2D LavandaHovered;
    Texture2D LavandaPressed;
    Texture2D EnefeteNormal;
    Texture2D EnefeteHovered;
    Texture2D EnefetePressed;
    Texture2D DarkNormal;
    Texture2D DarkHovered;
    Texture2D DarkPressed;
    Texture2D CyberNormal;
    Texture2D CyberHovered;
    Texture2D CyberPressed;
    Texture2D CandyNormal;
    Texture2D CandyHovered;
    Texture2D CandyPressed;
    Texture2D TerminalNormal;
    Texture2D TerminalHovered;
    Texture2D TerminalPressed;
    Texture2D BluishNormal;
    Texture2D BluishHovered;
    Texture2D BluishPressed;
};

extern ButtonTheme settingButtonTheme;
extern ButtonTheme playButtonTheme;
extern ButtonTheme nextButtonTheme;
extern ButtonTheme prevButtonTheme;
extern ButtonTheme pauseButtonTheme;
extern ButtonTheme startButtonTheme;
extern ButtonTheme endButtonTheme;
extern ButtonTheme reloadButtonTheme;
extern ButtonTheme exitButtonTheme;

extern Font codeBlockFont;
extern Font inputBoxFont;
extern Font inputBoxNameFont;
extern Font buttonFont;

#endif