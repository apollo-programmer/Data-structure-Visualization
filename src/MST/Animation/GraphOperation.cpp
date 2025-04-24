#include "MST/Animation/GraphOperation.h"

// Hàm nội suy màu (nếu raylib không có sẵn LerpColor)
Color GraphOperation::LerpColor(Color start, Color end, float t) {
    Color result;
    result.r = (unsigned char)(start.r + (end.r - start.r) * t);
    result.g = (unsigned char)(start.g + (end.g - start.g) * t);
    result.b = (unsigned char)(start.b + (end.b - start.b) * t);
    result.a = (unsigned char)(start.a + (end.a - start.a) * t);
    return result;
}

GraphOperation::GraphOperation(float & speed, GraphNode * vertice): speed(speed), vertice(vertice){
    this->curAnimation = 0.0f;
    this->type = CHOSEN_EDGE; // Có thể cần sửa nếu bạn muốn type khác cho vertice
    this->edge = nullptr;
}

GraphOperation::GraphOperation(float & speed, GraphEdge * edge): speed(speed), edge(edge){
    this->curAnimation = 0.0f;
    this->type = CHOSEN_EDGE;
    this->vertice = nullptr;
}

bool GraphOperation::DrawNormalNode(){
    if (vertice == nullptr) return true;

    if (curAnimation < 1.0f) {
        // Nội suy màu từ màu hiện tại sang màu bình thường
        Color targetColor = vertice->colorNormal;
        vertice->colorCurrent = LerpColor(vertice->colorCurrent, targetColor, curAnimation);
        curAnimation += speed;
        vertice->isVisited = false;
        return false; // Animation chưa hoàn tất
    } else {
        vertice->colorCurrent = vertice->colorNormal;
        return true; // Animation hoàn tất
    }
}

bool GraphOperation::DrawChosenNode(){
    if (vertice == nullptr) return true;

    if (curAnimation < 1.0f) {
        // Nội suy màu từ màu hiện tại sang màu được chọn
        Color targetColor = vertice->colorChosen;
        vertice->colorCurrent = LerpColor(vertice->colorCurrent, targetColor, curAnimation);
        curAnimation += speed;
        vertice->isVisited = true;
        return false; // Animation chưa hoàn tất
    } else {
        vertice->colorCurrent = vertice->colorChosen;
        return true; // Animation hoàn tất
    }
}

bool GraphOperation::DrawNormalEdge(){
    if (edge == nullptr) return true;

    if (curAnimation < 1.0f) {
        // Nội suy màu từ màu hiện tại sang màu bình thường
        Color targetColor = edge->colorNormal;
        edge->currentColor = LerpColor(edge->currentColor, targetColor, curAnimation);
        curAnimation += speed;
        edge->isChosen = false;
        edge->isFlur = false;
        return false; // Animation chưa hoàn tất
    } else {
        edge->currentColor = edge->colorNormal;
        return true; // Animation hoàn tất
    }
}

bool GraphOperation::DrawFlurEdge(){
    if (edge == nullptr) return true;

    if (curAnimation < 1.0f) {
        // Nội suy màu từ màu hiện tại sang màu mờ
        Color targetColor = edge->colorFlur;
        edge->currentColor = LerpColor(edge->currentColor, targetColor, curAnimation);
        curAnimation += speed;
        edge->isFlur = true;
        edge->isChosen = false;
        return false; // Animation chưa hoàn tất
    } else {
        edge->currentColor = edge->colorFlur;
        return true; // Animation hoàn tất
    }
}

bool GraphOperation::DrawChosenEdge(){
    if (edge == nullptr) return true;

    if (curAnimation < 1.0f) {
        // Nội suy màu từ màu hiện tại sang màu được chọn
        Color targetColor = edge->colorChosen;
        edge->currentColor = LerpColor(edge->currentColor, targetColor, curAnimation);
        curAnimation += speed;
        edge->isChosen = true;
        return false; // Animation chưa hoàn tất
    } else {
        edge->currentColor = edge->colorChosen;
        return true; // Animation hoàn tất
    }
}

bool GraphOperation::DrawMoveNode(){
    if(vertice == nullptr) return true;

    if(curAnimation < 1.0f){
        curAnimation += speed;
        vertice->position.x = vertice->position.x * (1.0f - curAnimation) + vertice->finalPos.x * curAnimation;
        vertice->position.y = vertice->position.y * (1.0f - curAnimation) + vertice->finalPos.y * curAnimation;
        std::cout << "Animating node " << vertice->data << ":( "<<vertice->position.x<<"; "<<vertice->position.y<<"), fin: ("<<vertice->finalPos.x<<"; "<<vertice->finalPos.y<<") " <<", curAnimation: " << curAnimation << std::endl;
        return false;
    }
    curAnimation = 0.0f;
    vertice->position = vertice->finalPos;
    std::cout << "node " << vertice->data << ": (" << vertice->position.x << "; " << vertice->position.y << ")" << std::endl;
    return true;
}

bool GraphOperation::DrawGOperation(){

    switch (type) {
        case CHOSEN_EDGE: return DrawChosenEdge();
        case NORMAL_EDGE: return DrawNormalEdge();
        case FLUR_EDGE: return DrawFlurEdge();
        case NORMAL_NODE: return DrawNormalNode();
        case CHOSEN_NODE: return DrawChosenNode();
        case MOVE_NODE: return DrawMoveNode();
    }
    std::cout<<"co animation"<<std::endl;
    return true;
}