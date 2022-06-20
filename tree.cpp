#include <iostream>
#include <stdio.h>


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
    

    public:
        typedef Node<T>     node;
        typedef T           value_type;
        BS_tree (): _root() {}
        void insert(value_type new_key)
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
        node* search(value_type new_key)
        {
            node* x = _root;
            while (x && x->key != new_key)
            {
                if (x->key < new_key)
                    x = x->right;
                else    
                    x = x->left;
            }
            return x;
        }
        value_type minimum()
        {
            node* x = _root;
            while (x->left)
                x = x->left;
            return x->key;
        }
        value_type maximum()
        {
            node* x = _root;
            while (x->right)
                x = x->right;
            return x->key;
        }
        value_type successor(value_type new_key)
        {
            node* x = search(new_key);
            if (x)
            {   
                if (x->right)
                    return _minimum(x->right);
                node* y = x->p;
                while (y && x == y->right)
                {
                    x = y;
                    y = y->p;
                }
                return y->key;
            }
            return 0;
        }
        value_type predecessor(value_type new_key)
        {
            node* x = search(new_key);

            if (x->left)
                return _maximum(x->left);
            node* y = x->p;
            while (y && x == y->left)
            {
                x = y;
                y = y->p;
            }
            return y->key;
        }

        void print_tree()
        {
            printTree(_root);
        }
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
        value_type _minimum(node* x)
        {
            while (x->left)
                x = x->left;
            return x->key;
        }
        value_type _maximum(node* x)
        {
            while (x->right)
                x = x->right;
            return x->key;
        }
};
int rec[1000006];
template <typename T>
void printTree(struct Node<T>* curr,int depth = 0)
{
    int i;
    if(!curr)return;
    printf("\t");
    for(i=0;i<depth;i++)
    {
        if(i==depth-1)
            printf("%s\u2014\u2014\u2014",rec[depth-1]?"\u0371":"\u221F");
        else
            printf("%s   ",rec[i]?"\u23B8":"  ");
    }
    printf("%d\n", curr->key);
    // std::cout << curr->key << std::endl;
    rec[depth]=1;
    printTree(curr->left,depth+1);
    rec[depth]=0;
    printTree(curr->right,depth+1);
}



int main()
{
    BS_tree<int> tree;
    tree.insert(23);
    tree.insert(3);
    tree.insert(30);
    tree.insert(6);
    // tree.print();
    tree.print_tree();

    BS_tree<int>::node* a = tree.search(3);
    std::cout << "min is : " << tree.minimum() << std::endl;
    std::cout << "max is : " << tree.maximum() << std::endl;
    // std::cout << "successor of " << 14 << " is : " << tree.successor(14) << std::endl;
    // std::cout << "predecessor of " << 14 << " is : " << tree.predecessor(14) << std::endl;

    return (0);
}