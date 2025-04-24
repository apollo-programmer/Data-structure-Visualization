#include <234tree/animation/SetofOperation.h>

SetofOperation::SetofOperation(float & speed) : speed(speed) {}



void SetofOperation::AddOperation(Operation operation){
    operations.push_back(operation);
}

bool SetofOperation::Draw(){
    if(operations.empty()) return true;
    bool isComplete = true;
    for(int i = 0; i < operations.size(); i++){
        if(!operations[i].DrawOperation()){
            isComplete = false;
        }
    }
    return isComplete;
}