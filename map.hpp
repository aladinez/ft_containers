#include <functional>


namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<std::pair<const Key, T> > >
	class map {
		public: // types:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef pair<const Key, T>						value_type;
			typedef Compare									value_type;
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			// typedef //										iterator;
			// typedef // 										const_iterator;
			// typedef //										size_type;
			// typedef //										difference_type;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
	};

	



}