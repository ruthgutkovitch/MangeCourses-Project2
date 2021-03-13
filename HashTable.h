#ifndef MAIN_CPP_HASHTABLE_H
#define MAIN_CPP_HASHTABLE_H

#include "List.h"


template<class T>
class HashTable {
private:
    int size;
    int numOfElements;
    List<T>** table;
public:
    explicit HashTable(int size = 1, int numOfElements = 0) : size(size), numOfElements(numOfElements), table(new List<T>* [size]) {
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    };

    ~HashTable();

    void DeleteTable();

    HashTable(const HashTable& other);

    HashTable& operator=(const HashTable& other);

    HashTable* InsertToTable(const T& data);

    HashTable* RemoveFromTable(Node<T>* node);

    void InsertToList(const T& data);///will increase size of array if needed
    void RemoveFromList(Node<T>* node); ///will reduce size of array if needed
    Node<T>* Find(const T& data);

    int GetTableSize() const;
    List<T>* GetPtrList(int index) const;

    int HashFunc(int i, int tableSize) {
        return i % tableSize;
    }
};

template <class T>
HashTable<T>::~HashTable() {
    DeleteTable();
    delete[] table;
}

template <class T>
void HashTable<T>::DeleteTable() {
    for (int i = 0; i < size; i++) {
        if (table[i] != nullptr) {
            delete table[i];
        }
    }
}

template <class T>
HashTable<T>::HashTable(const HashTable& other) : size(other.size), numOfElements(other.numOfElements), table(new List<T>* [other.size]) {

    for (int i = 0; i < other.size; i++) {
        if (other.table[i] != nullptr) {
            List<T>* newList = new List<T>;
            *newList = *(other.table[i]);
            table[i] = newList;
        }
        else {
            table[i] = nullptr;
        }
    }

}

template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& other) {
    if (this == &other) {
        return *this;
    }
    List<T>** newTable = new List<T> * [other.size];
    for (int i = 0; i < other.size; i++) {
        if (other.table[i] != nullptr) {
            List<T>* newList = new List<T>;
            *newList = *(other.table[i]);
            newTable[i] = newList;
        }
        else {
            newTable[i] = nullptr;
        }
    }
    this->DeleteTable();
    delete[]table;
    table = newTable;
    size = other.size;
    numOfElements = other.numOfElements;
    return *this;
}

template <class T>
HashTable<T>* HashTable<T>::InsertToTable(const T& data) {
    InsertToList(data);
    numOfElements += 1;
    if (numOfElements == size) {
        List<T>** newTable = new List<T> * [2 * size];
        for (int i = 0; i < 2 * size; i++) {
            newTable[i] = nullptr;
        }
        for (int i = 0; i < size; i++) {
            if (table[i] != nullptr) {
                int sizeList = table[i]->GetListSize();
                Node<T>* currNode = table[i]->GetHead()->GetNext();///beacuse first is dummy element
                for (int j = 0; j < sizeList; j++) {
                    int key = currNode->GetKey();
                    int newIndex = HashFunc(key, 2 * size);
                    if (newTable[newIndex] == nullptr) {
                        List<T>* newList = new List<T>;
                        newTable[newIndex] = newList;
                    }
                    newTable[newIndex]->InsertNode(*(currNode->GetData()));
                    currNode = currNode->GetNext();
                }
            }
        }
        this->DeleteTable();
        delete[]table;
        table = newTable;
        size = 2 * size;
    }
    return this;
}

template <class T>
HashTable<T>* HashTable<T>::RemoveFromTable(Node<T>* node) {
    RemoveFromList(node);
    numOfElements -= 1;
    if (size != 1) {
        if (numOfElements <= 0.25 * size) {
            List<T>** newTable = new List<T> * [size / 2];
            for (int i = 0; i < 0.5 * size; i++) {
                newTable[i] = nullptr;
            }
            for (int i = 0; i < size; i++) {
                if (table[i] != nullptr) {
                    int sizeList = table[i]->GetListSize();
                    Node<T>* currNode = table[i]->GetHead()->GetNext();///beacuse first is dummy element
                    for (int j = 0; j < sizeList; j++) {
                        int key = currNode->GetKey();
                        int newIndex = HashFunc(key, size / 2);
                        if (newTable[newIndex] == nullptr) {
                            List<T>* newList = new List<T>;
                            newTable[newIndex] = newList;
                        }
                        newTable[newIndex]->InsertNode(*(currNode->GetData()));
                        currNode = currNode->GetNext();
                    }
                }
            }
            this->DeleteTable();
            delete[]table;
            table = newTable;
            size = 0.5 * size;
        }
    }
    return this;
}

///will increase size of array if needed
template <class T>
void HashTable<T>::InsertToList(const T& data) {
    int key = data.GetKey();
    int index = HashFunc(key, size);
    if (table[index] == nullptr) {
        List<T>* newList = new List<T>;
        table[index] = newList;
    }
    table[index]->InsertNode(data);
}

///will reduce size of array if needed
template <class T>
void HashTable<T>::RemoveFromList(Node<T>* node) {
    int key = node->GetKey();
    int index = HashFunc(key, size);
    table[index]->RemoveNode(node);
}

template <class T>
Node<T>* HashTable<T>::Find(const T& data) {
    int key = data.GetKey();
    int index = HashFunc(key, size);
    if (table[index] != nullptr) {
        return table[index]->FindNode(data);
    }
    return nullptr;
}

template<class T>
int HashTable<T>::GetTableSize() const {
    return size;
}

template<class T>
List<T>* HashTable<T>::GetPtrList(int index) const {
    return table[index];
}

template <class T>
std::ostream& operator<<(std::ostream& os, const HashTable<T>& ht) {
    for (int i = 0; i < ht.GetTableSize(); i++) {
        if (ht.GetPtrList(i) == nullptr) {
            os << "table[" << i << "] is empty" << std::endl;
        }
        else {
            if (ht.GetPtrList(i)->GetListSize() != 0) {
                os << *(ht.GetPtrList(i));
            }
            else {
                os << "table[" << i << "] is empty" << std::endl;
            }
        }
    }
    return os;
}

#endif //MAIN_CPP_HASHTABLE_H
