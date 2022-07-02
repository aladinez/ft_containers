#include <functional>
#include "RBT_MAP.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public: // types:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference			const_reference;
			typedef ft::iterator<value_type>					iterator;							
			// typedef ft::iterator<const value_type>			const_iterator;	
			typedef typename Allocator::size_type			size_type;
			typedef std::ptrdiff_t                  		difference_type;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		private:
			class value_compare;
			typedef ft::RB_tree<value_type, value_compare, Allocator>	RBT;
			RBT _tree;
			size_type _size;
			value_compare val_comp;
			Allocator _alloc;
	
		
		public:
			///---------------------- constructor/Copy/destructor :
			explicit map(const Compare& comp = Compare(),
                     	const Allocator& alloc= Allocator()): val_comp(comp), _alloc(alloc), _tree(val_comp, _alloc), _size() {}
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : val_comp(comp), _alloc(alloc), _tree(val_comp, _alloc), _size()
			{
				for (;first != last; first++)
					_tree.insert(*first);
				_size = _tree.size();
			}
			map (const map& x): val_comp(x.val_comp), _alloc(x._alloc), _size(x._size), _tree(x._tree) {}
			~map(){}
			//-----------------------------------------------------------/

			///---------------------- iterators:
			iterator begin()
			{
				return iterator(_tree.maximum(), _tree.get_nil(), _tree.get_root());
			}
			// const_iterator begin() const;
			iterator end()
			{
				return iterator(_tree.get_nil(), _tree.get_nil(), _tree.get_root());
			}
			// const_iterator end()const;
			reverse_iterator rbegin(){return reverse_iterator(end());}
			// const_reverse_iterator rbegin() const{return const_reverse_iterator(end());}
			reverse_iterator rend(){return reverse_iterator(begin());}
			// const_reverse_iterator rend() const{return const_reverse_iterator(begin());}
			//-----------------------------------------------------------/

			// ------------ capacity:
			bool empty()const {return _tree.size() == 0;}
			size_type size() const {return _tree.size();}
			size_type max_size() const {return _alloc.max_size();}
			//-----------------------------------------------------------/

			// ------------ element access:
			T& operator[](const key_type& x)
			{
				// find x, if not insert it with default mapped_type T, and return it's second.
				Node<value_type>* n = _tree.search(ft::make_pair(x, T()));
				if (n != _tree.get_nil())
					return (n->key).second;
				_tree.insert(ft::make_pair(x, T()));
				n = _tree.search(ft::make_pair(x, T()));
				return (n->key).second;
			}
			//-----------------------------------------------------------/

			// ------------  modifiers:
			pair<iterator, bool> insert(const value_type& x)
			{
				Node<value_type>* n = _tree.search(x);
				if (n != _tree.get_nil())
					return ft::make_pair(iterator(n, _tree.get_nil(), _tree.get_root()), false);
				_tree.insert(x);
				n = _tree.search(x);
				return ft::make_pair(iterator(n, _tree.get_nil(), _tree.get_root()), true);
			}
			// iterator insert(iterator position, const value_type& x); template <class InputIterator>
			// 		void insert(InputIterator first, InputIterator last);
			// void erase(iterator position);
			// size_type erase(const key_type& x);
			// void erase(iterator first, iterator last); void swap(map<Key,T,Compare,Allocator>&);
			// void clear();
			//-----------------------------------------------------------/

			// void insert(value_type x)
			// {
			// 	_tree.insert(x);
			// }
			void print()
			{
				_tree.print_tree();
			}

	};


	template <class Key, class T, class Compare, class Alloc>
	class map<Key,T,Compare,Alloc>::value_compare
	{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
		friend class map;
		protected:
			Compare comp;
		public:
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
	};

}