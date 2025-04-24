#include "GUI/PlayBackControl.h"

PlaybackControl::PlaybackControl(Vector2 position, float width, float height, float & speed)
    : position(position), width(width), height(height), speed(speed),
      historySlider({position.x, position.y}, width, height, 0, 0, 0, 1),
      isPlaying(false) {

    // Khởi tạo các nút
    float buttonWidth = 50;
    float buttonHeight = 30;
    float spacing = 10;

    // Skip Back Button
    skipBackButton.setPosition({position.x, position.y + height + spacing});
    skipBackButton.setSize({buttonWidth, buttonHeight});
    skipBackButton.setText("<<", 20);
    //skipBackButton.setColor({80, 80, 80, 255}, GRAY, BLACK);

    // Step Back Button
    stepBackButton.setPosition({position.x + buttonWidth + spacing, position.y + height + spacing});
    stepBackButton.setSize({buttonWidth, buttonHeight});
    stepBackButton.setText("<", 20);
    //stepBackButton.setColor({80, 80, 80, 255}, GRAY, BLACK);

    // Step Next Button
    stepNextButton.setPosition({position.x + 2 * (buttonWidth + spacing), position.y + height + spacing});
    stepNextButton.setSize({buttonWidth, buttonHeight});
    stepNextButton.setText(">", 20);
    //stepNextButton.setColor({80, 80, 80, 255}, GRAY, BLACK);

    // Skip Next Button
    skipNextButton.setPosition({position.x + 3 * (buttonWidth + spacing), position.y + height + spacing});
    skipNextButton.setSize({buttonWidth, buttonHeight});
    skipNextButton.setText(">>", 20);
    //skipNextButton.setColor({80, 80, 80, 255}, GRAY, BLACK);
}

void PlaybackControl::UpdateHash(int& currentPresentationIndex, int& currentStateIndex, 
                             std::vector<std::vector<HashTable>> historyState) {
    if (historyState.empty()) return;

    // Cập nhật thanh slider
    historySlider.Update();
    historySlider.minVal = 0;
    historySlider.maxVal = historyState[currentPresentationIndex].size() - 1;
    historySlider.val = currentStateIndex;

    // Xử lý các nút
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Skip Back: Quay về trạng thái cuối của presentation trước
        if (skipBackButton.isPressed()) {
            if (currentPresentationIndex > 0) {
                currentPresentationIndex--;
                currentStateIndex = historyState[currentPresentationIndex].size() - 1;
                historySlider.val = currentStateIndex;
            }
            isPlaying = true;
        }

        // Step Back: Quay về set ngay trước đó
        if (stepBackButton.isPressed()) {
            if (currentStateIndex > 0) {
                currentStateIndex--;
                historySlider.val = currentStateIndex;
            }
            else{
                if(currentPresentationIndex != 0)
                {    currentPresentationIndex--;
                    currentStateIndex = historyState[currentPresentationIndex].size() - 1;
                    historySlider.val = currentStateIndex;
                }
            }
            isPlaying = true;
        }

        // Step Next: Đi tới bước tiếp theo
        if (stepNextButton.isPressed()) {
            if (currentStateIndex < static_cast<int>(historyState[currentPresentationIndex].size()) - 1) {
                currentStateIndex++;
                historySlider.val = currentStateIndex;
            }
            else{
                if(currentPresentationIndex != historyState.size() - 1){
                    currentPresentationIndex++;
                    currentStateIndex = 0;
                    historySlider.val = currentStateIndex;
                }
            }
            isPlaying = true;
        }

        // Skip Next: Nhảy tới trạng thái cuối
        if (skipNextButton.isPressed()) {
            currentPresentationIndex = historyState.size() - 1;
            currentStateIndex = historyState[currentPresentationIndex].size() - 1;
            historySlider.val = currentStateIndex;
            if(isPlaying == false){
                speed = 1.0f;
            }
            isPlaying = false;
            this->isSkip = true;
        }
    }

    // Cập nhật currentStateIndex từ slider
    currentStateIndex = static_cast<int>(std::round(historySlider.val));
}

void PlaybackControl::UpdateTree234(int& currentPresentationIndex, int& currentStateIndex,
                             std::vector<std::vector<TreeNode*>> historyState) {
    if (historyState.empty()) return;


    // Cập nhật thanh slider
    historySlider.Update();
    historySlider.minVal = 0;
    historySlider.maxVal = historyState[currentPresentationIndex].size() - 1;
    historySlider.val = currentStateIndex;

    // Xử lý các nút
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        std::cout<<"PlayBackControl"<<std::endl;
        // Skip Back: Quay về trạng thái cuối của presentation trước
        if (skipBackButton.isPressed()) {
            if (currentPresentationIndex > 0) {
                currentPresentationIndex--;
                currentStateIndex = historyState[currentPresentationIndex].size() - 1;
                historySlider.val = currentStateIndex;
            }
            isPlaying = true;
        }

        // Step Back: Quay về set ngay trước đó
        if (stepBackButton.isPressed()) {
            if (currentStateIndex > 0) {
                currentStateIndex--;
                historySlider.val = currentStateIndex;
            }
            else{
                if(currentPresentationIndex != 0)
                {    currentPresentationIndex--;
                    currentStateIndex = historyState[currentPresentationIndex].size() - 1;
                    historySlider.val = currentStateIndex;
                }
            }
            isPlaying = true;
        }

        // Step Next: Đi tới bước tiếp theo
        if (stepNextButton.isPressed()) {
            if (currentStateIndex < static_cast<int>(historyState[currentPresentationIndex].size()) - 1) {
                currentStateIndex++;
                historySlider.val = currentStateIndex;
            }
            else{
                if(currentPresentationIndex != historyState.size() - 1){
                    currentPresentationIndex++;
                    currentStateIndex = 0;
                    historySlider.val = currentStateIndex;
                }
            }
            isPlaying = true;
        }

        // Skip Next: Nhảy tới trạng thái cuối
        if (skipNextButton.isPressed()) {
            currentPresentationIndex = historyState.size() - 1;
            currentStateIndex = historyState[currentPresentationIndex].size() - 1;
            historySlider.val = currentStateIndex;
            if(isPlaying = false){
                speed = 1.0f;
            }
            isPlaying = false;
            isSkip = true;
        }
        //isPlaying = false;
        // std::cout<<"currentPresentationIndex: "<<currentPresentationIndex<<std::endl;
        // std::cout<<"currentStateIndex: "<<currentStateIndex<<std::endl;
    }

    // Cập nhật currentStateIndex từ slider
    currentStateIndex = static_cast<int>(std::round(historySlider.val));
}

void PlaybackControl::Draw() {
    historySlider.Draw();

    skipBackButton.drawRectangle({50, 30});
    stepBackButton.drawRectangle({50, 30});
    stepNextButton.drawRectangle({50, 30});
    skipNextButton.drawRectangle({50, 30});
}

bool PlaybackControl::IsPlaying() const {
    return isPlaying;
}