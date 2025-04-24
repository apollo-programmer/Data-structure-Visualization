#include <ShortestPath/STArrow.h>

STArrow::STArrow(Vector2 pos,int to) : Arrow(pos){
    this->to=to;
    this->weight=0;
}

void STArrow::setDestination(Vector2 targetDes){
    float disX=targetDes.x-position.x, disY=targetDes.y-position.y;
    float dis=sqrt(disX*disX+disY*disY);
    this->destination={targetDes.x-STNodeSize.x/(2.0f*dis)*disX,targetDes.y-STNodeSize.y/(2.0f*dis)*disY};
}

void STArrow::draw(bool isWeighted, bool isDirected){
    if(isWeighted){
        float midX = (position.x + destination.x) / 2.0f;
        float midY = (position.y + destination.y) / 2.0f;
        Vector2 dir = {destination.y - position.y,-(destination.x - position.x)};
        float length = sqrt(dir.x * dir.x + dir.y * dir.y);
        float labelX = midX - 5 + dir.x/length * 10;
        float labelY = midY - 5 + dir.y/length * 10;
        DrawText(std::to_string(this->weight).c_str(), labelX, labelY, 15,(isLine)? lineColor : ((isHighlight)? nodeHighlightColor : appTitleColor));
    }
    if(isDirected){
        color= (isLine)? lineColor : ((isHighlight)? nodeHighlightColor:appTitleColor);
        drawArrow(this->position,this->destination);
    }
    else{
        float disX=destination.x-position.x, disY=destination.y-position.y;
        float dis=sqrt(disX*disX+disY*disY);
        DrawLineEx(this->position,{this->destination.x+STNodeSize.x/(2.0f*dis)*disX,this->destination.y+STNodeSize.y/(2.0f*dis)*disY},3,(isLine)? lineColor:((isHighlight)? nodeHighlightColor : appTitleColor));
    }
}

void STArrow::setWeight(int weight){
    this->weight=weight;
}

int STArrow::getWeight(){
    return this->weight;
}

void STArrow::setTo(int to){
    this->to=to;
}

int STArrow::getTo(){
    return this->to;
}

void STArrow::setFrom(int from){
    this->from=from;
}

int STArrow::getFrom(){
    return this->from;
}

void STArrow::setHighlight(){
    isHighlight=true;
}

void STArrow::deHighlight(){
    isHighlight=false;
}

void STArrow::setLine(){
    isLine=true;
}

void STArrow::deLine(){
    isLine=false;
}