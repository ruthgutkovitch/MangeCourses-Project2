#ifndef MAIN_CPP_NODE_H
#define MAIN_CPP_NODE_H

template <class T>
class List;

template <class T>
class Node {
private:
    T* data;
    Node* prev;
    Node* next;
public:
    Node() : data(nullptr), prev(nullptr), next(nullptr){};
    ~Node() = default;
    Node(const Node<T>& other) = default;
    Node& operator=(const Node<T>& other) = default;
    //T* GetData();///maybe to delete
    T* GetData() const;
    Node* GetNext() const;
    Node* GetPrev() const;
    int GetKey() const;
    friend class List<T>;
};

/*template <class T>
T* Node<T>::GetData(){
    return this->data;
}*/

template <class T>
T* Node<T>::GetData() const{
    return this->data;
}

template<class T>
Node<T> *Node<T>::GetNext() const {
    return next;
}

template<class T>
Node<T> *Node<T>::GetPrev() const {
    return prev;
}

template<class T>
int Node<T>::GetKey() const {
    return this->data->GetKey();
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Node<T>& node){
    os << *(node.GetData());
    return os;
}


#endif //MAIN_CPP_NODE_H
