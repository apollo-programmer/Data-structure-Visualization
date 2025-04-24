#include <AVL/AVLPanel.h>

AVLPanel::AVLPanel(){
    this->Create.setText("Create",panelButtonFontSize);
    this->Create.setSize(panelButtonSize);
    this->Create.setPosition({panelButtonSize.x/2.0f+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f), 650+(panelButtonSize.y/2.0f)});

    this->Add.setText("Add",panelButtonFontSize);
    this->Add.setSize(panelButtonSize);
    this->Add.setPosition({panelButtonSize.x/2.0f+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f), 700+(panelButtonSize.y/2.0f)});

    this->Remove.setText("Remove",panelButtonFontSize);
    this->Remove.setSize(panelButtonSize);
    this->Remove.setPosition({panelButtonSize.x/2.0f+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f), 750+(panelButtonSize.y/2.0f)});

    this->Search.setText("Search",panelButtonFontSize);
    this->Search.setSize(panelButtonSize);
    this->Search.setPosition({panelButtonSize.x/2.0f+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f), 800+(panelButtonSize.y/2.0f)});
    
    this->Update.setText("Update",panelButtonFontSize);
    this->Update.setSize(panelButtonSize);
    this->Update.setPosition({panelButtonSize.x/2.0f+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f), 850+(panelButtonSize.y/2.0f)});

    setDataName("AVL Tree");
}

bool AVLPanel::isAnyButtonPressed(){
    return Create.isPressed()||Add.isPressed()||Remove.isPressed()||Search.isPressed()||Update.isPressed();
}

void AVLPanel::draw(){
    drawPanel();
    this->Create.drawRectangleRounded(100);
    this->Create.drawText();
    this->Add.drawRectangleRounded(100);
    this->Add.drawText();
    this->Remove.drawRectangleRounded(100);
    this->Remove.drawText();
    this->Search.drawRectangleRounded(100);
    this->Search.drawText();
    this->Update.drawRectangleRounded(100);
    this->Update.drawText();
    this->Back.drawOutlineRounded(100,0,3);
    this->Create.drawOutlineRounded(100,0,3);
    this->Add.drawOutlineRounded(100,0,3);
    this->Remove.drawOutlineRounded(100,0,3);
    this->Search.drawOutlineRounded(100,0,3);
    this->Update.drawOutlineRounded(100,0,3);
}

void AVLPanel::update(){
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
    else if(this->Add.isPressed()){
        if(isUsing&&isUsing==&Add) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Add.Selected();
            if(isUsing&&isUsing!=&Add) this->isUsing->deSelected();
            this->isUsing = &this->Add;
        }
    }
    else if(this->Remove.isPressed()){
        if(isUsing&&isUsing==&Remove) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Remove.Selected();
            if(isUsing&&isUsing!=&Remove) this->isUsing->deSelected();
            this->isUsing = &this->Remove;
        }
    }
    else if(this->Search.isPressed()){
        if(isUsing&&isUsing==&Search) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Search.Selected();
            if(isUsing&&isUsing!=&Search) this->isUsing->deSelected();
            this->isUsing = &this->Search;
        }
    }
    else if(this->Update.isPressed()){
        if(isUsing&&isUsing==&Update) {
            isUsing->deSelected();
            isUsing=nullptr;
        }
        else{
            this->Update.Selected();
            if(isUsing&&isUsing!=&Update) this->isUsing->deSelected();
            this->isUsing = &this->Update;
        }
    }
    this->Back.update();
    this->Create.update();
    this->Add.update();
    this->Remove.update();
    this->Search.update();
    this->Update.update();
}

bool AVLPanel::isCreateUsed(){
    return (isUsing == &Create);
}

bool AVLPanel::isAddUsed(){
    return (isUsing == &Add);
}

bool AVLPanel::isRemoveUsed(){
    return (isUsing == &Remove);
}

bool AVLPanel::isSearchUsed(){
    return (isUsing == &Search);
}

bool AVLPanel::isUpdateUsed(){
    return (isUsing == &Update);
}