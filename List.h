#ifndef MAIN_CPP_LIST_H
#define MAIN_CPP_LIST_H

#include <iostream>
#include "Node.h"

template <class T>
class List {
private:
    Node<T>* head;
    int size;
public:
    List(int size = 0) : head(new Node<T>), size(size) {};
    ~List();
    void DeleteList();
    List(const List<T>& other);///need to implement
    List& operator=(const List<T>& other);///need to implement
    void InsertNode(const T& data);
    void RemoveNode(Node<T>* toDelete);
    Node<T>* FindNode(const T& data);
    int GetListSize() const;///maybe
    Node<T>* GetHead() const;
    void PrintList();

};

template <class T>
List<T>::~List() {
    this->DeleteList();
    delete head;
}

template <class T>
void List<T>::DeleteList() {
    Node<T>* toDelete = head->next;
    while (toDelete != nullptr) {
        Node<T>* curr = toDelete->next;
        RemoveNode(toDelete);
        toDelete = curr;
    }
    head->next = nullptr;
}

/*Node<T>* curr = head->next;
    Node<T>* temp = head->next;
    while(temp != nullptr){
        temp = temp->next;
        if(curr->data != nullptr){
            delete curr->data;
        }
        delete curr;
        curr = temp;
    }
    head->next = nullptr;*/

template <class T>
List<T>::List(const List<T>& other) : head(new Node<T>(head)), size(other.size) {
    Node<T>* oldList = other.head->next;
    Node<T>* newList = head;
    for (int i = 0; i < other.size; i++) {
        Node<T>* newNode = new Node<T>();
        T* newData = new T(*(oldList->data));
        newNode->data = newData;
        newNode->prev = newList;
        newNode->prev->next = newNode;
        if (oldList->next != nullptr) {
            oldList = oldList->next;
            newList = newList->next;
        }
        else {
            newList = newList->next;
            newList->next = nullptr;
        }
    }
}

template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this == &other) {
        return *this;
    }
    Node<T>* newList = new Node<T>();
    Node<T>* oldList = other.head->next;
    for (int i = 0; i < other.size; i++) {
        Node<T>* newNode = new Node<T>();
        T* newData = new T(*(oldList->data));
        newNode->data = newData;
        newNode->prev = newList;
        newNode->prev->next = newNode;
        if (oldList->next != nullptr) {
            oldList = oldList->next;
            newList = newList->next;
        }
        else {
            newList = newList->next;
            newList->next = nullptr;
        }
    }
    this->DeleteList();
    head = newList;
    size = other.size;
    return *this;
}

template <class T>
void List<T>::InsertNode(const T& data) {
    Node<T>* newNode = new Node<T>();
    newNode->data = new T(data);
    Node<T>* temp = head->next;
    head->next = newNode;
    newNode->next = temp;
    newNode->prev = head;
    if (size > 0) {
        temp->prev = newNode;
    }
    size += 1;
}

template <class T>
void List<T>::RemoveNode(Node<T>* toDelete) {
    toDelete->prev->next = toDelete->next;
    if (toDelete->next != nullptr) {
        toDelete->next->prev = toDelete->prev;
    }
    delete toDelete->data;
    delete toDelete;
    size -= 1;
}

template <class T>
Node<T>* List<T>::FindNode(const T& data) {
   

    Node<T>* curr = head->next;
    while (curr != nullptr) {
        if (*(curr->GetData()) == data) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

template <class T>
int List<T>::GetListSize() const {
    return this->size;
}

template<class T>
Node<T>* List<T>::GetHead() const {
    return head;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {
    Node<T>* curr = list.GetHead()->GetNext();
    int count = 0;
    int listSize = list.GetListSize();
    while (count != listSize) {
        os << *curr;
        curr = curr->GetNext();
        count++;
        if (count != listSize) {
            os << ", ";
        }
    }
    os << std::endl;
    return os;
}

#endif //MAIN_CPP_LIST_H
