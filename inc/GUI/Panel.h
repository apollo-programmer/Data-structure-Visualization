#ifndef PANEL_H
#define PANEL_H

#include <fstream>
#include <sstream>
#include <GUI/Console.h>

extern "C" {
    #include <tinyfiledialogs.h>
}

class Panel : public Console{
    public:
        Panel();
        virtual void draw()=0;
        virtual void update()=0;
        bool isBackPressed();
        void setBackActive();
        virtual bool isAnyButtonPressed()=0;
        void updatePanel();
        void drawPanel();
        void reset();

        void setDataName(const char* name);

        std::string loadFileContent(){
            std::string text="";
            const char *filterPatterns[] = {"*.txt"};
            const char *filePath = tinyfd_openFileDialog("Open a File","",1,filterPatterns,"Text Files",0);
            if (filePath) {
                std::ifstream in(filePath);
                std::string line;
                while (std::getline(in, line)) {
                    text += line + '\n';
                }
            }
            return text;
        }
    protected:
        Rectangle dataTitle;
        Button Back;

        const char* dataName;

        Rectangle panelHolder;
        Rectangle subPanelHolder;
        Button* isUsing=nullptr;
};

#endif