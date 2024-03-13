#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include<iostream>

template<typename T>
class cfdVector
{
private:
    int dim;
    std::unique_ptr<std::vector<T>> vecPtr;
public:
    cfdVector(int dim);
    T& operator[](int i);
    const T& operator[](int i) const;
    void setValue(std::vector<T> &&data);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const cfdVector<U>&vec);
};


template<typename T>
cfdVector<T>::cfdVector(int dim){
    this->dim = dim;
    this->vecPtr = std::make_unique<std::vector<T>>(dim);
}

template<typename T>
T& cfdVector<T>::operator[](int i){
    return (*vecPtr)[i];
}

template<typename T>
const T & cfdVector<T>::operator[](int i) const{
    return (*vecPtr)[i];
}



template<typename T>
void cfdVector<T>::setValue(std::vector<T> &&data){
    assert(data.size() == this->dim);
    vecPtr = std::make_unique<std::vector<T>>(data);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const cfdVector<T>&vec){
    for(int i = 0; i < vec.dim - 1; i++){
        os << (*vec.vecPtr)[i]<< ", ";
    }
    os << (*vec.vecPtr)[vec.dim - 1] ;
    return os;
}