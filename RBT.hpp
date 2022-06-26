#include <iostream>
#include <stdio.h>

#define RED 0
#define BLACK 1

namespace ft
{
    template <typename T>
    struct Node {
        T key;
        bool color;
        Node* p;
        Node* left;
        Node* right;
        Node(Node* l = NULL, Node* r = NULL, Node* p = NULL, bool c = BLACK)
        : left(l), right(r), p(p), color(c) {}
    };

    template <class T>
    class RB_tree
    {
        public:
            typedef Node<T>     node;
            typedef T           value_type;
            RB_tree (): _NIL(new node) {_root = _NIL;}
            node* search(value_type new_key)
            {
                node* x = _root;
                while (x != _NIL && x->key != new_key)
                {
                    if (x->key < new_key)
                        x = x->right;
                    else    
                        x = x->left;
                }
                return x;
            }
            void left_rotate(node* x)
            {
                node* y = x->right;
                x->right = y->left;
                if (y->left != _NIL)
                    y->left->p = x;
                y->p = x->p;
                if (x->p == _NIL)
                    _root = y;
                else if (x == x->p->left)
                    x->p->left = y;
                else
                    x->p->right = y;
                y->left = x;
                x->p = y;
            }
            void right_rotate(node* x)
            {
                node* y = x->left;
                x->left = y->right;
                if (y->right != _NIL)
                    y->right->p = x;
                y->p = x->p;
                if (x->p == _NIL)
                    _root = y;
                else if (x == x->p->left)
                    x->p->left = y;
                else
                    x->p->right = y;
                y->right = x;
                x->p = y;
            }
            node* _newNode(value_type key)
            {
                node* z = new node(_NIL, _NIL, _NIL, RED);
                z->key = key;
                return z;
            }
            node* insert(value_type key)
            {
                node* z = _newNode(key);
                node* y = _NIL;
                node* x = _root;
                while (x != _NIL)
                {
                    y = x;
                    if (z->key < x->key)
                        x = x->left;
                    else 
                        x = x->right;
                }
                z->p = y;
                if (y == _NIL)
                    _root = z;
                else if (z->key < y->key)
                    y->left = z;
                else 
                    y->right = z;
                return z;
            }
            void print_tree()
            {
                printTree(_root);
            }
        private:
            node* _root;
            node* _NIL;
    
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
        
}