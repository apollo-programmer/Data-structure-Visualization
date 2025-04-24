#pragma once

#include "Operation.h"

class SetofOperation{
    public:
        std::vector<Operation> operations;
        float & speed;

        SetofOperation(float & speed);
        void AddOperation(Operation operation);
        bool Draw();
};