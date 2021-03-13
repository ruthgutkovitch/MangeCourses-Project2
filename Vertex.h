#ifndef MAIN_CPP_VERTEX_H
#define MAIN_CPP_VERTEX_H

template <class T>
class RankTree;

template <class T>
class Vertex{
private:
    T* data;
    Vertex* leftSon;
    Vertex* rightSon;
    Vertex* father;
    int height;
    int rank;

public:
    explicit Vertex(): data(nullptr), leftSon(nullptr), rightSon(nullptr), father(nullptr), height(0), rank(1){};
    ~Vertex() = default;
    Vertex(const Vertex<T>& other);
    Vertex& operator=(const Vertex<T>& other);
    T* GetData();
    T* GetData() const;
    int GetVertexHeight() const;
    int GetRank() const;
    friend class RankTree<T>;
};

// compare two vertex
template <class T>
bool operator>(const Vertex<T>& v1, const Vertex<T>& v2) {
    if (v1.GetData() > v2.GetData()){
        return true;
    }
    return false;
}


// compare two vertex
template <class T>
bool operator<(const Vertex<T>& v1, const Vertex<T>& v2){
    if (v1.GetData() < v2.GetData()){
        return true;
    }
    return false;

}

// check if two vertex are equal
template <class T>
bool operator==(const Vertex<T>& v1, const Vertex<T>& v2) {
    if (v1.GetData() == v2.GetData()){
        return true;
    }
    return false;

}

// return height
template<class T>
int Vertex<T>::GetVertexHeight() const {
    return this->height;
}

template<class T>
int Vertex<T>::GetRank() const {
    return this->rank;
}

// return pointer to data
template <class T>
T* Vertex<T>::GetData(){
    return this->data;
}

// return pointer to data - the function is const
template<class T>
T* Vertex<T>::GetData() const {
    return this->data;
}

// copy constructor
template<class T>
Vertex<T>::Vertex(const Vertex<T> &other) : data(other.data), leftSon(other.leftSon),
                                            rightSon(other.rightSon), father(other.father), height(other.height), rank(other.rank){
}

// operator assignment
template<class T>
Vertex<T>& Vertex<T>::operator=(const Vertex<T> &other) {
    if(this == &other){
        return *this;
    }
    data = other.data;
    leftSon = other.leftSon;
    rightSon = other.rightSon;
    father = other.father;
    height = other.height;
    rank = other.rank;
    return *this;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Vertex<T>& vertex){
    os << *(vertex.GetData()) << " height: " << vertex.GetVertexHeight() << " , " << "rank: " << vertex.GetRank() << std::endl;
    return os;
}


#endif //MAIN_CPP_VERTEX_H
