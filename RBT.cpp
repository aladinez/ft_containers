#include "RBT.hpp"


int main()
{
    ft::RB_tree<int> tree;
    tree.insert(23);
    tree.insert(3);
    tree.insert(30);
    // tree.insert(6);
    // tree.insert(15);
    // ft::Node<int>* zero = tree.insert(0);
    // tree.insert(99);
    // tree.insert(4);
    tree.print_tree();
    ft::Node<int>* s = tree.search(23);
    std::cout << s->key << std::endl;
    tree.left_rotate(s);
    tree.print_tree();
    s = tree.search(30);
    std::cout << s->key << std::endl;

    tree.right_rotate(s);
    tree.print_tree();
    
}