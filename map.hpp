#include <functional>
#include "RBT_MAP.hpp"
#include "pair.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public: // types:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			// typedef //										iterator;
			// typedef // 										const_iterator;
			typedef typename Allocator::size_type			size_type;
			typedef std::ptrdiff_t                  		difference_type;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			// typedef std::reverse_iterator<iterator>			reverse_iterator;
			// typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
		private:
			class value_compare;
			typedef ft::RB_tree<value_type, value_compare, Allocator>	RBT;
			RBT _tree;
			size_type _size;
			value_compare val_comp;
			Allocator _alloc;
	
		
		public:
			explicit map(const Compare& comp = Compare(),
                     	const Allocator& alloc= Allocator()): val_comp(comp), _alloc(alloc), _tree(val_comp, alloc), _size() {}
			void insert(value_type x)
			{
				_tree.insert(x);
			}
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