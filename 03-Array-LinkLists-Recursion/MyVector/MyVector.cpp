#include "MyVector.h"

template <typename T>
MyVector<T>::MyVector() {
    sz = 0;
    base = 1;
    array = new T[base];
}

template <typename T>
MyVector<T>::MyVector(uint32_t size) {
    sz = 0;
    base = 1;
    resize(size);
}

template <typename T>
MyVector<T>::MyVector(uint32_t size, T val) {
    sz = 0;
    base = 1;
    resize(size);
    for(int i{0}; i < size; ++i) {
        array[i] = val;
    }
}

template <typename T>
void MyVector<T>::resize(uint32_t size) {
    if(base >= size) {
        sz = size;
        return;
    }
    
    while(base < size) {
        base <<= 1;
    }

    T *tp = new T[base];
    for(int i{0}; i < sz; ++i) {
        tp[i] = array[i];
    }
    sz = size;
    delete array;
    array = tp;
}

template <typename T>
T& MyVector<T>::operator[](uint32_t index) {
    return array[index];
}

template <typename T>
void MyVector<T>::push_back(T val) {
    uint32_t push{sz};
    resize(sz + 1);
    array[sz] = val;
}

template <typename T>
void MyVector<T>::pop_back() {
    resize(sz - 1);
}

template <typename T>
void MyVector<T>::rebase(uint32_t length) {
    if(length < size) {
        resize(length);
    }
    base = length;
}

template <typename T>
void MyVector<T>::insert(uint32_t index, T val) {
    resize(sz + 1);
    for(int i{sz}; i >= index; --i) {
        array[i] = array[i - 1];
    }
    array[index] = val;
}

template <typename T>
void MyVector<T>::erase(uint32_t index) {
    for(uint32_t i{index}; i < sz; ++i) {
        array[i] = array[i + 1];
    }
    resize(sz - 1);
}

template <typename T>
bool MyVector<T>::empty() {
    return sz == 0;
}

template <typename T>
uint32_t MyVector<T>::size() {
    return sz;
}

template <typename T>
T* MyVector<T>::begin() {
    return array;
}

template <typename T>
T* MyVector<T>::end() {
    return array + sz;
}

