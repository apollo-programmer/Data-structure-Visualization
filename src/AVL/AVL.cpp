#include <AVL/AVL.h>

AVL::AVL() : root(nullptr), curNode(nullptr), temp(nullptr), animationStep(0) {}

AVL::~AVL(){
    clearTree();
    if(curNode) delete curNode;
    curNode=nullptr;
}

void AVL::createTree(std::string text){
    clearTree();
    if(text.empty()) return;
    for (char& c : text) {
        if (c == ';' || c == ' ') {
            c = ',';
        }
    }
    std::string value;
    std::stringstream ss(text);
    while(std::getline(ss,value,',')){
        insertNode(std::stoi(value));
    }
    curNode=root;
    setCreatePosition();
    setTargetPosition();
}

void AVL::insertNode(int value){
    if(!root){
        root = new AVLNode(); 
        root->setValue(value);
        calculateHeight();
        return;
    }
    AVLNode* cur = root;
    while(true){
        if(value<cur->getValue()){
            if(!cur->left){
                cur->left = new AVLNode();
                cur->left->setValue(value);
                cur->left->parent = cur;
                break;
            }
            cur = cur->left;
        }
        else{
            if(!cur->right){
                cur->right = new AVLNode();
                cur->right->setValue(value);
                cur->right->parent = cur;
                break;
            }
            cur = cur->right;
        }
    }
    calculateHeight();
    balanceTree();
}

void AVL::balanceTree(){
    balanceTree(root);
}

void AVL::balanceTree(AVLNode*& root){
    if(!root) return;
    balanceTree(root->left);
    balanceTree(root->right);
    int balanceFactor=getBalanceFactor(root);
    if(abs(balanceFactor)>1){
        if(balanceFactor>1){
            if(getBalanceFactor(root->left)<0) rotateLeftRight(root);
            else rotateRight(root);
        }
        else if(balanceFactor<-1){
            if(getBalanceFactor(root->right)>0) rotateRightLeft(root);
            else rotateLeft(root);
        }
    }
}

int AVL::getBalanceFactor(AVLNode* root){
    int balanceFactor=0;
    if(root->left) balanceFactor+=root->left->getHeight();
    if(root->right) balanceFactor-=root->right->getHeight();
    return balanceFactor;
}

void AVL::rotateRight(AVLNode*& root) {  
    if (!root || !root->left) return; 
    AVLNode* newRoot = root->left;
    root->left = newRoot->right;
    if (newRoot->right) newRoot->right->parent = root;
    newRoot->right = root;
    newRoot->parent = root->parent;
    root->parent = newRoot;

    if (!newRoot->parent) this->root = newRoot;  
    else if (newRoot->parent->left == root) newRoot->parent->left = newRoot;
    else newRoot->parent->right = newRoot;


    calculateHeight();
}

void AVL::rotateLeft(AVLNode*& root){
    if (!root || !root->right) return; 
    AVLNode* newRoot = root->right;
    root->right = newRoot->left;
    if(newRoot->left)newRoot->left->parent=root;
    newRoot->left=root;
    newRoot->parent=root->parent;
    root->parent=newRoot;

    if(!newRoot->parent) this->root=newRoot;
    else if(newRoot->parent->right == root) newRoot->parent->right=newRoot;
    else newRoot->parent->left=newRoot;
    
    calculateHeight();
}

void AVL::rotateRightLeft(AVLNode*& root){
    rotateRight(root->right);
    rotateLeft(root);
}

void AVL::rotateLeftRight(AVLNode*& root){
    rotateLeft(root->left);
    rotateRight(root);
}

void AVL::clear(){
    clearTree();
    curNode=nullptr;
    temp=nullptr;
    animationStep = 0;
}

void AVL::clearTree(){
    clearTree(root);
    root=nullptr;
}

void AVL::clearTree(AVLNode*& root) {
    if (root == nullptr) {
        return;
    }
    clearTree(root->left);
    clearTree(root->right);
    delete root;
    root = nullptr; 
}

void AVL::calculateHeight(){
    calculateHeight(this->root);
}

void AVL::calculateHeight(AVLNode* root){
    if(!root) return;
    calculateHeight(root->left);
    calculateHeight(root->right);
    if(!root->left && !root->right) {
        root->setHeight(1);
        root->setLeftNumNodes(0);
        root->setRightNumNodes(0);
    }
    else if(!root->left) {
        root->setHeight(1+root->right->getHeight());
        root->setLeftNumNodes(0);
        root->setRightNumNodes(root->right->getLeftNumNodes()+root->right->getRightNumNodes()+1);
    }
    else if(!root->right) {
        root->setHeight(1+root->left->getHeight());
        root->setLeftNumNodes(root->left->getLeftNumNodes()+root->left->getRightNumNodes()+1);
        root->setRightNumNodes(0);
    }
    else {
        root->setHeight(1+std::max(root->left->getHeight(), root->right->getHeight()));
        root->setLeftNumNodes(root->left->getLeftNumNodes()+root->left->getRightNumNodes()+1);
        root->setRightNumNodes(root->right->getLeftNumNodes()+root->right->getRightNumNodes()+1);
    }
}

void AVL::setCreatePosition(){
    root->setPosition({(float)GetScreenWidth()/2,AVLPosition.y});
    setCreatePosition(root);
}

void AVL::setCreatePosition(AVLNode* root){
    if(!root) return;
    if(root->left){
        root->left->setPosition({(float)GetScreenWidth()/2,AVLPosition.y});
    }
    if(root->right){
        root->right->setPosition({(float)GetScreenWidth()/2,AVLPosition.y});
    }
    setCreatePosition(root->left);
    setCreatePosition(root->right);
}

void AVL::setPosition(){
    root->setPosition({(float)GetScreenWidth()/2,AVLPosition.y});
    setPosition(root);
}

void AVL::setPosition(AVLNode* root){
    if(!root) return;
    if(root->left){
        root->left->setPosition({(float)(root->getTargetPosition().x-((1+((root->left->right)? root->left->right->getTotalNumNodes() : 0))*(AVLLeafSpace+AVLNodeSize.x)/2.0f)),root->getTargetPosition().y+AVLLevelSpace});
    }
    if(root->right){
        root->right->setPosition({(float)(root->getTargetPosition().x+((1+((root->right->left)? root->right->left->getTotalNumNodes() : 0))*(AVLLeafSpace+AVLNodeSize.x)/2.0f)),root->getTargetPosition().y+AVLLevelSpace});
    }
    setPosition(root->left);
    setPosition(root->right);
}

void AVL::setTargetPosition(){
    root->setTargetPosition({(float)GetScreenWidth()/2,AVLPosition.y});
    setTargetPosition(root);
}

void AVL::setTargetPosition(AVLNode* root){
    if(!root) return;
    if(root->left){
        root->left->setTargetPosition({(float)(root->getTargetPosition().x-((1+((root->left->right)? root->left->right->getTotalNumNodes() : 0))*(AVLLeafSpace+AVLNodeSize.x)/2.0f)),root->getTargetPosition().y+AVLLevelSpace});
    }
    if(root->right){
        root->right->setTargetPosition({(float)(root->getTargetPosition().x+((1+((root->right->left)? root->right->left->getTotalNumNodes() : 0))*(AVLLeafSpace+AVLNodeSize.x)/2.0f)),root->getTargetPosition().y+AVLLevelSpace});
    }
    setTargetPosition(root->left);
    setTargetPosition(root->right);
}

void AVL::resetHighlight(){
    resetHighlight(root);
}

void AVL::resetHighlight(AVLNode* root){
    if(!root) return;
    root->deHighlight();
    resetHighlight(root->left);
    resetHighlight(root->right);
}

void AVL::setArrowDestination(){
    setArrowDestination(root);
}

void AVL::setArrowDestination(AVLNode* root){
    if(!root) return;
    if(root->left) root->setDestinationLeft(root->left->getOrigin());
    if(root->right) root->setDestinationRight(root->right->getOrigin());
    setArrowDestination(root->left);
    setArrowDestination(root->right);
}

bool AVL::checkPosition(){
    return checkPosition(root);
}

bool AVL::checkPosition(AVLNode* root){
    if(!root) return true;
    return (root->getOrigin().x==root->getTargetPosition().x&&root->getOrigin().y==root->getTargetPosition().y&&checkPosition(root->left)&&checkPosition(root->right));
}

bool AVL::checkArrowDestination(){
    return checkArrowDestination(root);
}

bool AVL::checkArrowDestination(AVLNode* root){
    if(!root) return true;
    if(!root->left&&!root->right) return true;
    if(!root->left){
        return (root->getDestinationRight().x==root->right->getOrigin().x&&root->getDestinationRight().y==root->right->getOrigin().y&&checkArrowDestination(root->right));
    }
    if(!root->right){
        return (root->getDestinationLeft().x==root->left->getOrigin().x&&root->getDestinationLeft().y==root->left->getOrigin().y&&checkArrowDestination(root->left));
    }
    return (root->getDestinationLeft().x==root->left->getOrigin().x&&root->getDestinationLeft().y==root->left->getOrigin().y&&root->getDestinationRight().x==root->right->getOrigin().x&&root->getDestinationRight().y==root->right->getOrigin().y&&checkArrowDestination(root->left)&&checkArrowDestination(root->right));
}

AVL* AVL::clone() const{
    AVL* cloneAVL = new AVL();
    cloneAVL->root = clone(this->root,curNode,cloneAVL->curNode);
    if(curNode==root){
        cloneAVL->curNode=cloneAVL->root;
    }
    cloneAVL->animationStep=this->animationStep;
    return cloneAVL;
}

AVLNode* AVL::clone(AVLNode* root, AVLNode* curNode, AVLNode* &cloneCurNode) const{
    if(!root) return nullptr;
    AVLNode* cloneAVL = root->clone();
    cloneAVL->left = clone(root->left,curNode,cloneCurNode);
    if(curNode==root->left){
        cloneCurNode=cloneAVL->left;
    }
    if(cloneAVL->left){
        cloneAVL->left->parent=cloneAVL;
    }
    cloneAVL->right = clone(root->right,curNode,cloneCurNode);
    if(curNode==root->right){
        cloneCurNode=cloneAVL->right;
    }
    if(cloneAVL->right){
        cloneAVL->right->parent=cloneAVL;
    }
    return cloneAVL;
}

void AVL::update(){
    update(root);
}

void AVL::update(AVLNode* root){
    if(!root) return;
    root->updateCur();
    update(root->left);
    update(root->right);
}

void AVL::draw(){
    draw(root);
}

void AVL::draw(AVLNode* root){
    if(!root) return;
    root->drawCur();
    draw(root->left);
    draw(root->right);
}