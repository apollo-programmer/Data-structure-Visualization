#ifndef INPUTPANEL_H
#define INPUTPANEL_H

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

class InputPanel : public Panel {
private:
    std::vector<Button> buttons; // Các nút chức năng (Create, Search, Insert, Remove)
    InputBox inputBox; // Ô nhập liệu
    InputBox inputBoxFin; //just for update
    Button goButton; // Nút "Go"
    Button random;
    Button inputFileButton;
    std::vector<std::vector<int>> fileValues2D;
    std::vector<std::vector<int>> LoadFile(const std::string & filepath);
    bool showInputBox; // Trạng thái hiển thị của inputBox và nút Go
    bool isShowLoadFile;
    int activeButtonIndex; // Lưu nút nào đang được chọn để hiển thị inputBox (-1 nếu không có)
    std::vector<int> lastInputValue; // Lưu giá trị số đã nhập sau khi nhấn "Go"

public:
    InputPanel();
    void update() override;
    void draw() override;
    std::vector<int> GetInputText();
    int GetActiveButtonIndex() const; // Thêm hàm để lấy activeButtonIndex
    void ResetInputState(); // Thêm hàm để reset trạng thái
    bool IsCreatePressed();
    bool IsSearchPressed();
    bool IsInsertPressed();
    bool IsRemovePressed();
    bool IsUpdatePressed();
    bool isAnyButtonPressed() override;

    std::vector<std::vector<int>> GetFileValues2D() const;
    bool IsLoadFilePressed();
    bool IsRandomPressed();
};

#endif // INPUTPANEL_H