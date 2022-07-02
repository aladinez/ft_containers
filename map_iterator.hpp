#ifndef _MAP_ITERATOR_HPP
#define _MAP_ITERATOR_HPP
#include "RBT_MAP.hpp"

#include <iterator>

namespace ft
{
	template <class Pair>
	class iterator
	{
		public:
			typedef ft::Node<Pair>						node_val;
			typedef ft::Node<Pair>*                     node_ptr;
			typedef std::ptrdiff_t						difference_type;
			typedef Pair                            	value_type;   
			typedef Pair*                             	pointer;   
			typedef Pair&                             	reference;
			typedef std::bidirectional_iterator_tag		iterator_category;
			
			iterator(): _ptr(){}
            iterator(node_ptr ptr, node_ptr nil, node_ptr root): _ptr(ptr), _NIL(nil), _root(root) {}
            iterator(iterator const& it) 
			{
				_ptr = it._ptr;
				_NIL = it._NIL;
				_root = it._root;
			}
            ~iterator(){}
			
			iterator &operator=(iterator const& it)
            {
                _ptr = it._ptr;
                return *this;
            }

			bool operator== (iterator const& it){return _ptr == it._ptr;}
            bool operator!= (iterator const& it){return _ptr != it._ptr;}

			node_val& operator* () const                    {return *_ptr;}
			node_ptr  operator->() const                    {return _ptr;}

			iterator  operator++(int) /* postfix */        
			{
				// if (_ptr == _NIL)
				// 	return _ptr;
				iterator it(*this); 
				_ptr = successor(_ptr);
				return it;
			}
            iterator& operator++()    /* prefix */          
			{
				// if (_ptr == _NIL)
				// 	return _ptr;
				_ptr = successor(_ptr);
				return *this;
			}

			iterator  operator--(int) /* postfix */         
			{
				iterator it(*this);
				if (_ptr == _NIL)
					_ptr = _most_right(_root);
				else
					_ptr = predecessor(_ptr);
				return it;
			}
            iterator& operator--()    /* prefix */          
			{
				if (_ptr == _NIL)
					_ptr = _most_right(_root);
				else
					_ptr = predecessor(_ptr);
				return *this;
			}


		private:
			node_ptr _ptr;
			node_ptr _NIL;
			node_ptr _root;

		node_ptr _most_left(node_ptr x)
			{
				while (x->left != _NIL)
					x = x->left;
				return x;
			}
		node_ptr _most_right(node_ptr x)
		{
			while (x->right != _NIL)
				x = x->right;
			return x;
		}
		node_ptr successor(node_ptr x)
        {
            if (x)
            {   
                if (x->right)
                    return _most_left(x->right);
                node_ptr y = x->p;
                while (y && x == y->right)
                {
                    x = y;
                    y = y->p;
                }
                return y;
            }
            return x;
        }
        node_ptr predecessor(node_ptr x)
        {
            if (x)
            {
                if (x->left)
                    return _most_right(x->left);
                node_ptr y = x->p;
                while (y && x == y->left)
                {
                    x = y;
                    y = y->p;
                }
                return y;
            }
            return x;
        }
	};

}

#endif
