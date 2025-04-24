#include "HashTable/animation/Presentation.h"

Presentation::Presentation(float &speed, HashTable& table, std::vector<std::vector<HashTable>> &historyState, int &currentPresentationIndex, int&currentStateIndex)
    : speed(speed), table(table), historyState(historyState), currentStep(0), currentPresentationIndex(currentPresentationIndex), currentStateIndex(currentStateIndex){}

void Presentation::InsertNodeAnimation(int key, Node* newNode) {
    
    int bucket = key % table.GetSize();
    
    // Duyệt qua các node trong bucket để tạo animation tuần tự
    Node* current = table.getTable(bucket);
    Node* prev = nullptr;

    // Bước 1: Highlight lần lượt từng node trong bucket
    while (current != newNode && current != nullptr) {
        SetofAnimation set(speed);
        Animation highlight(speed, current);
        highlight.type = 1;
        set.AddAnimation(highlight);
        SetAnimations.push_back(set); // Thêm set để thực thi tuần tự
        

        SetofAnimation settemp(speed);
        Animation normal(speed, current);
        normal.type = 5;
        settemp.AddAnimation(normal);
        SetAnimations.push_back(settemp);

        prev = current;
        current = current->next;
    }

    // Bước 2: Fade in node mới (node 40)
    // Không cần đặt current->isVisual = true ở đây
    SetofAnimation fadeInSet(speed);
    Animation fadeIn(speed, newNode);
    fadeIn.type = 2; // Fade in
    fadeInSet.AddAnimation(fadeIn);
    SetAnimations.push_back(fadeInSet);

    // Bước 3: Vẽ mũi tên từ node trước đó (node 30) đến node mới (node 40)
    if (prev) {
        SetofAnimation edgeSet(speed);
        Animation edge(speed, prev);
        edge.type = 6; // Vẽ mũi tên
        edgeSet.AddAnimation(edge);
        SetAnimations.push_back(edgeSet);
    }
}

void Presentation::DeleteNodeAnimation(int key) {
    int bucket = key % table.GetSize();
    Node* current = table.getTable(bucket);
    Node* prev = nullptr;
    Node* nodeToDelete = nullptr;

    while (current != nullptr) {
        SetofAnimation highlightNode(speed);
        Animation highlight(speed, current);
        highlight.type = 1;
        highlightNode.AddAnimation(highlight);
        SetAnimations.push_back(highlightNode);

        SetofAnimation normalNode(speed);
        Animation normal(speed, current);
        normal.type = 5;
        normalNode.AddAnimation(normal);
        SetAnimations.push_back(normalNode);


        if (current->data == key) {
            nodeToDelete = current;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!nodeToDelete) return;

    if (prev && nodeToDelete->next) {
        SetofAnimation edgeSet(speed);
        Animation edge(speed, prev);
        edge.type = 7;
        edgeSet.AddAnimation(edge);
        SetAnimations.push_back(edgeSet);
    }

    SetofAnimation fadeOutSet(speed);
    Animation fadeOut(speed, nodeToDelete);
    fadeOut.type = 3;
    fadeOutSet.AddAnimation(fadeOut);
    SetAnimations.push_back(fadeOutSet);

    Node* nodeAfterDeleted = nodeToDelete->next;
    if (nodeAfterDeleted) {
        SetofAnimation moveSet(speed);
        while (nodeAfterDeleted != nullptr) {
            Vector2 newPosition = {nodeAfterDeleted->position.x, nodeAfterDeleted->position.y - 50};
            nodeAfterDeleted->finalPosition = newPosition;
            
            Animation moveNode(speed, nodeAfterDeleted, newPosition); // Truyền target
            moveNode.type = 4;
            moveSet.AddAnimation(moveNode);
            nodeAfterDeleted = nodeAfterDeleted->next;
        }
        SetAnimations.push_back(moveSet);
    }
}

void Presentation::FindNodeAnimation(int key) {
    int bucket = key % table.GetSize();
    Node* current = table.getTable(bucket);

    while (current != nullptr) {
        SetofAnimation set(speed);
        Animation highlight(speed, current);
        highlight.type = 1;
        set.AddAnimation(highlight);
        SetAnimations.push_back(set);

        SetofAnimation normalNode(speed);
        Animation normal(speed, current);
        normal.type = 5;
        normalNode.AddAnimation(normal);
        SetAnimations.push_back(normalNode);

        if (current->data == key) break;
        current = current->next;
    }
}

void Presentation::CreateTableAnimation(int size) {
    if(size < 0) return;
    SetofAnimation fadeInNode(speed);
    SetofAnimation drawEdge(speed);
    for (int i = 0; i < size; i++) {
        Node* current = table.getTable(i);
        while (current != nullptr) {
            Animation fadein(speed, current);
            Animation drawedge(speed, current);

            fadein.type = 2;
            drawedge.type = 6;

            fadeInNode.AddAnimation(fadein);
            drawEdge.AddAnimation(drawedge);

            current = current->next;
        }
    }
    SetAnimations.push_back(fadeInNode);
    SetAnimations.push_back(drawEdge);
}

// void Presentation::UpdateAnimation(int initValue, int finalValue, Node*newNode){
//     if(!table.Find(initValue)){
//         return;
//     }
//     DeleteNodeAnimation(initValue);
//     InsertNodeAnimation(finalValue, newNode);
//     return;
// }

bool Presentation::DrawPresentation() {
    if (SetAnimations.empty() || currentStep >= SetAnimations.size()) return true;

    if (SetAnimations[currentStep].Draw()) {
        
        HashTable tempHash(table);
        if(currentStep == 0){
            currentPresentationIndex++;
            std::vector<HashTable> temp = {};
            temp.push_back(tempHash);
            historyState.push_back(temp);
            currentStateIndex = historyState.back().size() - 1;
            
            
        }
        else{
            historyState.back().push_back(tempHash);
            currentStateIndex = historyState.back().size() - 1;
        }

        currentStep++;
    }
    return currentStep >= SetAnimations.size();
}



void Presentation::clear() {
    SetAnimations.clear();
    //historyOfSets.clear();
    currentStep = 0;
}

