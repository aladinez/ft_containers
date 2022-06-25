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
            node* y = NULL;
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
            z->left = z->right = NULL;
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
        node* most_left()
        {
            node* x = _root;
            while (x->left)
                x = x->left;
            return x;
        }
        node* most_right()
        {
            node* x = _root;
            while (x->right)
                x = x->right;
            return x;
        }
        node* successor(value_type new_key)
        {
            node* x = search(new_key);
            if (x)
            {   
                if (x->right)
                    return _most_left(x->right);
                node* y = x->p;
                while (y && x == y->right)
                {
                    x = y;
                    y = y->p;
                }
                return y;
            }
            return x;
        }
        node* predecessor(value_type new_key)
        {
            node* x = search(new_key);
            if (x)
            {
                if (x->left)
                    return _most_right(x->left);
                node* y = x->p;
                while (y && x == y->left)
                {
                    x = y;
                    y = y->p;
                }
                return y;
            }
            return x;
        }
        void remove(node* z)
        {
            if (z)
            {
                if (!z->left)
                    _transplant(z, z->right);
                else if (!z->right)
                    _transplant(z, z->left);
                else
                {
                    node* y = _most_left(z->right); //successor of z;
                    if (y->p != z)
                    {
                        _transplant(y, y->right);
                        y->right = z->right;
                        y->right->p = y;
                    }
                    _transplant(z, y);
                    y->left = z->left;
                    y->left->p = y;
                }
                delete z;
            }
        }

        node* remove(int key)
        {
            node* z = search(key);
            if (z)
            {
                std::cout << z << std::endl;
                if (!z->left)
                    _transplant(z, z->right);
                else if (!z->right)
                    _transplant(z, z->left);
                else
                {
                    node* y = _most_left(z->right); //successor of z;
                    if (y->p != z)
                    {
                        _transplant(y, y->right);
                        y->right = z->right;
                        y->right->p = y;
                    }
                    _transplant(z, y);
                    y->left = z->left;
                    y->left->p = y;
                }
                delete z;
                // z = NULL;
            }
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
        node* _most_left(node* x)
        {
            while (x->left)
                x = x->left;
            return x;
        }
        node* _most_right(node* x)
        {
            while (x->right)
                x = x->right;
            return x;
        }
        // void _transplant(node* u, node* v)
        // {

        //     if (!u->p)
        //         _root = v;
        //     else if (u == u->p->left)
        //         u->p->left = v;
        //     else
        //         u->p->right = v;
        //     if (v)
        //         v->p = u->p;
        // }
        void _transplant(node* u, node* v)
        {
            if (v && u)
            {
                if (u->p == nullptr)
                    _root = v;
                else if (u == u->p->left)
                    u->p->left = v;
                else
                    u->p->right = v;
                if (v)
                    v->p = u->p;
            }
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
    tree.insert(15);
    tree.insert(0);
    tree.insert(99);
    tree.insert(4);
    // tree.print();
    tree.print_tree();

    BS_tree<int>::node* a = tree.search(3);
    BS_tree<int>::node* min = tree.most_left();
    BS_tree<int>::node* max = tree.most_right();
    std::cout << "min is : " << min->key << std::endl;
    std::cout << "max is : " << max->key << std::endl;

    BS_tree<int>::node* succ = tree.successor(23);
    BS_tree<int>::node* pred = tree.predecessor(23);
    if (succ)
        std::cout << "successor of " << 23 << " is : " << succ->key << std::endl;
    if (pred)
        std::cout << "predecessor of " << 23 << " is : " << pred->key << std::endl;
    std::cout << pred << std::endl;
    tree.remove(succ);
    std::cout << pred << std::endl;
    // tree.remove(succ);


    tree.print_tree();
    tree.print_tree();
    tree.left_rotate(pred);
    // tree.print();



    return (0);
}