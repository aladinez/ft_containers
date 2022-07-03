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
			
			// iterator(): _ptr(NULL), _NIL(NULL), _root(NULL){}
            iterator(node_ptr ptr = NULL, node_ptr root = NULL): _ptr(ptr),_root(root) {
				if (root)
					_NIL = root->p;
				else
					_NIL = NULL;
			}
            iterator(iterator const& it) : _ptr(it._ptr), _root(it._root), _NIL(it._NIL) {}
            ~iterator(){}

			// template<typename U>
			// operator iterator<U>() const
            // { 
            //     return iterator<U>(reinterpret_cast<ft::Node<U>*>(_ptr), reinterpret_cast<ft::Node<U>*>(_root));
            // }

			// https://stackoverflow.com/questions/71965838/no-suitable-user-defined-conversion-but-the-convertion-is-specified
			// template<typename U>
  			// iterator(iterator<U> it)
			// {
			// 	_ptr = (ft::Node<const Pair>*)it._ptr;
			// 	_root = (ft::Node<const Pair>*)it._root;
			// 	_NIL = (ft::Node<const Pair>*)it._NIL;
			// }
			
			iterator &operator=(iterator const& it)
            {
                _ptr = it._ptr;
				_root = it._root;
				_NIL = it._NIL;
                return *this;
            }

			bool operator== (iterator const& it){return _ptr == it._ptr;}
            bool operator!= (iterator const& it){return _ptr != it._ptr;}

			value_type& operator* () const                    {return _ptr->key;}
			pointer  operator->() const                    {return &(_ptr->key);}

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
			if (x == _NIL)
				return x;
			node_ptr y = x;
			while (y->left != _NIL)
				y = y->left;
			return y;
		}
		node_ptr _most_right(node_ptr x)
		{
			if (x == _NIL)
				return x;
			node_ptr y = x;
			while (y->right != _NIL)
				y = y->right;
			return y;
		}
		node_ptr successor(node_ptr x)
        {
            if (x != _NIL)
            {   
                if (x->right != _NIL)
                    return _most_left(x->right);
                node_ptr y = x->p;
                while (y != _NIL && x == y->right)
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
            if (x != _NIL)
            {
                if (x->left != _NIL)
                    return _most_right(x->left);
                node_ptr y = x->p;
                while (y != _NIL && x == y->left)
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
