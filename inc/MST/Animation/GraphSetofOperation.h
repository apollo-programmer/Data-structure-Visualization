#pragma once

#include "GraphOperation.h"

class GraphSetofOperation{
    public:
        std::vector<GraphOperation> operations;
        float & speed;

        GraphSetofOperation(float & speed);
        void AddOperation(GraphOperation operation);
        bool Draw();
};