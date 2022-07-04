#ifndef _MAP_ITERATOR_HPP
#define _MAP_ITERATOR_HPP
#include "RBT_MAP.hpp"

#include <iterator>

namespace ft
{
	template <class Pair, class N>
	class map_iterator
	{
		public:
		
			typedef ft::Node<Pair>						node_val;
			// typedef ft::Node<Pair>*                     node_ptr;
			typedef N*				                     node_ptr;
			typedef const N*               const_node_ptr;
			// typedef const ft::Node<Pair>*               const_node_ptr;
			typedef std::ptrdiff_t						difference_type;
			typedef Pair                            	value_type;   
			typedef Pair*                             	pointer;   
			typedef Pair&                             	reference;
			typedef std::bidirectional_iterator_tag		iterator_category;
		private:
			node_ptr _ptr;
			node_ptr _root;
			node_ptr _NIL;
		public:
			// iterator(): _ptr(NULL), _NIL(NULL), _root(NULL){}
            map_iterator(node_ptr ptr = NULL, node_ptr root = NULL): _ptr(ptr),_root(root) {
				if (root)
					_NIL = root->p;
				else
					_NIL = NULL;
			}
            map_iterator(map_iterator const& it) : _ptr(it._ptr), _root(it._root), _NIL(it._NIL) {}
            ~map_iterator(){}

			operator map_iterator<value_type, const N>() const
            { 
                return map_iterator<value_type, const N>((_ptr), (_root));
            }
			

			// template<typename U>
  			// map_iterator(map_iterator<U> it)
			// {
			// 	_ptr = (ft::Node<const Pair>*)it._ptr;
			// 	_root = (ft::Node<const Pair>*)it._root;
			// 	_NIL = (ft::Node<const Pair>*)it._NIL;
			// }
			
			map_iterator &operator=(map_iterator const& it)
            {
                _ptr = it._ptr;
				_root = it._root;
				_NIL = it._NIL;
                return *this;
            }

			bool operator== (map_iterator const& it){return _ptr == it._ptr;}
            bool operator!= (map_iterator const& it){return _ptr != it._ptr;}

			value_type& operator* () const                    {return _ptr->key;}
			pointer  operator->() const                    {return &(_ptr->key);}
			//temp solution
			// pointer  operator->() const                    {return const_cast<Pair*>(&(_ptr->key));}

			map_iterator  operator++(int) /* postfix */        
			{
				// if (_ptr == _NIL)
				// 	return _ptr;
				map_iterator it(*this); 
				_ptr = successor(_ptr);
				return it;
			}
            map_iterator& operator++()    /* prefix */          
			{
				// if (_ptr == _NIL)
				// 	return _ptr;
				_ptr = successor(_ptr);
				return *this;
			}

			map_iterator  operator--(int) /* postfix */         
			{
				map_iterator it(*this);
				if (_ptr == _NIL)
					_ptr = _most_right(_root);
				else
					_ptr = predecessor(_ptr);
				return it;
			}
            map_iterator& operator--()    /* prefix */          
			{
				if (_ptr == _NIL)
					_ptr = _most_right(_root);
				else
					_ptr = predecessor(_ptr);
				return *this;
			}


		private:

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
