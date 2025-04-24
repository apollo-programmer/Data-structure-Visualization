#include <GUI/Panel.h>

Panel::Panel(){
    this->dataName="";
    this->dataTitle = {dataTitlePosition.x-dataTitleSize.x/2.0f,dataTitlePosition.y-dataTitleSize.y/2.0f,dataTitleSize.x,dataTitleSize.y};

    this->Back.setSize(backSize);
    this->Back.setPosition({dataTitle.y+dataTitle.height/2.0f,dataTitle.y+dataTitle.height/2.0f});
    this->Back.setTexture(exitButtonTheme);

    this->panelHolder = {0,650-(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f),panelButtonSize.x+(panelButtonSize.y-panelButtonFontSize),250+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f)};
    this->subPanelHolder = {panelHolder.width,650-(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f),400-panelHolder.width,250+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f)};
    Back.deActive();
}

bool Panel::isBackPressed(){
    bool res=Back.isPressed();
    if(res){
        Back.deActive();
    }
    return res;
}

void Panel::setBackActive(){
    this->Back.setTexture(exitButtonTheme);
    Back.setActive();
}

void Panel::updatePanel(){
    updateController();
    this->Back.update();
}

void Panel::drawPanel(){
    drawController();
    if(isUsing){
        DrawRectangleRounded(subPanelHolder, 0, 0, buttonNormal); 
        DrawRectangleLinesEx(subPanelHolder,3, outlineButtonColor);
    }
    DrawRectangleRounded(dataTitle,100,0,dataTitleColor);
    DrawRectangleRoundedLinesEx(dataTitle,100,0,3,dataTitleTextColor);
    DrawRectangleRounded(panelHolder,0,0,buttonNormal);
    DrawRectangleLinesEx(panelHolder,3,outlineButtonColor);
    this->Back.drawRectangleRounded(100);
    this->Back.drawTexture();
    this->Back.drawOutlineRounded(100,0,3);
    DrawTextEx(buttonFont, dataName, {GetScreenWidth()/2.0f-MeasureTextEx(buttonFont, dataName, dataTitleFontSize,0).x/2.0f,dataTitlePosition.y-dataTitleFontSize/2.0f}, dataTitleFontSize, 0, dataTitleTextColor);
}

void Panel::reset(){
    if(!isUsing) return;
    isUsing->deSelected();
    isUsing=nullptr;
}

void Panel::setDataName(const char* name){
    this->dataName=name;
}