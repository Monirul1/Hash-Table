#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

const int TABLE_SIZE = 131;

struct HashNode {
    int key;
    int value;
    HashNode* next;
    HashNode(int key, int value) {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }
};

class HashMap {
private:
    HashNode** htable;
public:
    HashMap();
    int hash(int key);
    void insert(int key, int data);
    void remove(int key);
    int get(int key);
    ~HashMap();
};

HashMap::HashMap() {
    htable = new HashNode*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        htable[i] = NULL;
    }
}

int HashMap::hash(int key) {
    return key % TABLE_SIZE;
}

void HashMap::insert(int key, int value) {
    int index = hash(key);
    HashNode* entry = htable[index];
    HashNode* prev = NULL;
    while (entry != NULL && entry -> key != key) {
        prev = entry;
        entry = entry -> next;
    }
    if (entry == NULL) {
        entry = new HashNode(key, value);
        if (prev == NULL) {
            htable[index] = entry;
        }
        else {
            prev->next = entry;
        }
    }
    else {
        entry -> value = value;
    }
}

int HashMap::get(int key) {
    int index = hash(key);
    HashNode* entry = htable[index];
    while (entry != NULL) {
        if (entry->key == key) {
            return entry->value;
        }
        entry = entry -> next;
    }
    return -1;
}

void HashMap::remove(int key) {
    int index = hash(key);
    HashNode* entry = htable[index];
    HashNode* prev = NULL;
    while (entry != NULL && entry -> key!= key) {
        prev = entry;
        entry = entry -> next;
    }
    if (entry == NULL) {
        return;
    }
    else {
        if (prev == NULL) {
            htable[index] = entry -> next;
        }
        else {
            prev -> next = entry -> next;
        }
    }
}

HashMap::~HashMap() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* entry = htable[i];
        while (entry != NULL) {
            HashNode* prev = entry;
            entry = entry -> next;
            delete prev;
        }
    }
    delete[] htable;
}


int main() {
    HashMap map;
    map.insert(1,2);
    map.insert(132, 23);
    map.insert(263, 32);
    map.insert(2,231);
    map.insert(0, 43);
    
    cout << "The value of key 1 is " << map.get(1) << endl;
    cout << "The value of key 132 is " << map.get(132) << endl;
    
    map.insert(132, 44);
    cout << "The value of key 132 is " << map.get(132) << endl;
    
    cout << "Remove the value with key of 132 " << endl;
    map.remove(132);
    cout << "The value of key 132 is " << map.get(132) << endl;
    
    cout << "Remove the value with key of 1 " << endl;
    map.remove(1);
    cout << "The value of key 1 is " << map.get(1) << endl;
}