#include <Application.h>

Application::Application(): TREE234(this->speed), hashTable(true, speed), graph(this->speed){}

void Application::run(){
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1600, 900, "Data Structure Visualization");
    SetTargetFPS(60);
    LoadFontsAndTextures();
    Resource::InitResource();
    srand(time(NULL));
    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(backgroundColor);
        colorThemeManager.update();
        if(SLL.isBackPressed()||AVL.isBackPressed()||ST.isBackPressed()||hashTable.isBackPressed()||TREE234.isBackPressed()){
            menuState.currentSelection=MenuSelection::NONE;
        }
        switch (menuState.currentSelection) {
        case MenuSelection::NONE:
            if(!colorThemeManager.isTheme){
                this->menuState.update();
            }
            if(!colorThemeManager.isUpdate){
                this->menuState.update();
                colorThemeManager.isUpdate=true;
            }
            this->menuState.draw();
            break;

        case MenuSelection::SLL:
            if(!colorThemeManager.isTheme){
                this->SLL.update();
            }
            if(!colorThemeManager.isUpdate){
                this->SLL.updateTheme();
                colorThemeManager.isUpdate=true;
            }
            this->SLL.draw();
            break;

        case MenuSelection::LINEAR_HT:
            
            this->hashTable.Draw();
            this->hashTable.Update();
            break;

        case MenuSelection::TREE_234:
            this->TREE234.Draw();
            this->TREE234.Update();
            
            break;

        case MenuSelection::AVL_TREE:
            if(!colorThemeManager.isTheme){
                this->AVL.update();
            }
            if(!colorThemeManager.isUpdate){
                this->AVL.updateTheme();
                colorThemeManager.isUpdate=true;
            }
            this->AVL.draw();
            break;

        case MenuSelection::MIN_SPANNING_TREE:
            graph.Draw();
            graph.Update();
            
            break;

        case MenuSelection::SHORTEST_PATH:
            if(!colorThemeManager.isTheme){
                this->ST.update();
            }
            if(!colorThemeManager.isUpdate){
                this->ST.updateTheme();
                colorThemeManager.isUpdate=true;
            }
            this->ST.draw();
            break;
        default:
            break;
        }
        colorThemeManager.draw();
        EndDrawing();
    }
    UnloadFontsAndTextures();
    CloseWindow();
}