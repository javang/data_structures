
#include <iostream>
#include <stdexcept>

namespace dst {

template <typename T>

struct StackNode {
    T value;
    StackNode *previous;

    StackNode(): previous(nullptr) {};
    StackNode(T v, StackNode *n): value(v), previous(n) {}
};


template <typename T>
class Stack {

private:

    StackNode<T> *last_;
    unsigned int size_;

public:

    Stack(): last_(nullptr), size_(0) {};

    //! Check if the stack is empty
    bool empty() const {
        if(size_ == 0) return true;
        return false;
    }

    //! Return the number of elements in the stack;
    unsigned int size() const {
        return size_;
    }

    //! Push an element into the stack
    void push(const T &element) {
        StackNode<T> *l = new StackNode<T>(element, last_);
        last_ = l;
        size_++;
    }

    //! Pop the last element of the stack
    T pop() {

        if( ! empty() ) {
            StackNode<T> *temp = last_;
            T value = last_->value;
            last_ = last_->previous;
            delete temp;
            size_--;
            return value;
        } else {
            throw std::out_of_range("Check index: Bad index");
        }
    }

    //! clear the stack
    void clear() {
        while( !empty()) pop();
    }

     ~Stack() {
        clear();
     }

};

}
