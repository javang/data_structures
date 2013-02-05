#include "base_types.h"
#include "string_func.h"
#include <stdexcept>
#include <functional>
#include <fstream>
#include <iostream>


#ifndef LIST_H
#define LIST_H


namespace dst {

template <typename T>

struct ListNode {
    T value;
    ListNode *next;

    ListNode(): next(nullptr) {};
    ListNode(T v, ListNode *n): value(v), next(n) {}
};


template <typename T>
class List {


private:

    ListNode<T> *first_;
    ListNode<T> *last_;
    unsigned int size_;


   void check_index(unsigned int i) {
        if( i >= size_) throw std::out_of_range("Check index: Bad index");
    }

    ListNode<T> *previous(unsigned int i) {
        ListNode<T> *l = first_;
        for(unsigned int j = 0; j < i - 1; ++j)  l = l->next;
        return l;
    }

public:


    class iterator {
    private:
        ListNode<T> *current;

    public:
        iterator() {};
        iterator(ListNode<T> *p): current(p) {}

        void operator++() {
            current = current->next;
        }

        T &operator *() {
           return current->value;
        }

        bool operator ==(const iterator &x) const {
            return current == x.current;
        }

        bool operator !=(const iterator &x) const {
            return current != x.current;
        }

        T *operator ->() {
            return &(current->value);
        }
    };





    List(): first_(nullptr), last_(nullptr), size_(0) {};



    iterator begin() const {
        return iterator(first_);
    }

    iterator end() const {
        return iterator(last_->next);
    }

    bool empty() const {
        if(size_ == 0) return true;
        return false;
    }

    unsigned int size() const {
        return size_;
    }

    void push_back(const T &element) {
        ListNode<T> *l = new ListNode<T>(element, nullptr);
        if(empty()) {
            first_ = l;
        } else {
            last_->next = l;
        }
        last_ = l;
        size_++;
    }

    void push_front(const T &element) {
        ListNode<T> *l = new ListNode<T>(element, first_);
        first_ = l;
        size_++;
    }

    void insert(const T &element, unsigned int i) {
        check_index(i);
        if(empty()) {
            push_back(element);
        } else {
            ListNode<T> *l = previous(i);
            l->next = new ListNode<T>(element, l->next);
            size_++;
        }
    }

    void remove(unsigned int i) {
        check_index(i);
        if(i == 0) {
            ListNode<T> *temp = first_->next;
            delete first_;
            first_ = temp;
        } else {
            ListNode<T> *l = previous(i);
            if(i == size_ - 1 ) {
                last_ = l;
            }
            ListNode<T> *temp = l->next;
            l->next = l->next->next;
            delete temp;
        }
        size_--;
    }


    T &operator[](unsigned int i) {
        check_index(i);
        if(i == 0 ) return first_->value;
        ListNode<T> *l = previous(i);
        return (l->next->value);
    }

     ~List() {
        while( !empty()) {
            remove(0);
        }
     }

};

// Version using a dummy node as head. Simplifies all the "if" for the first member
template <typename T>
class List2 {

private:

    ListNode<T> *head_;
    ListNode<T> *tail_;
    unsigned int size_;


   void check_index(unsigned int i) {
        if( i >= size_) throw std::out_of_range("Check index: Bad index");
    }

    ListNode<T> *previous(unsigned int i) {
        check_index(i);
        ListNode<T> *l = head_;
        for(unsigned int j = 0; j < i; ++j)  l = l->next;
        return l;
    }

public:

    List2(): head_(new ListNode<T>()), tail_(head_), size_(0) {};


    bool empty() const {
        if(size_ == 0) return true;
        return false;
    }

    unsigned int size() const {
        return size_;
    }

    void push_back(const T &element) {
        tail_->next = new ListNode<T>(element, nullptr);
        tail_ = tail_->next;
        size_++;
    }

    void push_front(const T &element) {
        head_->next = new ListNode<T>(element,head_->next);
        size_++;
    }

    void insert(const T &element, unsigned int i) {
        ListNode<T> *l = previous(i);
        l->next = new ListNode<T>(element, l->next);
        size_++;
    }

    void remove(unsigned int i) {
        ListNode<T> *l = previous(i);
        if(i == size_ - 1 ) tail_ = l;
        ListNode<T> *temp = l->next;
        l->next = l->next->next;
        delete temp;
        size_--;
    }


    T &operator[](unsigned int i) {
        return (previous(i)->next->value);
    }

    void clear() {
        while( !empty()) remove(0);
    }

     ~List2() {
        clear();
     }

   class iterator {
    private:
        ListNode<T> *current;

    public:
        iterator() {};
        iterator(ListNode<T> *p): current(p) {}

        void operator++() { current = current->next;        }

        T &operator *() { return current->value;        }

        bool operator ==(const iterator &x) const {
            return current == x.current;
        }

        bool operator !=(const iterator &x) const {
            return current != x.current;
        }

        T *operator ->() {return &(current->value);
        }
    };

    iterator begin() const {
        return iterator(head_->next);
    }

    iterator end() const {
        return iterator(tail_->next);
    }

};

}

#endif
