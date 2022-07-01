#ifndef _MAP_ITERATOR_HPP
#define _MAP_ITERATOR_HPP

#include <iterator>

namespace ft
{
	template <class T>
	class iterator
	{
		public:
			typedef T                               value_type;
			typedef std::ptrdiff_t                  difference_type;
			typedef T*                              pointer;   
			typedef T&                              reference;
			typedef std::bidirectional_iterator_tag iterator_category;
			

			iterator(): _ptr(){}
			iterator(pointer ptr): _ptr(ptr){}
			iterator(iterator const& it) {_ptr = it._ptr;}
			~iterator(){}

			operator iterator<const value_type>() const
			{ 
				return iterator<const value_type>(_ptr);
			}

			iterator &operator=(iterator const& it)
			{
				_ptr = it._ptr;
				return *this;
			}

			bool operator== (iterator const& it){return _ptr == it._ptr;}
			bool operator!= (iterator const& it){return _ptr != it._ptr;}
			bool operator> (iterator const& it){return _ptr > it._ptr;}
			bool operator< (iterator const& it){return _ptr < it._ptr;}
			bool operator>= (iterator const& it){return _ptr >= it._ptr;}
			bool operator<= (iterator const& it){return _ptr <= it._ptr;}

			iterator  operator++(int) /* postfix */         {iterator it(*this); _ptr++; return it;}
			iterator& operator++()    /* prefix */          {_ptr++; return *this;}
			iterator  operator--(int) /* postfix */         {iterator it(*this); _ptr--; return it;}
			iterator& operator--()    /* prefix */          {_ptr--; return *this;}
			reference operator* () const                    {return *_ptr;}
			reference operator[] (difference_type diff)     {return *(_ptr + diff);}
			pointer   operator->() const                    {return _ptr;}
			iterator  operator+ (difference_type diff)const {return _ptr + diff;}
			// iterator  operator+ (iterator const& it)const {return _ptr + it._ptr;}
			iterator  operator- (difference_type diff)const {return _ptr - diff;}
			difference_type  operator- (iterator const& it)const {return _ptr - it._ptr;}
			iterator  operator-= (difference_type diff) {_ptr = _ptr - diff; return *this;}
			iterator  operator+= (difference_type diff) {_ptr = _ptr + diff; return *this;}


		private:
			pointer _ptr;
	};
	template <class T>
	iterator<T> operator+ (typename iterator<T>::difference_type n, const iterator<T>& it)
	{
		return (it + n);
	}
}

#endif
