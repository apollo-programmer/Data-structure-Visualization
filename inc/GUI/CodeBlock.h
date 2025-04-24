#ifndef CODEBLOCK_H
#define CODEBLOCK_H

#include <vector>
#include <string>
#include <sstream>
#include <GUI/Resources.h>

class CodeBlock{
    public:
        CodeBlock();
        void draw();

        void setCode(std::string code);
        void clearCode();
        void drawCode(float x, float y);

        void setHighlight(std::vector<int> ID);
        void drawHighlight();
        void clearHighlight();

        int getBackHighlightID();

        CodeBlock clone() const;
    private:
        std::string code;
        std::vector<int> highlightID;
};

#endif