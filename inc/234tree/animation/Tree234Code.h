#pragma once

#include <string>

const std::string insertCode = {
    "Node * curr = root\n"
    "if(curr->keys->size() == 3) Split(curr)\n"
    "if(curr is not leaf) Move to child\n"
    "Insert to leaf\n"
};

const std::string removeCode = {
    "Node * curr = root\n"
    "if(both 2 child has 1 key) Merge\n"
    "if(key exists) change to successor\n"
    "Move to child\n"
    "if(key is found) remove leaf\n"
    "KEY NOT FOUND\n"
};

const std::string findCode = {
    "Node * curr = root\n",
    "if(!curr->leaf && notfound) MovetoChild\n"
    "FOUND\n"
    "NOT FOUND\n"
};

const std::string createCode = {
    
};