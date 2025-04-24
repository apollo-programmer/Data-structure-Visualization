#include "HashTable/HashTable.h"
#include <ctime> // Để sử dụng time() trong InitTable
#include <unordered_set>

HashTable::HashTable(int size) {
    this->size = size;
    table.resize(size);
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
    isEmpty = false;
}


HashTable::HashTable(const HashTable& initHash) {
    this->size = initHash.size;
    table.resize(size, nullptr);
    for (int i = 0; i < size; i++) {
        Node* current = initHash.table[i];
        Node* prevCopy = nullptr;
        while (current != nullptr) {
            Node* newNode = new Node(*current); // Sao chép node
            newNode->next = nullptr;
            if (prevCopy == nullptr) {
                table[i] = newNode;
            } else {
                prevCopy->next = newNode;
            }
            prevCopy = newNode;
            current = current->next;
        }
    }
}
HashTable::~HashTable() {
    for (int i = 0; i < size; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
}

Node* HashTable::getTable(int index) {
    return table[index];
}

int HashTable::GetSize() const {
    return size;
}

void HashTable::Insert(int key, const std::string& value) {
    int index = key % size;
    Node* newNode = new Node(key, {static_cast<float>(index * 50 + 200), 200.0f}, {15, 15});
    newNode->finalPosition = newNode->position;
    newNode->finalSize = newNode->size;
    newNode->colorFinal = newNode->colorNormal;
    
    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        Node* current = table[index];
        while (current->next != nullptr) {
            if(current->data == key) return;
            current = current->next;
        }
        current->next = newNode;
        newNode->position = {current->position.x, current->position.y + 50};
        newNode->finalPosition = newNode->position;
    }
    std::cout<<"INsert key: "<<key<<" thanh cong!!"<<std::endl;
}

void HashTable::Delete(int key) {
    int index = key % size;
    Node* current = table[index];
    Node* prev = nullptr;

    while (current != nullptr && current->data != key) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return;

    if (prev == nullptr) {
        table[index] = current->next;
        delete current;
    } else {
        prev->next = current->next;
        delete current;
    }

    // Cập nhật vị trí và arrowPos
    current = table[index];
    float yPos = 200.0f;
    Node* prevNode = nullptr;
    while (current != nullptr) {
        current->position = {static_cast<float>(index * 50 + 200), yPos};
        current->finalPosition = current->position;
        if (prevNode) {
            prevNode->arrowPos = current->position; // Mũi tên trỏ đến node tiếp theo
        }
        yPos += 50.0f;
        prevNode = current;
        current = current->next;
    }
    if (prevNode) {
        prevNode->arrowPos = prevNode->position; // Node cuối không có mũi tên
    }
}

bool HashTable::Find(int key) const {
    int index = key % size;
    Node* current = table[index];
    while (current != nullptr) {
        if (current->data == key) return true;
        current = current->next;
    }
    return false;
}   

void HashTable::InitTable(int size, int numofKey) {
    if(numofKey < 0) return;
    srand(static_cast<unsigned>(time(nullptr))); // Khởi tạo seed ngẫu nhiên

    // Xóa dữ liệu cũ và khởi tạo lại bảng
    for (int i = 0; i < this->size; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    this->size = size;
    table.clear();
    table.resize(size, nullptr);

    // Bước 1: Phân bổ số lượng key cho từng bucket
    std::vector<int> bucketCount(size, 0);
    for (int i = 0; i < numofKey; ++i) {
        int bucket = rand() % size;
        bucketCount[bucket]++;
    }

    // Bước 2: Chèn các key vào bảng băm
    std::unordered_set<int> usedKeys;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < bucketCount[i]; ++j) {
            int key;
            do {
                key = rand() % (numofKey * 10); // Chọn key ngẫu nhiên, tránh trùng lặp
            } while (usedKeys.count(key));
            usedKeys.insert(key);
            Insert(key, ""); // Hàm Insert đã được định nghĩa để chèn vào bảng băm
        }
    }
}

void HashTable::CreateTableFile(std::vector<int> keys){
    if(keys.empty()) return;

    for(int i = 0; i < this->size; i++){
        Node * current = table[i];
        while(current != nullptr){
            Node * next = current->next;
            delete current;
            current = next;
        }
    }
    int size = 2 * keys.size();
    for(int i = 0; i < size; i++){
        if(isPrime(size + i)){
            size +=i;
            break;
        }
        else if(isPrime(size - i)){
            size -= i;
            break;
        }
    }

    this->size = size;
    table.clear();
    table.resize(size, nullptr);
    
    for(int i = 0; i < keys.size(); i++){
        std::cout<<keys[i]<<" ";
        Insert(keys[i], "");
    }
    std::cout<<std::endl;
}

bool HashTable::isPrime(int number){
    if(number <= 1) return false;
    for(int i = 2; i < sqrt(number); i++){
        if(number % i == 0) return false;
    }
    return true;
}
