#include <SLL/SinglyLinkedList.h>

SinglyLinkedList::SinglyLinkedList() : head(new SLLArrow({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f})), cur(new SLLArrow({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f+ArrowLength})),newNode(nullptr), myNode(nullptr) {
    head->setTargetDestination({head->getPosition().x+ArrowLength,head->getPosition().y});
    head->setPosition({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f});
    head->setLabel("head");
    head->setNull();
    cur->setLabel("cur");
    cur->setNull();
    cur->setDestination({SLLposition.x+ArrowLength,SLLposition.y+SLLNodeSize.y/2.0f+ArrowLength});
}

SinglyLinkedList::~SinglyLinkedList() {
    clearList();
    if(head) delete head;
    if(cur) delete cur;
    if(myNode) delete myNode;
    if(newNode) delete newNode;
}

void SinglyLinkedList::createList(std::string text){
    clearList();
    head->setDestination({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f});
    isCreated=true;
    for (char& c : text) {
        if (c == ';' || c == ' ') {
            c = ',';
        }
    }
    std::string value;
    std::stringstream ss(text);
    int index=0;
    while (std::getline(ss, value, ',')) {
        int val=stoi(value);
        SLLNode* newNode = new SLLNode();
        newNode->setValue(val);
        list.insert(list.begin()+index++,newNode);
        for (int i=0;i<list.size();i++){
            list[i]->setPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
            list[i]->setTargetPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+ArrowLength), SLLposition.y});
        }
    }
    if(list.empty()){
        head->setTargetDestination({head->getPosition().x+ArrowLength,head->getPosition().y});
        head->setNull();
    }
    head->update();
    if (!list.empty()) {
        head->setTargetDestination(list[0]->getStartPos());
        for (int index = 0; index < list.size() - 1; index++) {
            list[index]->setTargetDestination(list[index + 1]->getStartPos());
            list[index]->updateCur();
        }
        list[list.size()-1]->setTargetDestination({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
        list[list.size() - 1]->updateCur();
        list[list.size() - 1]->setNull();
    }
}

void SinglyLinkedList::clear(){
    clearList();
    if(myNode) delete myNode;
    if(newNode) delete newNode;
    myNode = nullptr;
    newNode = nullptr;
    isNewNode=false;
    isCur=false;
    indexStep=-1;
    animationStep = 0;
    isCreated = false;   
}

void SinglyLinkedList::clearList(){
    for (auto node : list) {
        delete node;
        node=nullptr;
    }
    list.clear();
    isCreated=false;
}

void SinglyLinkedList::setArrowDestination(){
    if(list.empty()) {
        head->setDestination({head->getPosition().x+ArrowLength,head->getPosition().y});
        return;
    }
    head->setDestination(list[0]->getStartPos());
    for (int i=0;i<list.size()-1;i++){
        list[i]->setDestination(list[i+1]->getStartPos());
    }
    list[list.size()-1]->setDestination({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
    list[list.size() - 1]->setNull();
}

void SinglyLinkedList::resetHighlight(){
    for (auto node : list){
        node->deHighlight();
    }
}

int SinglyLinkedList::getListSize(){
    return list.size();
}

SinglyLinkedList* SinglyLinkedList::clone() const {
    SinglyLinkedList* cloneSLL = new SinglyLinkedList();
    delete cloneSLL->head;
    delete cloneSLL->cur;  
    cloneSLL->head=nullptr;
    cloneSLL->cur=nullptr;
    for (auto node : this->list) {
        cloneSLL->list.push_back(node->clone()); 
    }
    cloneSLL->head = (head)? new SLLArrow(*this->head) : nullptr;  
    cloneSLL->cur = (cur)? new SLLArrow(*this->cur) : nullptr;    
    cloneSLL->myNode = (myNode)? new SLLArrow(*this->myNode) : nullptr;
    cloneSLL->newNode = (newNode)? newNode->clone() : nullptr;
    cloneSLL->isNewNode=this->isNewNode;
    cloneSLL->isCur=this->isCur;
    cloneSLL->indexStep=this->indexStep;
    cloneSLL->animationStep=this->animationStep;
    cloneSLL->isCreated=this->isCreated;
    cloneSLL->checkNewNodeinList=this->checkNewNodeinList;
    return cloneSLL;
}

void SinglyLinkedList::update(){
    if(isCur)
        cur->update();
    if(isNewNode){
        if(myNode){
            myNode->update();
            myNode->setDestination(newNode->getStartPos());
        }
        if(newNode&&!checkNewNodeinList){
            newNode->updateCur();
        }
    }
    if(list.empty()){
        head->setTargetDestination({head->getPosition().x+ArrowLength,head->getPosition().y});
        head->setNull();
    }
    else if (!list.empty()) {
        head->setTargetDestination({list[0]->getStartPos()});
        for (int index = 0; index < list.size() - 1; index++) {
            list[index]->setTargetDestination(list[index + 1]->getStartPos());
            list[index]->updateCur();
        }
        list[list.size()-1]->setTargetDestination({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
        list[list.size() - 1]->updateCur();
        list[list.size() - 1]->setNull();
    }
    head->update();
}

void SinglyLinkedList::draw(){
    if(isNewNode){
        if(myNode)
            myNode->draw();
        if(newNode)
            newNode->drawCur();
    }
    if(isCur)
        cur->draw();
    if(isCreated)
        head->draw();
    for (auto node : list) {
        if (!node) continue;
        node->drawCur();
    }
}