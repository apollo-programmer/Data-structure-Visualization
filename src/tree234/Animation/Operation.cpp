#include <234tree/animation/Operation.h>
#include <iostream> // Thêm để debug
#include <memory> // Thêm để sử dụng std::unique_ptr

Operation::Operation(float& speed, TreeNode*& node, TreeNode *& root, bool& isSplit, CodeBlock & codeBlock)
    : speed(speed), node(node), root(root), isSplit(isSplit), codeBlock(codeBlock) {
    curAnimation = 0.0f;
    type = NORMAL;
    this->key = 0;
    this->newKey = 0;
}

bool Operation::DrawNormalNode() {
    if (!node) return true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        node->currentColor = node->colorNormal;
        node->textCurColor = node->textNorColor;
        node->isChosen = false;
        return false;
    }
    std::cout<<"xong normal nghen"<<std::endl;
    std::cout<<"Current Key: ";
    for(int i = 0; i < node->keys.size(); i++){
        std::cout<<node->keys[i]<<" ";
    }
    std::cout<<std::endl;
    curAnimation = 0.0f;
    return true;
}

bool Operation::DrawChosenNode() {
    if (!node) return true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        node->currentColor = node->colorChosen;
        node->textCurColor = node->textChosenColor;
        node->isChosen = true;
        return false;
    }
    std::cout<<"xong hihghlight nghen"<<std::endl;
    curAnimation = 0.0f;
    return true;
}

bool Operation::DrawInsertEdge() {
    if (!node || node->children.empty()) return true;
    if (curAnimation < 1.0f) {
        curAnimation += speed;
        for (int i = 0; i < node->children.size(); i++) {
            node->arrowPos[i] = {node->position.x + (node->children[i]->position.x - node->position.x) * curAnimation, 
                                 node->position.y + (node->children[i]->position.y - node->position.y) * curAnimation};
        }
        return false;
    }
    for (int i = 0; i < node->children.size(); i++) {
        node->arrowPos[i] = node->children[i]->position;
    }
    curAnimation = 0.0f;
    return true;
}

bool Operation::DrawMoveNode(){
    if(!node) return true;
    if(curAnimation < 1.0f){
        curAnimation += speed;
        node->position.x = node->position.x * (1.0f - curAnimation) + node->finalPosition.x * curAnimation;
        node->position.y = node->position.y * (1.0f - curAnimation) + node->finalPosition.y * curAnimation;
        if(!node->isLeaf){
            for(int i = 0; i < node->children.size(); i++){
                node->arrowPos[i] = node->children[i]->position;
            }
        }
        else{
            node->arrowPos[0] = node->position;
        }
        return false;
    }
    curAnimation = 0.0f;
    return true;
}

bool Operation::DrawMovetoFinalPos(){
    if(!root) return true;
    codeBlock.setHighlight({codeBlock.getBackHighlightID()});
    if(curAnimation < 1.0f){
        curAnimation += speed;
        MoveAllNodeToFinalPos(root, curAnimation);
        return false;
    }
    std::cout<<"root: "<<root->keys[0]<<std::endl;
    curAnimation = 0.0f;
    return true;
}

void Operation::MoveAllNodeToFinalPos(TreeNode * treeRoot, float curAnimation){
    if(!treeRoot) return;
    
    treeRoot->position.x = treeRoot->position.x * (1.0f - curAnimation) + treeRoot->finalPosition.x * curAnimation;
    treeRoot->position.y = treeRoot->position.y * (1.0f - curAnimation) + treeRoot->finalPosition.y * curAnimation;
    for(int i = 0; i < treeRoot->children.size(); i++){
        MoveAllNodeToFinalPos(treeRoot->children[i], curAnimation);
        treeRoot->arrowPos[i] = treeRoot->children[i]->position;
    }
}


bool Operation::SplitNode() {
    if(!node){
        this->isSplit = false;
        return true;
    }
    if(node->keys.size() < 3){
        this->isSplit = false;
        return true;
    }

    codeBlock.setHighlight({1});

    TreeNode * left = new TreeNode({node->keys[0]}, {}, {0, 0});
    TreeNode * right = new TreeNode({node->keys[2]}, {}, {0, 0});
    //node->children = {left, right};
    node->keys = {node->keys[1]};
    left->parent = node;
    right->parent = node;
    if(node->isLeaf == false){
        std::cout<<"da vao day"<<std::endl;
        left->children = {node->children[0], node->children[1]};
        right->children = {node->children[2], node->children[3]};
        std::cout<<"da vao day 2"<<std::endl;
        for(int i = 0; i < left->children.size(); i++){
            left->children[i]->parent = left;
            right->children[i]->parent = right;
        }

        left->isLeaf = false;
        right->isLeaf = false;
    }
    else{
        left->isLeaf = true;
        right->isLeaf = true;
    }
    node->children = {left, right};
    node->isLeaf = false;
    std::cout<<"tinh toa do"<<std::endl;

    root->calculateCoordinate({800, 100});
    std::cout<<"xong chia roi ne"<<std::endl;

    isSplit = true;
    

    return true;
}

bool Operation::MergeKeyToParent() {
    if(!node || node->parent == nullptr) return true;
    if(node->keys.size() > 1) return true;
    if(!isSplit) return true;

    codeBlock.setHighlight({1});


    TreeNode * parent = node->parent;
    int i = 0;
    for(; i < parent->keys.size(); i++){
        if(parent->keys[i] > node->keys[0]) break;
    }
    parent->keys.insert(parent->keys.begin() + i, node->keys[0]);
    parent->children[i] = node->children[0];
    parent->children.insert(parent->children.begin() + i + 1, node->children[1]);
    TreeNode * tempNode = node;
    node->children[0]->parent = parent;
    node->children[1]->parent = parent;
    node = node->parent;
    delete tempNode;
    
    root->calculateCoordinate({800, 100});

    return true;

    
}

bool Operation::InsertToLeaf() {
    if (!node) return true;

    codeBlock.setHighlight({3});
    if(node->keys.empty()){
        node->keys.push_back(key);
        root->calculateCoordinate({800, 100});
        return true;
    }
    for(int i = 0; i < node->keys.size(); i++){
        if(node->keys[i] > key){
            node->keys.insert(node->keys.begin() + i, key);
            return true;
        }
    }
    node->keys.push_back(key);
    root->calculateCoordinate({800, 100});
    return true;
}

bool Operation::MoveToChildrenNode(){
    if(!node) return true;
    if(node->isLeaf) return true;
    if(node->children.empty()) return true;

    codeBlock.setHighlight({2});
    for(int i = 0; i < node->keys.size(); i++){
        if(node->keys[i] > key){
            node = node->children[i];
            return true;
        }
    }
    node = node->children.back();
    return true;
}

bool Operation::Merge2Child() {
    if (!node || node->isLeaf || node->keys.empty()) return true;

    codeBlock.setHighlight({1});

    int i = 0;
    for (; i < node->keys.size(); i++) {
        if (node->keys[i] >= key) break;
    }

    // Đảm bảo i hợp lệ (cần ít nhất 2 con để merge)
    if (i >= node->children.size() - 1 || node->children.size() < 2) {
        i = node->children.size() - 2; // Chọn cặp con cuối cùng
        if (i < 0) return true; // Không đủ con để merge
    }

    // Lấy left và right
    TreeNode* left = node->children[i];
    TreeNode* right = node->children[i + 1];

    // Kiểm tra left và right hợp lệ
    if (!left || !right || left->keys.empty() || right->keys.empty()) return true;

    // Chỉ merge khi cả hai node con có 1 key
    if (left->keys.size() == 1 && right->keys.size() == 1) {
        // Lấy key từ parent
        int parentKey = node->keys[i];

        // Merge: đưa key từ parent xuống và kết hợp với keys của left và right
        left->keys.push_back(parentKey);
        left->keys.push_back(right->keys[0]);

        // Copy children nếu không phải lá
        if (!left->isLeaf && right->children.size() >= 2) {
            left->children.push_back(right->children[0]);
            left->children.push_back(right->children[1]);
            for (auto child : left->children) {
                if (child) child->parent = left;
            }
        }

        // Xóa key trong parent
        node->keys.erase(node->keys.begin() + i);

        // Xóa right child khỏi parent
        node->children.erase(node->children.begin() + i + 1);

        // Giải phóng right node
        delete right;

        // Nếu parent trở thành rỗng và không phải root
        if (node->keys.empty() && node->parent) {
            TreeNode* parent = node->parent;

            // Tìm chỉ số của node trong parent->children
            int nodeIndex = 0;
            for (; nodeIndex < parent->children.size(); nodeIndex++) {
                if (parent->children[nodeIndex] == node) break;
            }

            // Kiểm tra nodeIndex hợp lệ
            if (nodeIndex >= parent->children.size()) return true;

            // Tìm left_sibling và right_sibling
            TreeNode* left_sibling = (nodeIndex > 0) ? parent->children[nodeIndex - 1] : nullptr;
            TreeNode* right_sibling = (nodeIndex < parent->children.size() - 1) ? parent->children[nodeIndex + 1] : nullptr;

            // Mượn từ left_sibling nếu có >= 2 keys
            if (left_sibling && left_sibling->keys.size() >= 2 && nodeIndex > 0) {
                node->keys.push_back(parent->keys[nodeIndex - 1]);
                parent->keys[nodeIndex - 1] = left_sibling->keys.back();
                left_sibling->keys.pop_back();

                if (!node->isLeaf && !left_sibling->children.empty()) {
                    node->children.insert(node->children.begin(), left_sibling->children.back());
                    left_sibling->children.pop_back();
                    if (!node->children.empty()) {
                        node->children[0]->parent = node;
                    }
                }
                root->calculateCoordinate({800, 100});
                return true;
            }
            // Mượn từ right_sibling nếu có >= 2 keys
            else if (right_sibling && right_sibling->keys.size() >= 2 && nodeIndex < parent->keys.size()) {
                node->keys.push_back(parent->keys[nodeIndex]);
                parent->keys[nodeIndex] = right_sibling->keys[0];
                right_sibling->keys.erase(right_sibling->keys.begin());

                if (!node->isLeaf && !right_sibling->children.empty()) {
                    node->children.push_back(right_sibling->children[0]);
                    right_sibling->children.erase(right_sibling->children.begin());
                    if (!node->children.empty()) {
                        node->children.back()->parent = node;
                    }
                }
                root->calculateCoordinate({800, 100});
                return true;
            }

            // Nếu không mượn được, không làm gì thêm
            return true;
        }
        else if (node->keys.empty() && !node->parent && left) {
            // Nếu parent là root và trở thành rỗng
            TreeNode* tempNode = node;
            delete tempNode;
            root = left;
            node = left;
            root->parent = nullptr;
            root->calculateCoordinate({800, 100});
            return true;
        }

        root->calculateCoordinate({800, 100});
        return true;
    }

    return true;
}

bool Operation::RemoveLeaf() {
    if (!node || !node->isLeaf) return false;
    
    bool isChange = true;

    codeBlock.setHighlight({4});
    for(int i = 0; i < node->keys.size(); i++){
        if(node->keys[i] == key){
            isChange = false;
            break;
        }
    }
    if(isChange){
        key = newKey;
    }
    // Tìm và xóa key
    auto it = std::find(node->keys.begin(), node->keys.end(), key);
    if (it == node->keys.end()){
        codeBlock.setHighlight({5});
        return true;
    }
    node->keys.erase(it);

    // Nếu node vẫn có ít nhất 1 key (không underflow) hoặc là root
    if (!node->parent || !node->keys.empty()) return true;

    // Trường hợp underflow: node không còn key và không phải root
    TreeNode* parent = node->parent;
    int nodeIndex = 0;
    for (; nodeIndex < parent->children.size(); nodeIndex++) {
        if (parent->children[nodeIndex] == node) break;
    }

    // Tìm sibling để borrow hoặc merge
    TreeNode* leftSibling = (nodeIndex > 0) ? parent->children[nodeIndex - 1] : nullptr;
    TreeNode* rightSibling = (nodeIndex < parent->children.size() - 1) ? parent->children[nodeIndex + 1] : nullptr;

    // Case 1: Borrow từ left sibling nếu nó có >= 2 keys
    if (leftSibling && leftSibling->keys.size() >= 2) {
        // Lấy key lớn nhất từ leftSibling
        node->keys.push_back(parent->keys[nodeIndex - 1]);
        parent->keys[nodeIndex - 1] = leftSibling->keys.back();
        leftSibling->keys.pop_back();
        
        // Nếu không phải leaf, chuyển child tương ứng
        return true;
    }

    // Case 2: Borrow từ right sibling nếu nó có >= 2 keys
    if (rightSibling && rightSibling->keys.size() >= 2) {
        // Lấy key nhỏ nhất từ rightSibling
        node->keys.push_back(parent->keys[nodeIndex]);
        parent->keys[nodeIndex] = rightSibling->keys.front();
        rightSibling->keys.erase(rightSibling->keys.begin());
        
        // Nếu không phải leaf, chuyển child tương ứng
        
        return true;
    }

    // Case 3: Merge với sibling nếu không borrow được
    if (leftSibling) {
        // Merge node vào leftSibling
        leftSibling->keys.push_back(parent->keys[nodeIndex - 1]);
        if (!leftSibling->isLeaf) {
            leftSibling->children.insert(leftSibling->children.end(), node->children.begin(), node->children.end());
            for (auto child : node->children) child->parent = leftSibling;
        }
        parent->keys.erase(parent->keys.begin() + (nodeIndex - 1));
        parent->children.erase(parent->children.begin() + nodeIndex);
        delete node;
        node = leftSibling;
    } else if (rightSibling) {
        // Merge node vào rightSibling
        rightSibling->keys.insert(rightSibling->keys.begin(), parent->keys[nodeIndex]);
        if (!rightSibling->isLeaf) {
            rightSibling->children.insert(rightSibling->children.begin(), node->children.begin(), node->children.end());
            for (auto child : node->children) child->parent = rightSibling;
        }
        parent->keys.erase(parent->keys.begin() + nodeIndex);
        parent->children.erase(parent->children.begin() + nodeIndex);
        delete node;
        node = rightSibling;
    }

    // Nếu parent trở thành underflow, gọi đệ quy lên parent
    if (parent->keys.empty() && parent->parent) {
        node = parent;
        key = parent->keys.empty() ? INT_MAX : parent->keys[0]; // Cập nhật node và key để xử lý parent
        return RemoveLeaf(); // Gọi lại để xử lý parent
    }
    
    return true;
}

bool Operation::Changekey(){
    if(!node) return true;
    for(int i = 0; i < node->keys.size(); i++){
        if(node->keys[i] == key){
            std::cout<<"current key: "<<node->keys[i]<<std::endl;
            node->keys[i] = newKey;
            return true;
        }
    }
    return true;
}

bool Operation::ResetCur(){
    if(!node) return true;
    this->node = this->root;
    return true;
}

bool Operation::DrawOperation() {
    if (!node) return true;
    switch (type) {
        case NORMAL: return DrawNormalNode();
        case HIGHLIGHT: return DrawChosenNode();
        case INSERT_EDGE: return DrawInsertEdge();
        case MOVE_NODE: return DrawMoveNode();
        case SPLIT_NODE: return SplitNode();
        case MERGE_KEY_TO_PARENT: return MergeKeyToParent();
        case INSERT_TO_LEAF: return InsertToLeaf();
        case MOVE_TO_FINPOS: return DrawMovetoFinalPos();
        case MOVE_TO_CHILDREN_NODE: return MoveToChildrenNode();
        case MERGE_TO_CHILDREN: return Merge2Child();
        case REMOVE_LEAF: return RemoveLeaf();
        case CHANGE_KEY: return Changekey();
        case RESET_CURRENT: return ResetCur();
        default: return true;
    }
}