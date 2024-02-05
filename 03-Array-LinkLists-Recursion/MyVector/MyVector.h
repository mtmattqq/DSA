#include <cstdint>

template <typename T>
class MyVector {
public :
    MyVector();
    MyVector(uint32_t);
    MyVector(uint32_t, T);

    T& operator[](uint32_t);
    void push_back(T);
    void pop_back();
    void resize(uint32_t);
    void rebase(uint32_t);
    void insert(uint32_t, T);
    void erase(uint32_t);

    bool empty();
    uint32_t size();
    T* begin();
    T* end();

private :
    T *array;
    int sz, base;
};