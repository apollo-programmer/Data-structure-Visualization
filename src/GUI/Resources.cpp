#include "GUI/Resources.h"

namespace Resource{
    Sound clickSound;

    void InitResource() {
        InitAudioDevice(); // Khởi tạo hệ thống âm thanh
        clickSound = LoadSound("../resources/ButtonSound.wav"); // Tải âm thanh
        if (clickSound.frameCount == 0) {
            TraceLog(LOG_ERROR, "Failed load sound: resources/click.wav");
        }
    }

    void UnloadResource() {
        UnloadSound(clickSound); // Giải phóng âm thanh
        CloseAudioDevice(); // Đóng hệ thống âm thanh
    }
}
