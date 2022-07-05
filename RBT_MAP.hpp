#pragma once

#include <iostream>
#include <stdio.h>
#include <memory>
#include "pair.hpp"

#define RED__ 0
#define BLACK__ 1

// #define _RED     "\x1b[31m"
// #define BLUE    "\x1b[34m"
// #define RESET   "\x1b[0m"

namespace ft
{
	template <typename T>
	struct Node {
		Node* left;
		Node* right;
		Node* p;
		bool color;
		T key;
		Node(Node* l = NULL, Node* r = NULL, Node* p = NULL, bool c = BLACK__, T k = T())
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
		private:
			node* _root;
			node* _NIL;
			Compare _comp;
			_Allocator _alloc;
			size_type _size;
		public:
			// RB_tree (): _NIL(new node), _comp() {_root = _NIL;}
			RB_tree(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: _comp(comp), _alloc(alloc), _size() 
			{
				_NIL = _alloc.allocate(1);
				_alloc.construct(_NIL, node());
				_root = _NIL;
			}
			//copy constructor
			RB_tree (const RB_tree& rbt):  _comp(rbt._comp), _alloc(rbt._alloc) {
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
			
			node* search(value_type new_key) const
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
			node* find(node *x, value_type new_key) const
			{
				node* y = _NIL;
				while (x != _NIL)
				{
					y = x;
					if (_comp(x->key, new_key))
					{
						x = x->right;
					}
					else
					{
						x = x->left;
					}
				}
				return (y);
			}
			node* lower_bound(value_type new_key) const
			{
				if (_root == _NIL)
					return _root;
				node* y = search(new_key);
				if (y != _NIL)
					return y;
				node* x = _root;
				return find(x, new_key);
				
			}
			node* upper_bound(value_type new_key) const
			{
				if (_root == _NIL)
					return _root;
				node* y = search(new_key);
				if (y != _NIL)
					return successor(y);
				y = lower_bound(new_key);
				return successor(y);
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

				// node* z = new node(_NIL, _NIL, _NIL, RED__);
				node* z = _alloc.allocate(1);
				_alloc.construct(z, node(_NIL, _NIL, _NIL, RED__, key));
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
				// node* z = search(x->key);
				if (x == _NIL)
					return;
				clear(x->left);
				clear(x->right);
				delete_node(x);
				
			}
			void clear()
			{
				// node* x = _root;
				if (_root == _NIL)
					return;
				clear(_root->left);
				clear(_root->right);
				delete_node(_root);
				_root = _NIL;
				_size = 0;
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
				while (z->p->color == RED__) // violation cuz both z and z.p are red__
				{
					if (z->p == z->p->p->left)
					{
						node* y = z->p->p->right; // y is uncle of z
						if (y->color == RED__) // uncle is red__, recolor z.p and y
						{
							z->p->color = BLACK__;
							y->color = BLACK__;
							z->p->p->color = RED__; //recolor z.p.p and recheck.
							z = z->p->p; // next loop z will be z.p.p
						}
						else // uncle is black__ => rotate and recolor
						{
							if (z == z->p->right) // z in the right of its parent, so we will left rotate z.p
							{
								z = z->p;
								left_rotate(z);
							}
							z->p->color = BLACK__; // loop will stop after this.
							z->p->p->color = RED__;
							right_rotate(z->p->p);
						}
					}
					else
					{
						node* y = z->p->p->left;
						if (y->color == RED__)
						{
							z->p->color = BLACK__;
							y->color = BLACK__;
							z->p->p->color = RED__;
							z = z->p->p;
						}
						else
						{
							if (z == z->p->left)
							{
								z = z->p;
								right_rotate(z);
							}
							z->p->color = BLACK__;
							z->p->p->color = RED__;
							left_rotate(z->p->p);
						}
					}
				}
				_root->color = BLACK__;
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
					if (o_color == BLACK__)
						remove_fixup(x);
					_size--;
				}
			}
			void remove_fixup(node* x)
			{
				node* w;
				while (x != _root && x->color == BLACK__)
				{
					if (x == x->p->left) 
					{
						w = x->p->right; // z is x's sibling
						if (w->color == RED__) // case 1
						{
							w->color = BLACK__;
							x->p->color = RED__;
							left_rotate(x->p);
							w = x->p->right;
						}
						if (w->left->color == BLACK__ && w->right->color == BLACK__) // case 2
						{
							w->color = RED__;
							x = x->p;
						}
						else // case 3 and 4
						{
							if (w->right->color == BLACK__) // case 3
							{
								w->left->color = BLACK__;
								w->color = RED__;
								right_rotate(w);
								w = x->p->right;
							}
							w->color = x->p->color;
							x->p->color = BLACK__;
							w->right->color = BLACK__;
							left_rotate(x->p);
							x = _root; // to end the loop.
						}
					}
					else
					{
						w = x->p->left; // z is x's sibling
						if (w->color == RED__) // case 1
						{
							w->color = BLACK__;
							x->p->color = RED__;
							right_rotate(x->p);
							w = x->p->left;
						}
						if (w->right->color == BLACK__ && w->left->color == BLACK__) // case 2
						{
							w->color = RED__;
							x = x->p;
						}
						else // case 3 and 4
						{
							if (w->left->color == BLACK__) // case 3
							{
								w->right->color = BLACK__;
								w->color = RED__;
								left_rotate(w);
								w = x->p->left;
							}
							w->color = x->p->color;
							x->p->color = BLACK__;
							w->left->color = BLACK__;
							right_rotate(x->p);
							x = _root; // to end the loop.
						}
					}
				}
				x->color = BLACK__;
			}
			node* maximum() const
			{
				return _most_right(_root);
			}
			node* minimum() const
			{
				return _most_left(_root);
			}
			node* get_root() const {return _root;}
			node* get_nil() const {return _NIL;}
			size_type size() const {return _size;}
			void print_tree()
			{
				printTree(_root);
			}
		private:
			
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
	

			node* _most_left(node* x) const
			{
				if (x != _NIL)
				{
					while (x->left != _NIL)
						x = x->left;
				}
				return x;
			}
			node* _most_right(node* x) const
			{
				if (x != _NIL)
				{
					while (x->right != _NIL)
						x = x->right;
				}
				return x;
			}
			
			node* successor(node* x) const
			{
				if (x != _NIL)
				{   
					if (x->right != _NIL)
						return _most_left(x->right);
					node* y = x->p;
					while (y != _NIL && x == y->right)
					{
						x = y;
						y = y->p;
					}
					return y;
				}
				return x;
			}
			node* predecessor(node* x) const
			{
				if (x != _NIL)
				{
					if (x->left != _NIL)
						return _most_right(x->left);
					node* y = x->p;
					while (y != _NIL && x == y->left)
					{
						x = y;
						y = y->p;
					}
					return y;
				}
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
		// if (curr->color == BLACK__) // to print mapped type.
		// 	printf(BLUE "%s" RESET "\n", curr->key.second.c_str());
		// else
		// 	printf(_RED__ "%s" RESET "\n", curr->key.second.c_str());
		if (curr->color == BLACK__)
			printf("%c\n", curr->key.first);
		else
			printf("%c\n", curr->key.first);
		rec[depth]=1;
		printTree(curr->left,depth+1);
		rec[depth]=0;
		printTree(curr->right,depth+1);
	}
		
}