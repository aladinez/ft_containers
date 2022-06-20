#include <iostream>


template <typename T>
struct Node {
    Node* p;
    T key;
    Node* left;
    Node* right;
};

template <class T>
class BS_tree
{
    typedef Node<T> node;
    private:
        node* _root;
        void _print(node* root)
        {
            if (root)
            {
                _print(root->left);
                std::cout << root->key << std::endl;
                _print(root->right);
            }
        }
    public:
        BS_tree (): _root() {}
        void insert(T new_key)
        {
            node* y = nullptr;
            node* x = _root;
            while (x)
            {
                y = x;
                if (new_key < x->key)
                    x = x->left;
                else if (new_key > x->key)
                    x = x->right;
                else // TO NOT INSERT DUPPLICATE
                    return;
            }
            node* z = new node; //new node to insert
            z->key = new_key;
            z->p = y;
            z->left = z->right = nullptr;
            if (!y)
                _root = z; // empty tree;
            else if (z->key < y->key)
                y->left = z;
            else
                y->right = z;
        }
        void print() {_print(_root);}
        node* search(int new_key);   
};


int main()
{
    BS_tree<char> tree;
    tree.insert('q');
    tree.insert('b');
    tree.insert('a');
    tree.insert('z');
    tree.print();

    return (0);
}