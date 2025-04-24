#pragma once
#include <vector>
#include <string>
#include <cmath>
#include "raylib.h"
#include "Node.h"

class HashTable {
public:
    HashTable(int size);
    HashTable(const HashTable & initHash);
    ~HashTable();

    void Insert(int key, const std::string& value);
    void Delete(int key);
    bool Find(int key) const;
    void InitTable(int size, int numofKey); // Hàm khởi tạo HashTable với dữ liệu ngẫu nhiên
    void CreateTableFile(std::vector<int> keys);
    bool isPrime(int number);
    Node* getTable(int index);
    int GetSize() const;
    
    std::vector<Node*> table;
    int size;
    bool isEmpty = false;
};