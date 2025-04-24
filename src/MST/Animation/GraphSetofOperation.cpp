#include "MST/Animation/GraphSetofOperation.h"

GraphSetofOperation::GraphSetofOperation(float & speed): speed(speed) {}

void GraphSetofOperation::AddOperation(GraphOperation operation){
    operations.push_back(operation);
}

bool GraphSetofOperation::Draw(){
    if(operations.empty()) return true;
    bool isComplete = true;
    for(int i = 0; i < operations.size(); i++){
        if(!operations[i].DrawGOperation()){
            isComplete = false;
        }
    }
    return isComplete;
}