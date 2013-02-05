
#include "base_types.h"
#include "string_func.h"
#include <stdexcept>
#include <functional>
#include <fstream>
#include <iostream>

#ifndef BASE_TYPES_H
#define BASE_TYPES_H


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

/*

struct Token {
private:
    double number_;
    bool is_number_;
    std::function<double(double, double)> binary_operation_;     

public:
    Token(const String &x) {
        is_number_ = false;
        if( x == "*") {
            binary_operation_ = std::multiplies<double>();
        } else if ( x == "/") {
            binary_operation_ = std::divides<double>();
        } else if( x == "-") {
            binary_operation_ = std::minus<double>();
        } else if( x == "+") {
            binary_operation_ = std::plus<double>();
        } else {
            number_ = std::stod(x);        
            is_number_ = true;
        }
    }

    double evaluate( double x, double y) {
        return binary_operation_(x,y);
    }

    double evaluate() {
        return number_;
    }
    
    bool is_number() const {
        return is_number_;
    } 
};



typedef dst::TreeNode<Token> TokenNode; 

TokenNode *build_tree(const Strings &words) {
    if(words.size() == 0) {
        throw std::length_error("There are no tokens to process");    
    }
    TokenNode *current = nullptr;
    TokenNode *root = nullptr;
    for (auto w: words) {
        Token token(w);
        TokenNode *node = new TokenNode(token);
        if(root == nullptr) {
            root = node;
            current = root;
        } else {
            while(current->is_full()) { 
                current = current->parent();
                if (current == nullptr) { // root
                    throw std::invalid_argument("Wrong expression");
                }
            }
            current->add_child(node);                    
            if( ! token.is_number()) {
                current = node;
            }
        }
    }
    return root;
}

double evaluate_expression(TokenNode *node) {
    if(node->is_leaf()) return node->get_value().evaluate();
    return node->get_value().evaluate(evaluate_expression(node->left()),
                                     evaluate_expression(node->right()) );
}

int main(int argc, char **argv) {
    using namespace std;

    if(argc != 2) {
        cout << "Parameters" << endl;
        cout << "[1] - Input file" << endl;
        exit(0);
    }


    std::ifstream f_in;
    f_in.open(argv[1]);
    if( ! f_in.good() ) {
        throw ios_base::failure("Error opening the file ");
    }

    String line = "";
    while(std::getline(f_in, line)) {
        if(line.empty()) continue;
        Strings words = split(line, ' ');
        TokenNode *node = build_tree(words);
        std::cout << evaluate_expression(node) << std::endl;
        node->clear();
    }
    exit(0);
}
*/
#endif
