#include <ShortestPath/ShortestPathNode.h>

ShortestPathNode::ShortestPathNode(Vector2 pos) {
    id = 0;
    cost = -1;
    isKnown = false;
    isHighlight = false;
    position=pos;
}

ShortestPathNode::ShortestPathNode(int id) {
    this->id = id;
    cost = -1;
    isKnown = false;
    isHighlight = false;
}

ShortestPathNode::~ShortestPathNode() {
    for(auto node : adj){
        node=nullptr;
    }
    adj.clear();
}

void ShortestPathNode::setID(int id) {
    this->id = id;
}

int ShortestPathNode::getID() {
    return id;
}

void ShortestPathNode::setCost(int cost) {
    this->cost = cost;
}

int ShortestPathNode::getCost() {
    return cost;
}

void ShortestPathNode::setHighlight() {
    this->isHighlight = true;
}

void ShortestPathNode::deHighlight() {
    this->isHighlight = false;
}

bool ShortestPathNode::getHighlight() {
    return isHighlight;
}

void ShortestPathNode::setKnown() {
    this->isKnown = true;
}

void ShortestPathNode::deKnown() {
    this->isKnown = false;
}

bool ShortestPathNode::getKnown() {
    return isKnown;
}

Vector2 ShortestPathNode::getPosition() {
    return position;
}

void ShortestPathNode::setPosition(Vector2 position) {
    this->position = position;
    node = {position.x-STNodeSize.x/2.0f,position.y-STNodeSize.y/2.0f, STNodeSize.x, STNodeSize.y};
    for(auto a : arrow){
        a->setPosition(position);
    }
}

Vector2 ShortestPathNode::getForce(){
    return force;
}

void ShortestPathNode::setForce(Vector2 force){
    this->force=force;
}

void ShortestPathNode::addEdge(ShortestPathNode* node) {
    STArrow* a = new STArrow(position,node->getID());
    a->setFrom(id);
    a->setTo(node->getID());
    a->setDestination(node->getPosition());
    arrow.push_back(a);
}

void ShortestPathNode::removeEdge(ShortestPathNode* node) {
    for (auto it = arrow.begin(); it != arrow.end(); ++it) {
        if ((*it)->getTo() == node->getID()) {
            delete *it;  
            arrow.erase(it);  
            break;
        }
    }
}

void ShortestPathNode::clearEdges() {
    adj.clear();
    arrow.clear();
}

void ShortestPathNode::setChosen(){
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(),node)){
            isChosen=true;
    }
    else if(!IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        isChosen=false;
    }
}

bool ShortestPathNode::isCollision(ShortestPathNode* other) {
    Vector2 pos1 = this->getPosition();
    Vector2 pos2 = other->getPosition();
    Vector2 dis = {pos2.x-pos1.x,pos2.y-pos1.y};
    float distance = sqrt(dis.x*dis.x+dis.y*dis.y);
    float radius1 = STNodeSize.x / 2.0f;
    float radius2 = STNodeSize.x / 2.0f;
    return distance < (radius1 + radius2);
}

void ShortestPathNode::applyRepellingForce(ShortestPathNode* other) {
    Vector2 pos1 = this->getPosition();
    Vector2 pos2 = other->getPosition();
    Vector2 dis = {pos2.x - pos1.x, pos2.y - pos1.y};
    float distance=sqrt(dis.x*dis.x+dis.y*dis.y);
    float pushForce=STNodeSize.x-distance;
    if (pushForce>0) {
        Vector2 newPos1, newPos2;
        if(other->getBoundaryCollision()){
            newPos1 = {pos1.x - dis.x/distance*pushForce, pos1.y - dis.y/distance*pushForce};
            this->setPosition(newPos1);
        }
        else if (isChosen) {
            newPos2 = {pos2.x + dis.x/distance*pushForce, pos2.y + dis.y/distance*pushForce};
            other->setPosition(newPos2);
        }
        else {
            newPos1 = {pos1.x - dis.x/distance*pushForce/2.0f, pos1.y - dis.y/distance*pushForce/2.0f};
            newPos2 = {pos2.x + dis.x/distance*pushForce/2.0f, pos2.y + dis.y/distance*pushForce/2.0f};
            this->setPosition(newPos1);
            other->setPosition(newPos2);
        }
    }
}

void ShortestPathNode::boundaryCollision(){
    if((position.x+STNodeSize.x/2.0f>=centerX+rangeX/2.0f||position.x-STNodeSize.x/2.0f<=centerX-rangeX/2.0f)&&(position.y+STNodeSize.y/2.0f>=centerY+rangeY/2.0f||position.y-STNodeSize.y/2.0f<=centerY-rangeY/2.0f)){
        isBoundaryCollision=true;
    }
    else{
        isBoundaryCollision=false;
    }
    if(position.x+STNodeSize.x/2.0f>centerX+rangeX/2.0f){
        setPosition({getPosition().x-(position.x+STNodeSize.x/2.0f-centerX-rangeX/2.0f),getPosition().y});
    }
    if(position.x-STNodeSize.x/2.0f<centerX-rangeX/2.0f){
        setPosition({getPosition().x-(position.x-STNodeSize.x/2.0f-centerX+rangeX/2.0f),getPosition().y});
    }
    if(position.y+STNodeSize.y/2.0f>centerY+rangeY/2.0f){
        setPosition({getPosition().x,getPosition().y-(position.y+STNodeSize.y/2.0f-centerY-rangeY/2.0f)});
    }
    if(position.y-STNodeSize.y/2.0f<centerY-rangeY/2.0f){
        setPosition({getPosition().x,getPosition().y-(position.y-STNodeSize.y/2.0f-centerY+rangeY/2.0f)});
    }
}

bool ShortestPathNode::getBoundaryCollision(){
    return isBoundaryCollision;
}

bool ShortestPathNode::checkMouseHovered() {
    Vector2 mousePos = GetMousePosition();
    Vector2 center = {position.x, position.y};
    float radius = STNodeSize.x / 2.0f;
    float distance = sqrt((mousePos.x - center.x)*(mousePos.x - center.x)+(mousePos.y - center.y)*(mousePos.y - center.y));
    return distance <= radius;
}

void ShortestPathNode::setLine() {
    isLine=true;
}

void ShortestPathNode::deLine() {
    isLine=false;
}

ShortestPathNode* ShortestPathNode::clone() const{
    ShortestPathNode* cloneST= new ShortestPathNode(position);
    for (auto arr : arrow){
        cloneST->arrow.push_back(new STArrow(*arr));
    }
    cloneST->node=this->node;
    cloneST->force=this->force;
    cloneST->id=this->id;
    cloneST->cost=this->cost;
    cloneST->isKnown=this->isKnown;
    cloneST->isHighlight=this->isHighlight;
    return cloneST;  
}

void ShortestPathNode::updateNode() {
    setChosen();
    if(isChosen){
        setPosition(GetMousePosition());
    }
    boundaryCollision();
}

void ShortestPathNode::update(){
    for(auto ar : arrow){
        for(auto node : adj){
            if(ar&&ar->getTo()==node->getID()){
                ar->setDestination(node->getPosition());
                ar->setPosition(position);
            }
        }
    }
    node={position.x-STNodeSize.x/2.0f,position.y-STNodeSize.y/2.0f,STNodeSize.x,STNodeSize.y};
}

void ShortestPathNode::draw(bool isWeighted, bool isDirected) {
    for(auto ar : arrow){
        if(ar)
            ar->draw(isWeighted, isDirected);
    }
}

void ShortestPathNode::drawNode(){
    DrawRectangleRounded(node, 100, 0, (isLine)? lineColor : ((isKnown)? nodeKnownColor : ((isHighlight) ? nodeHighlightColor : nodeColor)));
    if(cost==-1){
        DrawText("INF", position.x+STNodeSize.x/2.0f, position.y-STNodeSize.y/2.0f, STNodeCostFontSize, nodeCostColor);
    }
    else{
        DrawText(std::to_string(cost).c_str(), position.x+STNodeSize.x/2.0f, position.y-STNodeSize.y/2.0f, STNodeCostFontSize, nodeCostColor);
    }
    DrawText(std::to_string(id).c_str(), position.x-MeasureText(std::to_string(id).c_str(),STNodeIDFontSize)/2.0f,position.y-STNodeIDFontSize/2.0f,STNodeIDFontSize, (isLine)? lineTextColor : ((isKnown)? nodeKnownTextColor : ((isHighlight)? nodeHighlightTextColor:nodeTextColor)));
}