#include "MST/Animation/GraphInputPanel.h"
#include <cstdlib> // Để dùng std::stoi
#include <iostream>
#include <string>

GraphInputPanel::GraphInputPanel()
    : inputBox(120, 680, SLLBoxSize.x, SLLBoxSize.y, SLLBoxFontSize, boxColor, boxTextColor) {
    activeButtonIndex = -1;
    lastInputValue = -1;
    numVertices = 0;
    numEdges = 0;
    showInputBox = false;
    isShowLoadFile = false;

    const char* buttonLabels[] = {"Create", "Kruskal", "Prim"};
    for(int i = 0; i < 3; i++){
        Button btn;
        btn.setPosition({panelButtonSize.x/2.0f + (panelButtonSize.y/2.0f - panelButtonFontSize/2.0f), 650 + 50 * i + (panelButtonSize.y/2.0f)});
        btn.setSize(panelButtonSize);
        btn.setText(buttonLabels[i], panelButtonFontSize);

        buttons.push_back(btn);
    }

    randomButton.setSize({260, 30});
    randomButton.setText("Random", SLLButtonFontSize);
    randomButton.setPosition({250, 750});

    loadFileButton.setSize({100, 30});
    loadFileButton.setText("Load File", SLLButtonFontSize);
    loadFileButton.setPosition({175, 790});

    keyboardButton.setSize({100, 30});
    keyboardButton.setText("Keyboard", SLLButtonFontSize);
    keyboardButton.setPosition({325, 790});

    Apply.setSize({260, 30});
    Apply.setText("Apply", SLLButtonFontSize);
    Apply.setPosition({250, 750});
}

std::vector<std::vector<int>> GraphInputPanel::ProcessKeyboardInput(const char* input) {
    std::vector<std::vector<int>> result;

    if (!input || input[0] == '\0') {
        std::cout << "Error: Empty keyboard input\n";
        return result;
    }

    // Chuyển chuỗi input thành vector các số
    std::vector<int> numbers;
    std::stringstream ss(input);
    int num;
    while (ss >> num) {
        numbers.push_back(num);
    }

    // Kiểm tra số lượng phần tử tối thiểu
    if (numbers.size() < 2) {
        std::cout << "Error: Input must contain at least num_vertices and num_edges\n";
        return result;
    }

    // Lấy num_vertices và num_edges
    int num_vertices = numbers[0];
    int num_edges = numbers[1];

    // Kiểm tra hợp lệ
    if (num_vertices <= 0 || num_edges < 0 || num_edges > num_vertices * (num_vertices - 1) / 2) {
        std::cout << "Error: Invalid num_vertices or num_edges\n";
        return result;
    }

    // Kiểm tra số lượng phần tử đủ cho các cạnh
    if (numbers.size() != 2 + num_edges * 3) {
        std::cout << "Error: Incorrect number of edge data (expected " << (2 + num_edges * 3) << " numbers, got " << numbers.size() << ")\n";
        return result;
    }

    // Thêm dòng đầu: [num_vertices, num_edges]
    result.push_back({num_vertices, num_edges});

    // Thêm các cạnh: [v1, v2, weight]
    for (int i = 0; i < num_edges; ++i) {
        int idx = 2 + i * 3;
        int v1 = numbers[idx];
        int v2 = numbers[idx + 1];
        int weight = numbers[idx + 2];

        // Kiểm tra hợp lệ
        if (v1 < 0 || v1 > num_vertices || v2 < 0 || v2 > num_vertices || v1 == v2) {
            std::cout << "Error: Invalid vertices for edge " << i + 1 << ": v1=" << v1 << ", v2=" << v2 << "\n";
            return {};
        }
        if (weight <= 0) {
            std::cout << "Error: Invalid weight for edge " << i + 1 << ": weight=" << weight << "\n";
            return {};
        }

        result.push_back({v1, v2, weight});
    }

    // In result để debug
    std::cout << "Processed keyboard input, fileValues2D:\n";
    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return result;
}

void GraphInputPanel::update() {
    updatePanel(); // Cập nhật trạng thái của panel
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].update();
        if (buttons[i].isPressed()) {
            activeButtonIndex = i;
            if (isUsing && isUsing == &buttons[i]) {
                isUsing->deSelected();
                isUsing = nullptr;
                showInputBox = false;
                isShowPrim = false;
            } else {
                buttons[i].Selected();
                if (isUsing && isUsing != &buttons[i]) this->isUsing->deSelected();
                this->isUsing = &buttons[i];
                if(i == 0){
                    showInputBox = true;
                    isShowLoadFile = true;
                    isShowPrim = false;
                }
                else if(i == 1){
                    showInputBox = false;
                    isShowLoadFile = false;
                    isShowPrim = false;
                }
                else{
                    showInputBox = false;
                    isShowLoadFile = false;
                    isShowPrim = true;
                }
            }
        }
        if (&buttons[i] == isUsing) {
            activeButtonIndex = i;
        }
    }

    if (activeButtonIndex == 0) {
        //inputBox.Update();
        randomButton.update();
        loadFileButton.update();
        keyboardButton.update();

        if (loadFileButton.isPressed()) {
            static const char* filters[] = {"*.txt"};
            const char * filepath = tinyfd_openFileDialog("Choose file", "", 1, filters, "Text file", 0);
            if (filepath) {
                fileValues2D = LoadFile(filepath);
                lastInputValue = -1;
            } else {
                fileValues2D.clear();
                lastInputValue = -1;
            }
        }

        else if (keyboardButton.isPressed()) {
            // Mở hộp thoại nhập liệu văn bản
            const char* input = tinyfd_inputBox(
                "Graph Input",
                "Enter graph (format: num_vertices num_edges v1 v2 weight1 ...):",
                ""
            );
            if (input) {
                std::cout << "Raw keyboard input: " << input << std::endl;
                fileValues2D = ProcessKeyboardInput(input);
                if (!fileValues2D.empty()) {
                    std::cout << "Processed keyboard input, fileValues2D:\n";
                    for (const auto& row : fileValues2D) {
                        for (int val : row) {
                            std::cout << val << " ";
                        }
                        std::cout << std::endl;
                    }
                    lastInputValue = -1;
                } else {
                    std::cout << "Failed to process keyboard input\n";
                    fileValues2D.clear();
                }
            } else {
                std::cout << "No keyboard input provided\n";
                fileValues2D.clear();
            }
        
        }
    }
    else if(activeButtonIndex == 2){
        inputBox.Update();
        Apply.update();
    }
}

void GraphInputPanel::draw() {
    drawPanel();
    // Vẽ nút Create Graph
    for (auto& btn : buttons) {
        btn.drawRectangleRounded(100);
        btn.drawOutlineRounded(100, 0, 3); // Vẽ viền cho nút
        btn.drawText();
    }

    // Vẽ ô nhập liệu và các nút liên quan nếu đang hiển thị
    if (showInputBox) {
        //inputBox.Draw();
        randomButton.drawRectangleRounded(100);
        randomButton.drawOutlineRounded(100, 0, 3);
        randomButton.drawText();

        loadFileButton.drawRectangleRounded(100);
        loadFileButton.drawOutlineRounded(100, 0, 3);
        loadFileButton.drawText();

        keyboardButton.drawRectangleRounded(100);
        keyboardButton.drawOutlineRounded(100, 0, 3);
        keyboardButton.drawText();
    }
    else if(isShowPrim){
        inputBox.Draw();
        Apply.drawRectangleRounded(100);
        Apply.drawOutlineRounded(100, 0, 3);
        Apply.drawText();
    }
}

int GraphInputPanel::GetInputText() {
    if (showInputBox && randomButton.isPressed()) {
        std::string input = inputBox.GetText();
        inputBox.clearText(); // Xóa nội dung ô nhập sau khi nhấn "Random"
        if (input.empty()) {
            lastInputValue = -1; // Trả về -1 nếu ô nhập rỗng
        } else {
            try {
                size_t pos;
                lastInputValue = std::stoi(input, &pos);
                if (pos != input.length() || lastInputValue <= 0) {
                    lastInputValue = -1; // Trả về -1 nếu không phải số hợp lệ hoặc số đỉnh <= 0
                }
            } catch (...) {
                lastInputValue = -1; // Trả về -1 nếu có lỗi
            }
        }
        return lastInputValue;
    }
    return -1; // Trả về -1 nếu không có giá trị mới
}

std::vector<std::vector<int>> GraphInputPanel::LoadFile(const std::string & filepath) {
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

std::vector<std::vector<int>> GraphInputPanel::GetFileValues2D() const {
    return fileValues2D;
}

int GraphInputPanel::GetNumVertices() const {
    return numVertices;
}

int GraphInputPanel::GetNumEdges() const {
    return numEdges;
}

int GraphInputPanel::GetActiveButtonIndex() const {
    return activeButtonIndex;
}

void GraphInputPanel::ResetInputState() {
    activeButtonIndex = -1;
    lastInputValue = -1;
    fileValues2D.clear();
    numVertices = 0;
    numEdges = 0;
}

bool GraphInputPanel::IsCreateGraphPressed() {
    return activeButtonIndex == 0;
}

bool GraphInputPanel::IsRandomPressed() {
    return showInputBox && randomButton.isPressed() && lastInputValue != -1;
}

bool GraphInputPanel::IsLoadFilePressed() {
    return showInputBox && !fileValues2D.empty();
}

bool GraphInputPanel::IsKeyboardPressed() {
    return showInputBox && !fileValues2D.empty();
}

bool GraphInputPanel::IsApplyPressed(){
    return isShowPrim && Apply.isPressed() && !fileValues2D.empty();
}

bool GraphInputPanel::isAnyButtonPressed() {
    for (auto & btn : buttons) {
        if (btn.isPressed()) {
            return true;
        }
    }
    return randomButton.isPressed() || loadFileButton.isPressed() || keyboardButton.isPressed();
}