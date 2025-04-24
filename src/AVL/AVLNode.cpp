#include <AVL/AVLNode.h>

AVLNode::AVLNode() : parent(nullptr), left(nullptr), right(nullptr), leftPointer(nullptr), rightPointer(nullptr) {
    height=0;
    depth=0;
    isHighlight=false;
}

AVLNode::~AVLNode(){
    if(leftPointer) delete leftPointer;
    leftPointer=nullptr;
    if(rightPointer) delete rightPointer;
    rightPointer=nullptr;
}

void AVLNode::setValue(int value){
    this->value=value;
}

void AVLNode::setPosition(Vector2 position){
    this->position=position;
    this->targetPosition=position;
    this->node = {position.x-AVLNodeSize.x/2.0f,position.y-AVLNodeSize.y/2.0f, AVLNodeSize.x, AVLNodeSize.y};
    if(leftPointer) delete leftPointer;
    leftPointer = new AVLArrow(position);
    if(rightPointer) delete rightPointer;
    rightPointer = new AVLArrow(position);
}

void AVLNode::setTargetPosition(Vector2 targetPos){
    this->targetPosition=targetPos;
}

void AVLNode::setHeight(int value){
    height=value;
}

void AVLNode::setDepth(int value){
    depth=value;
}

void AVLNode::setHighlight(){
    isHighlight=true;
}

void AVLNode::deHighlight(){
    isHighlight=false;
}

Vector2 AVLNode::getOrigin(){
    return position;
}

Vector2 AVLNode::getTargetPosition(){
    return targetPosition;
}

int AVLNode::getValue(){
    return value;
}

int AVLNode::getDepth(){
    return depth;
}

int AVLNode::getHeight(){
    return height;
}

bool AVLNode::isLeaf(){
    return (!left&&!right);
}

void AVLNode::updateHeight(){
    if(!left&&!right) height=1;
    else if(!left) height=1+right->getHeight();
    else if(!right) height=1+left->getHeight();
    else height=1+std::max(left->getHeight(),right->getHeight());
}

void AVLNode::updateNode(){
    if (position.x == targetPosition.x&&position.y == targetPosition.y) return;
    float deltaTime=GetFrameTime();
    float disX=targetPosition.x-position.x, disY=targetPosition.y-position.y;
    float dis=sqrt(disX*disX+disY*disY);
    float deltaX=disX/dis*speed*deltaTime;
    float deltaY=disY/dis*speed*deltaTime;
    if(fabs(deltaX)>=fabs(disX)&&fabs(deltaY)>=fabs(disY)){
        position=targetPosition;
    }
    else{
        position.x+=deltaX;
        position.y+=deltaY;
    }
}

void AVLNode::updateCur(){
    updateNode();
    leftPointer->setPosition(this->position);
    rightPointer->setPosition(this->position);
    if(!left) leftPointer->setDestination(this->position);
    if(!right) rightPointer->setDestination(this->position);
    node={position.x-AVLNodeSize.x/2.0f,position.y-AVLNodeSize.y/2.0f, AVLNodeSize.x, AVLNodeSize.y};
    if(left&&leftPointer){
        leftPointer->setTargetDestination(left->getOrigin());
        leftPointer->update();
    }
    if(right&&rightPointer){
        rightPointer->setTargetDestination(right->getOrigin());
        rightPointer->update();
    }
}

void AVLNode::drawCur(){
    if(left&&leftPointer){
        leftPointer->draw();
    }
    if(right&&rightPointer){
        rightPointer->draw();
    }
    DrawRectangleRounded(node,100,0,(isHighlight)? nodeHighlightColor : nodeColor);
    DrawText(std::to_string(this->value).c_str(),position.x-MeasureText(std::to_string(this->value).c_str(),AVLNodeFontSize)/2.0f,position.y-AVLNodeFontSize/2.0f,AVLNodeFontSize,(isHighlight)? nodeHighlightTextColor:nodeTextColor);
}

void AVLNode::setDestinationLeft(Vector2 targetDes){
    if(leftPointer){
        leftPointer->setDestination(targetDes);
    }
}

void AVLNode::setDestinationRight(Vector2 targetDes){
    if(rightPointer){
        rightPointer->setDestination(targetDes);
    }
}

void AVLNode::setTargetDestinationLeft(Vector2 targetDes){
    if(leftPointer){
        leftPointer->setTargetDestination(targetDes);
    }
}

void AVLNode::setTargetDestinationRight(Vector2 targetDes){
    if(rightPointer){
        rightPointer->setTargetDestination(targetDes);
    }
}

Vector2 AVLNode::getDestinationLeft(){
    return leftPointer->getDestination();
}

Vector2 AVLNode::getDestinationRight(){
    return rightPointer->getDestination();
}

AVLNode* AVLNode::clone() const{
    AVLNode* newNode = new AVLNode();
    newNode->node=this->node;

    newNode->isHighlight = this->isHighlight;
    newNode->leftPointer = (this->leftPointer)? new AVLArrow(*this->leftPointer):nullptr;
    newNode->rightPointer = (this->rightPointer)? new AVLArrow(*this->rightPointer):nullptr;
    
    newNode->position = this->position;
    newNode->targetPosition = this->targetPosition;
    newNode->value = this->value;
    newNode->height=this->height;
    newNode->depth=this->depth;
    newNode->leftNumNodes=this->leftNumNodes;
    newNode->rightNumNodes=this->rightNumNodes;
    return newNode;
}

int AVLNode::getLeftNumNodes(){
    return leftNumNodes;
}

int AVLNode::getRightNumNodes(){
    return rightNumNodes;
}

void AVLNode::setLeftNumNodes(int value){
    leftNumNodes=value;
}

void AVLNode::setRightNumNodes(int value){
    rightNumNodes=value;
}

int AVLNode::getTotalNumNodes(){
    return leftNumNodes+rightNumNodes+1;
}