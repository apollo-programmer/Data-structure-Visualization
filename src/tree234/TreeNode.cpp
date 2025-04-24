#include <234tree/TreeNode.h>
#include <iostream> // Thêm để debug

TreeNode::TreeNode(std::vector<int> keys, std::vector<TreeNode*> children, Vector2 position) 
    : keys(keys), children(children), position(position), colorChosen(nodeHighlightColor),
    colorNormal(nodeColor), textNorColor(nodeTextColor), textChosenColor(nodeHighlightTextColor) {
    this->isLeaf = true;
    this->isEmpty = false;
    this->isChosen = false;
    finalPosition = position;
    parent = nullptr;
    size = {3 * 50.0f, 50.0f}; // Chiều cao cố định
    isLeaf = children.empty();
    arrowPos.resize(4, {position.x + size.x / 2, position.y + size.y / 2});
    // colorChosen = nodeColor;
    // colorNormal = nodeHighlightColor;
    currentColor = nodeColor;
    // textNorColor = nodeTextColor;
    // textChosenColor = nodeHighlightTextColor;
    textCurColor = textNorColor;
    fontNumber = buttonFont;
}

TreeNode::TreeNode(TreeNode* node) : parent(nullptr), width(0), currentColor(node->currentColor), textCurColor(node->textCurColor),
colorNormal(node->colorNormal), colorChosen(node->colorChosen), textChosenColor(node->textChosenColor), textNorColor(node->textNorColor) {
    if (!node) {
        keys = {};
        children = {};
        isLeaf = true;
        isChosen = false;
        position = {0, 0};
        finalPosition = {0, 0};
        arrowPos = {};
        size = {100, 50};
        
        colorChosen = nodeHighlightColor;
        colorNormal = nodeColor;
        currentColor = colorNormal;

        textNorColor = nodeTextColor;
        textChosenColor = nodeHighlightTextColor;
        textCurColor = textNorColor;
        fontNumber = buttonFont;
        CalculateWidth();
        return;
    }

    // Sao chép thuộc tính của node
    keys = node->keys;
    isLeaf = node->isLeaf;
    isChosen = node->isChosen;
    position = node->position;
    finalPosition = node->finalPosition;
    arrowPos = node->arrowPos;
    size = node->size;
    currentColor = node->currentColor;
    colorChosen = node->colorChosen;
    colorNormal = node->colorNormal;
    
    textCurColor = node->textCurColor;
    textNorColor = node->textNorColor;
    textChosenColor = node->textCurColor;
    //CalculateWidth();

    // Sao chép đệ quy các node con
    if(node->children.empty()){
        children = {};
        this->isLeaf = true;
        return;
    }
    children.resize(node->children.size(), nullptr);
    for (size_t i = 0; i < node->children.size(); i++) {
        if (node->children[i]) {
            children[i] = new TreeNode(node->children[i]);
            children[i]->parent = this;
        }
    }
    this->isLeaf = false;
}
// TreeNode::~TreeNode() {
//     deleteTree(this);
// }

void TreeNode::deleteTree(TreeNode * node){
    if(node == nullptr) return;
    for(int i = 0; i < node->children.size(); i++){
        deleteTree(node->children[i]);
    }
    delete node;
}

void TreeNode::DrawNode() {
    float size_x = 50.0f * keys.size();
    float size_y = 50.0f;
    if(!isChosen){
        currentColor = nodeColor;
        textCurColor = nodeTextColor;
    }
    else{
        currentColor = nodeHighlightColor;
        textCurColor = nodeHighlightTextColor;
    }
    
    DrawRectangle(position.x, position.y, size_x, size_y, currentColor);

    float keyWidth = size_x / (keys.size() > 0 ? keys.size() : 1); // Chia đều chiều rộng cho số keys
    for (int i = 0; i < keys.size(); i++) {
        DrawRectangleLines(position.x + i * keyWidth, position.y, keyWidth, size_y, lineColor);

        char buffer[5]; // Buffer để chứa chuỗi 4 chữ số + ký tự null
        snprintf(buffer, sizeof(buffer), "%04d", keys[i]); // Định dạng số với 4 chữ số, thêm 0 vào bên trái
        std::string keyStr = buffer;

        int textWidth = MeasureText(keyStr.c_str(), 20); // Đo chiều rộng của text
        int textHeight = 20; // Chiều cao của text
        DrawText(
            keyStr.c_str(),
            position.x + i * keyWidth + (keyWidth - textWidth) / 2, // Căn giữa theo chiều ngang
            position.y + (size.y - textHeight) / 2, // Căn giữa theo chiều dọc
            20, // Kích thước font
            textCurColor // Màu chữ
        );
        
    }
}

void TreeNode::DrawArrow(Vector2 start, Vector2 end) {
    DrawLineEx(start, end, 2, BLACK);
    Vector2 diff = Vector2Subtract(end, start);
    float length = Vector2Length(diff);
    if (length < 0.001f) return;
    Vector2 dir = Vector2Normalize(diff);
    float arrowSize = 10.0f;
    Vector2 tip = end;
    Vector2 baseLeft = Vector2Add(end, Vector2Scale(Vector2Rotate(dir, 150.0f), arrowSize));
    Vector2 baseRight = Vector2Add(end, Vector2Scale(Vector2Rotate(dir, 210.0f), arrowSize));
    DrawTriangle(tip, baseLeft, baseRight, BLACK);
}

void TreeNode::DrawLinktoChild() {

    Vector2 parentPos = {position.x + 25.0f * keys.size(), position.y + size.y / 2};
    for (int i = 0; i < children.size(); i++) {
        if (children[i]) {
            Vector2 childPos = {children[i]->position.x + 25.0f * children[i]->keys.size(), children[i]->position.y + children[i]->size.y / 2};
            DrawArrow(parentPos, childPos);
        }
    }
}

void TreeNode::CalculateWidth(){
    if(isLeaf){
        width = size.x;
        return;
    }
    
    float totalWidth = 0;
    for(int i = 0; i < children.size(); i++){
        children[i]->CalculateWidth();
        totalWidth += children[i]->width + 20;
    }
    totalWidth -= 20;
    width = totalWidth > size.x ? totalWidth : size.x;
    return;
}

void TreeNode::assignCoordinates(float x, float y){
    if(this == nullptr) return;
    
    this->finalPosition = {x + this->width /2 , y};

    if(!this->children.empty()){
        float currentX = x;
        for(int i = 0; i < this->children.size(); i++){
            this->children[i]->assignCoordinates(currentX, y + size.y + 100);
            currentX += this->children[i]->width + 20;
        }
    }
}

void TreeNode::calculateCoordinate(Vector2 start){
    if(this == nullptr) return;

    this->CalculateWidth();
    float treeWidth = this->width;
    this->assignCoordinates(start.x - treeWidth / 2, start.y);

}

TreeNode* TreeNode::CreateTree(int numofKey) {
    if (numofKey < 0) return nullptr;

    // Tạo node gốc
    TreeNode* root = new TreeNode({}, {}, {400, 50}); // Root ở giữa trên cùng
    root->isLeaf = true;
    root->parent = nullptr;

    // Sinh key ngẫu nhiên
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100); // Key từ 1 đến 100
    std::vector<int> randomKeys;
    randomKeys.reserve(numofKey);

    while (randomKeys.size() < static_cast<size_t>(numofKey)) {
        int newKey = dis(gen);
        if (std::find(randomKeys.begin(), randomKeys.end(), newKey) == randomKeys.end()) {
            randomKeys.push_back(newKey);
        }
    }

    // Chèn từng key
    for (int key : randomKeys) {
        insertKey(root, key);
        root = getRoot(root);
    }

    // Gán tọa độ
    //root->calculateCoordinate({400, 50});
    return root;
}

TreeNode* TreeNode::CreateTreewithKey(std::vector<int> keys){
    TreeNode * root = new TreeNode({}, {}, {400, 50});
    root->isLeaf = true;
    root->parent = nullptr;

    for(int i = 0; i < keys.size(); i++){
        insertKey(root, keys[i]);
        root = getRoot(root);
    }
    return root;
}

TreeNode* TreeNode::getRoot(TreeNode* node) {
    while (node && node->parent) {
        node = node->parent;
    }
    return node;
}

void TreeNode::insertKey(TreeNode*& root, int key) {
    TreeNode* current = root;

    if (current->keys.empty()) {
        current->keys.push_back(key);
        std::sort(current->keys.begin(), current->keys.end());
        //current->CalculateWidth();
        return;
    }

    if (current->keys.size() == 3) {
        TreeNode* newRoot = new TreeNode({}, {}, {400, 50});
        newRoot->isLeaf = false;
        newRoot->children.push_back(root);
        root->parent = newRoot;
        splitNode(newRoot, 0, root);
        root = newRoot;
        current = root;
    }

    while (!current->isLeaf) {
        int i = 0;
        for (; i < current->keys.size(); i++) {
            if (key < current->keys[i]) break;
        }
        TreeNode* next = current->children[i];
        if (next->keys.size() == 3) {
            splitNode(current, i, next);
            if (key > current->keys[i]) i++;
            next = current->children[i];
        }
        current = next;
    }

    current->keys.push_back(key);
    std::sort(current->keys.begin(), current->keys.end());
    //current->CalculateWidth();
}

void TreeNode::splitNode(TreeNode* parent, int index, TreeNode* fullNode) {
    TreeNode* newNode = new TreeNode({}, {}, parent->position);
    newNode->isLeaf = fullNode->isLeaf;
    newNode->parent = parent;

    int midKey = fullNode->keys[1];
    newNode->keys.push_back(fullNode->keys[2]);
    fullNode->keys.resize(1);

    if (!fullNode->isLeaf) {
        newNode->children.push_back(fullNode->children[2]);
        newNode->children.push_back(fullNode->children[3]);
        fullNode->children.resize(2);
        for (TreeNode* child : newNode->children) {
            if (child) child->parent = newNode;
        }
    }

    parent->keys.insert(parent->keys.begin() + index, midKey);
    parent->children.insert(parent->children.begin() + index + 1, newNode);
    parent->isLeaf = false;

    // fullNode->CalculateWidth();
    // newNode->CalculateWidth();
    // parent->CalculateWidth();
}