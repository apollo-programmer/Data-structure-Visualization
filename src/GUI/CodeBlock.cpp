#include <GUI/CodeBlock.h>

CodeBlock::CodeBlock(){}

void CodeBlock::draw(){
    if(code!=""){   
        DrawRectangleRec(codeBlockRec,buttonNormal);
        DrawRectangleLinesEx(codeBlockRec,3,outlineButtonColor);
    }
    drawHighlight();
    drawCode(codePosition.x,codePosition.y);
}

void CodeBlock::setCode(std::string code){
    this->code=code;
}

void CodeBlock::clearCode(){
    this->code="";
}

void CodeBlock::drawCode( float x, float y){
    std::stringstream stream(code);
    std::string line;
    int lineDis=codeBlockFontSize+5;
    int pos=0;
    while(std::getline(stream,line)){
        DrawTextEx(codeBlockFont, line.c_str(), {x,y+pos+5.0f}, codeBlockFontSize, 0, codeBlockTextColor);
        pos+=lineDis;
    }
}

void CodeBlock::setHighlight(std::vector<int> ID){
    highlightID=ID;
}

void CodeBlock::drawHighlight(){
    for (int x : highlightID){
        DrawRectangle(codeBlockRec.x,codeBlockRec.y+x*(codeBlockFontSize+5)+2.5f,codeBlockRec.width,codeBlockFontSize+5.0f,codeBlockHighlightColor);
    }
}

void CodeBlock::clearHighlight(){
    highlightID.clear();
}

int CodeBlock::getBackHighlightID(){
    if(highlightID.empty()) return -1;
    return highlightID.back();
}

CodeBlock CodeBlock::clone() const {
    CodeBlock newCodeBlock;
    newCodeBlock.code = this->code;
    newCodeBlock.highlightID=this->highlightID;
    return newCodeBlock;
}