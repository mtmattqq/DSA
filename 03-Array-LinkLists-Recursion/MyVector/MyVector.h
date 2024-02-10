#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <cstdint>
#include <cassert>
#include <stdexcept>
template <typename T>
class MyVector {
public :
    MyVector();
    MyVector(uint32_t);
    MyVector(uint32_t, T);
    MyVector(MyVector&);
    ~MyVector();

    T& operator[](uint32_t);
    void push_back(T);
    void pop_back();
    void resize(uint32_t);
    void rebase(uint32_t);
    void insert(uint32_t, T);
    void erase(uint32_t);

    bool empty();
    uint32_t size() const;
    T* begin();
    T* end();
    T& front();
    T& back();
    void operator=(MyVector&);

private :
    T *array;
    uint32_t sz, base;
};

template <typename T>
MyVector<T>::MyVector() {
    sz = 0;
    base = 16;
    array = new T[base];
}

template <typename T>
MyVector<T>::MyVector(uint32_t size) {
    sz = 0;
    base = 16;
    array = new T[base];
    resize(size);
}

template <typename T>
MyVector<T>::MyVector(uint32_t size, T val) {
    sz = 0;
    base = 16;
    array = new T[base];
    resize(size);
    for(int i{0}; i < size; ++i) {
        array[i] = val;
    }
}

template <typename T>
MyVector<T>::MyVector(MyVector &vec) {
    sz = vec.sz;
    base = vec.base;
    array = new T[base];
    for(int i{0}; i < sz; ++i) {
        array[i] = vec[i];
    }
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] array;
}

template <typename T>
void MyVector<T>::resize(uint32_t size) {
    if(base >= size) {
        for(int i{int(std::min(sz, size))}; i < std::max(sz, size); ++i) {
            array[i] = 0;
        }
        sz = size;
        return;
    }
    
    while(base <= size) {
        base <<= 1;
    }
    assert(base >= size);

    T *tp = new T[base];
    for(int i{0}; i < sz; ++i) {
        tp[i] = array[i];
    }
    for(int i{int(sz)}; i < base; ++i) {
        tp[i] = 0;
    }
    sz = size;
    delete[] array;
    array = tp;
}

template <typename T>
T& MyVector<T>::operator[](uint32_t index) {
    if(index >= sz) 
        throw std::out_of_range(
            "Error: index out of range: expect index < " + std::to_string(sz) + ", found " + std::to_string(index) + " (MyVector)");
    return array[index];
}

template <typename T>
void MyVector<T>::push_back(T val) {
    uint32_t push{sz};
    resize(sz + 1);
    assert(push + 1 == sz);
    array[push] = val;
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
    for(int i{sz - 1}; i >= index; --i) {
        array[i] = array[i - 1];
    }
    array[index] = val;
}

template <typename T>
void MyVector<T>::erase(uint32_t index) {
    for(uint32_t i{index}; i < sz - 1; ++i) {
        array[i] = array[i + 1];
    }
    resize(sz - 1);
}

template <typename T>
bool MyVector<T>::empty() {
    return sz == 0;
}

template <typename T>
uint32_t MyVector<T>::size() const {
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

template <typename T>
T& MyVector<T>::front() {
    return array[0];
}

template <typename T>
T& MyVector<T>::back() {
    return array[sz - 1];
}

template <typename T>
void MyVector<T>::operator=(MyVector &vec) {
    sz = vec.sz;
    base = vec.base;
    array = new T[base];
    for(int i{0}; i < sz; ++i) {
        array[i] = vec[i];
    }
}

#endif