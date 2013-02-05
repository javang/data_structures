
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
