#ifndef GRAPHINPUTPANEL_H
#define GRAPHINPUTPANEL_H

#include "raylib.h"
#include "GUI/Button.h"
#include "GUI/inputBox.h"
#include <vector>
#include <GUI/Resources.h>
#include <GUI/Panel.h>
#include <tinyfiledialogs.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

class GraphInputPanel : public Panel {
private:
    std::vector<Button> buttons; // Các nút chức năng (chỉ có Create Graph)
    InputBox inputBox; // Ô nhập liệu số đỉnh
    
    std::vector<std::vector<int>> fileValues2D; // Lưu dữ liệu từ file hoặc keyboard (đỉnh1, đỉnh2, trọng số)
    int numVertices; // Số đỉnh của đồ thị
    int numEdges; // Số cạnh của đồ thị
    std::vector<std::vector<int>> LoadFile(const std::string & filepath);
    
    int activeButtonIndex; // Lưu nút nào đang được chọn (-1 nếu không có)
    int lastInputValue; // Lưu số đỉnh đã nhập sau khi nhấn "Random"
    std::vector<std::vector<int>> ProcessKeyboardInput(const char* input); // Xử lý dữ liệu nhập từ hộp thoại

public:
    GraphInputPanel();
    void update() override;
    void draw() override;
    int GetInputText(); // Lấy số đỉnh từ inputBox
    int GetActiveButtonIndex() const; // Lấy activeButtonIndex
    void ResetInputState(); // Reset trạng thái
    bool IsCreateGraphPressed(); // Kiểm tra nút Create Graph
    bool IsRandomPressed(); // Kiểm tra nút Random
    bool IsLoadFilePressed(); // Kiểm tra nút Load File
    bool IsKeyboardPressed(); // Kiểm tra nút Keyboard
    bool IsApplyPressed();
    bool isAnyButtonPressed() override;

    std::vector<std::vector<int>> GetFileValues2D() const; // Lấy dữ liệu đồ thị
    int GetNumVertices() const; // Lấy số đỉnh
    int GetNumEdges() const; // Lấy số cạnh

    bool showInputBox = false; // Trạng thái hiển thị của inputBox và các nút liên quan
    bool isShowLoadFile = false; // Trạng thái hiển thị nút Load File
    bool isShowPrim = false;
    Button randomButton; // Nút "Random" để tạo đồ thị ngẫu nhiên
    Button loadFileButton; // Nút "Load File" để tải file
    Button keyboardButton; // Nút "Keyboard" để mở giao diện nhập liệu
    Button Apply;
};

#endif // GRAPHINPUTPANEL_H