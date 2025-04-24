#include <GUI/ColorThemeManager.h>

StyleTheme currentTheme = StyleTheme::DEF;

ColorThemeManager::ColorThemeManager() {
    currentTheme = StyleTheme::DEF;
    setColorTheme();

    panel={500,250,600,300};

    settingTheme.setSize(backSize);
    settingTheme.setPosition({1600-15-25,15+25});
    settingTheme.setTexture(settingButtonTheme);

    def.setSize(themeButtonSize);
    sunny.setSize(themeButtonSize);
    rltech.setSize(themeButtonSize);
    lavanda.setSize(themeButtonSize);
    enefete.setSize(themeButtonSize);
    dark.setSize(themeButtonSize);
    cyber.setSize(themeButtonSize);
    candy.setSize(themeButtonSize);
    terminal.setSize(themeButtonSize);
    bluish.setSize(themeButtonSize);
    def.setPosition({570,365});
    sunny.setPosition({685,365});
    rltech.setPosition({800,365});
    lavanda.setPosition({915,365});
    enefete.setPosition({1030,365});
    dark.setPosition({570,480});
    cyber.setPosition({685,480});
    candy.setPosition({800,480});
    terminal.setPosition({915,480}); 
    bluish.setPosition({1030,480});
    def.setText("Default", themeButtonFontSize);
    sunny.setText("Sunny", themeButtonFontSize);
    rltech.setText("RLTech", themeButtonFontSize);
    lavanda.setText("Lavanda", themeButtonFontSize);
    enefete.setText("EneFete", themeButtonFontSize);
    dark.setText("Dark", themeButtonFontSize);
    cyber.setText("Cyber", themeButtonFontSize);
    candy.setText("Candy", themeButtonFontSize);
    terminal.setText("Terminal", themeButtonFontSize);
    bluish.setText("Bluish", themeButtonFontSize);
}

void ColorThemeManager::setColorTheme(){
    switch (currentTheme) {
        case StyleTheme::DEF:
            applyTheme(Default);
            break;
        case StyleTheme::SUNNY:
            applyTheme(Sunny);
            break;
        case StyleTheme::RLTECH:
            applyTheme(RLTech);
            break;
        case StyleTheme::LAVANDA:
            applyTheme(Lavanda);
            break;
        case StyleTheme::ENEFETE:
            applyTheme(EneFete);
            break;
        case StyleTheme::DARK:
            applyTheme(Dark);
            break;
        case StyleTheme::CYBER:
            applyTheme(Cyber);
            break;
        case StyleTheme::CANDY:
            applyTheme(Candy);
            break;
        case StyleTheme::TERMINAL:
            applyTheme(Terminal);
            break;
        case StyleTheme::BLUISH:
            applyTheme(Bluish);
            break;
        default:
            break;
    }
}

void ColorThemeManager::applyTheme(ColorTheme theme) {
    isUpdate = false;
    appTitleColor = theme.appTitleColor;
    backgroundColor = theme.backgroundColor;

    dataTitleColor = theme.dataTitleColor;
    dataTitleTextColor = theme.dataTitleTextColor;
    buttonNormal = theme.buttonNormal;
    buttonHovered = theme.buttonHovered;
    buttonPressed = theme.buttonPressed;
    textButtonNormal = theme.textButtonNormal;
    textButtonHovered = theme.textButtonHovered;
    textButtonPressed = theme.textButtonPressed;
    outlineButtonColor = theme.outlineButtonColor;
    outlineButtonHoveredColor = theme.outlineButtonHoveredColor;
    outlineButtonPressedColor = theme.outlineButtonPressedColor;

    codeBlockTextColor = theme.codeBlockTextColor;
    codeBlockHighlightColor = theme.codeBlockHighlightColor;
    
    nodeColor = theme.nodeColor;
    nodeTextColor = theme.nodeTextColor;

    nodeHighlightColor = theme.nodeHighlightColor;
    nodeHighlightTextColor = theme.nodeHighlightTextColor;

    nodeCostColor = theme.nodeCostColor;
    nodeKnownColor = theme.nodeKnownColor;
    nodeKnownTextColor = theme.nodeKnownTextColor;
    lineColor = theme.lineColor;
    lineTextColor = theme.lineTextColor;

    boxColor = theme.boxColor;
    boxTextColor = theme.boxTextColor;
}

void ColorThemeManager::update() {
    settingTheme.setTexture(settingButtonTheme);
    settingTheme.update();
    if(settingTheme.isPressed()||(isTheme && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&!CheckCollisionPointRec(GetMousePosition(), panel))){
        isTheme = !isTheme;
    }
    if(isTheme){
        def.update(Default);
        sunny.update(Sunny);
        rltech.update(RLTech);
        lavanda.update(Lavanda);
        enefete.update(EneFete);
        dark.update(Dark);
        cyber.update(Cyber);
        candy.update(Candy);
        terminal.update(Terminal);
        bluish.update(Bluish);

        if(def.isPressed()){
            currentTheme = StyleTheme::DEF;
            setColorTheme();
        }
        if(sunny.isPressed()){
            currentTheme = StyleTheme::SUNNY;
            setColorTheme();
        }
        if(rltech.isPressed()){
            currentTheme = StyleTheme::RLTECH;
            setColorTheme();
        }
        if(lavanda.isPressed()){
            currentTheme = StyleTheme::LAVANDA;
            setColorTheme();
        }
        if(enefete.isPressed()){
            currentTheme = StyleTheme::ENEFETE;
            setColorTheme();
        }
        if(dark.isPressed()){
            currentTheme = StyleTheme::DARK;
            setColorTheme();
        }
        if(cyber.isPressed()){
            currentTheme = StyleTheme::CYBER;
            setColorTheme();
        }
        if(candy.isPressed()){
            currentTheme = StyleTheme::CANDY;
            setColorTheme();
        }
        if(terminal.isPressed()){
            currentTheme = StyleTheme::TERMINAL;
            setColorTheme();
        }
        if(bluish.isPressed()){
            currentTheme = StyleTheme::BLUISH;
            setColorTheme();
        }
    }
}

void ColorThemeManager::draw(){
    if(isTheme){
        DrawRectangle(0,0,1600,900,Fade(BLACK,0.5f));
        DrawRectangleRounded(panel, 0, 0, buttonNormal); 
        DrawRectangleRoundedLinesEx(panel, 0, 0, 1, BLACK);
        DrawText("Theme", 800-MeasureText("Theme",30)/2.0f, 290-15 , 30, textButtonNormal);
        def.drawRectangleRounded(0);
        sunny.drawRectangleRounded(0);
        rltech.drawRectangleRounded(0);
        lavanda.drawRectangleRounded(0);
        enefete.drawRectangleRounded(0);
        dark.drawRectangleRounded(0);
        cyber.drawRectangleRounded(0);
        candy.drawRectangleRounded(0);
        terminal.drawRectangleRounded(0);
        bluish.drawRectangleRounded(0);
        def.drawOutlineRounded(0, 0, 5);
        sunny.drawOutlineRounded(0, 0, 5);
        rltech.drawOutlineRounded(0, 0, 5);
        lavanda.drawOutlineRounded(0, 0, 5);
        enefete.drawOutlineRounded(0, 0, 5);
        dark.drawOutlineRounded(0, 0, 5);
        cyber.drawOutlineRounded(0, 0, 5);
        candy.drawOutlineRounded(0, 0, 5);
        terminal.drawOutlineRounded(0, 0, 5);
        bluish.drawOutlineRounded(0, 0, 5);
        def.drawText();
        sunny.drawText();
        rltech.drawText();
        lavanda.drawText();
        enefete.drawText();
        dark.drawText();
        cyber.drawText();
        candy.drawText();
        terminal.drawText();
        bluish.drawText();
    }
    settingTheme.drawRectangleRounded(100);
    settingTheme.drawOutlineRounded(100, 0, 3);
    settingTheme.drawTexture();
}

//Menu
Color appTitleColor({BLACK});
Color backgroundColor({WHITE});

//Panel
Color dataTitleColor({185,185,185,255});
Color dataTitleTextColor({BLACK});
Color buttonNormal({161,161,161,255});
Color buttonHovered({133,133,133,255});
Color buttonPressed({110,110,110,255});
Color textButtonNormal({BLACK});
Color textButtonHovered({BLACK});
Color textButtonPressed({BLACK});
Color outlineButtonColor({0,0,0,255});
Color outlineButtonHoveredColor({0,0,0,255});
Color outlineButtonPressedColor({0,0,0,255});

//CodeBlock
Color codeBlockTextColor({0,0,0,255});
Color codeBlockHighlightColor({255,253,85,255});

//Data
Color nodeColor({0,0,0,255});
Color nodeTextColor({255,255,255,255});

Color nodeHighlightColor({255,0,0,255});
Color nodeHighlightTextColor({255,255,255,255});

//Shortest Path
Color nodeCostColor({0,0,0,255});
Color nodeKnownColor({0,255,0,255});
Color nodeKnownTextColor({0,0,0,255});
Color lineColor({0,0,255,255});
Color lineTextColor({0,0,0,255});

Color boxColor({LIGHTGRAY});
Color boxTextColor({BLACK});

ButtonTheme settingButtonTheme;
ButtonTheme playButtonTheme;
ButtonTheme nextButtonTheme;
ButtonTheme prevButtonTheme;
ButtonTheme pauseButtonTheme;
ButtonTheme startButtonTheme;
ButtonTheme endButtonTheme;
ButtonTheme reloadButtonTheme;
ButtonTheme exitButtonTheme;

Font codeBlockFont;
Font inputBoxFont;
Font inputBoxNameFont;
Font buttonFont;
float tempSpeed = 0.05f;

void LoadFontsAndTextures(){
    codeBlockFont = LoadFont("../resources/RobotoMono-Regular.ttf");
    inputBoxFont = LoadFont("../resources/Inter_28pt-Regular.ttf");
    inputBoxNameFont = LoadFont("../resources/UbuntuMono-Regular.ttf");
    buttonFont = LoadFont("../resources/Ubuntu-Bold.ttf");

    settingButtonTheme.DefaultNormal = LoadTexture("../resources/settingDefaultNormal.png");
    settingButtonTheme.DefaultHovered = LoadTexture("../resources/settingDefaultHovered.png");
    settingButtonTheme.DefaultPressed = LoadTexture("../resources/settingDefaultPressed.png");
    settingButtonTheme.SunnyNormal = LoadTexture("../resources/settingSunnyNormal.png");
    settingButtonTheme.SunnyHovered = LoadTexture("../resources/settingSunnyHovered.png");
    settingButtonTheme.SunnyPressed = LoadTexture("../resources/settingSunnyPressed.png");
    settingButtonTheme.RltechNormal = LoadTexture("../resources/settingRltechNormal.png");
    settingButtonTheme.RltechHovered = LoadTexture("../resources/settingRltechHovered.png");
    settingButtonTheme.RltechPressed = LoadTexture("../resources/settingRltechPressed.png");
    settingButtonTheme.LavandaNormal = LoadTexture("../resources/settingLavandaNormal.png");
    settingButtonTheme.LavandaHovered = LoadTexture("../resources/settingLavandaHovered.png");
    settingButtonTheme.LavandaPressed = LoadTexture("../resources/settingLavandaPressed.png");
    settingButtonTheme.EnefeteNormal = LoadTexture("../resources/settingEnefeteNormal.png");
    settingButtonTheme.EnefeteHovered = LoadTexture("../resources/settingEnefeteHovered.png");
    settingButtonTheme.EnefetePressed = LoadTexture("../resources/settingEnefetePressed.png");
    settingButtonTheme.DarkNormal = LoadTexture("../resources/settingDarkNormal.png");
    settingButtonTheme.DarkHovered = LoadTexture("../resources/settingDarkHovered.png");
    settingButtonTheme.DarkPressed = LoadTexture("../resources/settingDarkPressed.png");
    settingButtonTheme.CyberNormal = LoadTexture("../resources/settingCyberNormal.png");
    settingButtonTheme.CyberHovered = LoadTexture("../resources/settingCyberHovered.png");
    settingButtonTheme.CyberPressed = LoadTexture("../resources/settingCyberPressed.png");
    settingButtonTheme.CandyNormal = LoadTexture("../resources/settingCandyNormal.png");
    settingButtonTheme.CandyHovered = LoadTexture("../resources/settingCandyHovered.png");
    settingButtonTheme.CandyPressed = LoadTexture("../resources/settingCandyPressed.png");
    settingButtonTheme.TerminalNormal = LoadTexture("../resources/settingTerminalNormal.png");
    settingButtonTheme.TerminalHovered = LoadTexture("../resources/settingTerminalHovered.png");
    settingButtonTheme.TerminalPressed = LoadTexture("../resources/settingTerminalPressed.png");
    settingButtonTheme.BluishNormal = LoadTexture("../resources/settingBluishNormal.png");
    settingButtonTheme.BluishHovered = LoadTexture("../resources/settingBluishHovered.png");
    settingButtonTheme.BluishPressed = LoadTexture("../resources/settingBluishPressed.png");
    playButtonTheme.DefaultNormal = LoadTexture("../resources/playDefaultNormal.png");
    playButtonTheme.DefaultHovered = LoadTexture("../resources/playDefaultHovered.png");
    playButtonTheme.DefaultPressed = LoadTexture("../resources/playDefaultPressed.png");
    playButtonTheme.SunnyNormal = LoadTexture("../resources/playSunnyNormal.png");
    playButtonTheme.SunnyHovered = LoadTexture("../resources/playSunnyHovered.png");
    playButtonTheme.SunnyPressed = LoadTexture("../resources/playSunnyPressed.png");
    playButtonTheme.RltechNormal = LoadTexture("../resources/playRltechNormal.png");
    playButtonTheme.RltechHovered = LoadTexture("../resources/playRltechHovered.png");
    playButtonTheme.RltechPressed = LoadTexture("../resources/playRltechPressed.png");
    playButtonTheme.LavandaNormal = LoadTexture("../resources/playLavandaNormal.png");
    playButtonTheme.LavandaHovered = LoadTexture("../resources/playLavandaHovered.png");
    playButtonTheme.LavandaPressed = LoadTexture("../resources/playLavandaPressed.png");
    playButtonTheme.EnefeteNormal = LoadTexture("../resources/playEnefeteNormal.png");
    playButtonTheme.EnefeteHovered = LoadTexture("../resources/playEnefeteHovered.png");
    playButtonTheme.EnefetePressed = LoadTexture("../resources/playEnefetePressed.png");
    playButtonTheme.DarkNormal = LoadTexture("../resources/playDarkNormal.png");
    playButtonTheme.DarkHovered = LoadTexture("../resources/playDarkHovered.png");
    playButtonTheme.DarkPressed = LoadTexture("../resources/playDarkPressed.png");
    playButtonTheme.CyberNormal = LoadTexture("../resources/playCyberNormal.png");
    playButtonTheme.CyberHovered = LoadTexture("../resources/playCyberHovered.png");
    playButtonTheme.CyberPressed = LoadTexture("../resources/playCyberPressed.png");
    playButtonTheme.CandyNormal = LoadTexture("../resources/playCandyNormal.png");
    playButtonTheme.CandyHovered = LoadTexture("../resources/playCandyHovered.png");
    playButtonTheme.CandyPressed = LoadTexture("../resources/playCandyPressed.png");
    playButtonTheme.TerminalNormal = LoadTexture("../resources/playTerminalNormal.png");
    playButtonTheme.TerminalHovered = LoadTexture("../resources/playTerminalHovered.png");
    playButtonTheme.TerminalPressed = LoadTexture("../resources/playTerminalPressed.png");
    playButtonTheme.BluishNormal = LoadTexture("../resources/playBluishNormal.png");
    playButtonTheme.BluishHovered = LoadTexture("../resources/playBluishHovered.png");
    playButtonTheme.BluishPressed = LoadTexture("../resources/playBluishPressed.png");
    nextButtonTheme.DefaultNormal = LoadTexture("../resources/forwardDefaultNormal.png");
    nextButtonTheme.DefaultHovered = LoadTexture("../resources/forwardDefaultHovered.png");
    nextButtonTheme.DefaultPressed = LoadTexture("../resources/forwardDefaultPressed.png");
    nextButtonTheme.SunnyNormal = LoadTexture("../resources/forwardSunnyNormal.png");
    nextButtonTheme.SunnyHovered = LoadTexture("../resources/forwardSunnyHovered.png");
    nextButtonTheme.SunnyPressed = LoadTexture("../resources/forwardSunnyPressed.png");
    nextButtonTheme.RltechNormal = LoadTexture("../resources/forwardRltechNormal.png");
    nextButtonTheme.RltechHovered = LoadTexture("../resources/forwardRltechHovered.png");
    nextButtonTheme.RltechPressed = LoadTexture("../resources/forwardRltechPressed.png");
    nextButtonTheme.LavandaNormal = LoadTexture("../resources/forwardLavandaNormal.png");
    nextButtonTheme.LavandaHovered = LoadTexture("../resources/forwardLavandaHovered.png");
    nextButtonTheme.LavandaPressed = LoadTexture("../resources/forwardLavandaPressed.png");
    nextButtonTheme.EnefeteNormal = LoadTexture("../resources/forwardEnefeteNormal.png");
    nextButtonTheme.EnefeteHovered = LoadTexture("../resources/forwardEnefeteHovered.png");
    nextButtonTheme.EnefetePressed = LoadTexture("../resources/forwardEnefetePressed.png");
    nextButtonTheme.DarkNormal = LoadTexture("../resources/forwardDarkNormal.png");
    nextButtonTheme.DarkHovered = LoadTexture("../resources/forwardDarkHovered.png");
    nextButtonTheme.DarkPressed = LoadTexture("../resources/forwardDarkPressed.png");
    nextButtonTheme.CyberNormal = LoadTexture("../resources/forwardCyberNormal.png");
    nextButtonTheme.CyberHovered = LoadTexture("../resources/forwardCyberHovered.png");
    nextButtonTheme.CyberPressed = LoadTexture("../resources/forwardCyberPressed.png");
    nextButtonTheme.CandyNormal = LoadTexture("../resources/forwardCandyNormal.png");
    nextButtonTheme.CandyHovered = LoadTexture("../resources/forwardCandyHovered.png");
    nextButtonTheme.CandyPressed = LoadTexture("../resources/forwardCandyPressed.png");
    nextButtonTheme.TerminalNormal = LoadTexture("../resources/forwardTerminalNormal.png");
    nextButtonTheme.TerminalHovered = LoadTexture("../resources/forwardTerminalHovered.png");
    nextButtonTheme.TerminalPressed = LoadTexture("../resources/forwardTerminalPressed.png");
    nextButtonTheme.BluishNormal = LoadTexture("../resources/forwardBluishNormal.png");
    nextButtonTheme.BluishHovered = LoadTexture("../resources/forwardBluishHovered.png");
    nextButtonTheme.BluishPressed = LoadTexture("../resources/forwardBluishPressed.png");
    prevButtonTheme.DefaultNormal = LoadTexture("../resources/backwardDefaultNormal.png");
    prevButtonTheme.DefaultHovered = LoadTexture("../resources/backwardDefaultHovered.png");
    prevButtonTheme.DefaultPressed = LoadTexture("../resources/backwardDefaultPressed.png");
    prevButtonTheme.SunnyNormal = LoadTexture("../resources/backwardSunnyNormal.png");
    prevButtonTheme.SunnyHovered = LoadTexture("../resources/backwardSunnyHovered.png");
    prevButtonTheme.SunnyPressed = LoadTexture("../resources/backwardSunnyPressed.png");
    prevButtonTheme.RltechNormal = LoadTexture("../resources/backwardRltechNormal.png");
    prevButtonTheme.RltechHovered = LoadTexture("../resources/backwardRltechHovered.png");
    prevButtonTheme.RltechPressed = LoadTexture("../resources/backwardRltechPressed.png");
    prevButtonTheme.LavandaNormal = LoadTexture("../resources/backwardLavandaNormal.png");
    prevButtonTheme.LavandaHovered = LoadTexture("../resources/backwardLavandaHovered.png");
    prevButtonTheme.LavandaPressed = LoadTexture("../resources/backwardLavandaPressed.png");
    prevButtonTheme.EnefeteNormal = LoadTexture("../resources/backwardEnefeteNormal.png");
    prevButtonTheme.EnefeteHovered = LoadTexture("../resources/backwardEnefeteHovered.png");
    prevButtonTheme.EnefetePressed = LoadTexture("../resources/backwardEnefetePressed.png");
    prevButtonTheme.DarkNormal = LoadTexture("../resources/backwardDarkNormal.png");
    prevButtonTheme.DarkHovered = LoadTexture("../resources/backwardDarkHovered.png");
    prevButtonTheme.DarkPressed = LoadTexture("../resources/backwardDarkPressed.png");
    prevButtonTheme.CyberNormal = LoadTexture("../resources/backwardCyberNormal.png");
    prevButtonTheme.CyberHovered = LoadTexture("../resources/backwardCyberHovered.png");
    prevButtonTheme.CyberPressed = LoadTexture("../resources/backwardCyberPressed.png");
    prevButtonTheme.CandyNormal = LoadTexture("../resources/backwardCandyNormal.png");
    prevButtonTheme.CandyHovered = LoadTexture("../resources/backwardCandyHovered.png");
    prevButtonTheme.CandyPressed = LoadTexture("../resources/backwardCandyPressed.png");
    prevButtonTheme.TerminalNormal = LoadTexture("../resources/backwardTerminalNormal.png");
    prevButtonTheme.TerminalHovered = LoadTexture("../resources/backwardTerminalHovered.png");
    prevButtonTheme.TerminalPressed = LoadTexture("../resources/backwardTerminalPressed.png");
    prevButtonTheme.BluishNormal = LoadTexture("../resources/backwardBluishNormal.png");
    prevButtonTheme.BluishHovered = LoadTexture("../resources/backwardBluishHovered.png");
    prevButtonTheme.BluishPressed = LoadTexture("../resources/backwardBluishPressed.png");
    pauseButtonTheme.DefaultNormal = LoadTexture("../resources/pauseDefaultNormal.png");
    pauseButtonTheme.DefaultHovered = LoadTexture("../resources/pauseDefaultHovered.png");
    pauseButtonTheme.DefaultPressed = LoadTexture("../resources/pauseDefaultPressed.png");
    pauseButtonTheme.SunnyNormal = LoadTexture("../resources/pauseSunnyNormal.png");
    pauseButtonTheme.SunnyHovered = LoadTexture("../resources/pauseSunnyHovered.png");
    pauseButtonTheme.SunnyPressed = LoadTexture("../resources/pauseSunnyPressed.png");
    pauseButtonTheme.RltechNormal = LoadTexture("../resources/pauseRltechNormal.png");
    pauseButtonTheme.RltechHovered = LoadTexture("../resources/pauseRltechHovered.png");
    pauseButtonTheme.RltechPressed = LoadTexture("../resources/pauseRltechPressed.png");
    pauseButtonTheme.LavandaNormal = LoadTexture("../resources/pauseLavandaNormal.png");
    pauseButtonTheme.LavandaHovered = LoadTexture("../resources/pauseLavandaHovered.png");
    pauseButtonTheme.LavandaPressed = LoadTexture("../resources/pauseLavandaPressed.png");
    pauseButtonTheme.EnefeteNormal = LoadTexture("../resources/pauseEnefeteNormal.png");
    pauseButtonTheme.EnefeteHovered = LoadTexture("../resources/pauseEnefeteHovered.png");
    pauseButtonTheme.EnefetePressed = LoadTexture("../resources/pauseEnefetePressed.png");
    pauseButtonTheme.DarkNormal = LoadTexture("../resources/pauseDarkNormal.png");
    pauseButtonTheme.DarkHovered = LoadTexture("../resources/pauseDarkHovered.png");
    pauseButtonTheme.DarkPressed = LoadTexture("../resources/pauseDarkPressed.png");
    pauseButtonTheme.CyberNormal = LoadTexture("../resources/pauseCyberNormal.png");
    pauseButtonTheme.CyberHovered = LoadTexture("../resources/pauseCyberHovered.png");
    pauseButtonTheme.CyberPressed = LoadTexture("../resources/pauseCyberPressed.png");
    pauseButtonTheme.CandyNormal = LoadTexture("../resources/pauseCandyNormal.png");
    pauseButtonTheme.CandyHovered = LoadTexture("../resources/pauseCandyHovered.png");
    pauseButtonTheme.CandyPressed = LoadTexture("../resources/pauseCandyPressed.png");
    pauseButtonTheme.TerminalNormal = LoadTexture("../resources/pauseTerminalNormal.png");
    pauseButtonTheme.TerminalHovered = LoadTexture("../resources/pauseTerminalHovered.png");
    pauseButtonTheme.TerminalPressed = LoadTexture("../resources/pauseTerminalPressed.png");
    pauseButtonTheme.BluishNormal = LoadTexture("../resources/pauseBluishNormal.png");
    pauseButtonTheme.BluishHovered = LoadTexture("../resources/pauseBluishHovered.png");
    pauseButtonTheme.BluishPressed = LoadTexture("../resources/pauseBluishPressed.png");
    startButtonTheme.DefaultNormal = LoadTexture("../resources/startDefaultNormal.png");
    startButtonTheme.DefaultHovered = LoadTexture("../resources/startDefaultHovered.png");
    startButtonTheme.DefaultPressed = LoadTexture("../resources/startDefaultPressed.png");
    startButtonTheme.SunnyNormal = LoadTexture("../resources/startSunnyNormal.png");
    startButtonTheme.SunnyHovered = LoadTexture("../resources/startSunnyHovered.png");
    startButtonTheme.SunnyPressed = LoadTexture("../resources/startSunnyPressed.png");
    startButtonTheme.RltechNormal = LoadTexture("../resources/startRltechNormal.png");
    startButtonTheme.RltechHovered = LoadTexture("../resources/startRltechHovered.png");
    startButtonTheme.RltechPressed = LoadTexture("../resources/startRltechPressed.png");
    startButtonTheme.LavandaNormal = LoadTexture("../resources/startLavandaNormal.png");
    startButtonTheme.LavandaHovered = LoadTexture("../resources/startLavandaHovered.png");
    startButtonTheme.LavandaPressed = LoadTexture("../resources/startLavandaPressed.png");
    startButtonTheme.EnefeteNormal = LoadTexture("../resources/startEnefeteNormal.png");
    startButtonTheme.EnefeteHovered = LoadTexture("../resources/startEnefeteHovered.png");
    startButtonTheme.EnefetePressed = LoadTexture("../resources/startEnefetePressed.png");
    startButtonTheme.DarkNormal = LoadTexture("../resources/startDarkNormal.png");
    startButtonTheme.DarkHovered = LoadTexture("../resources/startDarkHovered.png");
    startButtonTheme.DarkPressed = LoadTexture("../resources/startDarkPressed.png");
    startButtonTheme.CyberNormal = LoadTexture("../resources/startCyberNormal.png");
    startButtonTheme.CyberHovered = LoadTexture("../resources/startCyberHovered.png");
    startButtonTheme.CyberPressed = LoadTexture("../resources/startCyberPressed.png");
    startButtonTheme.CandyNormal = LoadTexture("../resources/startCandyNormal.png");
    startButtonTheme.CandyHovered = LoadTexture("../resources/startCandyHovered.png");
    startButtonTheme.CandyPressed = LoadTexture("../resources/startCandyPressed.png");
    startButtonTheme.TerminalNormal = LoadTexture("../resources/startTerminalNormal.png");
    startButtonTheme.TerminalHovered = LoadTexture("../resources/startTerminalHovered.png");
    startButtonTheme.TerminalPressed = LoadTexture("../resources/startTerminalPressed.png");
    startButtonTheme.BluishNormal = LoadTexture("../resources/startBluishNormal.png");
    startButtonTheme.BluishHovered = LoadTexture("../resources/startBluishHovered.png");
    startButtonTheme.BluishPressed = LoadTexture("../resources/startBluishPressed.png");
    endButtonTheme.DefaultNormal = LoadTexture("../resources/endDefaultNormal.png");
    endButtonTheme.DefaultHovered = LoadTexture("../resources/endDefaultHovered.png");
    endButtonTheme.DefaultPressed = LoadTexture("../resources/endDefaultPressed.png");
    endButtonTheme.SunnyNormal = LoadTexture("../resources/endSunnyNormal.png");
    endButtonTheme.SunnyHovered = LoadTexture("../resources/endSunnyHovered.png");
    endButtonTheme.SunnyPressed = LoadTexture("../resources/endSunnyPressed.png");
    endButtonTheme.RltechNormal = LoadTexture("../resources/endRltechNormal.png");
    endButtonTheme.RltechHovered = LoadTexture("../resources/endRltechHovered.png");
    endButtonTheme.RltechPressed = LoadTexture("../resources/endRltechPressed.png");
    endButtonTheme.LavandaNormal = LoadTexture("../resources/endLavandaNormal.png");
    endButtonTheme.LavandaHovered = LoadTexture("../resources/endLavandaHovered.png");
    endButtonTheme.LavandaPressed = LoadTexture("../resources/endLavandaPressed.png");
    endButtonTheme.EnefeteNormal = LoadTexture("../resources/endEnefeteNormal.png");
    endButtonTheme.EnefeteHovered = LoadTexture("../resources/endEnefeteHovered.png");
    endButtonTheme.EnefetePressed = LoadTexture("../resources/endEnefetePressed.png");
    endButtonTheme.DarkNormal = LoadTexture("../resources/endDarkNormal.png");
    endButtonTheme.DarkHovered = LoadTexture("../resources/endDarkHovered.png");
    endButtonTheme.DarkPressed = LoadTexture("../resources/endDarkPressed.png");
    endButtonTheme.CyberNormal = LoadTexture("../resources/endCyberNormal.png");
    endButtonTheme.CyberHovered = LoadTexture("../resources/endCyberHovered.png");
    endButtonTheme.CyberPressed = LoadTexture("../resources/endCyberPressed.png");
    endButtonTheme.CandyNormal = LoadTexture("../resources/endCandyNormal.png");
    endButtonTheme.CandyHovered = LoadTexture("../resources/endCandyHovered.png");
    endButtonTheme.CandyPressed = LoadTexture("../resources/endCandyPressed.png");
    endButtonTheme.TerminalNormal = LoadTexture("../resources/endTerminalNormal.png");
    endButtonTheme.TerminalHovered = LoadTexture("../resources/endTerminalHovered.png");
    endButtonTheme.TerminalPressed = LoadTexture("../resources/endTerminalPressed.png");
    endButtonTheme.BluishNormal = LoadTexture("../resources/endBluishNormal.png");
    endButtonTheme.BluishHovered = LoadTexture("../resources/endBluishHovered.png");
    endButtonTheme.BluishPressed = LoadTexture("../resources/endBluishPressed.png");
    reloadButtonTheme.DefaultNormal = LoadTexture("../resources/reloadDefaultNormal.png");
    reloadButtonTheme.DefaultHovered = LoadTexture("../resources/reloadDefaultHovered.png");
    reloadButtonTheme.DefaultPressed = LoadTexture("../resources/reloadDefaultPressed.png");
    reloadButtonTheme.SunnyNormal = LoadTexture("../resources/reloadSunnyNormal.png");
    reloadButtonTheme.SunnyHovered = LoadTexture("../resources/reloadSunnyHovered.png");
    reloadButtonTheme.SunnyPressed = LoadTexture("../resources/reloadSunnyPressed.png");
    reloadButtonTheme.RltechNormal = LoadTexture("../resources/reloadRltechNormal.png");
    reloadButtonTheme.RltechHovered = LoadTexture("../resources/reloadRltechHovered.png");
    reloadButtonTheme.RltechPressed = LoadTexture("../resources/reloadRltechPressed.png");
    reloadButtonTheme.LavandaNormal = LoadTexture("../resources/reloadLavandaNormal.png");
    reloadButtonTheme.LavandaHovered = LoadTexture("../resources/reloadLavandaHovered.png");
    reloadButtonTheme.LavandaPressed = LoadTexture("../resources/reloadLavandaPressed.png");
    reloadButtonTheme.EnefeteNormal = LoadTexture("../resources/reloadEnefeteNormal.png");
    reloadButtonTheme.EnefeteHovered = LoadTexture("../resources/reloadEnefeteHovered.png");
    reloadButtonTheme.EnefetePressed = LoadTexture("../resources/reloadEnefetePressed.png");
    reloadButtonTheme.DarkNormal = LoadTexture("../resources/reloadDarkNormal.png");
    reloadButtonTheme.DarkHovered = LoadTexture("../resources/reloadDarkHovered.png");
    reloadButtonTheme.DarkPressed = LoadTexture("../resources/reloadDarkPressed.png");
    reloadButtonTheme.CyberNormal = LoadTexture("../resources/reloadCyberNormal.png");
    reloadButtonTheme.CyberHovered = LoadTexture("../resources/reloadCyberHovered.png");
    reloadButtonTheme.CyberPressed = LoadTexture("../resources/reloadCyberPressed.png");
    reloadButtonTheme.CandyNormal = LoadTexture("../resources/reloadCandyNormal.png");
    reloadButtonTheme.CandyHovered = LoadTexture("../resources/reloadCandyHovered.png");
    reloadButtonTheme.CandyPressed = LoadTexture("../resources/reloadCandyPressed.png");
    reloadButtonTheme.TerminalNormal = LoadTexture("../resources/reloadTerminalNormal.png");
    reloadButtonTheme.TerminalHovered = LoadTexture("../resources/reloadTerminalHovered.png");
    reloadButtonTheme.TerminalPressed = LoadTexture("../resources/reloadTerminalPressed.png");
    reloadButtonTheme.BluishNormal = LoadTexture("../resources/reloadBluishNormal.png");
    reloadButtonTheme.BluishHovered = LoadTexture("../resources/reloadBluishHovered.png");
    reloadButtonTheme.BluishPressed = LoadTexture("../resources/reloadBluishPressed.png");
    exitButtonTheme.DefaultNormal = LoadTexture("../resources/exitDefaultNormal.png");
    exitButtonTheme.DefaultHovered = LoadTexture("../resources/exitDefaultHovered.png");
    exitButtonTheme.DefaultPressed = LoadTexture("../resources/exitDefaultPressed.png");
    exitButtonTheme.SunnyNormal = LoadTexture("../resources/exitSunnyNormal.png");
    exitButtonTheme.SunnyHovered = LoadTexture("../resources/exitSunnyHovered.png");
    exitButtonTheme.SunnyPressed = LoadTexture("../resources/exitSunnyPressed.png");
    exitButtonTheme.RltechNormal = LoadTexture("../resources/exitRltechNormal.png");
    exitButtonTheme.RltechHovered = LoadTexture("../resources/exitRltechHovered.png");
    exitButtonTheme.RltechPressed = LoadTexture("../resources/exitRltechPressed.png");
    exitButtonTheme.LavandaNormal = LoadTexture("../resources/exitLavandaNormal.png");
    exitButtonTheme.LavandaHovered = LoadTexture("../resources/exitLavandaHovered.png");
    exitButtonTheme.LavandaPressed = LoadTexture("../resources/exitLavandaPressed.png");
    exitButtonTheme.EnefeteNormal = LoadTexture("../resources/exitEnefeteNormal.png");
    exitButtonTheme.EnefeteHovered = LoadTexture("../resources/exitEnefeteHovered.png");
    exitButtonTheme.EnefetePressed = LoadTexture("../resources/exitEnefetePressed.png");
    exitButtonTheme.DarkNormal = LoadTexture("../resources/exitDarkNormal.png");
    exitButtonTheme.DarkHovered = LoadTexture("../resources/exitDarkHovered.png");
    exitButtonTheme.DarkPressed = LoadTexture("../resources/exitDarkPressed.png");
    exitButtonTheme.CyberNormal = LoadTexture("../resources/exitCyberNormal.png");
    exitButtonTheme.CyberHovered = LoadTexture("../resources/exitCyberHovered.png");
    exitButtonTheme.CyberPressed = LoadTexture("../resources/exitCyberPressed.png");
    exitButtonTheme.CandyNormal = LoadTexture("../resources/exitCandyNormal.png");
    exitButtonTheme.CandyHovered = LoadTexture("../resources/exitCandyHovered.png");
    exitButtonTheme.CandyPressed = LoadTexture("../resources/exitCandyPressed.png");
    exitButtonTheme.TerminalNormal = LoadTexture("../resources/exitTerminalNormal.png");
    exitButtonTheme.TerminalHovered = LoadTexture("../resources/exitTerminalHovered.png");
    exitButtonTheme.TerminalPressed = LoadTexture("../resources/exitTerminalPressed.png");
    exitButtonTheme.BluishNormal = LoadTexture("../resources/exitBluishNormal.png");
    exitButtonTheme.BluishHovered = LoadTexture("../resources/exitBluishHovered.png");
    exitButtonTheme.BluishPressed = LoadTexture("../resources/exitBluishPressed.png");
}

void UnloadFontsAndTextures(){
    UnloadFont(codeBlockFont);
    UnloadFont(inputBoxFont);
    UnloadFont(buttonFont);

    UnloadTexture(settingButtonTheme.DefaultNormal); 
    UnloadTexture(settingButtonTheme.DefaultHovered); 
    UnloadTexture(settingButtonTheme.DefaultPressed); 
    UnloadTexture(settingButtonTheme.SunnyNormal); 
    UnloadTexture(settingButtonTheme.SunnyHovered); 
    UnloadTexture(settingButtonTheme.SunnyPressed); 
    UnloadTexture(settingButtonTheme.RltechNormal); 
    UnloadTexture(settingButtonTheme.RltechHovered); 
    UnloadTexture(settingButtonTheme.RltechPressed); 
    UnloadTexture(settingButtonTheme.LavandaNormal); 
    UnloadTexture(settingButtonTheme.LavandaHovered); 
    UnloadTexture(settingButtonTheme.LavandaPressed); 
    UnloadTexture(settingButtonTheme.EnefeteNormal); 
    UnloadTexture(settingButtonTheme.EnefeteHovered); 
    UnloadTexture(settingButtonTheme.EnefetePressed); 
    UnloadTexture(settingButtonTheme.DarkNormal); 
    UnloadTexture(settingButtonTheme.DarkHovered); 
    UnloadTexture(settingButtonTheme.DarkPressed); 
    UnloadTexture(settingButtonTheme.CyberNormal); 
    UnloadTexture(settingButtonTheme.CyberHovered); 
    UnloadTexture(settingButtonTheme.CyberPressed); 
    UnloadTexture(settingButtonTheme.CandyNormal); 
    UnloadTexture(settingButtonTheme.CandyHovered); 
    UnloadTexture(settingButtonTheme.CandyPressed); 
    UnloadTexture(settingButtonTheme.TerminalNormal); 
    UnloadTexture(settingButtonTheme.TerminalHovered); 
    UnloadTexture(settingButtonTheme.TerminalPressed); 
    UnloadTexture(settingButtonTheme.BluishNormal); 
    UnloadTexture(settingButtonTheme.BluishHovered); 
    UnloadTexture(settingButtonTheme.BluishPressed); 
    UnloadTexture(playButtonTheme.DefaultNormal); 
    UnloadTexture(playButtonTheme.DefaultHovered); 
    UnloadTexture(playButtonTheme.DefaultPressed); 
    UnloadTexture(playButtonTheme.SunnyNormal); 
    UnloadTexture(playButtonTheme.SunnyHovered); 
    UnloadTexture(playButtonTheme.SunnyPressed); 
    UnloadTexture(playButtonTheme.RltechNormal); 
    UnloadTexture(playButtonTheme.RltechHovered); 
    UnloadTexture(playButtonTheme.RltechPressed); 
    UnloadTexture(playButtonTheme.LavandaNormal); 
    UnloadTexture(playButtonTheme.LavandaHovered); 
    UnloadTexture(playButtonTheme.LavandaPressed); 
    UnloadTexture(playButtonTheme.EnefeteNormal); 
    UnloadTexture(playButtonTheme.EnefeteHovered); 
    UnloadTexture(playButtonTheme.EnefetePressed); 
    UnloadTexture(playButtonTheme.DarkNormal); 
    UnloadTexture(playButtonTheme.DarkHovered); 
    UnloadTexture(playButtonTheme.DarkPressed); 
    UnloadTexture(playButtonTheme.CyberNormal); 
    UnloadTexture(playButtonTheme.CyberHovered); 
    UnloadTexture(playButtonTheme.CyberPressed); 
    UnloadTexture(playButtonTheme.CandyNormal); 
    UnloadTexture(playButtonTheme.CandyHovered); 
    UnloadTexture(playButtonTheme.CandyPressed); 
    UnloadTexture(playButtonTheme.TerminalNormal); 
    UnloadTexture(playButtonTheme.TerminalHovered); 
    UnloadTexture(playButtonTheme.TerminalPressed); 
    UnloadTexture(playButtonTheme.BluishNormal); 
    UnloadTexture(playButtonTheme.BluishHovered); 
    UnloadTexture(playButtonTheme.BluishPressed); 
    UnloadTexture(nextButtonTheme.DefaultNormal); 
    UnloadTexture(nextButtonTheme.DefaultHovered); 
    UnloadTexture(nextButtonTheme.DefaultPressed); 
    UnloadTexture(nextButtonTheme.SunnyNormal); 
    UnloadTexture(nextButtonTheme.SunnyHovered); 
    UnloadTexture(nextButtonTheme.SunnyPressed); 
    UnloadTexture(nextButtonTheme.RltechNormal); 
    UnloadTexture(nextButtonTheme.RltechHovered); 
    UnloadTexture(nextButtonTheme.RltechPressed); 
    UnloadTexture(nextButtonTheme.LavandaNormal); 
    UnloadTexture(nextButtonTheme.LavandaHovered); 
    UnloadTexture(nextButtonTheme.LavandaPressed); 
    UnloadTexture(nextButtonTheme.EnefeteNormal); 
    UnloadTexture(nextButtonTheme.EnefeteHovered); 
    UnloadTexture(nextButtonTheme.EnefetePressed); 
    UnloadTexture(nextButtonTheme.DarkNormal); 
    UnloadTexture(nextButtonTheme.DarkHovered); 
    UnloadTexture(nextButtonTheme.DarkPressed); 
    UnloadTexture(nextButtonTheme.CyberNormal); 
    UnloadTexture(nextButtonTheme.CyberHovered); 
    UnloadTexture(nextButtonTheme.CyberPressed); 
    UnloadTexture(nextButtonTheme.CandyNormal); 
    UnloadTexture(nextButtonTheme.CandyHovered); 
    UnloadTexture(nextButtonTheme.CandyPressed); 
    UnloadTexture(nextButtonTheme.TerminalNormal); 
    UnloadTexture(nextButtonTheme.TerminalHovered); 
    UnloadTexture(nextButtonTheme.TerminalPressed); 
    UnloadTexture(nextButtonTheme.BluishNormal); 
    UnloadTexture(nextButtonTheme.BluishHovered); 
    UnloadTexture(nextButtonTheme.BluishPressed); 
    UnloadTexture(prevButtonTheme.DefaultNormal); 
    UnloadTexture(prevButtonTheme.DefaultHovered); 
    UnloadTexture(prevButtonTheme.DefaultPressed); 
    UnloadTexture(prevButtonTheme.SunnyNormal); 
    UnloadTexture(prevButtonTheme.SunnyHovered); 
    UnloadTexture(prevButtonTheme.SunnyPressed); 
    UnloadTexture(prevButtonTheme.RltechNormal); 
    UnloadTexture(prevButtonTheme.RltechHovered); 
    UnloadTexture(prevButtonTheme.RltechPressed); 
    UnloadTexture(prevButtonTheme.LavandaNormal); 
    UnloadTexture(prevButtonTheme.LavandaHovered); 
    UnloadTexture(prevButtonTheme.LavandaPressed); 
    UnloadTexture(prevButtonTheme.EnefeteNormal); 
    UnloadTexture(prevButtonTheme.EnefeteHovered); 
    UnloadTexture(prevButtonTheme.EnefetePressed); 
    UnloadTexture(prevButtonTheme.DarkNormal); 
    UnloadTexture(prevButtonTheme.DarkHovered); 
    UnloadTexture(prevButtonTheme.DarkPressed); 
    UnloadTexture(prevButtonTheme.CyberNormal); 
    UnloadTexture(prevButtonTheme.CyberHovered); 
    UnloadTexture(prevButtonTheme.CyberPressed); 
    UnloadTexture(prevButtonTheme.CandyNormal); 
    UnloadTexture(prevButtonTheme.CandyHovered); 
    UnloadTexture(prevButtonTheme.CandyPressed); 
    UnloadTexture(prevButtonTheme.TerminalNormal); 
    UnloadTexture(prevButtonTheme.TerminalHovered); 
    UnloadTexture(prevButtonTheme.TerminalPressed); 
    UnloadTexture(prevButtonTheme.BluishNormal); 
    UnloadTexture(prevButtonTheme.BluishHovered); 
    UnloadTexture(prevButtonTheme.BluishPressed); 
    UnloadTexture(pauseButtonTheme.DefaultNormal); 
    UnloadTexture(pauseButtonTheme.DefaultHovered); 
    UnloadTexture(pauseButtonTheme.DefaultPressed); 
    UnloadTexture(pauseButtonTheme.SunnyNormal); 
    UnloadTexture(pauseButtonTheme.SunnyHovered); 
    UnloadTexture(pauseButtonTheme.SunnyPressed); 
    UnloadTexture(pauseButtonTheme.RltechNormal); 
    UnloadTexture(pauseButtonTheme.RltechHovered); 
    UnloadTexture(pauseButtonTheme.RltechPressed); 
    UnloadTexture(pauseButtonTheme.LavandaNormal); 
    UnloadTexture(pauseButtonTheme.LavandaHovered); 
    UnloadTexture(pauseButtonTheme.LavandaPressed); 
    UnloadTexture(pauseButtonTheme.EnefeteNormal); 
    UnloadTexture(pauseButtonTheme.EnefeteHovered); 
    UnloadTexture(pauseButtonTheme.EnefetePressed); 
    UnloadTexture(pauseButtonTheme.DarkNormal); 
    UnloadTexture(pauseButtonTheme.DarkHovered); 
    UnloadTexture(pauseButtonTheme.DarkPressed); 
    UnloadTexture(pauseButtonTheme.CyberNormal); 
    UnloadTexture(pauseButtonTheme.CyberHovered); 
    UnloadTexture(pauseButtonTheme.CyberPressed); 
    UnloadTexture(pauseButtonTheme.CandyNormal); 
    UnloadTexture(pauseButtonTheme.CandyHovered); 
    UnloadTexture(pauseButtonTheme.CandyPressed); 
    UnloadTexture(pauseButtonTheme.TerminalNormal); 
    UnloadTexture(pauseButtonTheme.TerminalHovered); 
    UnloadTexture(pauseButtonTheme.TerminalPressed); 
    UnloadTexture(pauseButtonTheme.BluishNormal); 
    UnloadTexture(pauseButtonTheme.BluishHovered); 
    UnloadTexture(pauseButtonTheme.BluishPressed); 
    UnloadTexture(startButtonTheme.DefaultNormal); 
    UnloadTexture(startButtonTheme.DefaultHovered); 
    UnloadTexture(startButtonTheme.DefaultPressed); 
    UnloadTexture(startButtonTheme.SunnyNormal); 
    UnloadTexture(startButtonTheme.SunnyHovered); 
    UnloadTexture(startButtonTheme.SunnyPressed); 
    UnloadTexture(startButtonTheme.RltechNormal); 
    UnloadTexture(startButtonTheme.RltechHovered); 
    UnloadTexture(startButtonTheme.RltechPressed); 
    UnloadTexture(startButtonTheme.LavandaNormal); 
    UnloadTexture(startButtonTheme.LavandaHovered); 
    UnloadTexture(startButtonTheme.LavandaPressed); 
    UnloadTexture(startButtonTheme.EnefeteNormal); 
    UnloadTexture(startButtonTheme.EnefeteHovered); 
    UnloadTexture(startButtonTheme.EnefetePressed); 
    UnloadTexture(startButtonTheme.DarkNormal); 
    UnloadTexture(startButtonTheme.DarkHovered); 
    UnloadTexture(startButtonTheme.DarkPressed); 
    UnloadTexture(startButtonTheme.CyberNormal); 
    UnloadTexture(startButtonTheme.CyberHovered); 
    UnloadTexture(startButtonTheme.CyberPressed); 
    UnloadTexture(startButtonTheme.CandyNormal); 
    UnloadTexture(startButtonTheme.CandyHovered); 
    UnloadTexture(startButtonTheme.CandyPressed); 
    UnloadTexture(startButtonTheme.TerminalNormal); 
    UnloadTexture(startButtonTheme.TerminalHovered); 
    UnloadTexture(startButtonTheme.TerminalPressed); 
    UnloadTexture(startButtonTheme.BluishNormal); 
    UnloadTexture(startButtonTheme.BluishHovered); 
    UnloadTexture(startButtonTheme.BluishPressed); 
    UnloadTexture(endButtonTheme.DefaultNormal); 
    UnloadTexture(endButtonTheme.DefaultHovered); 
    UnloadTexture(endButtonTheme.DefaultPressed); 
    UnloadTexture(endButtonTheme.SunnyNormal); 
    UnloadTexture(endButtonTheme.SunnyHovered); 
    UnloadTexture(endButtonTheme.SunnyPressed); 
    UnloadTexture(endButtonTheme.RltechNormal); 
    UnloadTexture(endButtonTheme.RltechHovered); 
    UnloadTexture(endButtonTheme.RltechPressed); 
    UnloadTexture(endButtonTheme.LavandaNormal); 
    UnloadTexture(endButtonTheme.LavandaHovered); 
    UnloadTexture(endButtonTheme.LavandaPressed); 
    UnloadTexture(endButtonTheme.EnefeteNormal); 
    UnloadTexture(endButtonTheme.EnefeteHovered); 
    UnloadTexture(endButtonTheme.EnefetePressed); 
    UnloadTexture(endButtonTheme.DarkNormal); 
    UnloadTexture(endButtonTheme.DarkHovered); 
    UnloadTexture(endButtonTheme.DarkPressed); 
    UnloadTexture(endButtonTheme.CyberNormal); 
    UnloadTexture(endButtonTheme.CyberHovered); 
    UnloadTexture(endButtonTheme.CyberPressed); 
    UnloadTexture(endButtonTheme.CandyNormal); 
    UnloadTexture(endButtonTheme.CandyHovered); 
    UnloadTexture(endButtonTheme.CandyPressed); 
    UnloadTexture(endButtonTheme.TerminalNormal); 
    UnloadTexture(endButtonTheme.TerminalHovered); 
    UnloadTexture(endButtonTheme.TerminalPressed); 
    UnloadTexture(endButtonTheme.BluishNormal); 
    UnloadTexture(endButtonTheme.BluishHovered); 
    UnloadTexture(endButtonTheme.BluishPressed); 
    UnloadTexture(reloadButtonTheme.DefaultNormal); 
    UnloadTexture(reloadButtonTheme.DefaultHovered); 
    UnloadTexture(reloadButtonTheme.DefaultPressed); 
    UnloadTexture(reloadButtonTheme.SunnyNormal); 
    UnloadTexture(reloadButtonTheme.SunnyHovered); 
    UnloadTexture(reloadButtonTheme.SunnyPressed); 
    UnloadTexture(reloadButtonTheme.RltechNormal); 
    UnloadTexture(reloadButtonTheme.RltechHovered); 
    UnloadTexture(reloadButtonTheme.RltechPressed); 
    UnloadTexture(reloadButtonTheme.LavandaNormal); 
    UnloadTexture(reloadButtonTheme.LavandaHovered); 
    UnloadTexture(reloadButtonTheme.LavandaPressed); 
    UnloadTexture(reloadButtonTheme.EnefeteNormal); 
    UnloadTexture(reloadButtonTheme.EnefeteHovered); 
    UnloadTexture(reloadButtonTheme.EnefetePressed); 
    UnloadTexture(reloadButtonTheme.DarkNormal); 
    UnloadTexture(reloadButtonTheme.DarkHovered); 
    UnloadTexture(reloadButtonTheme.DarkPressed); 
    UnloadTexture(reloadButtonTheme.CyberNormal); 
    UnloadTexture(reloadButtonTheme.CyberHovered); 
    UnloadTexture(reloadButtonTheme.CyberPressed); 
    UnloadTexture(reloadButtonTheme.CandyNormal); 
    UnloadTexture(reloadButtonTheme.CandyHovered); 
    UnloadTexture(reloadButtonTheme.CandyPressed); 
    UnloadTexture(reloadButtonTheme.TerminalNormal); 
    UnloadTexture(reloadButtonTheme.TerminalHovered); 
    UnloadTexture(reloadButtonTheme.TerminalPressed); 
    UnloadTexture(reloadButtonTheme.BluishNormal); 
    UnloadTexture(reloadButtonTheme.BluishHovered); 
    UnloadTexture(reloadButtonTheme.BluishPressed); 
    UnloadTexture(exitButtonTheme.DefaultNormal); 
    UnloadTexture(exitButtonTheme.DefaultHovered); 
    UnloadTexture(exitButtonTheme.DefaultPressed); 
    UnloadTexture(exitButtonTheme.SunnyNormal); 
    UnloadTexture(exitButtonTheme.SunnyHovered); 
    UnloadTexture(exitButtonTheme.SunnyPressed); 
    UnloadTexture(exitButtonTheme.RltechNormal); 
    UnloadTexture(exitButtonTheme.RltechHovered); 
    UnloadTexture(exitButtonTheme.RltechPressed); 
    UnloadTexture(exitButtonTheme.LavandaNormal); 
    UnloadTexture(exitButtonTheme.LavandaHovered); 
    UnloadTexture(exitButtonTheme.LavandaPressed); 
    UnloadTexture(exitButtonTheme.EnefeteNormal); 
    UnloadTexture(exitButtonTheme.EnefeteHovered); 
    UnloadTexture(exitButtonTheme.EnefetePressed); 
    UnloadTexture(exitButtonTheme.DarkNormal); 
    UnloadTexture(exitButtonTheme.DarkHovered); 
    UnloadTexture(exitButtonTheme.DarkPressed); 
    UnloadTexture(exitButtonTheme.CyberNormal); 
    UnloadTexture(exitButtonTheme.CyberHovered); 
    UnloadTexture(exitButtonTheme.CyberPressed); 
    UnloadTexture(exitButtonTheme.CandyNormal); 
    UnloadTexture(exitButtonTheme.CandyHovered); 
    UnloadTexture(exitButtonTheme.CandyPressed); 
    UnloadTexture(exitButtonTheme.TerminalNormal); 
    UnloadTexture(exitButtonTheme.TerminalHovered); 
    UnloadTexture(exitButtonTheme.TerminalPressed); 
    UnloadTexture(exitButtonTheme.BluishNormal); 
    UnloadTexture(exitButtonTheme.BluishHovered); 
    UnloadTexture(exitButtonTheme.BluishPressed); 
}