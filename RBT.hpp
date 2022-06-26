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
        : left(l), right(r), p(p), color(c), key() {}
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
            void insert(value_type key)
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
                insert_fixup(z);
            }

            void insert_fixup(node* z)
            {
                while (z->p->color == RED) // violation cuz both z and z.p are red
                {
                    if (z->p == z->p->p->left)
                    {
                        node* y = z->p->p->right; // y is uncle of z
                        if (y->color == RED) // uncle is red, recolor z.p and y
                        {
                            z->p->color = BLACK;
                            y->color = BLACK;
                            z->p->p->color = RED; //recolor z.p.p and recheck.
                            z = z->p->p; // next loop z will be z.p.p
                        }
                        else // uncle is black => rotate and recolor
                        {
                            if (z == z->p->right) // z in the right of its parent, so we will left rotate z.p
                            {
                                z = z->p;
                                left_rotate(z);
                            }
                            z->p->color = BLACK; // loop will stop after this.
                            z->p->p->color = RED;
                            right_rotate(z->p->p);
                        }
                    }
                    else
                    {
                        node* y = z->p->p->left;
                        if (y->color == RED)
                        {
                            z->p->color = BLACK;
                            y->color = BLACK;
                            z->p->p->color = RED;
                            z = z->p->p;
                        }
                        else
                        {
                            if (z == z->p->left)
                            {
                                z = z->p;
                                right_rotate(z);
                            }
                            z->p->color = BLACK;
                            z->p->p->color = RED;
                            left_rotate(z->p->p);
                        }
                    }
                }
                _root->color = BLACK;
            }

            // void remove(value_type key)
            // {
            //     node* z = search(key);
            //     node* y = z;
            //     node* x = _NIL;
            //     bool o_color = y->color;
            //     if (z->left == _NIL) // z has only right child
            //     {
            //         x = z->right;
            //         _transplant(z, z->right);
            //     }
            //     else if (z->right == _NIL) // z has only left child
            //     {
            //         x = z->left;
            //         _transplant(z, z->left);
            //     }
            //     else
            //     {
            //         y = _most_left(z->right); // successor
            //         o_color = y->color;
            //         x = y->right;
            //         if ()
            //     }


            // }
            void print_tree()
            {
                printTree(_root);
            }
        private:
            node* _root;
            node* _NIL;
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
            void _transplant(node* u, node* v)
            {
                if (u->p == _NIL)
                    _root = v;
                else if (u == u->p->left)
                    u->p->left = v;
                else
                    u->p->right = v;
                v->p = u->p;
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
        
}