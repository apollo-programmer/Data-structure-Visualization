#include <SLL/SLLState.h>

SLLState::SLLState(): createBox(120,680,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,boxColor, boxTextColor), indexBox(120,680,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,boxColor, boxTextColor), valueBox(120,790,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,boxColor, boxTextColor), speedSlider(0.1,5,1,50){
    this->Random.setText("Random",SLLButtonFontSize);
    this->Random.setSize({120, 30});
    this->Random.setPosition({180,740});

    this->LoadFile.setText("Load File",SLLButtonFontSize);
    this->LoadFile.setSize({120, 30});
    this->LoadFile.setPosition({320,740});

    this->Front.setText("Front",SLLButtonFontSize);
    this->Front.setSize({120, 30});
    this->Front.setPosition({180,740});

    this->End.setText("Back",SLLButtonFontSize);
    this->End.setSize({120, 30});
    this->End.setPosition({320,740});

    this->Apply.setText("Apply",SLLButtonFontSize);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,780});

    createBox.setNameBox("Input Elements");
    indexBox.setNameBox("Index");
    valueBox.setNameBox("Value");
}

void SLLState::updateTheme(){
    panel.update();
    Random.update();
    LoadFile.update();
    Apply.update();
    Front.update();
    End.update();
    createBox.Update();
    indexBox.Update();
    valueBox.Update();
}

void SLLState::update(){
    panel.setBackActive();
    if(!stateList.empty()&&currentStep==stateList.size()-1){
        panel.setEnd();
    }
    else{
        panel.deEnd();
    }
    if((isPlaying&&isPaused)||!isPlaying){
        panel.setPause();
    }
    else{
        panel.dePause();
    }
    if (panel.isPlayPressed()) {
        if(currentStep==stateList.size()-1){
            restart();
        }
        else if(currentStep==0){
            play();
        }
        else if(isPlaying&&!isPaused){
            pause();
        }
        else if(isPlaying&&isPaused){
            resume();
        }
    }
    else if (panel.isNextPressed()) {
        nextStep();
    }
    else if (panel.isPrevPressed()) {
        prevStep();
    }
    else if (panel.isEndPressed()) {
        moveEnd();
    }
    else if (panel.isStartPressed()) {
        moveStart();
    }
    
    SLL.update();
    panel.update();
    speedSlider.Update();

    switch (animationState) {
        case SLLAnimationMode::INSERT_FRONT:
            if (!isStateSaved) {
                saveInsertFrontState(std::stoi(indexText), std::stoi(valueText));
                isStateSaved = true;
            }
            animateInsertFront(std::stoi(indexText), std::stoi(valueText));
            break;
        case SLLAnimationMode::INSERT_MID:
            if (!isStateSaved) {
                saveInsertMidState(std::stoi(indexText), std::stoi(valueText));
                isStateSaved = true; 
            }
            animateInsertMid(std::stoi(indexText), std::stoi(valueText));
            break;
        case SLLAnimationMode::REMOVE_FRONT:
            if (!isStateSaved) {
                saveRemoveFrontState(std::stoi(indexText));
                isStateSaved = true; 
            }
            animateRemoveFront(std::stoi(indexText));
            break;
        case SLLAnimationMode::REMOVE_MID:
            if (!isStateSaved) {
                saveRemoveMidState(std::stoi(indexText));
                isStateSaved = true; 
            }
            animateRemoveMid(std::stoi(indexText));
            break;
        case SLLAnimationMode::SEARCH:
            if (!isStateSaved) {
                saveSearchState(std::stoi(valueText));
                isStateSaved = true;
            }
            animateSearch(std::stoi(valueText));
            break;
        case SLLAnimationMode::UPDATE:
            if (!isStateSaved) {
                saveUpdateState(std::stoi(indexText), std::stoi(valueText));
                isStateSaved = true;
            }
            animateUpdate(std::stoi(indexText), std::stoi(valueText));
            break;
        case SLLAnimationMode::IDLE:
            break;
        default:
            break;
    }

    if(panel.isCreateUsed()){
        valueBox.setPosition({120,790});
        Apply.setPosition({250,780});
        Random.setActive();
        LoadFile.setActive();
        Apply.setActive();
        Front.deActive();
        End.deActive();
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()){
        if(panel.isAddUsed()){
            Apply.setPosition({250,850});
            valueBox.setPosition({120,790});
        }
        else{
            valueBox.setPosition({120,680});
            Apply.setPosition({250,780});
        }
        Front.setActive();
        End.setActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.setActive();
    }
    else if(panel.isUpdateUsed()){
        Apply.setPosition({250,810});
        valueBox.setPosition({120,750});
        Front.deActive();
        End.deActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.setActive();
    }
    else if(panel.isSearchUsed()){
        Apply.setPosition({250,740});
        valueBox.setPosition({120,680});
        Front.deActive();
        End.deActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.setActive();
    }
    else{
        Front.deActive();
        End.deActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    if(Random.isPressed()){
        SLL.createList(getRandomInput());
    }
    else if(Front.isPressed()){
        indexBox.setText("0");
    }
    else if(End.isPressed()){
        if(panel.isAddUsed())
            indexBox.setText(std::to_string(SLL.getListSize()));
        else if(panel.isRemoveUsed()){
            indexBox.setText(std::to_string(SLL.getListSize()-1));
        }
    }
    else if(LoadFile.isPressed()){
        std::string input=panel.loadFileContent();
        SLL.createList(input);
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        indexText=indexBox.GetText();
        valueText=valueBox.GetText();
        createText=createBox.GetText();
        resetBox();
        if(panel.isCreateUsed()){
            SLL.createList(createText);
        }
        else if(panel.isAddUsed()&&indexText!=""&&valueText!=""){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            if(std::stoi(indexText)==0){
                code.setCode(insertFrontCode);
                animationState=SLLAnimationMode::INSERT_FRONT;
            }
            else if(std::stoi(indexText)>0&&std::stoi(indexText)<=SLL.list.size()){
                code.setCode(insertMiddleCode);
                animationState=SLLAnimationMode::INSERT_MID;
            }
        }
        else if(panel.isRemoveUsed()&&indexText!=""){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            if(std::stoi(indexText)==0&&!SLL.list.empty()){
                code.setCode(removeFrontCode);
                animationState=SLLAnimationMode::REMOVE_FRONT;
            }
            else if(!SLL.list.empty()&&std::stoi(indexText)>0&&std::stoi(indexText)<SLL.list.size()){
                code.setCode(removeMiddleCode);
                animationState=SLLAnimationMode::REMOVE_MID;
            }
        }
        else if(panel.isUpdateUsed()&&valueText!=""){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            code.setCode(updateCode);
            animationState=SLLAnimationMode::UPDATE;
        }
        else if(panel.isSearchUsed()&&valueText!=""){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false; 
            code.setCode(searchCode);
            animationState=SLLAnimationMode::SEARCH;
        }
    }
    else if(panel.isAnyButtonPressed()){
        moveEnd();
        clearState();
        SLL.resetHighlight();
        resetBox();
        code.clearCode();
        code.clearHighlight();
    }
    if(panel.isCreateUsed()){
        createBox.Update();
        this->Random.update();
        this->LoadFile.update();
        this->Apply.update();
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isUpdateUsed()){
        this->Front.update();
        this->End.update();
        indexBox.Update();
        this->Apply.update();
        if(!panel.isRemoveUsed())
            valueBox.Update();
    }
    else if(panel.isSearchUsed()){
        valueBox.Update();
        this->Apply.update();
    }
}

void SLLState::draw(){
    code.draw();
    SLL.draw();
    panel.draw();
    speedSlider.Draw();
    if(panel.isCreateUsed()){
        createBox.Draw();
        this->Random.drawRectangleRounded(100);
        this->Random.drawText();
        this->LoadFile.drawRectangleRounded(100);
        this->LoadFile.drawText();
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText();
        this->Random.drawOutlineRounded(100, 10, 3);
        this->LoadFile.drawOutlineRounded(100, 10, 3);
        this->Apply.drawOutlineRounded(100, 10, 3);
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isUpdateUsed()){
        if(!panel.isUpdateUsed()){
            this->Front.drawRectangleRounded(100);
            this->Front.drawText();
            this->End.drawRectangleRounded(100);
            this->End.drawText();
            this->Front.drawOutlineRounded(100, 10, 3);
            this->End.drawOutlineRounded(100, 10, 3);
        }
        indexBox.Draw();
        if(!panel.isRemoveUsed())
            valueBox.Draw();
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText();
        this->Apply.drawOutlineRounded(100, 10, 3);
    }
    else if(panel.isSearchUsed()){
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText();
        this->Apply.drawOutlineRounded(100, 10, 3);
        valueBox.Draw();
    }
}

void SLLState::saveInsertFrontState(int index, int value){
    if(SLL.indexStep>=index) return;
    saveState();
    if(SLL.indexStep+1==index&&SLL.animationStep==0){
        SLL.isNewNode=true;
        SLL.newNode=new SLLNode();
        SLL.newNode->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
        SLL.newNode->setNull();
        SLL.newNode->setValue(value);
        SLL.newNode->setDestination({SLL.newNode->getEndPos().x+ArrowLength,SLL.newNode->getEndPos().y});
        SLL.myNode=new SLLArrow({SLL.head->getPosition().x + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
        SLL.myNode->setLabel("myNode");
        SLL.myNode->setPosition({SLL.newNode->getStartPos().x-ArrowLength,SLL.newNode->getStartPos().y});
        SLL.myNode->setDestination(SLL.newNode->getStartPos());
        SLL.myNode->setTargetDestination(SLL.newNode->getStartPos());
        code.setHighlight({0});
        saveState();
        if(!SLL.list.empty()){
            for (int i=index;i<SLL.list.size();i++){
                SLL.list[i]->setPosition({SLL.head->getPosition().x+ArrowLength + (i+1) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
            }
            SLL.setArrowDestination();
            SLL.animationStep++;
            saveState();
        }
        else{
            SLL.isCreated=true;
            SLL.head=new SLLArrow({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f});
            SLL.head->setDestination({SLLposition.x+ArrowLength,SLLposition.y+SLLNodeSize.y/2.0f});
            SLL.head->setLabel("head");
            SLL.animationStep+=2;
        }
    }
    if(SLL.animationStep==1){
        code.setHighlight({1});
        SLL.newNode->setDestination(SLL.list[index]->getStartPos());
        SLL.animationStep++;
        saveState();
    }
    if(SLL.animationStep==2){
        SLL.list.insert(SLL.list.begin(),SLL.newNode);
        SLL.animationStep++;
    }
    if(SLL.animationStep==3){
        code.setHighlight({2});
        SLL.head->setDestination(SLL.newNode->getStartPos());
        SLL.animationStep++;
        SLL.isNewNode=false;
        saveState();
    }
    if(SLL.animationStep==4){
        SLL.list[index]->setPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
        SLL.indexStep=-1;
        SLL.animationStep=0;
        SLL.newNode=nullptr;
        delete SLL.myNode;
        SLL.myNode=nullptr;
        animationState=SLLAnimationMode::IDLE;
        SLL.setArrowDestination();
        code.clearHighlight();
        saveState();
    }
    currentStep=0;
    applyState();
}

void SLLState::saveInsertMidState(int index, int value){
    if(SLL.indexStep>index) return;
    saveState();
    if(!SLL.isCur){
        SLL.isCur=true;
        resetCursorPosition();
    }
    saveState();
    while(SLL.indexStep<index-1){
        if(SLL.indexStep==-1){
            code.setHighlight({0});
        }
        else{
            code.setHighlight({1,2});
        }
        SLL.cur->setDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-ArrowLength,SLL.list[SLL.indexStep+1]->getStartPos().y+ArrowLength});
        SLL.indexStep++;
        saveState();
    }
    if(SLL.indexStep+1==index&&SLL.animationStep==0){
        SLL.isNewNode=true;
        SLL.newNode=new SLLNode();
        SLL.newNode->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
        SLL.newNode->setNull();
        SLL.newNode->setValue(value);
        SLL.newNode->setDestination({SLL.newNode->getEndPos().x+ArrowLength,SLL.newNode->getEndPos().y});
        SLL.myNode=new SLLArrow({SLL.head->getPosition().x + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
        SLL.myNode->setLabel("myNode");
        SLL.myNode->setPosition({SLL.newNode->getStartPos().x-ArrowLength,SLL.newNode->getStartPos().y});
        SLL.myNode->setDestination(SLL.newNode->getStartPos());
        SLL.myNode->setTargetDestination(SLL.newNode->getStartPos());
        code.setHighlight({3});
        saveState();
        if(SLL.indexStep+1!=SLL.list.size()){
            for (int i=index;i<SLL.list.size();i++){
                SLL.list[i]->setPosition({SLL.head->getPosition().x+ArrowLength + (i+1) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
            }
            SLL.setArrowDestination();
            SLL.animationStep++;
            saveState();
        }
        else{
            SLL.animationStep+=2;
        }
    }
    if(SLL.animationStep==1){
        code.setHighlight({4});
        SLL.newNode->setDestination(SLL.list[index]->getStartPos());
        SLL.animationStep++;
        saveState();
    }
    if(SLL.animationStep==2){
        SLL.animationStep++;
        SLL.list.insert(SLL.list.begin()+index,SLL.newNode);
    }
    if(SLL.animationStep==3){
        code.setHighlight({5});
        SLL.list[index-1]->setDestination(SLL.newNode->getStartPos());
        SLL.animationStep++;
        SLL.isNewNode=false;
        saveState();
    }
    if(SLL.animationStep==4){
        SLL.list[index]->setPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
        SLL.setArrowDestination();
        SLL.indexStep=-1;
        SLL.animationStep=0;
        SLL.newNode=nullptr;
        if(SLL.myNode);
            delete SLL.myNode;
        SLL.myNode=nullptr;
        SLL.isCur=false;
        resetCursorPosition();
        animationState=SLLAnimationMode::IDLE;
        code.clearHighlight();
        saveState();
    }
    currentStep=0;
    applyState();
}

void SLLState::saveRemoveFrontState(int index){
    if(SLL.indexStep>index) return;
    saveState();
    if(SLL.animationStep==0){
        if(!SLL.isCur){
            SLL.isCur=true;
            resetCursorPosition();
            saveState();
        }
        code.setHighlight({0});
        SLL.cur->setTargetDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-ArrowLength,SLL.list[SLL.indexStep+1]->getStartPos().y+ArrowLength});
        SLL.animationStep++;
        saveState();
    }
    if(SLL.animationStep==1){
        SLL.list[index]->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-ArrowLength,SLL.list[index]->getStartPos().y+ArrowLength});
        SLL.setArrowDestination();
        saveState();
        SLL.animationStep++;
        SLL.newNode=SLL.list[index];
        SLL.list.erase(SLL.list.begin()+index);
        SLL.isNewNode=true;
    }
    if(SLL.list.empty()){
        code.setHighlight({1});
        SLL.head->setDestination({SLLposition.x+ArrowLength,SLLposition.y});
        code.setHighlight({2});
        SLL.isNewNode=false;
        delete SLL.newNode;
        SLL.newNode=nullptr;
        SLL.isCur=false;
        SLL.animationStep=0;
        SLL.indexStep=-1;
        animationState=SLLAnimationMode::IDLE;
        SLL.setArrowDestination();
        saveState();
        currentStep=0;
        applyState();
        return;
    }
    if(SLL.animationStep==2){
        code.setHighlight({1});
        SLL.setArrowDestination();
        saveState();
        code.setHighlight({2});
        SLL.isNewNode=false;
        delete SLL.newNode;
        SLL.newNode=nullptr;
        SLL.isCur=false;
        SLL.animationStep++;
        saveState();
    }
    if(SLL.animationStep==3){
        for (int i=index;i<SLL.list.size();i++){
            SLL.list[i]->setPosition({SLL.head->getPosition().x+ArrowLength + i * (SLLNodeSize.x+ArrowLength), SLLposition.y});
        }
        SLL.setArrowDestination();
        SLL.animationStep=0;
        SLL.indexStep=-1;
        animationState=SLLAnimationMode::IDLE;
        code.clearHighlight();
        saveState();
    }
    currentStep=0;
    applyState();
}

void SLLState::saveRemoveMidState(int index){
    if(SLL.indexStep>index) return;
    saveState();
    if(!SLL.isCur){
        SLL.isCur=true;
        resetCursorPosition();
        saveState();
    }
    for (int i=0;i<index;i++){
        SLL.cur->setDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-ArrowLength,SLL.list[SLL.indexStep+1]->getStartPos().y+ArrowLength});
        if(SLL.indexStep==-1){
            code.setHighlight({0});
        }
        else{
            code.setHighlight({1,2});
        }
        SLL.indexStep++;
        if(i==index-1){
            SLL.animationStep++;
        }
        saveState();
    }
    if(SLL.animationStep==1){
        code.setHighlight({3});
        SLL.newNode=SLL.list[index];
        SLL.checkNewNodeinList=true;
        SLL.list[index]->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
        if(!SLL.myNode){
            SLL.myNode=new SLLArrow({SLL.head->getPosition().x + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
            SLL.myNode->setLabel("myNode");
        }
        SLL.myNode->setDestination(SLL.list[index]->getStartPos());
        SLL.myNode->setPosition({SLL.list[index]->getStartPos().x-ArrowLength,SLL.list[index]->getStartPos().y+ArrowLength});
        SLL.isNewNode=true;
        SLL.setArrowDestination();
        SLL.animationStep++;
        saveState();
    }
    if(SLL.animationStep==2&&index>=SLL.list.size()-1){
        SLL.list.erase(SLL.list.begin()+index);
        SLL.checkNewNodeinList=false;
        SLL.setArrowDestination();
        SLL.animationStep++;
        code.setHighlight({4,5});
        saveState();
    }
    else if(SLL.animationStep==2){
        SLL.list.erase(SLL.list.begin()+index);
        SLL.checkNewNodeinList=false;
        code.setHighlight({4});
        SLL.list[index-1]->setDestination(SLL.list[index]->getStartPos());
        SLL.animationStep++;
        saveState();
    }
    if(SLL.animationStep==3&&index>=SLL.list.size()-1){
        SLL.animationStep=0;
        SLL.indexStep=-1;
        animationState=SLLAnimationMode::IDLE;
        SLL.setArrowDestination();
        SLL.isCur=false;
        resetCursorPosition();
        delete SLL.newNode;
        SLL.newNode=nullptr;
        delete SLL.myNode;
        SLL.myNode=nullptr;
        SLL.isNewNode=false;
        code.clearHighlight();
        saveState();
        currentStep=0;
        applyState();
        return;
    }
    else if(SLL.animationStep==3){
        code.setHighlight({5});
        SLL.animationStep++;
        SLL.isCur=false;
        resetCursorPosition();
        delete SLL.newNode;
        SLL.newNode=nullptr;
        delete SLL.myNode;
        SLL.myNode=nullptr;
        SLL.isNewNode=false;
        saveState();
    }
    if(SLL.animationStep==4){
        for (int i=index;i<SLL.list.size();i++){
            SLL.list[i]->setPosition({SLL.head->getPosition().x+ArrowLength + i * (SLLNodeSize.x+ArrowLength), SLLposition.y});
        }
        SLL.setArrowDestination();
        SLL.animationStep++;
        saveState();
    }
    if(SLL.animationStep==5){
        SLL.animationStep=0;
        SLL.indexStep=-1;
        animationState=SLLAnimationMode::IDLE;
        code.clearHighlight();
        saveState();
    }
    currentStep=0;
    applyState();
}

void SLLState::saveSearchState(int value){
    if(SLL.list.empty()){
        code.setHighlight({0});
        saveState();
        animationState=SLLAnimationMode::IDLE;
        code.clearHighlight();
        saveState();
        currentStep=0;
        applyState();
        return;
    }
    SLL.resetHighlight();
    saveState();
    if(!SLL.isCur){
        SLL.isCur=true;
        resetCursorPosition();
        saveState();
    }
    while(true){
        if(SLL.indexStep==-1){
            code.setHighlight({1,2});
        }
        else{
            code.setHighlight({3,4,5});
        }
        SLL.cur->setDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-ArrowLength,SLL.list[SLL.indexStep+1]->getStartPos().y+ArrowLength});
        saveState();
        if(SLL.list[SLL.indexStep+1]->getValue()==value||SLL.list.size()<SLL.indexStep+3){
            if(SLL.list[SLL.indexStep+1]->getValue()==value){
                code.setHighlight({7});
            }
            else if(SLL.list.size()<SLL.indexStep+3){
                code.setHighlight({6});
            }
            if(SLL.list[SLL.indexStep+1]->getValue()==value)
                SLL.list[SLL.indexStep+1]->setHighlight();
            saveState();
            SLL.isCur=false;
            resetCursorPosition();
            SLL.indexStep=-1;
            animationState=SLLAnimationMode::IDLE;
            code.clearHighlight();
            saveState();
            currentStep=0;
            applyState();
            return;
        }
        else {
            SLL.indexStep++;
        }
    }
    currentStep=0;
    applyState();
}

void SLLState::saveUpdateState(int index, int value){
    if(index>=SLL.list.size()||index<0){
        animationState=SLLAnimationMode::IDLE;
        return;
    }
    if(SLL.indexStep>index) return;
    saveState();
    if(!SLL.isCur){
        SLL.isCur=true;
        resetCursorPosition();
        saveState();
    }
    while (SLL.indexStep<index){
        if(SLL.indexStep==-1){
            code.setHighlight({0});
        }
        else{
            code.setHighlight({1,2});
        }
        SLL.cur->setDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-ArrowLength,SLL.list[SLL.indexStep+1]->getStartPos().y+ArrowLength});
        SLL.indexStep++;
        if(SLL.indexStep==index){
            SLL.animationStep++;
        }
        saveState();
    }
    if(SLL.animationStep==1){
        SLL.list[index]->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-ArrowLength,SLL.list[index]->getStartPos().y+ArrowLength});
        SLL.setArrowDestination();
        code.setHighlight({3});
        saveState();
        SLL.animationStep++;
    }
    if(SLL.animationStep==2){
        SLL.animationStep++;
        SLL.list[index]->setValue(value);
        saveState();
    }
    if(SLL.animationStep==3){
        SLL.list[index]->setPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-ArrowLength,SLL.list[index]->getStartPos().y+ArrowLength});
        SLL.setArrowDestination();
        saveState();
        SLL.indexStep=-1;
        SLL.animationStep=0;
        SLL.isCur=false;
        resetCursorPosition();
        animationState=SLLAnimationMode::IDLE;
        code.clearHighlight();
        saveState();
    }
    currentStep=0;
    applyState();
}

void SLLState::animateInsertFront(int index, int value){
    if(!isPlaying||isPaused) return;
    static float checkTimer = 0.0f;
    if(SLL.indexStep>=index) return;
    if(SLL.indexStep+1==index&&SLL.animationStep==0){
        SLL.isNewNode=true;
        if(!SLL.newNode){
            SLL.newNode=new SLLNode();
            SLL.newNode->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
            SLL.newNode->setNull();
            SLL.newNode->setValue(value);
            SLL.newNode->setDestination({SLL.newNode->getEndPos().x+ArrowLength,SLL.newNode->getEndPos().y});
        }
        if(!SLL.myNode){
            SLL.myNode=new SLLArrow({SLL.head->getPosition().x + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
            SLL.myNode->setLabel("myNode");
            SLL.myNode->setPosition({SLL.newNode->getStartPos().x-ArrowLength,SLL.newNode->getStartPos().y});
            SLL.myNode->setDestination(SLL.newNode->getStartPos());
            SLL.myNode->setTargetDestination(SLL.newNode->getStartPos());
            code.setHighlight({0});
            currentStep++;
        }
        if(!SLL.list.empty()){
            for (int i=index;i<SLL.list.size();i++){
                SLL.list[i]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + (i+1) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
            }
            if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index+1) * (SLLNodeSize.x+ArrowLength)){
                checkTimer+=GetFrameTime();
                if(checkTimer>=delayTime){
                    checkTimer=0;
                    SLL.animationStep++;
                    currentStep++;
                }
            }
        }
        else{
            SLL.isCreated=true;
            SLL.head=new SLLArrow({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f});
            SLL.head->setDestination({SLLposition.x+ArrowLength,SLLposition.y+SLLNodeSize.y/2.0f});
            SLL.head->setLabel("head");
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                checkTimer=0;
                SLL.animationStep+=2;
            }
        }
    }
    else if(SLL.animationStep==1){
        SLL.newNode->setTargetDestination(SLL.list[index]->getStartPos());
        code.setHighlight({1});
        if(SLL.newNode->getDestination().x==SLL.list[index]->getStartPos().x&&SLL.newNode->getDestination().y==SLL.list[index]->getStartPos().y){
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                checkTimer=0;
                SLL.animationStep++;
                currentStep++;
            }
        }
    }
    else if(SLL.animationStep==2){
        SLL.list.insert(SLL.list.begin(),SLL.newNode);
        SLL.animationStep++;
    }
    else if(SLL.animationStep==3){
        code.setHighlight({2});
        if(SLL.head->getDestination().x==SLL.newNode->getStartPos().x&&SLL.head->getDestination().y==SLL.newNode->getStartPos().y){
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                checkTimer=0;
                SLL.animationStep++;
                SLL.isNewNode=false;
                currentStep++;
            }
        }
    }
    else if(SLL.animationStep==4){
        SLL.list[index]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength)&&SLL.list[index]->getPosition().y==SLLposition.y){
            SLL.indexStep=-1;
            SLL.animationStep=0;
            SLL.newNode=nullptr;
            delete SLL.myNode;
            SLL.myNode=nullptr;
            animationState=SLLAnimationMode::IDLE;
            currentStep++;
            isPlaying=false;
            isPaused=true;
            code.clearHighlight();
        }
    }
}

void SLLState::animateInsertMid(int index, int value){
    if(!isPlaying||isPaused) return;
    if(SLL.indexStep>=index) return;
    static float checkTimer = 0.0f;
    if(SLL.indexStep+1<index&&(SLL.cur->getDestination().x!=SLL.list[SLL.indexStep+1]->getStartPos().x||SLL.cur->getDestination().y!=SLL.list[SLL.indexStep+1]->getStartPos().y)){
        if(!SLL.isCur){
            SLL.isCur=true;
            resetCursorPosition();
            currentStep++;
        }
        if(SLL.indexStep==-1){
            code.setHighlight({0});
        }
        else{
            code.setHighlight({1,2});
        }
        SLL.cur->setTargetDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setTargetPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-ArrowLength,SLL.list[SLL.indexStep+1]->getStartPos().y+ArrowLength});
    }
    else if(SLL.indexStep+1<index){
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            checkTimer=0;
            SLL.indexStep++;
            currentStep++;
        }
    }
    if(SLL.indexStep+1==index&&SLL.animationStep==0){
        SLL.isNewNode=true;
        if(!SLL.newNode){
            SLL.newNode=new SLLNode();
            SLL.newNode->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
            SLL.newNode->setNull();
            SLL.newNode->setValue(value);
            SLL.newNode->setDestination({SLL.newNode->getEndPos().x+ArrowLength,SLL.newNode->getEndPos().y});
        }
        if(!SLL.myNode){
            SLL.myNode=new SLLArrow({SLL.head->getPosition().x + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
            SLL.myNode->setLabel("myNode");
            SLL.myNode->setPosition({SLL.newNode->getStartPos().x-ArrowLength,SLL.newNode->getStartPos().y});
            SLL.myNode->setDestination(SLL.newNode->getStartPos());
            SLL.myNode->setTargetDestination(SLL.newNode->getStartPos());
            code.setHighlight({3});
            currentStep++;
        }
        if(SLL.indexStep+1!=SLL.list.size()){
            for (int i=index;i<SLL.list.size();i++){
                SLL.list[i]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + (i+1) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
            }
            if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index+1) * (SLLNodeSize.x+ArrowLength)){
                checkTimer+=GetFrameTime();
                if(checkTimer>=delayTime){
                    checkTimer=0;
                    SLL.animationStep++;
                    currentStep++;
                }
            }
        }
        else{
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                checkTimer=0;
                SLL.animationStep+=2;
            }
        }
    }
    else if(SLL.animationStep==1){
        code.setHighlight({4});
        SLL.newNode->setTargetDestination(SLL.list[index]->getStartPos());
        if(SLL.newNode->getDestination().x==SLL.list[index]->getStartPos().x&&SLL.newNode->getDestination().y==SLL.list[index]->getStartPos().y){
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                checkTimer=0;
                SLL.animationStep++;
                currentStep++;
            }
        }
    }
    else if(SLL.animationStep==2){
        SLL.animationStep++;
        SLL.list.insert(SLL.list.begin()+index,SLL.newNode);
    }
    else if(SLL.animationStep==3){
        code.setHighlight({5});
        if(SLL.list[index-1]->getDestination().x==SLL.newNode->getStartPos().x&&SLL.list[index-1]->getDestination().y==SLL.newNode->getStartPos().y){
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                checkTimer=0;
                SLL.animationStep++;
                SLL.isNewNode=false;
                currentStep++;
            }
        }
    }
    else if(SLL.animationStep==4){
        SLL.list[index]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength)&&SLL.list[index]->getPosition().y==SLLposition.y){
            SLL.indexStep=-1;
            SLL.animationStep=0;
            SLL.newNode=nullptr;
            delete SLL.myNode;
            SLL.myNode=nullptr;
            SLL.isCur=false;
            resetCursorPosition();
            animationState=SLLAnimationMode::IDLE;
            currentStep++;
            isPlaying=false;
            isPaused=true;
            code.clearHighlight();
        }
    }
}

void SLLState::animateRemoveFront(int index){
    if(!isPlaying||isPaused) return;
    static float checkTimer = 0.0f;
    if(SLL.indexStep>index) return;
    if(SLL.animationStep==0){
        if(!SLL.isCur){
            SLL.isCur=true;
            resetCursorPosition();
            currentStep++;
        }
        code.setHighlight({0});
        SLL.cur->setTargetDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setTargetPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-ArrowLength,SLL.list[SLL.indexStep+1]->getStartPos().y+ArrowLength});
        if(SLL.cur->getDestination().x==SLL.list[SLL.indexStep+1]->getStartPos().x&&SLL.cur->getDestination().y==SLL.list[SLL.indexStep+1]->getStartPos().y){
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                checkTimer=0;
                SLL.animationStep++;
                currentStep++;
            }
        }
    }
    if(SLL.animationStep==1){
        SLL.list[index]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-ArrowLength,SLL.list[index]->getStartPos().y+ArrowLength});
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength)&&SLL.list[index]->getPosition().y==SLLposition.y+100){
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                checkTimer=0;
                currentStep++;
                SLL.animationStep++;
                SLL.newNode=SLL.list[index];
                SLL.list.erase(SLL.list.begin()+index);
                SLL.isNewNode=true;
            }
        }
    }
    if(SLL.list.empty()){
        code.setHighlight({1});
        if(SLL.head->getDestination().x==SLL.head->getPosition().x+ArrowLength&&SLL.head->getDestination().y==SLL.head->getPosition().y){
            checkTimer+=GetFrameTime();
            code.setHighlight({2});
            if(checkTimer>=delayTime){
                SLL.isNewNode=false;
                delete SLL.newNode;
                SLL.newNode=nullptr;
                SLL.isCur=false;
                SLL.animationStep=0;
                SLL.indexStep=-1;
                animationState=SLLAnimationMode::IDLE;
                currentStep++;
                isPlaying=false;
                isPaused=true;
                code.clearHighlight();
            }
        }
    }
    else if(SLL.animationStep==2){
        code.setHighlight({1});
        currentStep++;
        if(SLL.head->getDestination().x==SLL.list[index]->getStartPos().x&&SLL.head->getDestination().y==SLL.list[index]->getStartPos().y){
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                code.setHighlight({2});
                checkTimer=0;
                SLL.isNewNode=false;
                delete SLL.newNode;
                SLL.newNode=nullptr;
                SLL.isCur=false;
                SLL.animationStep++;
                currentStep++;
            }
        }
    }
    else if(SLL.animationStep==3){
        for (int i=index;i<SLL.list.size();i++){
            SLL.list[i]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + i * (SLLNodeSize.x+ArrowLength), SLLposition.y});
        }
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength)){
            SLL.animationStep=0;
            SLL.indexStep=-1;
            animationState=SLLAnimationMode::IDLE;
            currentStep++;
            isPlaying=false;
            isPaused=true;
            code.clearHighlight();
        }
    }
}

void SLLState::animateRemoveMid(int index){
    if(!isPlaying||isPaused) return;
    if(SLL.indexStep>index) return;
    static float checkTimer = 0.0f;
    if(SLL.animationStep==0&&SLL.indexStep<index&&(SLL.cur->getDestination().x!=SLL.list[SLL.indexStep+1]->getStartPos().x||SLL.cur->getDestination().y!=SLL.list[SLL.indexStep+1]->getStartPos().y)){
        if(!SLL.isCur){
            SLL.isCur=true;
            resetCursorPosition();
            currentStep++;
        }
        if(SLL.indexStep==-1){
            code.setHighlight({0});
        }
        else{
            code.setHighlight({1,2});
        }
        SLL.cur->setTargetDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setTargetPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-ArrowLength,SLL.list[SLL.indexStep+1]->getStartPos().y+ArrowLength});
    }
    else if(SLL.animationStep==0&&SLL.indexStep<index-1){
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            checkTimer=0;
            SLL.indexStep++;
            if(SLL.indexStep==index-1){
                SLL.animationStep++;
            }
            currentStep++;
        }
    }
    else if(SLL.animationStep==1){
        code.setHighlight({3});
        SLL.newNode=SLL.list[index];
        SLL.checkNewNodeinList=true;
        SLL.list[index]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
        if(!SLL.myNode){
            SLL.myNode=new SLLArrow({SLL.head->getPosition().x + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
            SLL.myNode->setLabel("myNode");
        }
        SLL.myNode->setDestination(SLL.list[index]->getStartPos());
        SLL.myNode->setPosition({SLL.list[index]->getStartPos().x-ArrowLength,SLL.list[index]->getStartPos().y+ArrowLength});
        SLL.isNewNode=true;
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength)&&SLL.list[index]->getPosition().y==SLLposition.y+100){
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                checkTimer=0;
                SLL.animationStep++;
                currentStep++;
            }
        }
    }
    else if(SLL.animationStep==2&&index>=SLL.list.size()-1){
        SLL.list.erase(SLL.list.begin()+index);
        SLL.checkNewNodeinList=false;
        SLL.animationStep++;
        currentStep++;
        code.setHighlight({4,5});
    }
    else if(SLL.animationStep==2){
        code.setHighlight({4});
        if(SLL.checkNewNodeinList){
            SLL.list.erase(SLL.list.begin()+index);
            SLL.checkNewNodeinList=false;
        }
        if(SLL.list[index-1]->getDestination().x==SLL.list[index]->getStartPos().x&&SLL.list[index-1]->getDestination().y==SLL.list[index]->getStartPos().y){
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                checkTimer=0;
                SLL.animationStep++;
                currentStep++;
            }
        }
    }
    else if(SLL.animationStep==3&&index>=SLL.list.size()-1){
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            checkTimer=0;
            SLL.animationStep=0;
            SLL.indexStep=-1;
            animationState=SLLAnimationMode::IDLE;
            currentStep++;
            isPlaying=false;
            isPaused=true;
            SLL.isCur=false;
            resetCursorPosition();
            delete SLL.newNode;
            SLL.newNode=nullptr;
            delete SLL.myNode;
            SLL.myNode=nullptr;
            SLL.isNewNode=false;
            code.clearHighlight();
        }
    }
    else if(SLL.animationStep==3){
        code.setHighlight({5});
        SLL.animationStep++;
        currentStep++;
        SLL.isCur=false;
        resetCursorPosition();
        delete SLL.newNode;
        SLL.newNode=nullptr;
        delete SLL.myNode;
        SLL.myNode=nullptr;
        SLL.isNewNode=false;
    }
    else if(SLL.animationStep==4){
        for (int i=index;i<SLL.list.size();i++){
            SLL.list[i]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + i * (SLLNodeSize.x+ArrowLength), SLLposition.y});
        }
        SLL.animationStep++;
        currentStep++;
    }
    else if(SLL.animationStep==5){
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength)){
            SLL.animationStep=0;
            SLL.indexStep=-1;
            animationState=SLLAnimationMode::IDLE;
            currentStep++;
            isPlaying=false;
            isPaused=true;
            code.clearHighlight();
        }
    }
}

void SLLState::animateSearch(int value){
    if(!isPlaying||isPaused) return;
    static float checkTimer = 0.0f;
    if(SLL.list.empty()){
        checkTimer+=GetFrameTime();
        code.setHighlight({0});
        if(checkTimer>=delayTime){
            checkTimer=0;
            animationState=SLLAnimationMode::IDLE;
            currentStep++;
            isPlaying=false;
            isPaused=true;
            code.clearHighlight();
            return;
        }
        return;
    }
    SLL.resetHighlight(); 
    if((SLL.cur->getDestination().x!=SLL.list[SLL.indexStep+1]->getStartPos().x||SLL.cur->getDestination().y!=SLL.list[SLL.indexStep+1]->getStartPos().y)){
        if(!SLL.isCur){
            SLL.isCur=true;
            resetCursorPosition();
            currentStep++;
        }
        if(SLL.indexStep==-1){
            code.setHighlight({1,2});
        }
        else{
            code.setHighlight({3,4,5});
        }
        SLL.cur->setTargetDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setTargetPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-ArrowLength,SLL.list[SLL.indexStep+1]->getStartPos().y+ArrowLength});
    }
    else {
        checkTimer+=GetFrameTime();
        if(SLL.list[SLL.indexStep+1]->getValue()==value){
            code.setHighlight({7});
        }
        else if(SLL.list.size()<SLL.indexStep+3){
            code.setHighlight({6});
        }
        if(checkTimer>=delayTime){
            if(SLL.list[SLL.indexStep+1]->getValue()==value||SLL.list.size()<SLL.indexStep+3){
                if(SLL.list[SLL.indexStep+1]->getValue()==value)
                    SLL.list[SLL.indexStep+1]->setHighlight();
                SLL.isCur=false;
                SLL.cur->setPosition({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f+ArrowLength});
                SLL.cur->setDestination({SLLposition.x+ArrowLength,SLLposition.y+SLLNodeSize.y/2.0f+ArrowLength});
                SLL.indexStep=-1;
                animationState=SLLAnimationMode::IDLE;
                currentStep++;
                isPlaying=false;
                isPaused=true;
                code.clearHighlight();
                return;
            }
            currentStep++;
            SLL.indexStep++;
            checkTimer=0;
        }
    }
}

void SLLState::animateUpdate(int index, int value){
    if(index>=SLL.list.size()||index<0){
        animationState=SLLAnimationMode::IDLE;
        currentStep++;
        isPlaying=false;
        isPaused=true;
        return;
    }
    if(!isPlaying||isPaused) return;
    if(SLL.indexStep>index) return;
    static float checkTimer = 0.0f;
    if(SLL.animationStep==0&&SLL.indexStep<index&&(SLL.cur->getDestination().x!=SLL.list[SLL.indexStep+1]->getStartPos().x||SLL.cur->getDestination().y!=SLL.list[SLL.indexStep+1]->getStartPos().y)){
        if(!SLL.isCur){
            SLL.isCur=true;
            resetCursorPosition();
            currentStep++;
        }
        if(SLL.indexStep==-1){
            code.setHighlight({0});
        }
        else{
            code.setHighlight({1,2});
        }
        SLL.cur->setTargetDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setTargetPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-ArrowLength,SLL.list[SLL.indexStep+1]->getStartPos().y+ArrowLength});
    }
    else if(SLL.animationStep==0&&SLL.indexStep<index){
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            checkTimer=0;
            SLL.indexStep++;
            if(SLL.indexStep==index) {
                SLL.animationStep++;
            }
            currentStep++;
        }
    }
    else if(SLL.animationStep==1){
        SLL.list[index]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+ArrowLength), SLLposition.y+100});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-ArrowLength,SLL.list[index]->getStartPos().y+ArrowLength});
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength)&&SLL.list[index]->getPosition().y==SLLposition.y+100){
            code.setHighlight({3});
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                checkTimer=0;
                currentStep++;
                SLL.animationStep++;
            }
        }
    }
    else if(SLL.animationStep==2){
        checkTimer=0;
        SLL.animationStep++;
        SLL.list[index]->setValue(value);
        currentStep++;
    }
    else if(SLL.animationStep==3){
        SLL.list[index]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-ArrowLength,SLL.list[index]->getStartPos().y+ArrowLength});
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+ArrowLength)&&SLL.list[index]->getPosition().y==SLLposition.y){
            currentStep++;
            SLL.indexStep=-1;
            SLL.animationStep=0;
            SLL.isCur=false;
            resetCursorPosition();
            animationState=SLLAnimationMode::IDLE;
            currentStep++;
            isPlaying=false;
            isPaused=true;
            code.clearHighlight();
        }
    }
}

void SLLState::resetCursorPosition(){
    SLL.cur->setPosition({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f+ArrowLength});
    SLL.cur->setDestination({SLLposition.x+ArrowLength,SLLposition.y+SLLNodeSize.y/2.0f+ArrowLength});
}

void SLLState::resetBox(){
    createBox.resetBox();
    indexBox.resetBox();
    valueBox.resetBox();
}

std::string SLLState::getRandomInput(){
    int numElement=rand()%10;
    std::string elements="";
    for (int i=0;i<=numElement;i++){
        if(i==numElement){
            elements+=std::to_string(rand()%100);
            continue;
        }
        elements+= std::to_string(rand()%100) +",";
    }
    return elements;
}

bool SLLState::isBackPressed(){
    bool res=panel.isBackPressed();
    if(res){
        speedSlider.reset();
        Front.deActive();
        End.deActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
        SLL.clear();
        resetBox();
        isPlaying = false;
        isPaused = false;
        currentStep = 0;
        isStateSaved=false;
        clearState();
        animationState=SLLAnimationMode::IDLE;
        code.clearCode();
        code.clearHighlight();
        panel.reset();
    }
    return res;
}

void SLLState::play(){
    if (!stateList.empty()) {
        isPlaying = true;   
        isPaused = false;   
        currentStep = 0;    
        animationState = stateList[currentStep]->animationState;
    }
}

void SLLState::pause() {
    isPaused = true;  
}

void SLLState::resume() {
    isPaused = false;
}

void SLLState::nextStep(){
    isPlaying=true;
    if(currentStep<stateList.size()-1){
        currentStep++;
        if(currentStep==stateList.size()-1){
            isPlaying=false;
        }
        applyState();
    }
}

void SLLState::prevStep() {
    isPlaying=true;
    if (currentStep > 0) {
        currentStep--;
        applyState();
    }
}

void SLLState::restart(){
    isPlaying=true;
    isPaused=false;
    currentStep=0;
    applyState();
}

void SLLState::moveEnd(){
    isPlaying=false;
    isPaused=true;
    currentStep=stateList.size()-1;
    applyState();
}

void SLLState::moveStart(){
    isPlaying=true;
    currentStep=0;
    applyState();
}

void SLLState::saveState(){
    SinglyLinkedList* currentState = SLL.clone();
    SLLAnimationMode currentMode = this->animationState;
    CodeBlock currentCodeBlock = this->code;
    stateList.push_back(new AnimationStep{currentState, currentMode,currentCodeBlock});
}

void SLLState::applyState(){
    if(stateList.empty()) return;
    if (currentStep < 0) {
        currentStep = 0; 
    }
    else  if (currentStep >= stateList.size()) {
        currentStep = stateList.size() - 1;
    }
    SLL.clear();
    SLL = *stateList[currentStep]->SLL->clone();
    animationState=stateList[currentStep]->animationState;
    code=stateList[currentStep]->code;
}

void SLLState::clearState() {
    for (auto state : stateList) {
        if (state) {
            delete state;
            state=nullptr;
        }
    }
    stateList.clear();
}