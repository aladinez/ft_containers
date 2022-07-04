#include <functional>
#include "RBT_MAP.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "equal.hpp"
#include <stdexcept>


namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public: // types:
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const Key, T>										value_type;
			typedef Compare														key_compare;
			typedef Allocator													allocator_type;
			typedef typename Allocator::reference								reference;
			typedef typename Allocator::const_reference							const_reference;
			typedef ft::map_iterator<value_type, ft::Node<value_type> >					iterator;							
			typedef ft::map_iterator<value_type, const ft::Node<value_type> >		const_iterator;	
			typedef typename Allocator::size_type								size_type;
			typedef std::ptrdiff_t                  							difference_type;
			typedef typename Allocator::pointer									pointer;
			typedef typename Allocator::const_pointer							const_pointer;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		
		private:
			class value_compare;
			typedef ft::RB_tree<value_type, value_compare, Allocator>	RBT;
			key_compare _comp;
			value_compare val_comp;
			allocator_type _alloc;
			RBT _tree;
			size_type _size;
	
		
		public:
			///---------------------- constructor/Copy/destructor :
			explicit map(const Compare& comp = Compare(),
                     	const Allocator& alloc= Allocator()): _comp(comp), val_comp(comp), _alloc(alloc), _tree(comp, alloc), _size() {}
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _comp(comp), val_comp(comp), _alloc(alloc), _tree(comp, alloc), _size()
			{
				for (;first != last; first++)
					_tree.insert(*first);
				_size = _tree.size();
			}
			map (const map& x): _comp(x._comp), val_comp(x.val_comp), _alloc(x._alloc), _tree(x._tree), _size(x._size) {}
			~map(){}
			map& operator= (const map& x)
			{
				clear();
				_tree = x._tree;
				return *this;
			}
			//-----------------------------------------------------------/

			
			///---------------------- iterators:
			iterator begin()
			{
				return iterator(_tree.minimum(), _tree.get_root());
			}
			const_iterator begin() const
			{
				return const_iterator(_tree.minimum(), _tree.get_root());
			}
			iterator end()
			{
				return iterator(_tree.get_nil(), _tree.get_root());
			}
			const_iterator end()const
			{
				return const_iterator(_tree.get_nil(), _tree.get_root());
			}
			reverse_iterator rbegin(){return reverse_iterator(end());}
			const_reverse_iterator rbegin() const{return const_reverse_iterator(end());}
			reverse_iterator rend(){return reverse_iterator(begin());}
			const_reverse_iterator rend() const{return const_reverse_iterator(begin());}
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

			// mapped_type& at (const key_type& x)
			// {
			// 	Node<value_type>* n = _tree.search(ft::make_pair(x, T()));
			// 	if (n != _tree.get_nil())
			// 		return (n->key).second;
			// 	else
			// 		throw std::out_of_range("map");
			// }
			// const mapped_type& at (const key_type& x) const
			// {
			// 	Node<value_type>* n = _tree.search(ft::make_pair(x, T()));
			// 	if (n != _tree.get_nil())
			// 		return (n->key).second;
			// 	else
			// 		throw std::out_of_range("map");
			// }
			//-----------------------------------------------------------/

			// ------------  modifiers:
			pair<iterator, bool> insert(const value_type& x)
			{
				Node<value_type>* n = _tree.search(x);
				if (n != _tree.get_nil())
					return ft::make_pair(iterator(n, _tree.get_root()), false);
				_tree.insert(x);
				n = _tree.search(x);
				return ft::make_pair(iterator(n, _tree.get_root()), true);
			}
			iterator insert(iterator position, const value_type& x) // position : used as a suggestion as to where to start the search
			{
				(void)position;
				Node<value_type>* n = _tree.search(x);
				if (n != _tree.get_nil())
					return iterator(n, _tree.get_root());
				_tree.insert(x);
				n = _tree.search(x);
				return iterator(n, _tree.get_root());

			}
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					_tree.insert(*first);
			}
			void erase(iterator position)
			{
				_tree.remove(*position);
			}
			size_type erase(const key_type& x)
			{
				Node<value_type>* n = _tree.search(ft::make_pair(x, T()));
				if (n != _tree.get_nil())
				{
					_tree.remove(n->key);
					return 1;
				}
				return 0;
			}
			void erase(iterator first, iterator last)
			{	
				iterator it = first;
				first++;
				for (; first != last; first++)
				{
					_tree.remove(*it);
					it = first;
				}
				_tree.remove(*it);
			}
			void swap(map<Key,T,Compare,Allocator>& x)
			{
				std::swap(_tree, x._tree);
			}
			void clear()
			{
				_tree.clear();
			}
			//-----------------------------------------------------------/
			// observers:
			key_compare key_comp() const {return _comp;}
			value_compare value_comp() const {return val_comp;}
			allocator_type get_allocator() const { return _alloc;}
			//-----------------------------------------------------------/


			// ----------------- map operations:
			iterator find(const key_type& x)
			{
				Node<value_type>* n = _tree.search(value_type(x, T()));
				return iterator(n, _tree.get_root());
			}
			const_iterator find(const key_type& x) const
			{
				Node<value_type>* n = _tree.search(value_type(x, T()));
				return iterator(n, _tree.get_root());
			}
			size_type count(const key_type& x) const
			{
				Node<value_type>* n = _tree.search(value_type(x, T()));
				if (n != _tree.get_nil())
					return 1;
				return 0;
			}
			iterator lower_bound(const key_type& x);
			const_iterator lower_bound(const key_type& x) const;
			iterator upper_bound(const key_type& x);
			const_iterator upper_bound(const key_type& x) const;
			pair<iterator,iterator>
			equal_range(const key_type& x);
			pair<const_iterator,const_iterator>
			equal_range(const key_type& x) const;
			//-----------------------------------------------------------/


			void print()
			{
				_tree.print_tree();
			}
	};

	
	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		if (x.size() == y.size()){
			return (ft::equal(x.begin(), x.end(), y.begin()));
		}
		return false;
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		if (x.size() == y.size()){
			return (!ft::equal(x.begin(), x.end(), y.begin()));
		}
		return true;
	}

		template <class Key, class T, class Compare, class Allocator>
	bool operator< (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator> (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end());
	}
	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return !(ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}
	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
	{
		return !(ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end()));
	}

	


	




	template <class Key, class T, class Compare, class Alloc>
	class map<Key,T,Compare,Alloc>::value_compare
		: public std::binary_function<value_type, value_type, bool>
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