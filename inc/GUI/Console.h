#ifndef CONSOLE_H
#define CONSOLE_H

#include <GUI/Button.h>

class Console{
    public:
        Console();
        bool isPlayPressed();
        bool isNextPressed();
        bool isPrevPressed();
        bool isEndPressed();
        bool isStartPressed();
        void updateController();
        void drawController();
        void setEnd();
        void deEnd();
        void setPause();
        void dePause();
    protected:
        Rectangle Controller;
        Button Play;
        Button Next;
        Button Prev;
        Button End;
        Button Start;
        bool isEnd=false;
        bool isPause=false;
};

#endif