#pragma once

#include <iostream>
#include <stdio.h>
#include <memory>
#include "pair.hpp"

#define RED 0
#define BLACK 1

#define _RED     "\x1b[31m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

namespace ft
{
	template <typename T>
	struct Node {
		T key;
		bool color;
		Node* p;
		Node* left;
		Node* right;
		Node(Node* l = NULL, Node* r = NULL, Node* p = NULL, bool c = BLACK, T k = T())
		: left(l), right(r), p(p), color(c), key(k) {}
	};

	template <class Pair, class Compare, class Allocator = std::allocator<Pair> >
	class RB_tree
	{
		public:
			typedef Node<Pair>		node;
			typedef Pair				value_type;
			typedef typename Allocator::size_type			size_type;
			typedef typename Allocator::template rebind<node>::other _Allocator;
			
			// RB_tree (): _NIL(new node), _comp() {_root = _NIL;}
			RB_tree(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			:_alloc(alloc), _comp(comp), _size() 
			{
				_NIL = _alloc.allocate(1);
				_alloc.construct(_NIL, node());
				_root = _NIL;
			}
			//copy constructor
			RB_tree (const RB_tree& rbt): _alloc(rbt._alloc), _comp(rbt._comp) {
				_NIL = _alloc.allocate(1);
				_alloc.construct(_NIL, node());
				_root = _makeCopy(rbt._root, rbt._NIL);
				_size = rbt._size;
			}
			~RB_tree ()
			{
				clear(_root);
				delete_node(_NIL);
			}
			// Copy assignment
			RB_tree& operator= (const RB_tree& rbt)
			{
				clear(_root);
				_comp = rbt._comp;
				_root = _makeCopy(rbt._root, rbt._NIL);
				_size = rbt._size;
				return *this;
			}
			node* search(value_type new_key)
			{
				node* x = _root;
				// while (x != _NIL && x->key != new_key) // TODO: COMPARE USING _comp
				while (x != _NIL && (_comp(x->key, new_key) || _comp(new_key, x->key))) // TODO: COMPARE USING _comp
				{
					//if (x->key < new_key) 
					if (_comp(x->key, new_key))
						x = x->right;
					else    
						x = x->left;
				}
				return x;
			}
			//
			value_type* val_search(value_type new_key)
			{
				node* x = _root;
				// while (x != _NIL && x->key != new_key) // TODO: COMPARE USING _comp
				while (x != _NIL && (_comp(x->key, new_key) || _comp(new_key, x->key))) // TODO: COMPARE USING _comp
				{
					//if (x->key < new_key) 
					if (_comp(x->key, new_key))
						x = x->right;
					else    
						x = x->left;
				}
				return &(x->key);
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

				// node* z = new node(_NIL, _NIL, _NIL, RED);
				node* z = _alloc.allocate(1);
				_alloc.construct(z, node(_NIL, _NIL, _NIL, RED, key));
				// z->key = key;
				return z;
			}
			void delete_node(node* x)
			{
				_alloc.destroy(x);
				_alloc.deallocate(x, 1);
			}

			void clear(node* x)
			{
				if (x == _NIL)
					return;
				clear(x->left);
				clear(x->right);
				delete_node(x);
			}
			void insert(value_type key)
			{
				node* z = _newNode(key);
				node* y = _NIL;
				node* x = _root;
				while (x != _NIL)
				{
					y = x;
					// if (z->key < x->key)
					if (_comp(z->key, x->key))
						x = x->left;
					else 
						x = x->right;
				}
				z->p = y;
				if (y == _NIL)
					_root = z;
				// else if (z->key < y->key)
				else if (_comp(z->key, y->key))
					y->left = z;
				else 
					y->right = z;
				insert_fixup(z);
				_size++;
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

			void remove(value_type key)
			{
				node* z = search(key);
				if (z != _NIL)
				{
					node* y = z;
					node* x = _NIL;
					bool o_color = y->color;
					if (z->left == _NIL) // z has only right child
					{
						x = z->right;
						_transplant(z, z->right);
					}
					else if (z->right == _NIL) // z has only left child
					{
						x = z->left;
						_transplant(z, z->left);
					}
					else
					{
						y = _most_left(z->right); // successor of z
						o_color = y->color;
						x = y->right;
						if (y->p == z)
							x->p = y;
						else
						{
							_transplant(y, y->right);
							y->right = z->right;
							y->right->p = y;
						}
						_transplant(z, y);
						y->left = z->left;
						y->left->p = y;
						y->color = z->color;
					}
					delete_node(z);
					if (o_color == BLACK)
						remove_fixup(x);
					_size--;
				}
			}
			void remove_fixup(node* x)
			{
				node* w;
				while (x != _root && x->color == BLACK)
				{
					if (x == x->p->left) 
					{
						w = x->p->right; // z is x's sibling
						if (w->color == RED) // case 1
						{
							w->color = BLACK;
							x->p->color = RED;
							left_rotate(x->p);
							w = x->p->right;
						}
						if (w->left->color == BLACK && w->right->color == BLACK) // case 2
						{
							w->color = RED;
							x = x->p;
						}
						else // case 3 and 4
						{
							if (w->right->color == BLACK) // case 3
							{
								w->left->color = BLACK;
								w->color = RED;
								right_rotate(w);
								w = x->p->right;
							}
							w->color = x->p->color;
							x->p->color = BLACK;
							w->right->color = BLACK;
							left_rotate(x->p);
							x = _root; // to end the loop.
						}
					}
					else
					{
						w = x->p->left; // z is x's sibling
						if (w->color == RED) // case 1
						{
							w->color = BLACK;
							x->p->color = RED;
							right_rotate(x->p);
							w = x->p->left;
						}
						if (w->right->color == BLACK && w->left->color == BLACK) // case 2
						{
							w->color = RED;
							x = x->p;
						}
						else // case 3 and 4
						{
							if (w->left->color == BLACK) // case 3
							{
								w->right->color = BLACK;
								w->color = RED;
								left_rotate(w);
								w = x->p->left;
							}
							w->color = x->p->color;
							x->p->color = BLACK;
							w->left->color = BLACK;
							right_rotate(x->p);
							x = _root; // to end the loop.
						}
					}
				}
				x->color = BLACK;
			}
			node* maximum()
			{
				return _most_right(_root);
			}
			node* minimum()
			{
				return _most_left(_root);
			}
			node* get_root() {return _root;}
			node* get_nil() {return _NIL;}
			size_type size() const {return _size;}
			void print_tree()
			{
				printTree(_root);
			}
		private:
			node* _root;
			node* _NIL;
			Compare _comp;
			_Allocator _alloc;
			size_type _size;
			
			

			node* _makeCopy(node* x, node* nil)
			{
				if (x == nil)
					return _NIL;
				node* new_node = _alloc.allocate(1);
				_alloc.construct(new_node, node(_makeCopy(x->left, nil), _makeCopy(x->right, nil), _NIL, x->color, x->key));
				if (new_node->left != _NIL)
					new_node->left->p = new_node;
				if (new_node->right != _NIL)
					new_node->right->p = new_node;
				return new_node;
			}
	

			node* _most_left(node* x)
			{
				while (x->left != _NIL)
					x = x->left;
				return x;
			}
			node* _most_right(node* x)
			{
				while (x->right != _NIL)
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
		// if (curr->color == BLACK) // to print mapped type.
		// 	printf(BLUE "%s" RESET "\n", curr->key.second.c_str());
		// else
		// 	printf(_RED "%s" RESET "\n", curr->key.second.c_str());
		if (curr->color == BLACK)
			printf(BLUE "%c" RESET "\n", curr->key.first);
		else
			printf(_RED "%c" RESET "\n", curr->key.first);
		rec[depth]=1;
		printTree(curr->left,depth+1);
		rec[depth]=0;
		printTree(curr->right,depth+1);
	}
		
}