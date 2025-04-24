#include <ShortestPath/ShortestPath.h>

ShortestPath::ShortestPath() : current(nullptr) {
    isWeighted = false;
    isDirected = false;
    k = 0.0f;
    cool=1.5f;
    deltaTime=0.0f;
}

ShortestPath::~ShortestPath() {
   clear();
}

void ShortestPath::createGraph(int numNodes, int edges){
    clear();
    k = sqrt((rangeX * rangeY) / numNodes);
    for(int i = 0; i < numNodes; i++){
        float posX = centerX + (rand() % (int)rangeX - rangeX / 2);
        float posY = centerY + (rand() % (int)rangeY - rangeY / 2);
        ShortestPathNode* n = new ShortestPathNode({posX,posY});
        n->setID(i);
        graph.push_back(n);
    }
    for(int i=0;i<edges;){
        int from = rand() % numNodes;
        int to = rand() % numNodes;
        if (from != to) {
            bool exists = false;
            for (const auto &e : graph[from]->arrow) {
                if (e->getTo() == to) {
                    exists = true;
                    break;
                }
            }
            for (const auto &e : graph[to]->arrow) {
                if (e->getTo() == from) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                graph[from]->adj.push_back(graph[to]);
                STArrow* edge=new STArrow(graph[from]->getPosition(), to);
                edge->setFrom(from);
                edge->setWeight(rand()%100+1);
                graph[from]->arrow.push_back(edge);
                allArrows.push_back(edge);
                i++;
            }
        }
    }
}

void ShortestPath::createGraph(std::string input) {
    clear();
    std::stringstream ss(input);
    int numNodes, edges;
    ss >> numNodes >> edges;
    k = sqrt((rangeX * rangeY) / numNodes);
    for (int i = 0; i < numNodes; i++) {
        float posX = centerX + (rand() % (int)rangeX - rangeX / 2);
        float posY = centerY + (rand() % (int)rangeY - rangeY / 2);
        ShortestPathNode* n = new ShortestPathNode({posX, posY});
        n->setID(i);
        graph.push_back(n);
    }
    int from, to, weight;
    while (ss >> from >> to >> weight) {
        if (from != to) {
            bool exists = false;
            for (const auto& e : graph[from]->arrow) {
                if (e->getTo() == to) {
                    exists = true;
                    break;
                }
            }
            for (const auto& e : graph[to]->arrow) {
                if (e->getTo() == from) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                graph[from]->adj.push_back(graph[to]);
                STArrow* edge = new STArrow(graph[from]->getPosition(), to);
                edge->setFrom(from);
                edge->setWeight(weight); 
                graph[from]->arrow.push_back(edge);
                allArrows.push_back(edge);
            }
        }
    }
}

void ShortestPath::addEdge(int node1, int node2){
    if(node1 < graph.size() && node2 < graph.size()){
        graph[node1]->addEdge(graph[node2]);
        if(!isDirected){
            graph[node2]->addEdge(graph[node1]);
        }
    }
}

void ShortestPath::removeEdge(int node1, int node2){
    if(node1 < graph.size() && node2 < graph.size()){
        graph[node1]->removeEdge(graph[node2]);
        if(!isDirected){
            graph[node2]->removeEdge(graph[node1]);
        }
    }
}

void ShortestPath::clear(){
    clearGraph();
    current=nullptr;
    animationStep = 0;
    findSmall = -1;  
    minCost = INT_MAX;
    index=0;
    isWeighted = false;
    isDirected = false;
    k = 0.0f;
    cool=1.5f;
    deltaTime=0.0f;
}

void ShortestPath::clearGraph(){
    for (auto arrow : allArrows) {
        delete arrow;
    }
    allArrows.clear();
    for (auto node : graph) {
        if (node) {
            node->clearEdges();
            delete node;
        }
    }
    graph.clear();
}

void ShortestPath::resetGraph(){
    for(auto n : graph){
        n->deHighlight();
        n->deKnown();
        n->setCost(-1);
    }
}

void ShortestPath::setWeighted(){
    isWeighted = true;
}

void ShortestPath::deWeighted(){
    isWeighted = false;
}

void ShortestPath::setDirected(){
    isDirected = true;
}

void ShortestPath::deDirected(){
    isDirected = false;
}

ShortestPath* ShortestPath::clone() const {
    ShortestPath* cloneST = new ShortestPath();
    for (auto node : graph) {
        ShortestPathNode* newNode = node->clone();
        cloneST->graph.push_back(newNode);
        if (this->current == node) {
            cloneST->current = newNode;
        }
    }
    for (auto node : graph) {
        for(auto prevNode : graph){
            if(node->prev == prevNode){
                cloneST->graph[node->getID()]->prev = cloneST->graph[prevNode->getID()];
                break;
            }
        }
    }
    for (auto from : this->allArrows){
        for (auto arr : cloneST->graph[from->getFrom()]->arrow){
            if(arr->getTo()==from->getTo()){
                cloneST->allArrows.push_back(arr);
                break;
            }
        }
    }
    for (int i=0;i<cloneST->graph.size();i++){
        for (auto adj : this->graph[i]->adj){
            cloneST->graph[i]->adj.push_back(cloneST->graph[adj->getID()]);
        }
    }
    cloneST->k = this->k;
    cloneST->isWeighted = this->isWeighted;
    cloneST->isDirected = this->isDirected;
    cloneST->cool = this->cool;
    cloneST->deltaTime = this->deltaTime;
    cloneST->animationStep = this->animationStep;
    cloneST->findSmall = this->findSmall;
    cloneST->minCost = this->minCost;
    cloneST->index=this->index;
    return cloneST;
}

void ShortestPath::update(){
    for(auto n : graph){
        if(n)
            n->updateNode();
    }
    for (int i=0;i<graph.size();i++){
        for (int j=0;j<graph.size();j++){
            if (i != j && graph[i]->isCollision(graph[j])) {
                graph[i]->applyRepellingForce(graph[j]);
            }
        }
    }
    for (auto n: graph){
        if(n)   
            n->update();
    }
}

void ShortestPath::draw(){
    for(auto n : graph){
        if(n)
            n->draw(isWeighted, isDirected);
    }
    for (auto n: graph){
        if(n)
            n->drawNode();
    }
}

Vector2 ShortestPath::ComputeRepulsiveForce(ShortestPathNode* &v, ShortestPathNode* &u) {
    Vector2 posU = u->getPosition(), posV = v->getPosition();
    Vector2 delta = { posV.x - posU.x, posV.y - posU.y };
    float distance = sqrt(delta.x * delta.x + delta.y * delta.y) + 0.01f;
    float force = (k * k) / distance;
    return {(float)(delta.x / distance) * force, (float)(delta.y / distance) * force};
}

Vector2 ShortestPath::ComputeAttractiveForce(ShortestPathNode* &v, ShortestPathNode* &u) {
    Vector2 posU = u->getPosition(), posV = v->getPosition();
    Vector2 delta = { posV.x - posU.x, posV.y - posU.y };  
    float distance = sqrt(delta.x * delta.x + delta.y * delta.y) + 0.01f;
    float force = (distance * distance) / k;
    return {(float)(delta.x / distance) * force, (float)(delta.y / distance) * force};
}

void ShortestPath::updateLine(){
    ShortestPathNode* cur=nullptr;
    for (auto n : graph){
        if(n->checkMouseHovered()){
            cur=n;
            n->setLine();
            if(cur->getCost()==0) return;
            break;
        }
    }
    if(!cur||!cur->prev){
        for (auto n : graph){
            n->deLine();
        }
        for (auto arr : allArrows){
            arr->deLine();
        }
        return;
    }
    while(cur&&cur->prev){
        cur->prev->setLine();
        for (auto arr : cur->arrow){
            if(arr->getTo()==cur->prev->getID()){
                arr->setLine();
                break;
            }
        }
        for (auto arr : cur->prev->arrow){
            if(arr->getTo()==cur->getID()){
                arr->setLine();
                break;
            }
        }
        cur=cur->prev;
    }
}