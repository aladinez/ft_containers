#include <iostream>

typedef struct Node {
    Node* p;
    int key;
    Node* left;
    Node* right;
}Node;

class BS_tree
{
    private:
        Node* _root;
        void _print(Node* root)
        {
            if (root)
            {
                _print(root->left);
                std::cout << root->key << std::endl;
                _print(root->right);
            }
        }
    public:
        BS_tree (): _root() {
            // _root = new Node;
            // Node* r = new Node; //new node to insert
            // Node* l = new Node;
            // _root->left = l;
            // _root->right = r;
            // _root->key = 10;

            // r->p = l->p = _root;
            // r->key = 20;
            // l->key = 5;


            // r->left = r->right = nullptr;
            // l->left = l->right = nullptr;


        }
        void insert(int new_key)
        {
            Node* y = nullptr;
            Node* x = _root;
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
            Node* z = new Node; //new node to insert
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
        
};


int main()
{
    BS_tree tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(4);
    tree.insert(2);
    tree.print();

    return (0);
}