#pragma once

#include "MenuState.h"

class Application{
    public:
        Application();
        void run();
    private:
        MenuState menuState;
};