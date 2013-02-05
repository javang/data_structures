
#include "base_types.h"
#include "string_func.h"
#include <stdexcept>
#include <functional>
#include <fstream>
#include <iostream>

#ifndef BINARY_TREE_H
#define BINARY_TREE_H


namespace dst {

template <typename T>
class TreeNode {

private:
    T value_;
    TreeNode<T> *right_;
    TreeNode<T> *left_;
    TreeNode<T> *parent_;
    
    void swap_pointer(TreeNode<T> *t, TreeNode<T> *p) {
        TreeNode<T> *temp = t;
        t = p;
        p = temp;
    }

public:
    TreeNode(T value, TreeNode *right=nullptr, TreeNode *left=nullptr):
         value_(value), right_(right), left_(left), parent_(nullptr) {}

    void delete_left() {
        delete right_;    
        right_ = nullptr;
    }
       
    void delete_right() {
        delete left_;
        left_ = nullptr;
    }

    void set_right(const T &value) {
        if(right_ != nullptr) delete_right();
        right_ = new TreeNode(value);
        right_->set_parent(this);
    }

    void set_right(TreeNode<T> *t) {
        if(right_ != nullptr) delete_right();
        right_ = t;
        right_->set_parent(this);
    }

    void set_parent(TreeNode <T> *t) {
        parent_ = t;
    }
    void set_left(const T &value) {
        if(left_ != nullptr) delete_left();
        left_ = new TreeNode(value);
        left_->set_parent(this);
    }

    void set_left(TreeNode<T> *t) {
        if(left_ != nullptr) delete_left();
        left_ = t;
        left_->set_parent(this);
    }

    void swap(TreeNode<T> *t) {
        std::swap(value_,t->value);
        swap_pointer(right_, t->right_);
        swap_pointer(left_, t->left_);
    }
    
    TreeNode<T> *left() {
        return left_;
    }

    TreeNode<T> *parent() {
        return parent_;
    }

    TreeNode<T> *right() {
        return right_;
    }

    T get_value() const { return value_; }
    
    bool is_leaf() const {
        if( left_ == nullptr && right_ == nullptr) return true;
        return false;
    }

    void add_child(TreeNode<T> *t) {
        if (left_ == nullptr) {
            set_left(t);
        } else if (right_ == nullptr) {
            set_right(t);
        } else {
            throw std::length_error("It is not possible to add more children");
        }
    }

    //! true if the node has two children already
    bool is_full() const {
        if (left_==nullptr ||right_==nullptr ) return false;
        return true;
    }

    void clear() {
        if(left_ != nullptr) {
            left_->clear(); 
            left_ = nullptr;
        }
        if(right_ != nullptr) {
            right_->clear(); 
            right_ = nullptr;
        }
    }
};
}

#endif
