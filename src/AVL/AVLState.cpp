//FIX LOAD FILE
#include <AVL/AVLState.h>

AVLState::AVLState(): createBox(120,680,AVLBoxSize.x, AVLBoxSize.y,AVLBoxFontSize,boxColor, boxTextColor), valueBox(120,680,AVLBoxSize.x, AVLBoxSize.y,AVLBoxFontSize,boxColor, boxTextColor), initialValue(120,680,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,boxColor, boxTextColor), finalValue(120,750,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,boxColor, boxTextColor), speedSlider(0.1,5,1,50){
    this->Random.setText("Random",AVLButtonFontSize);
    this->Random.setSize({120, 30});
    this->Random.setPosition({180,740});

    this->LoadFile.setText("Load File",AVLButtonFontSize);
    this->LoadFile.setSize({120, 30});
    this->LoadFile.setPosition({320,740});

    this->Apply.setText("Apply",AVLButtonFontSize);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,780});

    createBox.setNameBox("Input Elements");
    valueBox.setNameBox("Value");
    initialValue.setNameBox("Current Value");
    finalValue.setNameBox("New Value");
}

void AVLState::updateTheme(){
    panel.update();
    Random.update();
    LoadFile.update();
    Apply.update();
    createBox.Update();
    valueBox.Update();
    initialValue.Update();
    finalValue.Update();
}

void AVLState::update(){
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

    AVLTree.update();
    panel.update();
    speedSlider.Update();

    switch (animationState) {
        case AVLAnimationMode::INSERT:
            if (!isStateSaved) {
                saveInsertState(std::stoi(valueText));
                isStateSaved = true;
            }
            animateInsert(std::stoi(valueText));
            break;
        case AVLAnimationMode::REMOVE:
            if (!isStateSaved) {
                saveRemoveState(std::stoi(valueText));
                isStateSaved = true; 
            }
            animateRemove(std::stoi(valueText));
            break;
        case AVLAnimationMode::SEARCH:
            if (!isStateSaved) {
                saveSearchState(std::stoi(valueText));
                isStateSaved = true;
            }
            animateSearch(std::stoi(valueText));
            break;
        case AVLAnimationMode::UPDATE:
            if (!isStateSaved) {
                code.setCode(Remove);
                saveRemoveState(std::stoi(initialValueText));
                code.setCode(Insert);
                saveInsertState(std::stoi(finalValueText));
                isStateSaved = true;
            }
            animateRemove(std::stoi(initialValueText));
            break;
        case AVLAnimationMode::UPDATEINS:
            animateInsert(std::stoi(finalValueText));
            break;
        case AVLAnimationMode::IDLE:
            break;
        default:
            break;
    }
    if(panel.isCreateUsed()){
        Random.setActive();
        LoadFile.setActive();
        Apply.setActive();
        Apply.setPosition({250,780});
        
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isSearchUsed()){
        Random.deActive();
        LoadFile.deActive();
        Apply.setActive();
        Apply.setPosition({250,740});
    }
    else if(panel.isUpdateUsed()){
        Random.deActive();
        LoadFile.deActive();
        Apply.setActive();
        Apply.setPosition({250,810});
    }
    else{
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    if(Random.isPressed()){
        AVLTree.createTree(getRandomInput());
    }
    else if(LoadFile.isPressed()){
        std::string input=panel.loadFileContent();
        AVLTree.createTree(input);
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        AVLTree.resetHighlight();
        valueText=valueBox.GetText();
        createText=createBox.GetText();
        initialValueText=initialValue.GetText();
        finalValueText=finalValue.GetText();
        resetBox();
        if(panel.isCreateUsed()){
            AVLTree.createTree(createText);
        }
        else if(panel.isAddUsed()&&valueText!=""){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            code.setCode(Insert);
            animationState=AVLAnimationMode::INSERT;
        }
        else if(panel.isRemoveUsed()&&valueText!=""&&AVLTree.root){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            code.setCode(Remove);
            animationState=AVLAnimationMode::REMOVE;
        }
        else if(panel.isSearchUsed()&&valueText!=""&&AVLTree.root){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            code.setCode(Search);
            animationState=AVLAnimationMode::SEARCH;
        }
        else if(panel.isUpdateUsed()&&initialValueText!=""&&finalValueText!=""&&AVLTree.root){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            animationState=AVLAnimationMode::UPDATE;
        }
    }
    else if(panel.isAnyButtonPressed()){
        moveEnd();
        clearState();
        AVLTree.resetHighlight();
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
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isSearchUsed()){
        valueBox.Update();
        this->Apply.update();
    }
    else if(panel.isUpdateUsed()){
        initialValue.Update();
        finalValue.Update();
        this->Apply.update();
    }
}

void AVLState::draw(){
    code.draw();
    AVLTree.draw();
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
        this->Random.drawOutlineRounded(100, 0, 3);
        this->LoadFile.drawOutlineRounded(100, 0, 3);
        this->Apply.drawOutlineRounded(100, 0, 3);
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isSearchUsed()){
        valueBox.Draw();
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText();
        this->Apply.drawOutlineRounded(100, 0, 3);
    }
    else if(panel.isUpdateUsed()){
        initialValue.Draw();
        finalValue.Draw();
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText();
        this->Apply.drawOutlineRounded(100, 0, 3);
    }
}

void AVLState::saveInsertState(int value){
    saveState();
    while(true){
        if(!AVLTree.root){
            code.setHighlight({0});
            AVLTree.root = new AVLNode(); 
            AVLTree.root->setValue(value);
            AVLTree.calculateHeight();
            AVLTree.root->setPosition({(float)GetScreenWidth()/2,AVLPosition.y});
            AVLTree.root->setTargetPosition({(float)GetScreenWidth()/2,AVLPosition.y});
            AVLTree.curNode=AVLTree.root;
            animationState=AVLAnimationMode::IDLE;
            saveState();
            currentStep=0;
            applyState();
            return;
        }
        if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
            code.setHighlight({0});
            AVLTree.curNode->setHighlight();
            AVLTree.animationStep++;
        }
        else if(AVLTree.animationStep==1){
            saveState();
            if(AVLTree.curNode) AVLTree.curNode->deHighlight();
            if(value<AVLTree.curNode->getValue()){
                if(!AVLTree.curNode->left){
                    AVLTree.curNode->deHighlight();
                    AVLTree.animationStep++;
                }
                else{
                    AVLTree.curNode=AVLTree.curNode->left;
                }
            }
            else{
                if(!AVLTree.curNode->right){
                    AVLTree.curNode->deHighlight();
                    AVLTree.animationStep++;
                }
                else{
                    AVLTree.curNode=AVLTree.curNode->right;
                }
            }
            AVLTree.curNode->setHighlight();
        }
        else if(AVLTree.animationStep==2){
            if(value<AVLTree.curNode->getValue()){
                AVLTree.curNode->left=new AVLNode();
                AVLTree.curNode->left->setPosition(AVLTree.curNode->getOrigin());
                AVLTree.curNode->left->setValue(value);
                AVLTree.curNode->left->parent=AVLTree.curNode;
            }
            else{
                AVLTree.curNode->right=new AVLNode();
                AVLTree.curNode->right->setPosition(AVLTree.curNode->getOrigin());
                AVLTree.curNode->right->setValue(value);
                AVLTree.curNode->right->parent=AVLTree.curNode;
            }
            AVLTree.calculateHeight();
            AVLTree.setPosition();
            AVLTree.setArrowDestination();
            AVLTree.animationStep++;
            AVLTree.curNode->deHighlight();
        }
        else if(AVLTree.animationStep==3){
            if(value<AVLTree.curNode->getValue()){
                AVLTree.curNode->left->setHighlight();
                AVLTree.curNode->setDestinationLeft(AVLTree.curNode->left->getOrigin());
                AVLTree.curNode=AVLTree.curNode->left;
            }
            else{
                AVLTree.curNode->right->setHighlight();
                AVLTree.curNode->setDestinationRight(AVLTree.curNode->right->getOrigin());
                AVLTree.curNode=AVLTree.curNode->right;
            }
            AVLTree.animationStep++;
        }
        else if(AVLTree.animationStep==4){
            if (AVLTree.curNode) {
                code.setHighlight({1});
                AVLTree.curNode->setHighlight();
                saveState();
                int balanceFactor=getBalanceFactor(AVLTree.curNode);
                if(abs(balanceFactor)>1){
                    if(balanceFactor>1){
                        if(getBalanceFactor(AVLTree.curNode->left)<0) {
                            code.setHighlight({3});
                            AVLTree.rotateLeftRight(AVLTree.curNode);
                        }
                        else {
                            code.setHighlight({2});
                            AVLTree.rotateRight(AVLTree.curNode);
                        }
                    }
                    else if(balanceFactor<-1){
                        if(getBalanceFactor(AVLTree.curNode->right)>0) {
                            code.setHighlight({5});
                            AVLTree.rotateRightLeft(AVLTree.curNode);
                        }
                        else {
                            code.setHighlight({4});
                            AVLTree.rotateLeft(AVLTree.curNode);
                        }
                    }
                    AVLTree.setArrowDestination();
                    AVLTree.animationStep++;
                    saveState();
                }
                else {
                    AVLTree.curNode->deHighlight();
                    if (AVLTree.curNode->parent) {
                        AVLTree.animationStep++;
                    } else {
                        AVLTree.resetHighlight();
                        animationState = AVLAnimationMode::IDLE;
                        AVLTree.animationStep=0;
                        code.clearHighlight();
                        saveState();
                        currentStep=0;
                        applyState();
                        return;
                    }
                }
            }
        }
        else if(AVLTree.animationStep==5){
            AVLTree.animationStep++;
            AVLTree.setPosition();
        }
        else if(AVLTree.animationStep==6){
            AVLTree.setArrowDestination();
            AVLTree.animationStep-=2;
            AVLTree.curNode->deHighlight();
            if(AVLTree.curNode->parent)
                AVLTree.curNode=AVLTree.curNode->parent;
        }
    }
}

void AVLState::saveRemoveState(int value){
    saveState();
    while(true){
        if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
            code.setHighlight({0});
            AVLTree.curNode->setHighlight();
            AVLTree.animationStep++;
            saveState();
        }   
        else if(AVLTree.animationStep==1){
            if(!AVLTree.curNode){
                AVLTree.animationStep=0;
                animationState=AVLAnimationMode::IDLE;
                AVLTree.curNode=AVLTree.root;
                code.clearHighlight();
                saveState();
                currentStep=0;
                applyState();
                return;
            }
            if(AVLTree.curNode) AVLTree.curNode->deHighlight();
            if(value==AVLTree.curNode->getValue()){
                AVLTree.animationStep++;
            }
            else if(value<AVLTree.curNode->getValue()){
                AVLTree.curNode=AVLTree.curNode->left;    
            }
            else{
                AVLTree.curNode=AVLTree.curNode->right;
            }
            if(AVLTree.curNode){
                AVLTree.curNode->setHighlight();
            }
            saveState();
        }
        else if(AVLTree.animationStep==2){
            if(AVLTree.curNode->isLeaf()){
                AVLNode* del = AVLTree.curNode;
                if(AVLTree.curNode->parent){
                    if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = nullptr;
                    else AVLTree.curNode->parent->right = nullptr;
                    AVLTree.curNode=AVLTree.curNode->parent;
                    delete del;
                }
                else {
                    AVLTree.root = nullptr;
                    delete del;
                    AVLTree.curNode=nullptr;
                }
                AVLTree.animationStep++;
                AVLTree.calculateHeight();
                saveState();
            }
            else if(AVLTree.curNode->left&&AVLTree.curNode->right){
                if(!AVLTree.temp) {
                    AVLTree.temp=AVLTree.curNode->left;
                    AVLTree.temp->setHighlight();
                    saveState();
                }
                if(AVLTree.temp->right){
                    AVLTree.temp->deHighlight();
                    AVLTree.temp=AVLTree.temp->right;
                    AVLTree.temp->setHighlight();
                    saveState();
                }
                else{
                    AVLTree.curNode->setValue(AVLTree.temp->getValue());
                    AVLTree.curNode->deHighlight();
                    AVLTree.curNode=AVLTree.temp;
                }
            }
            else if(AVLTree.curNode->left){
                AVLNode* del = AVLTree.curNode;
                if(AVLTree.curNode->parent){
                    if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = AVLTree.curNode->left;
                    else AVLTree.curNode->parent->right = AVLTree.curNode->left;
                }
                else{
                    AVLTree.root=AVLTree.curNode->left;
                }
                AVLTree.curNode->left->parent = AVLTree.curNode->parent;
                AVLTree.animationStep++;
                AVLTree.curNode=AVLTree.curNode->left;
                delete del;
                AVLTree.calculateHeight();
                AVLTree.setArrowDestination();
            }
            else if(AVLTree.curNode->right){
                AVLNode* del = AVLTree.curNode;
                if(AVLTree.curNode->parent){
                    if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = AVLTree.curNode->right;
                    else AVLTree.curNode->parent->right = AVLTree.curNode->right;
                }
                else{
                    AVLTree.root=AVLTree.curNode->right;
                }
                AVLTree.curNode->right->parent = AVLTree.curNode->parent;
                AVLTree.animationStep++;
                AVLTree.curNode=AVLTree.curNode->right;
                delete del;
                AVLTree.calculateHeight();
                AVLTree.setArrowDestination();
            }
        }   
        else if(AVLTree.animationStep==3){
            if (AVLTree.curNode) {
                code.setHighlight({1});
                AVLTree.curNode->setHighlight();
                saveState();
                int balanceFactor=getBalanceFactor(AVLTree.curNode);
                if(abs(balanceFactor)>1){
                    if(balanceFactor>1){
                        if(getBalanceFactor(AVLTree.curNode->left)<0) {
                            code.setHighlight({3});
                            AVLTree.rotateLeftRight(AVLTree.curNode);
                        }
                        else {
                            code.setHighlight({2});
                            AVLTree.rotateRight(AVLTree.curNode);
                        }
                    }
                    else if(balanceFactor<-1){
                        if(getBalanceFactor(AVLTree.curNode->right)>0) {
                            code.setHighlight({5});
                            AVLTree.rotateRightLeft(AVLTree.curNode);
                        }
                        else {
                            code.setHighlight({4});
                            AVLTree.rotateLeft(AVLTree.curNode);
                        }
                    }
                    AVLTree.setArrowDestination();
                    AVLTree.animationStep++;
                    saveState();
                }
                else {
                    AVLTree.curNode->deHighlight();
                    if (AVLTree.curNode->parent) {
                        AVLTree.animationStep++;
                    } else {
                        AVLTree.resetHighlight();
                        AVLTree.animationStep=0;
                        code.clearHighlight();
                        if(animationState==AVLAnimationMode::UPDATE){
                            animationState = AVLAnimationMode::UPDATEINS;
                            code.setCode(Insert);
                            saveState();
                            return;
                        }
                        animationState = AVLAnimationMode::IDLE;
                        saveState();
                        currentStep=0;
                        applyState();
                        return;
                    }
                }
            }
            else{
                AVLTree.resetHighlight();
                AVLTree.animationStep=0;
                code.clearHighlight();
                if(animationState==AVLAnimationMode::UPDATE){
                    animationState = AVLAnimationMode::UPDATEINS;
                    code.setCode(Insert);
                    saveState();
                    return;
                }
                animationState = AVLAnimationMode::IDLE;
                saveState();
                currentStep=0;
                applyState();
                return;
            }
        }
        else if(AVLTree.animationStep==4){
            AVLTree.animationStep++;
            AVLTree.setPosition();
        }
        else if(AVLTree.animationStep==5){
            AVLTree.setArrowDestination();
            AVLTree.animationStep-=2;
            AVLTree.curNode->deHighlight();
            if(AVLTree.curNode->parent)
                AVLTree.curNode=AVLTree.curNode->parent;
        }
    }
}

void AVLState::saveSearchState(int value){
    saveState();
    if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
        AVLTree.curNode->setHighlight();
        AVLTree.animationStep++;
        if(value<AVLTree.curNode->getValue()){
            code.setHighlight({4,5});
        }
        else if(value>AVLTree.curNode->getValue()){
            code.setHighlight({6,7});
        }
        saveState();
    }
    while (AVLTree.animationStep==1){
        if(!AVLTree.curNode||value==AVLTree.curNode->getValue()){
            AVLTree.animationStep++;
            break;
        }
        if(AVLTree.curNode) AVLTree.curNode->deHighlight();
        if(value<AVLTree.curNode->getValue()){
            code.setHighlight({4,5});
            AVLTree.curNode=AVLTree.curNode->left;    
        }
        else{
            code.setHighlight({6,7});
            AVLTree.curNode=AVLTree.curNode->right;
        }
        if(AVLTree.curNode){
            AVLTree.curNode->setHighlight();
            if(AVLTree.curNode&&value!=AVLTree.curNode->getValue()){
                saveState();
            }
        }
    }
    while(AVLTree.animationStep==2){
        if(!AVLTree.curNode){
            code.setHighlight({0,1});
        }
        else{
            AVLTree.curNode->setHighlight();
            code.setHighlight({2,3});
        }
        AVLTree.animationStep=0;
        animationState=AVLAnimationMode::IDLE;
        AVLTree.curNode=AVLTree.root;
        saveState();
        currentStep=0;
        applyState();
        return;
    }
}

void AVLState::animateInsert(int value){
    if(!isPlaying||isPaused) return;
    if(!AVLTree.root){
        code.setHighlight({0});
        AVLTree.root = new AVLNode(); 
        AVLTree.root->setValue(value);
        AVLTree.calculateHeight();
        AVLTree.root->setPosition({(float)GetScreenWidth()/2,AVLPosition.y});
        AVLTree.root->setTargetPosition({(float)GetScreenWidth()/2,AVLPosition.y});
        AVLTree.curNode=AVLTree.root;
        isPlaying=false;
        isPaused=true;
        AVLTree.animationStep=0;
        animationState=AVLAnimationMode::IDLE;
        currentStep++;
        return;
    }
    static float checkTimer = 0.0f;
    if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
        code.setHighlight({0});
        checkTimer+=GetFrameTime();
        AVLTree.curNode->setHighlight();
        AVLTree.animationStep++;
    }
    else if(AVLTree.animationStep==1){
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            currentStep++;
            if(AVLTree.curNode) AVLTree.curNode->deHighlight();
            if(value<AVLTree.curNode->getValue()){
                if(!AVLTree.curNode->left){
                    AVLTree.curNode->deHighlight();
                    AVLTree.animationStep++;
                }
                else{
                    AVLTree.curNode=AVLTree.curNode->left;
                }
            }
            else{
                if(!AVLTree.curNode->right){
                    AVLTree.curNode->deHighlight();
                    AVLTree.animationStep++;
                }
                else{
                    AVLTree.curNode=AVLTree.curNode->right;
                }
            }
            AVLTree.curNode->setHighlight();
            checkTimer=0;
        }
    }
    else if(AVLTree.animationStep==2){
        if(value<AVLTree.curNode->getValue()){
            AVLTree.curNode->left=new AVLNode();
            AVLTree.curNode->left->setPosition(AVLTree.curNode->getOrigin());
            AVLTree.curNode->left->setValue(value);
            AVLTree.curNode->left->parent=AVLTree.curNode;
        }
        else{
            AVLTree.curNode->right=new AVLNode();
            AVLTree.curNode->right->setPosition(AVLTree.curNode->getOrigin());
            AVLTree.curNode->right->setValue(value);
            AVLTree.curNode->right->parent=AVLTree.curNode;
        }
        AVLTree.calculateHeight();
        AVLTree.setTargetPosition();
        AVLTree.curNode->deHighlight();
        AVLTree.animationStep++;
    }
    else if(AVLTree.animationStep==3){
        if(value<AVLTree.curNode->getValue()){
            AVLTree.curNode->left->setHighlight();
            AVLTree.curNode->setDestinationLeft(AVLTree.curNode->left->getOrigin());
            if(AVLTree.checkPosition()){         
                AVLTree.animationStep++;
                AVLTree.curNode=AVLTree.curNode->left;
            }
        }
        else{
            AVLTree.curNode->right->setHighlight();
            AVLTree.curNode->setDestinationRight(AVLTree.curNode->right->getOrigin());
            if(AVLTree.checkPosition()){
                AVLTree.animationStep++;
                AVLTree.curNode=AVLTree.curNode->right;
            }
        }
    }
    else if(AVLTree.animationStep==4){
        if (AVLTree.curNode) {
            code.setHighlight({1});
            AVLTree.curNode->setHighlight();
            int balanceFactor=getBalanceFactor(AVLTree.curNode);
            if(abs(balanceFactor)>1){
                currentStep++;
                if(balanceFactor>1){
                    if(getBalanceFactor(AVLTree.curNode->left)<0) {
                        code.setHighlight({3});
                        AVLTree.rotateLeftRight(AVLTree.curNode);
                    }
                    else {
                        code.setHighlight({2});
                        AVLTree.rotateRight(AVLTree.curNode);
                    }
                }
                else if(balanceFactor<-1){
                    if(getBalanceFactor(AVLTree.curNode->right)>0) {
                        code.setHighlight({5});
                        AVLTree.rotateRightLeft(AVLTree.curNode);
                    }
                    else {
                        code.setHighlight({4});
                        AVLTree.rotateLeft(AVLTree.curNode);
                    }
                }
                AVLTree.animationStep++;
                currentStep++;
            }
            else {
                checkTimer += GetFrameTime();
                if (checkTimer >= delayTime) {
                    currentStep++;
                    AVLTree.curNode->deHighlight();
                    if (AVLTree.curNode->parent) {
                        AVLTree.animationStep++;
                    } else {
                        AVLTree.resetHighlight();
                        animationState = AVLAnimationMode::IDLE;
                        checkTimer=0;
                        isPlaying=false;
                        isPaused=true;
                        AVLTree.animationStep=0;
                        currentStep++;
                        code.clearHighlight();
                        return;
                    }
                    checkTimer = 0;
                }
            }
        }
    }
    else if(AVLTree.animationStep==5){
        if(AVLTree.checkArrowDestination()){
            AVLTree.animationStep++;
            AVLTree.setTargetPosition();
        }
    }
    else if(AVLTree.animationStep==6){
        if(AVLTree.checkPosition()){
            AVLTree.animationStep-=2;
            AVLTree.curNode->deHighlight();
            if(AVLTree.curNode->parent)
                AVLTree.curNode=AVLTree.curNode->parent;
        }
    }
}

void AVLState::animateRemove(int value){
    if(!isPlaying||isPaused) return;
    static float checkTimer = 0.0f;
    if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
        code.setHighlight({0});
        checkTimer+=GetFrameTime();
        AVLTree.curNode->setHighlight();
        AVLTree.animationStep++;
        currentStep++;
    }
    else if(AVLTree.animationStep==1){
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            if(!AVLTree.curNode){
                AVLTree.animationStep=0;
                animationState=AVLAnimationMode::IDLE;
                AVLTree.curNode=AVLTree.root;
                checkTimer=0;
                currentStep++;
                isPlaying=false;
                isPaused=true;
                code.clearHighlight();
                return;
            }
            if(AVLTree.curNode) AVLTree.curNode->deHighlight();
            if(value==AVLTree.curNode->getValue()){
                AVLTree.animationStep++;
            }
            else if(value<AVLTree.curNode->getValue()){
                AVLTree.curNode=AVLTree.curNode->left;    
            }
            else{
                AVLTree.curNode=AVLTree.curNode->right;
            }
            if(AVLTree.curNode){
                AVLTree.curNode->setHighlight();
            }
            checkTimer=0;
            currentStep++;
        }
    }    
    else if(AVLTree.animationStep==2){
        if(AVLTree.curNode->isLeaf()){
            AVLNode* del = AVLTree.curNode;
            if(AVLTree.curNode->parent){
                if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = nullptr;
                else AVLTree.curNode->parent->right = nullptr;
                AVLTree.curNode=AVLTree.curNode->parent;
                delete del;
            }
            else {
                AVLTree.root = nullptr;
                delete del;
                AVLTree.curNode=nullptr;
            }
            AVLTree.animationStep++;
            AVLTree.calculateHeight();
            currentStep++;
        }
        else if(AVLTree.curNode->left&&AVLTree.curNode->right){
            if(!AVLTree.temp) {
                AVLTree.temp=AVLTree.curNode->left;
                AVLTree.temp->setHighlight();
                currentStep++;
            }
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                if(AVLTree.temp->right){
                    AVLTree.temp->deHighlight();
                    AVLTree.temp=AVLTree.temp->right;
                    AVLTree.temp->setHighlight();
                    currentStep++;
                }
                else{
                    AVLTree.curNode->setValue(AVLTree.temp->getValue());
                    AVLTree.curNode->deHighlight();
                    AVLTree.curNode=AVLTree.temp;
                }
                checkTimer=0;
            }
        }
        else if(AVLTree.curNode->left){
            AVLNode* del = AVLTree.curNode;
            if(AVLTree.curNode->parent){
                if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = AVLTree.curNode->left;
                else AVLTree.curNode->parent->right = AVLTree.curNode->left;
            }
            else{
                AVLTree.root=AVLTree.curNode->left;
                AVLTree.setTargetPosition();
            }
            AVLTree.curNode->left->parent = AVLTree.curNode->parent;
            AVLTree.animationStep++;
            AVLTree.curNode=AVLTree.curNode->left;
            delete del;
            AVLTree.calculateHeight();
        }
        else if(AVLTree.curNode->right){
            AVLNode* del = AVLTree.curNode;
            if(AVLTree.curNode->parent){
                if(AVLTree.curNode->parent->left==AVLTree.curNode) AVLTree.curNode->parent->left = AVLTree.curNode->right;
                else AVLTree.curNode->parent->right = AVLTree.curNode->right;
            }
            else{
                AVLTree.root=AVLTree.curNode->right;
                AVLTree.setTargetPosition();
            }
            AVLTree.curNode->right->parent = AVLTree.curNode->parent;
            AVLTree.animationStep++;
            AVLTree.curNode=AVLTree.curNode->right;
            delete del;
            AVLTree.calculateHeight();
        }
    }
    else if(AVLTree.animationStep==3){ 
        if (AVLTree.curNode) {
            code.setHighlight({1});
            AVLTree.curNode->setHighlight();
            int balanceFactor=getBalanceFactor(AVLTree.curNode);
            if(abs(balanceFactor)>1){
                currentStep++;
                if(balanceFactor>1){
                    if(getBalanceFactor(AVLTree.curNode->left)<0) {
                        code.setHighlight({3});
                        AVLTree.rotateLeftRight(AVLTree.curNode);
                    }
                    else {
                        code.setHighlight({2});
                        AVLTree.rotateRight(AVLTree.curNode);
                    }
                }
                else if(balanceFactor<-1){
                    if(getBalanceFactor(AVLTree.curNode->right)>0) {
                        code.setHighlight({5});
                        AVLTree.rotateRightLeft(AVLTree.curNode);
                    }
                    else {
                        code.setHighlight({4});
                        AVLTree.rotateLeft(AVLTree.curNode);
                    }
                }
                AVLTree.animationStep++;
                currentStep++;
            }
            else {
                checkTimer += GetFrameTime();
                if (checkTimer >= delayTime) {
                    currentStep++;
                    AVLTree.curNode->deHighlight();
                    if (!AVLTree.curNode->parent){
                        AVLTree.resetHighlight();
                        checkTimer=0;
                        AVLTree.animationStep=0;
                        currentStep++;
                        code.clearHighlight();
                        if(animationState==AVLAnimationMode::UPDATE){
                            animationState = AVLAnimationMode::UPDATEINS;
                            code.setCode(Insert);
                            currentStep++;
                            return;
                        }
                        animationState = AVLAnimationMode::IDLE;
                        isPlaying=false;
                        isPaused=true;
                        return;
                    }
                    checkTimer = 0;
                    AVLTree.animationStep++;
                }
            }
        }
        else{
            AVLTree.resetHighlight();
            animationState = AVLAnimationMode::IDLE;
            checkTimer=0;
            currentStep++;
            isPlaying=false;
            isPaused=true;
            AVLTree.animationStep=0;
            currentStep++;
            code.clearHighlight();
            return;
        }
    }
    else if(AVLTree.animationStep==4){
        if(AVLTree.checkArrowDestination()){
            AVLTree.animationStep++;
            AVLTree.setTargetPosition();
        }
    }
    else if(AVLTree.animationStep==5){
        if(AVLTree.checkPosition()){
            AVLTree.animationStep-=2;
            AVLTree.curNode->deHighlight();
            if(AVLTree.curNode->parent)
                AVLTree.curNode=AVLTree.curNode->parent;
        }
    }
}

void AVLState::animateSearch(int value){
    if(!isPlaying||isPaused) return;
    static float checkTimer = 0.0f;
    if(AVLTree.curNode==AVLTree.root&&AVLTree.animationStep==0){
        checkTimer+=GetFrameTime();
        AVLTree.curNode->setHighlight();
        if(value<AVLTree.curNode->getValue()){
            code.setHighlight({4,5});
        }
        else if(value>AVLTree.curNode->getValue()){
            code.setHighlight({6,7});
        }
        AVLTree.animationStep++;
        currentStep++;
    }
    else if(AVLTree.animationStep==1){
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            if(!AVLTree.curNode||value==AVLTree.curNode->getValue()){
                AVLTree.animationStep++;
                checkTimer=0;
                return;
            }
            if(AVLTree.curNode) AVLTree.curNode->deHighlight();
            if(value<AVLTree.curNode->getValue()){
                code.setHighlight({4,5});
                AVLTree.curNode=AVLTree.curNode->left;    
            }
            else{
                code.setHighlight({6,7});
                AVLTree.curNode=AVLTree.curNode->right;
            }
            if(AVLTree.curNode){
                AVLTree.curNode->setHighlight();
                if(AVLTree.curNode&&value!=AVLTree.curNode->getValue()){
                    currentStep++;
                }
            }
            checkTimer=0;
        }
    }
    else if(AVLTree.animationStep==2){
        if(!AVLTree.curNode){
            code.setHighlight({0,1});
        }
        else{
            AVLTree.curNode->setHighlight();
            code.setHighlight({2,3});
        }
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            checkTimer=0;
            AVLTree.animationStep=0;
            animationState=AVLAnimationMode::IDLE;
            AVLTree.curNode=AVLTree.root;
            currentStep++;
            isPlaying=false;
            isPaused=true;
            code.clearHighlight();
            return;
        }
    }
}

int AVLState::getBalanceFactor(AVLNode* root){
    int balanceFactor=0;
    if(root->left) balanceFactor+=root->left->getHeight();
    if(root->right) balanceFactor-=root->right->getHeight();
    return balanceFactor;
}

void AVLState::resetBox(){
    createBox.resetBox();
    valueBox.resetBox();
    initialValue.resetBox();
    finalValue.resetBox();
}

std::string AVLState::getRandomInput(){
    int numElement=rand()%30;
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

bool AVLState::isBackPressed(){
    bool res=panel.isBackPressed();
    if(res){
        speedSlider.reset();
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
        AVLTree.clear();
        resetBox();
        isPlaying = false;
        isPaused = false;
        currentStep = 0;
        isStateSaved=false;
        clearState();
        animationState=AVLAnimationMode::IDLE;
        code.clearCode();
        code.clearHighlight();
        panel.reset();
    }
    return res;
}

void AVLState::play(){
    if (!stateList.empty()) {
        isPlaying = true;   
        isPaused = false;   
        currentStep = 0;    
        animationState = stateList[currentStep]->animationState;
    }
}

void AVLState::pause() {
    isPaused = true;  
}

void AVLState::resume() {
    isPaused = false;
}

void AVLState::nextStep(){
    isPlaying=true;
    if(currentStep<stateList.size()-1){
        currentStep++;
        if(currentStep==stateList.size()-1){
            isPlaying=false;
        }
        applyState();
    }
}

void AVLState::prevStep() {
    isPlaying=true;
    if (currentStep > 0) {
        currentStep--;
        applyState();
    }
}

void AVLState::restart(){
    isPlaying=true;
    isPaused=false;
    currentStep=0;
    applyState();
}

void AVLState::moveEnd(){
    isPlaying=false;
    isPaused=true;
    currentStep=stateList.size()-1;
    applyState();
}

void AVLState::moveStart(){
    isPlaying=true;
    currentStep=0;
    applyState();
}

void AVLState::saveState(){
    AVL* currentState = AVLTree.clone();
    AVLAnimationMode currentMode = this->animationState;
    CodeBlock currentCodeBlock = this->code;
    stateList.push_back(new AnimationStep{currentState, currentMode,currentCodeBlock});
}

void AVLState::applyState(){
    if(stateList.empty()) return;
    if (currentStep < 0) {
        currentStep = 0; 
    }
    else  if (currentStep >= stateList.size()) {
        currentStep = stateList.size() - 1;
    }
    AVLTree.clearTree();
    AVLTree = *stateList[currentStep]->AVLTree->clone();
    animationState=stateList[currentStep]->animationState;
    code = stateList[currentStep]->code;
}

void AVLState::clearState(){
    for (auto state : stateList) {
        if (state) {
            delete state;
            state=nullptr;
        }
    }
    stateList.clear();
}