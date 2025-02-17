#include "Application.h"

Application::Application() : menuState(MenuState()) {
    InitWindow(1600, 900, "Data Structure Visualization");
    SetTargetFPS(60);
}

void Application::run(){
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if(!this->menuState.isStarted){
            this->menuState.draw();
            this->menuState.update();
        }
        EndDrawing();
    }
    CloseWindow();
}