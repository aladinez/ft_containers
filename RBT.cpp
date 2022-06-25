#include "RBT.hpp"


int main()
{
    ft::RB_tree<int> tree;
    tree.insert(23);
    tree.insert(3);
    tree.insert(30);
    tree.insert(6);
    tree.insert(15);
    ft::Node<int>* zero = tree.insert(0);
    tree.insert(99);
    tree.insert(4);
    // tree.print();
    tree.print_tree();
    tree.left_rotate(zero);
}