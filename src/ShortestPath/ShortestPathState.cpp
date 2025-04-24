#include <ShortestPath/ShortestPathState.h>

const float COOLDOWN=0.93f;

ShortestPathState::ShortestPathState() : NodesBox(120,680,STBoxSize.x,STBoxSize.y,STBoxFontSize,boxColor,boxTextColor), EdgesBox(120,750,STBoxSize.x,STBoxSize.y,STBoxFontSize,boxColor,boxTextColor), StartNodesBox(120,680,STBoxSize.x,STBoxSize.y,STBoxFontSize,boxColor,boxTextColor), speedSlider(0.1,5,1,50){
    this->Random.setText("Random",STButtonFontSize);
    this->Random.setSize({120, 30});
    this->Random.setPosition({180,810});

    this->LoadFile.setText("Load File",STButtonFontSize);
    this->LoadFile.setSize({120, 30});
    this->LoadFile.setPosition({320,810});

    this->Apply.setText("Apply",STButtonFontSize);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,850});

    this->Weighted.setText("Weighted",STButtonFontSize);
    this->Weighted.setSize({120, 30});
    this->Weighted.setPosition({180,680});

    this->Unweighted.setText("Unweighted",STButtonFontSize);
    this->Unweighted.setSize({120, 30});
    this->Unweighted.setPosition({320,680});

    this->Directed.setText("Directed",STButtonFontSize);
    this->Directed.setSize({120, 30});
    this->Directed.setPosition({180,720});

    this->Undirected.setText("UnDirected",STButtonFontSize);
    this->Undirected.setSize({120, 30});
    this->Undirected.setPosition({320,720});
    
    this->Undirected.Selected();
    this->Unweighted.Selected();
    ST.deDirected();
    ST.deWeighted();

    NodesBox.setNameBox("Number Of Vertices");
    EdgesBox.setNameBox("Number Of Edges");
    StartNodesBox.setNameBox("Start Node");
}

void ShortestPathState::updateTheme(){
    panel.update();
    Random.update();
    LoadFile.update();
    Apply.update();
    Weighted.update();
    Unweighted.update();
    Directed.update();
    Undirected.update();
    NodesBox.Update();
    EdgesBox.Update();
    StartNodesBox.Update();
}

void ShortestPathState::update(){
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

    ST.update();
    if(currentStep==stateList.size()-1){
        ST.updateLine();
    }
    panel.update();
    speedSlider.Update();

    switch (animationState) {
        case STAnimationMode::CREATE:
            animateFruchtermanReingold();
            break;
        case STAnimationMode::DIJKSTRA:
            if (!isStateSaved) {
                saveDijkstraState(std::stoi(startNodeText));
                isStateSaved = true; 
            }
            animateDijkstra(std::stoi(startNodeText));
            break;
        case STAnimationMode::IDLE:
            break;
        default:
            break;
    }

    if(panel.isCreateUsed()){
        Apply.setPosition({250,850});
        Random.setActive();
        LoadFile.setActive();
        Apply.setActive();
        Weighted.deActive();
        Unweighted.deActive();
        Directed.deActive();
        Undirected.deActive();
    }
    else if(panel.isDijkstraUsed()){
        Apply.setPosition({250,740});
        Random.deActive();
        LoadFile.deActive();
        Apply.setActive();
        Weighted.deActive();
        Unweighted.deActive();
        Directed.deActive();
        Undirected.deActive();
    }
    else if(panel.isSettingUsed()){
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
        Weighted.setActive();
        Unweighted.setActive();
        Directed.setActive();
        Undirected.setActive();
    }
    else{
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
        Weighted.deActive();
        Unweighted.deActive();
        Directed.deActive();
        Undirected.deActive();
    }
    if(Random.isPressed()){
        int numNodes=rand()%9+2;
        ST.createGraph(numNodes,int(rand()%(numNodes*(numNodes-1))/2+1));
        if(Weighted.isSelected())
            ST.setWeighted();
        else if(Unweighted.isSelected())
            ST.deWeighted();
        if(Directed.isSelected())
            ST.setDirected();
        else if(Undirected.isSelected())
            ST.deDirected();
        animationState=STAnimationMode::CREATE;
    }
    else if(LoadFile.isPressed()){
        isLoadFile=true;
    }
    else if(Weighted.isPressed()){
        Weighted.Selected();
        Unweighted.deSelected();
        ST.setWeighted();
    }
    else if(Unweighted.isPressed()){
        Unweighted.Selected();
        Weighted.deSelected();
        ST.deWeighted();
    }
    else if(Directed.isPressed()){
        Directed.Selected();
        Undirected.deSelected();
        ST.setDirected();
    }
    else if(Undirected.isPressed()){
        Undirected.Selected();
        Directed.deSelected();
        ST.deDirected();
    }
    else if(isLoadFile&&panel.isCreateUsed()){
        ST.createGraph(panel.loadFileContent());
        if(Weighted.isSelected())
            ST.setWeighted();
        else if(Unweighted.isSelected())
            ST.deWeighted();
        if(Directed.isSelected())
            ST.setDirected();
        else if(Undirected.isSelected())
            ST.deDirected();
        isLoadFile=false;
        animationState=STAnimationMode::CREATE;
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        startNodeText=StartNodesBox.GetText();
        nodesText=NodesBox.GetText();
        edgesText=EdgesBox.GetText();
        resetBox();
        ST.deltaTime=0;
        if(panel.isCreateUsed()&&nodesText!=""&&edgesText!=""&&std::stoi(nodesText)>0&&std::stoi(edgesText)>0&&std::stoi(edgesText)<=(std::stoi(nodesText)*(std::stoi(nodesText)-1)/2)){
            ST.createGraph(std::stoi(nodesText),std::stoi(edgesText));
            animationState=STAnimationMode::CREATE;
        }
        else if(!ST.graph.empty()&&panel.isDijkstraUsed()&&startNodeText!=""&&std::stoi(startNodeText)<ST.graph.size()&&std::stoi(startNodeText)>=0){
            isStateSaved=false;
            clearState();
            isPlaying=true;
            isPaused=false;
            animationState=STAnimationMode::DIJKSTRA;
            code.setCode(DijkstraCode);
        }
    }
    else if(panel.isAnyButtonPressed()){
        moveEnd();
        clearState();
        resetBox();
        code.clearCode();
        code.clearHighlight();
    }
    if(panel.isCreateUsed()){
        NodesBox.Update();
        EdgesBox.Update();
        this->Random.update();
        this->LoadFile.update();
        this->Apply.update();
    }
    else if(panel.isDijkstraUsed()){
        StartNodesBox.Update();
        this->Apply.update();
    }
    else if(panel.isSettingUsed()){
        this->Weighted.update();
        this->Unweighted.update();
        this->Directed.update();
        this->Undirected.update();
    }
}

void ShortestPathState::draw(){
    code.draw();
    ST.draw();
    panel.draw();
    speedSlider.Draw();
    if(panel.isCreateUsed()){
        NodesBox.Draw();
        EdgesBox.Draw();
        this->Random.drawRectangleRounded(100);
        this->LoadFile.drawRectangleRounded(100);
        this->Apply.drawRectangleRounded(100);
        this->Random.drawText();
        this->LoadFile.drawText();
        this->Apply.drawText();
        this->Random.drawOutlineRounded(100, 10, 3);
        this->LoadFile.drawOutlineRounded(100, 10, 3);
        this->Apply.drawOutlineRounded(100, 10, 3);
    }
    else if(panel.isDijkstraUsed()){
        StartNodesBox.Draw();
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText();
        this->Apply.drawOutlineRounded(100, 10, 3);
    }
    else if(panel.isSettingUsed()){
        Weighted.drawRectangleRounded(100);
        Directed.drawRectangleRounded(100);
        Unweighted.drawRectangleRounded(100);
        Undirected.drawRectangleRounded(100);
        Weighted.drawText();
        Directed.drawText();
        Unweighted.drawText();
        Undirected.drawText();
        Weighted.drawOutlineRounded(100, 10, 3);
        Directed.drawOutlineRounded(100, 10, 3);
        Unweighted.drawOutlineRounded(100, 10, 3);
        Undirected.drawOutlineRounded(100, 10, 3);
    }
}

void ShortestPathState::saveDijkstraState(int startNode){
    while(true){
        if(ST.animationStep==0){
            ST.resetGraph();
            saveState();
            code.setHighlight({0,1});
            ST.current=ST.graph[startNode];
            ST.animationStep++;
            ST.graph[startNode]->setCost(0);
            saveState();
        }
        else if(ST.animationStep==1){
            ST.current->setHighlight();
            ST.animationStep++;
            saveState();
        }
        else if(ST.animationStep==2){
            if(ST.isDirected){
                if(ST.current->arrow.empty()){
                    code.setHighlight({6});
                    ST.current->setKnown();
                    ST.animationStep++;
                    saveState();
                    continue;
                }
                if(ST.index>=ST.current->arrow.size()){
                    code.setHighlight({6});
                    ST.index=0;
                    ST.animationStep++;
                    ST.current->setKnown();
                    saveState();
                    continue;
                }
                ST.current->arrow[ST.index]->setHighlight();
                code.setHighlight({3,4});
                saveState();
                int to = ST.current->arrow[ST.index]->getTo();
                int weight = (ST.isWeighted) ? ST.current->arrow[ST.index]->getWeight() : 1;
                int newCost = ST.current->getCost() + weight;
                if (ST.current->getCost()!=-1&&(ST.graph[to]->getCost() == -1 || newCost < ST.graph[to]->getCost())) {
                    code.setHighlight({5});
                    ST.graph[to]->setCost(newCost);
                    ST.graph[to]->prev=ST.current;
                    ST.animationStep=4;
                    saveState();
                }
                else{
                    ST.current->arrow[ST.index]->deHighlight();
                    ST.index++;
                }
            }
            else{
                if(ST.index>=ST.allArrows.size()){
                    code.setHighlight({6});
                    ST.index=0;
                    ST.animationStep++;
                    ST.current->setKnown();
                    saveState();
                    continue;
                }
                code.setHighlight({3,4});
                int from = ST.allArrows[ST.index]->getFrom();
                int to = ST.allArrows[ST.index]->getTo();
                int weight = (ST.isWeighted)? ST.allArrows[ST.index]->getWeight() : 1;
                if(from == ST.current->getID()||to == ST.current->getID()){
                    ST.allArrows[ST.index]->setHighlight();
                    saveState();
                    int newCost = ST.current->getCost() + weight;
                    if (from == ST.current->getID()) {
                        if(ST.current->getCost()!=-1&&(ST.graph[to]->getCost() == -1 || newCost < ST.graph[to]->getCost())) {
                            code.setHighlight({5});
                            ST.graph[to]->setCost(newCost);
                            ST.graph[to]->prev=ST.current;
                            ST.animationStep=4;
                            saveState();
                        }
                        else{
                            ST.allArrows[ST.index]->deHighlight();
                            ST.index++;
                        }
                    } 
                    else if (to == ST.current->getID()) {
                        if(ST.current->getCost()!=-1&&(ST.graph[from]->getCost() == -1 || newCost < ST.graph[from]->getCost())) {
                            code.setHighlight({5});
                            ST.graph[from]->setCost(newCost);
                            ST.graph[from]->prev=ST.current;
                            ST.animationStep=4;
                            saveState();
                        }
                        else{
                            ST.allArrows[ST.index]->deHighlight();
                            ST.index++;
                        }
                    }
                }
                else{
                    ST.index++;
                }
            }
        }
        else if(ST.animationStep==3){
            code.setHighlight({7});
            for (auto n : ST.graph) {
                if(n->getCost()!=-1)
                    n->setHighlight();
                if (!n->getKnown() && n->getCost()!=-1 && n->getCost() <= minCost) {
                    if(n->getCost()!=-1)
                        minCost = n->getCost();
                    findSmall = n->getID();
                }
            }
            saveState();
            if (findSmall == -1) {
                for (auto n : ST.graph){
                    n->deKnown();
                    n->deHighlight();
                }
                ST.animationStep=0;
                ST.index=0;
                animationState=STAnimationMode::IDLE;
                code.clearHighlight();
                saveState();
                currentStep=0;
                applyState();
                return;
            }
            else{
                code.setHighlight({2});
                ST.current = ST.graph[findSmall];
                ST.animationStep-=2;
                for (auto n : ST.graph){
                    if(n!=ST.current)
                        n->deHighlight();
                }
                saveState();
            }
            findSmall = -1;
            minCost = INT_MAX;
        }
        else if(ST.animationStep==4){
            if(ST.isDirected){
                ST.current->arrow[ST.index]->deHighlight();
            }
            else{
                ST.allArrows[ST.index]->deHighlight();
            }
            ST.index++;
            ST.animationStep=2;
        }
    }
}
        
void ShortestPathState::animateFruchtermanReingold() {
    float X_min = centerX - rangeX / 2.0f, X_max = centerX + rangeX / 2.0f;
    float Y_min = centerY - rangeY / 2.0f, Y_max = centerY + rangeY / 2.0f;

    if (ST.deltaTime <= 8.0f) {
        ST.deltaTime += GetFrameTime();
        for (auto& node : ST.graph) {
            node->setForce({0, 0});
        }
        for (int i = 0; i < ST.graph.size(); i++) {
            if (!ST.graph[i]) continue;
            for (int j = i + 1; j < ST.graph.size(); j++) {
                if (!ST.graph[j]) continue;
                Vector2 force = ST.ComputeRepulsiveForce(ST.graph[i], ST.graph[j]);
                ST.graph[i]->setForce({ST.graph[i]->getForce().x + force.x,ST.graph[i]->getForce().y + force.y});
                ST.graph[j]->setForce({ST.graph[j]->getForce().x - force.x,ST.graph[j]->getForce().y - force.y});
            }
            for (auto& edge : ST.graph[i]->arrow) {
                int from = edge->getFrom();
                int to = edge->getTo();
                Vector2 force = ST.ComputeAttractiveForce(ST.graph[from], ST.graph[to]);
                ST.graph[from]->setForce({ST.graph[from]->getForce().x - force.x,ST.graph[from]->getForce().y - force.y});
                ST.graph[to]->setForce({ST.graph[to]->getForce().x + force.x,ST.graph[to]->getForce().y + force.y});
            }
        }
        float epsilon = 0.3f;
        float maxDisplacement = 10.0f;
        bool allStable = true;

        for (auto& node : ST.graph) {
            Vector2 force = node->getForce();
            float dx = force.x * ST.cool;
            float dy = force.y * ST.cool;
            float disp = sqrt(dx * dx + dy * dy);
            if (disp > maxDisplacement) {
                dx = dx / disp * maxDisplacement;
                dy = dy / disp * maxDisplacement;
            }
            if (fabs(dx) < epsilon) dx = 0;
            if (fabs(dy) < epsilon) dy = 0;
            float newX = node->getPosition().x + dx;
            float newY = node->getPosition().y + dy;
            newX = std::max(X_min, std::min(newX, X_max));
            newY = std::max(Y_min, std::min(newY, Y_max));
            if (dx != 0 || dy != 0) {
                node->setPosition({newX, newY});
                allStable = false;
            }
        }
        if (allStable || ST.deltaTime > 8.0f) {
            ST.cool = 1.5;
            ST.deltaTime = 0;
            animationState = STAnimationMode::IDLE;
            return;
        }

        ST.cool *= COOLDOWN;
    }
    else {
        ST.cool = 1.5;
        ST.deltaTime = 0;
        animationState = STAnimationMode::IDLE;
        return;
    }
}

void ShortestPathState::animateDijkstra(int startNode){
    if(!isPlaying||isPaused) return;
    static float checkTimer = 0.0f;
    if(ST.animationStep==0){
        code.setHighlight({0,1});
        ST.resetGraph();
        ST.current=ST.graph[startNode];
        ST.animationStep++;
        ST.graph[startNode]->setCost(0);
        currentStep++;
    }
    else if(ST.animationStep==1){
        ST.current->setHighlight();
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            checkTimer=0;
            ST.animationStep++;
            currentStep++;
        }
    }
    else if(ST.animationStep==2){
        if(ST.isDirected){
            if(ST.current->arrow.empty()){
                code.setHighlight({6});
                ST.current->setKnown();
                ST.animationStep++;
                currentStep++;
                return;
            }
            if(ST.index>=ST.current->arrow.size()){
                code.setHighlight({6});
                ST.index=0;
                ST.animationStep++;
                ST.current->setKnown();
                currentStep++;
                return;
            }
            ST.current->arrow[ST.index]->setHighlight();
            code.setHighlight({3,4});
            int to = ST.current->arrow[ST.index]->getTo();
            int weight = (ST.isWeighted) ? ST.current->arrow[ST.index]->getWeight() : 1;
            int newCost = ST.current->getCost() + weight;
            checkTimer+=GetFrameTime();
            if(checkTimer>=delayTime){
                currentStep++;
                checkTimer=0;
                if (ST.current->getCost()!=-1&&(ST.graph[to]->getCost() == -1 || newCost < ST.graph[to]->getCost())) {
                    code.setHighlight({5});
                    ST.graph[to]->setCost(newCost);
                    ST.graph[to]->prev=ST.current;
                    currentStep++;
                    ST.animationStep=4;
                }
                else{
                    ST.current->arrow[ST.index]->deHighlight();
                    ST.index++;
                }
            }
        }
        else{
            if(ST.index>=ST.allArrows.size()){
                code.setHighlight({6});
                ST.index=0;
                ST.animationStep++;
                ST.current->setKnown();
                currentStep++;
                return;
            }
            code.setHighlight({3,4});
            int from = ST.allArrows[ST.index]->getFrom();
            int to = ST.allArrows[ST.index]->getTo();
            int weight = (ST.isWeighted)? ST.allArrows[ST.index]->getWeight() : 1;
            if(from == ST.current->getID()||to == ST.current->getID()){
                checkTimer+=GetFrameTime();
                ST.allArrows[ST.index]->setHighlight();
                int newCost = ST.current->getCost() + weight;
                if (from == ST.current->getID()) {
                    if(checkTimer>=delayTime){
                        currentStep++;
                        checkTimer=0;
                        if (ST.current->getCost()!=-1&&(ST.graph[to]->getCost() == -1 || newCost < ST.graph[to]->getCost())) {
                            code.setHighlight({5});
                            ST.graph[to]->setCost(newCost);
                            ST.graph[to]->prev=ST.current;
                            ST.animationStep=4;
                            currentStep++;
                        }
                        else{
                            ST.allArrows[ST.index]->deHighlight();
                            ST.index++;
                        }
                    }
                } 
                else if (to == ST.current->getID()) {
                    if(checkTimer>=delayTime){
                        currentStep++;
                        checkTimer=0;
                        if (ST.current->getCost()!=-1&&(ST.graph[from]->getCost() == -1 || newCost < ST.graph[from]->getCost())) {
                            code.setHighlight({5});
                            ST.graph[from]->setCost(newCost);
                            ST.graph[from]->prev=ST.current;
                            ST.animationStep=4;
                            currentStep++;
                        }
                        else{
                            ST.allArrows[ST.index]->deHighlight();
                            ST.index++;
                        }
                    }
                }
            }
            else{
                ST.index++;
            }
        }
    }
    else if(ST.animationStep==3){
        code.setHighlight({7});
        checkTimer+=GetFrameTime();
        for (auto n : ST.graph) {
            if(n->getCost()!=-1)
                n->setHighlight();
            if (checkTimer>=delayTime&&!n->getKnown() && n->getCost()!=-1 && n->getCost() <= minCost) {
                if(n->getCost()!=-1)
                    minCost = n->getCost();
                findSmall = n->getID();
            }
        }
        if(checkTimer>=delayTime){
            currentStep++;
            checkTimer=0;
            if (findSmall == -1) {
                for (auto n : ST.graph){
                    n->deKnown();
                    n->deHighlight();
                }
                ST.animationStep=0;
                ST.index=0;
                animationState=STAnimationMode::IDLE;
                isPlaying=false;
                isPaused=true;
                currentStep++;
                code.clearHighlight();
                return;
            }
            else{
                code.setHighlight({2});
                ST.current = ST.graph[findSmall];
                ST.animationStep-=2;
                for (auto n : ST.graph){
                    if(n!=ST.current)
                        n->deHighlight();
                }
                currentStep++;
            }
            findSmall = -1;
            minCost = INT_MAX;
        }
    }
    else if(ST.animationStep==4){
        checkTimer+=GetFrameTime();
        if(checkTimer>=delayTime){
            if(ST.isDirected){
                ST.current->arrow[ST.index]->deHighlight();
            }
            else{
                ST.allArrows[ST.index]->deHighlight();
            }
            checkTimer=0;
            ST.index++;
            ST.animationStep=2;
        }
    }
}

void ShortestPathState::resetBox(){
    NodesBox.resetBox();
    EdgesBox.resetBox();
    StartNodesBox.resetBox();
}

bool ShortestPathState::isBackPressed(){
    bool res=panel.isBackPressed();
    if(res){
        speedSlider.reset();
        ST.clear();
        resetBox();
        Unweighted.Selected();
        Undirected.Selected();
        Weighted.deSelected();
        Directed.deSelected();
        ST.deDirected();
        ST.deWeighted();
        isPlaying = false;
        isPaused = false;
        currentStep = 0;
        isStateSaved=false;
        findSmall=-1;
        minCost =  INT_MAX;
        isLoadFile=false;
        clearState();
        animationState=STAnimationMode::IDLE;
        code.clearCode();
        code.clearHighlight();
        panel.reset();
    }
    return res;
}

void ShortestPathState::play(){
    if (!stateList.empty()) {
        isPlaying = true;   
        isPaused = false;   
        currentStep = 0;    
        animationState = stateList[currentStep]->animationState;
    }
}

void ShortestPathState::pause() {
    isPaused = true;  
}

void ShortestPathState::resume() {
    isPaused = false;
}

void ShortestPathState::nextStep(){
    isPlaying=true;
    if(currentStep<stateList.size()-1){
        currentStep++;
        if(currentStep==stateList.size()-1){
            isPlaying=false;
        }
        applyState();
    }
}

void ShortestPathState::prevStep() {
    isPlaying=true;
    if (currentStep > 0) {
        currentStep--;
        applyState();
    }
}

void ShortestPathState::restart(){
    isPlaying=true;
    isPaused=false;
    currentStep=0;
    applyState();
}

void ShortestPathState::moveEnd(){
    isPlaying=false;
    isPaused=true;
    currentStep=stateList.size()-1;
    applyState();
}

void ShortestPathState::moveStart(){
    isPlaying=true;
    currentStep=0;
    applyState();
}

void ShortestPathState::saveState(){
    ShortestPath* currentState = ST.clone();
    STAnimationMode currentMode = this->animationState;
    CodeBlock currentCodeBlock = this->code;
    stateList.push_back(new AnimationStep{currentState, currentMode,currentCodeBlock});
}

void ShortestPathState::applyState(){
    if(stateList.empty()) return;
    if (currentStep < 0) {
        currentStep = 0; 
    }
    else  if (currentStep >= stateList.size()) {
        currentStep = stateList.size() - 1;
    }
    ST.clearGraph();
    ST = *stateList[currentStep]->ST->clone();
    animationState=stateList[currentStep]->animationState;
    code=stateList[currentStep]->code.clone();
}

void ShortestPathState::clearState() {
    for (auto state : stateList) {
        if (state) {
            delete state;
            state=nullptr;
        }
    }
    stateList.clear();
}