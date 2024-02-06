#ifndef LINKLIST_H
#define LINKLIST_H

#include <vector>

namespace List {
    template <typename T>
    struct Node {
        T val;
        Node *prev, *next;

        Node() {prev = next = nullptr;}
        Node(T v) {
            val = v;
            prev = next = nullptr;
        }
    };
};

using namespace List;

template <typename T>
class LinkList {
public :
    LinkList();
    ~LinkList();

    void insert(Node<T> *now, T val);
    void erase(Node<T> *now);

    Node<T>* begin();
    Node<T>* next(Node<T>*);
    Node<T>* prev(Node<T>*);
    Node<T>* end();

    Node<T>& front();
    Node<T>& back();
    
private :
    Node<T> *head, *tail;
    std::vector<Node<T>*> node;
};

template <typename T>
LinkList<T>::LinkList() {
    head = tail = nullptr;
}

template <typename T>
LinkList<T>::~LinkList() {
    for(int i{0}; i < node.size(); ++i) {
        delete(node[i]);
    }
}

template <typename T>
void LinkList<T>::insert(Node<T> *now, T val) {
    Node<T> *new_node = new Node<T>(val);
    node.push_back(new_node);
    if(head == nullptr) {
        head = tail = new_node;
        return;
    }

    Node<T> *left, *right;
    left = now;
    right = now->next;

    if(left == nullptr)
        head = new_node;
    if(right == nullptr)
        tail = new_node;

    if(left != nullptr)
        left->next = new_node;
    new_node->prev = left;
    if(right != nullptr)
        right->prev = new_node;
    new_node->next = right;
}

template <typename T>
void LinkList<T>::erase(Node<T> *now) {
    if(now == nullptr)
        return;

    Node<T> *left, *right;
    left = now->prev;
    right = now->next;

    if(left != nullptr)
        left->next = right;
    else
        head = right;

    if(right != nullptr) 
        right->prev = left;
    else 
        tail = left;
}

template <typename T>
Node<T>* LinkList<T>::begin() {
    return head;
}

template <typename T>
Node<T>* LinkList<T>::next(Node<T> *now) {
    return now != nullptr ? now->next : nullptr;
}

template <typename T>
Node<T>* LinkList<T>::prev(Node<T> *now) {
    return now != nullptr ? now->prev : nullptr;
}

template <typename T>
Node<T>* LinkList<T>::end() {
    return nullptr;
}

template <typename T>
Node<T>& LinkList<T>::front() {
    return *head;
}

template <typename T>
Node<T>& LinkList<T>::back() {
    return *tail;
}

#endif