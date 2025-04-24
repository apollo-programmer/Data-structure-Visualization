#include <234tree/Tree234Visual.h>
#include <string>

Tree234Visual::Tree234Visual(float & speed) :speed(speed), currentPresentationIndex(-1), currentStateIndex(0), historyState({}), inputPanel(), speedSlider(0.01f, 0.1f, 0.05f, 10), codeBlock(),
                                  playbackControl({900, 600}, 200, 10,speed) ,treePresentation(speed, root, historyState, currentPresentationIndex, currentStateIndex, codeBlock) {    
    //root = nullptr;
    //speed = 0.05f;
    //std::vector<std::vector<TreeNode*>> history;
    //int presIndex = 0, stateIndex = 0;

    root = new TreeNode({}, {}, {800, 100});
    
    showInputBox = false;
    inputText = "";
    inputNumber = 0;
    insertButton = {20, 20, 100, 40};
    isRewinding = false;
    
    currentPresentationIndex = -1;
    currentStateIndex = 0;
    inputPanel.setDataName("234 Tree");
    //inputPanel = InputPanel({150, 500}, {150, 200}, LIGHTGRAY);
}

Tree234Visual::~Tree234Visual() {
    //delete treePresentation;
    // TODO: Thêm logic để delete toàn bộ cây (root)
}

void Tree234Visual::Update() {
    inputPanel.setBackActive();
    inputPanel.update();

    if(inputPanel.IsRandomPressed()){
        std::random_device rd; // Tạo seed
        std::mt19937 gen(rd()); // Engine ngẫu nhiên
        std::uniform_int_distribution<> dis(10, 20); // Khoảng [1, 100]

        int randomNum = dis(gen); // Random một số
        this->root = this->root->CreateTree(randomNum);
        this->root->calculateCoordinate({800, 100});
        std::cout<<"da tao tree roi"<<std::endl;

        treePresentation.clear();
        treePresentation.CreateTree(randomNum);
        std::cout << "Create button pressed\n";
    }

    if(inputPanel.IsLoadFilePressed()){
        auto fileValues = inputPanel.GetFileValues2D();
        int activeButton = inputPanel.GetActiveButtonIndex();

        if(!fileValues.empty()){
            switch (activeButton)
            {
            case 0:{
                if(fileValues.size() >= 2 && !fileValues[0].empty()){
                    int size = fileValues[0][0];
                    std::vector<int> keys = fileValues[1];
                    root = root->CreateTreewithKey(keys);
                    root->calculateCoordinate({800, 100});
                    treePresentation.clear();
                    treePresentation.CreateTree(size);
                }
                break;
            }
            case 1:{
                if(!fileValues[0].empty()){
                    int key = fileValues[0][0];
                    treePresentation.clear();
                    treePresentation.FindKeyOperation(key);
                }
                break;
            }
            case 2:{
                if(!fileValues[0].empty()){
                    int key = fileValues[0][0];
                    std::cout<<"INSERT: "<<key<<std::endl;
                    treePresentation.clear();
                    treePresentation.InsertKeyOperation(key);
                    break;
                }
            }
            case 3:{
                if(!fileValues[0].empty()){
                    int key = fileValues[0][0];
                    treePresentation.clear();
                    treePresentation.DeleteKeyOperation(key);
                }
                break;
            }
            }
            inputPanel.ResetInputState();
        }
    }
    else{
        // Lấy giá trị từ InputPanel và hành động đã chọn
        auto inputValue = inputPanel.GetInputText();
        int activeButton = inputPanel.GetActiveButtonIndex();

        // Chỉ thực hiện hành động nếu vừa nhấn "Go" và có giá trị hợp lệ
        if (inputValue.empty() == false && activeButton != -1) {
            switch (activeButton) {
                case 0: // Create
                    // Tạo cây mới (đã comment trong code gốc, tôi giữ nguyên)
                    /*
                    root = new TreeNode({}, {}, {400, 100});
                    treePresentation->tree = root;
                    treePresentation->current = root;
                    treePresentation->isFinished = false;
                    treePresentation->clear();
                    */
                    this->root = this->root->CreateTree(inputValue[0]);
                    this->root->calculateCoordinate({800, 100});
                    std::cout<<"da tao tree roi"<<std::endl;
            
                    treePresentation.clear();
                    treePresentation.CreateTree(inputValue[0]);
                    std::cout << "Create button pressed\n";
                    break;
                case 1: // Search
                    treePresentation.clear();
                    inputNumber = inputValue[0];
                    treePresentation.FindKeyOperation(inputNumber);
                    std::cout << "Search key: " << inputNumber << std::endl;
                    break;
                case 2: // Insert
                    treePresentation.clear();
                    Insert(inputValue[0]);
                    std::cout << "Insert key: " << inputValue[0] << std::endl;
                    break;
                case 3: // Remove
                    treePresentation.clear();
                    inputNumber = inputValue[0];
                    treePresentation.DeleteKeyOperation(inputNumber);
                    std::cout << "Remove key: " << inputNumber << std::endl;
                    break;
                case 4:
                    treePresentation.clear();
                    if(inputValue.size() == 2){
                        treePresentation.UpdateTree(inputValue[0], inputValue[1]);
                    }
            }
            // Reset trạng thái của InputPanel sau khi thực hiện hành động
            inputPanel.ResetInputState();
        }
    }

    

    speedSlider.Update();
    if(isPlaying == true){
        isRewinding = false;
        if(inputPanel.isEndPressed() == true){
            isSkipBack = true;
        }
        
        if(isSkipBack){
            isDrawTree = false;
            speed = 1.0f;
        }
        else{
            speed = speedSlider.val;
        }
    }
    else{
        speed = speedSlider.val;
        if(inputPanel.isNextPressed()){
            this->isRewinding = true;
            currentStateIndex++;
            if(currentStateIndex == historyState[currentPresentationIndex].size()){
                currentPresentationIndex++;
                currentStateIndex = 0;
                if(currentPresentationIndex == historyState.size()){
                    this->isRewinding = false;
                    currentPresentationIndex = historyState.size() - 1;
                    currentStateIndex = historyState.back().size() - 1;
                }
            }
        }
        else if(inputPanel.isEndPressed()){
            this->isRewinding = false;
            currentPresentationIndex = historyState.size() - 1;
            currentStateIndex = historyState.back().size() - 1;
        }
        else if(inputPanel.isPrevPressed()){
            this->isRewinding = true;
            currentStateIndex--;
            if(currentStateIndex < 0){
                currentPresentationIndex--;
                if(currentPresentationIndex < 0){
                    currentPresentationIndex = 0;
                    currentStateIndex = 0;
                }
                else{
                    currentStateIndex = historyState[currentPresentationIndex].size() - 1;
                }
            }
        }
        else if(inputPanel.isStartPressed()){
            this->isRewinding = true;
            currentPresentationIndex--;
            if(currentPresentationIndex < 0){
                currentPresentationIndex = 0;
            }
            currentStateIndex = historyState[currentPresentationIndex].size() - 1;
        }
    }

    // if(IsKeyPressed(KEY_U)){
    //     treePresentation.UpdateTree(10, 99);
    // }
    //inputPanel.reset();
    

    //playbackControl.UpdateTree234(currentPresentationIndex, currentStateIndex, historyState);

    

}

void Tree234Visual::Draw() {
    inputPanel.draw();
    //std::cout<<"Drawing tree with keys: "<<std::endl;
    
    if(treePresentation.DrawPresentation()){
        speed = speedSlider.val;
        this->isPlaying = false;
        isDrawTree = true;
        isSkipBack = false;
        //playbackControl.isSkip = false;
    }
    else{
        this->isPlaying = true;
    }
    speedSlider.Draw();
    //playbackControl.Draw();
    //root->calculateCoordinate({800, 100});

    //std::cout<<"isRewinding: "<<isRewinding<<std::endl;
    if(this->isRewinding == false){
        //std::cout<<"draw current"<<std::endl;
        if(isDrawTree){
            DrawTree(root);
        }
    }
    else{
        //std::cout<<"draw history"<<std::endl;
        DrawTree(historyState[currentPresentationIndex][currentStateIndex]);
    }

    codeBlock.draw();
}

void Tree234Visual::DrawTree(TreeNode* root) {
    if(!root) return;

    //root->LayoutTree(0, 800, 0, 100); // Căn chỉnh vị trí của cây
    //std::cout<<"Drawing tree with keys: "<<std::endl;
    if (root) {
        // root->colorChosen = nodeHighlightColor;
        // root->colorNormal = nodeColor;
        // root->textChosenColor = nodeHighlightTextColor;
        // root->textNorColor = nodeTextColor;
        
        root->DrawLinktoChild();
        root->DrawNode();
        for (TreeNode* child : root->children) {
            DrawTree(child);
        }
    }
}

void Tree234Visual::Insert(int key) {
    treePresentation.clear();
    treePresentation.InsertKeyOperation(key);
    //treePresentation->DrawPresentation();
}

bool Tree234Visual::isBackPressed() {
    bool res = inputPanel.isBackPressed();
    if (res) {
        inputPanel.reset();
        speedSlider.reset();
        treePresentation.clear();
        root->deleteTree(root);
        root = nullptr;
        speed = 0.05f;
        currentPresentationIndex = -1;
        currentStateIndex = 0;
        isRewinding = false;
    }
    return res;
}