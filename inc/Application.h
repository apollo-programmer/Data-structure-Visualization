#ifndef APPLICATION_H
#define APPLICATION_H

#include <MenuState.h>
#include <SLL/SLLState.h>
#include <AVL/AVLState.h>
#include <GUI/Resources.h>
#include <GUI/Resources.h>
#include <ShortestPath/ShortestPathState.h>
#include <HashTable/HashTableVisual.h>
#include <234tree/Tree234Visual.h>
#include <MST/GraphVisual.h>
#include <GUI/ColorThemeManager.h>

class Application{
    public:
        Application();
        void run();
    private:
        ColorThemeManager colorThemeManager;

        MenuState menuState;
        SLLState SLL;
        AVLState AVL;
        ShortestPathState ST;
        HashTableVisualization hashTable;
        Tree234Visual TREE234;
        GraphVisual graph;
        float speed = 0.05f;
};

#endif