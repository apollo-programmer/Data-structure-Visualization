#include <234tree/animation/InputPanel.h>
#include <cstdlib> // Để dùng std::stoi
#include <iostream>

InputPanel::InputPanel()
    : inputBox(120,680,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,boxColor, boxTextColor),
    inputBoxFin(120,730, SLLBoxSize.x, SLLBoxSize.y, SLLBoxFontSize, boxColor, boxTextColor) {
    activeButtonIndex = -1; // Không có nút nào được chọn
    lastInputValue = {}; // Giá trị mặc định ban đầu
    // Thiết lập các nút chức năng (Create, Search, Insert, Remove)
    const char* buttonLabels[] = {"Create", "Search", "Insert", "Remove", "Update"};
    for (int i = 0; i < 5; i++) {
        Button btn;
        btn.setPosition({panelButtonSize.x/2.0f+(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f), 650+50*i+(panelButtonSize.y/2.0f)}); // Căn giữa theo chiều ngang
        btn.setSize(panelButtonSize);
        btn.setText(buttonLabels[i], panelButtonFontSize);

        inputFileButton.setPosition({320,740});
        inputFileButton.setSize({120, 30});
        inputFileButton.setText("Load File",SLLButtonFontSize);
        // btn.setColor(LIGHTGRAY, GRAY, DARKGRAY);
        // btn.setRectangle();
        buttons.push_back(btn);
    }
    isShowLoadFile = false;

    // Thiết lập nút "Go" (ban đầu không hiển thị, sẽ cập nhật vị trí sau)
    goButton.setSize({260, 30});
    goButton.setText("Apply",SLLButtonFontSize);
    goButton.setPosition({250,780});
    //goButton.setColor(LIGHTGRAY, GRAY, DARKGRAY);

    random.setSize({120, 30});
    random.setPosition({180, 740});
    random.setText("Random", SLLButtonFontSize);
}

void InputPanel::update() {
    updatePanel(); // Cập nhật trạng thái của panel
    // Chỉ cập nhật các thành phần bên trong panel nếu panel đang mở
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].update();
        if (buttons[i].isPressed()) {
            // Khi một nút chức năng được nhấn, hiển thị inputBox kế bên nút đó
            activeButtonIndex = i;
            if(isUsing&&isUsing==&buttons[i]) {
                isUsing->deSelected();
                isUsing=nullptr;
            }
            else{
                buttons[i].Selected();
                if(isUsing&&isUsing!=&buttons[i]) this->isUsing->deSelected();
                this->isUsing = &buttons[i];
            }
            //goButton.setRectangle();
        }
        if(&buttons[i]==isUsing){
            activeButtonIndex = i;
            if(i == 0){
                isShowLoadFile = true;
            }
        }
    }

    if (isUsing) {
        if(activeButtonIndex != 4){
            if(activeButtonIndex == 0){
                random.update();
            }
            goButton.setPosition({250, 780});
            inputBox.Update();
            goButton.update();
            inputFileButton.update();
            if(isShowLoadFile){
                if(inputFileButton.isPressed()){
                    static const char* filters[] = {"*.txt"};
                    const char * filepath = tinyfd_openFileDialog("Choose file", "", 1,filters, "Text file", 0);
                    if(filepath){
                        fileValues2D = LoadFile(filepath);
                        lastInputValue = {};
                    }
                    else{
                        fileValues2D.clear();
                        lastInputValue = {};
                    }
                }
            }
        }
        else{
            inputBox.Update();
            goButton.setPosition({250, 830});
            inputBoxFin.Update();
            goButton.update();
        }
    }
}


void InputPanel::draw() {
    drawPanel();
    // Vẽ các nút chức năng
    for (auto& btn : buttons) {
        btn.drawRectangleRounded(100);
        btn.drawOutlineRounded(100, 0, 3); // Vẽ viền cho nút
        btn.drawText();
    }

    // Vẽ ô nhập liệu và nút "Go" nếu đang hiển thị
    if (isUsing) {
        if(activeButtonIndex != 4){
            if(activeButtonIndex == 0){
                random.drawRectangleRounded(100);
                random.drawOutlineRounded(100, 0, 3);
                random.drawText();
            }
            inputBox.Draw();
            goButton.drawRectangleRounded(100);
            goButton.drawOutlineRounded(100, 0, 3); // Vẽ viền cho nút "Go"
            goButton.drawText();

            if(isShowLoadFile){
                inputFileButton.drawRectangleRounded(100);
                inputFileButton.drawText();
                inputFileButton.drawOutlineRounded(100, 0, 3);
            }
        }
        else{
            inputBox.Draw();
            inputBoxFin.Draw();
            goButton.drawRectangleRounded(100);
            goButton.drawOutlineRounded(100, 0, 3); // Vẽ viền cho nút "Go"
            goButton.drawText();

        }
    }
}


std::vector<int> InputPanel::GetInputText() {
    lastInputValue.clear();
    if (isUsing && goButton.isPressed() && activeButtonIndex != 4) {
        std::string input = inputBox.GetText();
        inputBox.clearText(); // Xóa nội dung ô nhập sau khi nhấn "Go"
        int LastInput;
        if (input.empty()) {
            LastInput = -1; // Trả về -1 nếu ô nhập rỗng
        } else {
            try {
                size_t pos;
                LastInput = std::stoi(input, &pos);
                // Kiểm tra xem toàn bộ chuỗi đã được chuyển đổi thành số chưa
                if (pos != input.length()) {
                    LastInput = -1; // Trả về -1 nếu chuỗi không phải số hợp lệ
                }
            } catch (...) {
                LastInput = -1; // Trả về -1 nếu có lỗi (ví dụ: chuỗi không phải số)
            }
        }
        lastInputValue.push_back(LastInput);
        lastInputValue.push_back(-1);
        return lastInputValue;
    }
    else if(isUsing &&goButton.isPressed() && activeButtonIndex == 4){
        std::string inputInit = inputBox.GetText();
        std::string inputFin = inputBoxFin.GetText();

        inputBox.clearText();
        inputBoxFin.clearText();

        int inputI, inputF;

        if(inputInit.empty() || inputFin.empty()){
            lastInputValue = {-1, -1};
            return lastInputValue;
        }
        else{
            try {
                size_t pos1, pos2;
                inputI = std::stoi(inputInit, &pos1);
                inputF = std::stoi(inputFin, &pos2);
                // Kiểm tra xem toàn bộ chuỗi đã được chuyển đổi thành số chưa
                if (pos1 != inputInit.length()) {
                    inputI = -1; // Trả về -1 nếu chuỗi không phải số hợp lệ
                }
                if(pos2 != inputFin.length()){
                    inputF = -1;
                }
            } catch (...) {
                inputI  = -1; // Trả về -1 nếu có lỗi (ví dụ: chuỗi không phải số)
                inputF = -1;
            }
        }
        lastInputValue.clear();
        lastInputValue = {inputI, inputF};
        return lastInputValue;
    }
    return lastInputValue; // Trả về -1 nếu không có giá trị mới
}

std::vector<std::vector<int>> InputPanel::LoadFile(const std::string & filepath) {
    std::vector<std::vector<int>> values;
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "Không thể mở file: " << filepath << std::endl;
        return values;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> lineValues;
        std::stringstream ss(line);
        std::string value;
        while (ss >> value) {
            try {
                size_t pos;
                int intValue = std::stoi(value, &pos);
                if (pos == value.length()) {
                    lineValues.push_back(intValue);
                } else {
                    std::cout << "Giá trị không hợp lệ (không phải số nguyên đầy đủ): " << value << std::endl;
                }
            } catch (const std::exception& e) {
                std::cout << "Lỗi chuyển đổi giá trị: " << value << " - " << e.what() << std::endl;
            }
        }
        if (!lineValues.empty()) {
            values.push_back(lineValues);
        }
    }

    file.close();
    if (values.empty()) {
        std::cout << "File rỗng hoặc không chứa số hợp lệ: " << filepath << std::endl;
    } else {
        std::cout << "Đọc thành công từ file: " << filepath << std::endl;
        for (const auto& row : values) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
    return values;
}


std::vector<std::vector<int>> InputPanel::GetFileValues2D() const{
    return fileValues2D;
}


int InputPanel::GetActiveButtonIndex() const {
    return activeButtonIndex;
}

void InputPanel::ResetInputState() {
    activeButtonIndex = -1;
    lastInputValue = {};
    fileValues2D.clear();
    inputBox.clearText();
    inputBoxFin.clearText();
}

bool InputPanel::IsCreatePressed() {
    return activeButtonIndex == 0 && lastInputValue.empty();
}

bool InputPanel::IsSearchPressed() {
    return activeButtonIndex == 1 && lastInputValue.empty();
}

bool InputPanel::IsInsertPressed() {
    return activeButtonIndex == 2 && lastInputValue.empty();
}

bool InputPanel::IsRemovePressed() {
    return activeButtonIndex == 3 && lastInputValue.empty();
}

bool InputPanel::IsUpdatePressed(){
    return activeButtonIndex == 4 && lastInputValue.empty();
}

bool InputPanel::isAnyButtonPressed() {
    for (auto & btn : buttons) {
        if (btn.isPressed()) {
            return true; // Nếu bất kỳ nút nào được nhấn, trả về true
        }
    }
    return false; // Nếu không có nút nào được nhấn, trả về false
}

bool InputPanel::IsLoadFilePressed(){
    return (activeButtonIndex >= 0 && activeButtonIndex <= 3) && !fileValues2D.empty();
}

bool InputPanel::IsRandomPressed(){
    return random.isPressed() && activeButtonIndex == 0;
}