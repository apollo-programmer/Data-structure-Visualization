#include <ShortestPath/STPanel.h>

STPanel::STPanel(){
    this->Create.setText("Create",panelButtonFontSize);
    this->Create.setSize(panelButtonSize);
    this->Create.setPosition({panelButtonSize.x/2.0f+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f), 650+(panelButtonSize.y/2.0f)});

    this->Dijkstra.setText("Dijkstra",panelButtonFontSize);
    this->Dijkstra.setSize(panelButtonSize);
    this->Dijkstra.setPosition({panelButtonSize.x/2.0f+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f), 700+(panelButtonSize.y/2.0f)});

    this->Setting.setText("Setting",panelButtonFontSize);
    this->Setting.setSize(panelButtonSize);
    this->Setting.setPosition({panelButtonSize.x/2.0f+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f), 750+(panelButtonSize.y/2.0f)});

    setDataName("Shortest Path");
}

bool STPanel::isAnyButtonPressed(){
    return Create.isPressed()||Dijkstra.isPressed()||Setting.isPressed();
}

void STPanel::draw(){
    drawPanel();
    this->Create.drawRectangleRounded(100);
    this->Create.drawText();
    this->Dijkstra.drawRectangleRounded(100);
    this->Dijkstra.drawText();
    this->Setting.drawRectangleRounded(100);
    this->Setting.drawText();
    this->Back.drawOutlineRounded(100,0,3);
    this->Create.drawOutlineRounded(100,0,3);
    this->Dijkstra.drawOutlineRounded(100,0,3);
    this->Setting.drawOutlineRounded(100,0,3);
}

void STPanel::update(){
    updatePanel();
    if(this->Create.isPressed()){
        if(isUsing&&isUsing==&Create) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Create.Selected();
            if(isUsing&&isUsing!=&Create) this->isUsing->deSelected();
            this->isUsing = &this->Create;
        }
    }
    else if(this->Dijkstra.isPressed()){
        if(isUsing&&isUsing==&Dijkstra) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Dijkstra.Selected();
            if(isUsing&&isUsing!=&Dijkstra) this->isUsing->deSelected();
            this->isUsing = &this->Dijkstra;
        }
    }
    else if(this->Setting.isPressed()){
        if(isUsing&&isUsing==&Setting) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Setting.Selected();
            if(isUsing&&isUsing!=&Setting) this->isUsing->deSelected();
            this->isUsing = &this->Setting;
        }
    }
    this->Back.update();
    this->Create.update();
    this->Dijkstra.update(); 
    this->Setting.update();
}

bool STPanel::isCreateUsed(){
    return (isUsing == &Create);
}

bool STPanel::isDijkstraUsed(){
    return (isUsing == &Dijkstra);
}

bool STPanel::isSettingUsed(){
    return (isUsing == &Setting);
}