#ifndef _VECTOR_HPP
#define _VECTOR_HPP

#include <memory>
#include <cstddef>
#include "Iterator.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include <iostream>
#include <typeinfo>

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
		public: 
			typedef typename Allocator::reference           reference;
			typedef typename Allocator::const_reference     const_reference;
			typedef ft::iterator<T>                  		iterator;
			typedef ft::iterator<const T>                	const_iterator;
			typedef typename Allocator::size_type			size_type;
			typedef std::ptrdiff_t                  		difference_type;
			typedef T                                       value_type;
			typedef Allocator                               allocator_type;
			typedef typename Allocator::pointer             pointer;
			typedef typename Allocator::const_pointer       const_pointer;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

            // 23.2.4.1 construct/copy/destroy:
            explicit vector(const allocator_type& alloc = Allocator()) : _alloc(alloc), _array(), _size(), _capacity(){}
			explicit vector(size_type n, const T& value = T(), const allocator_type& alloc = Allocator()): _alloc(alloc), _size(n), _capacity(n)
			{
				_array = _alloc.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_array + i, value);
			}
			template <class InputIterator>
         		vector (InputIterator first, typename enable_if<Identify<typename std::iterator_traits<InputIterator>::iterator_category>::is_true, InputIterator>::type last, const allocator_type& alloc = allocator_type()): _array(), _alloc(alloc), _size(), _capacity()
				{
					difference_type ret = _distance(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
					if (ret != -1 && (_capacity = (size_type)ret))
						_array = _alloc.allocate(_capacity);
					for (; first != last; first++)
						push_back(*first);
				}

			vector(const vector<T,Allocator>& x) : _size(x._size), _capacity(x._capacity), _alloc(x._alloc)
			{
				_array = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_array + i, *(x._array + i));
			}
			~vector()
			{
				clear();
				if (_array)
					_alloc.deallocate(_array, _capacity);
			}
			vector<T,Allocator>& operator=(const vector<T,Allocator>& x)
			{
				clear();
				if (_array)
					_alloc.deallocate(_array, _capacity);
				_alloc = x._alloc;
				_capacity = x._capacity;
				_array = _alloc.allocate(_capacity);
				for (_size = 0; _size < x._size; _size++)
					_alloc.construct(_array + _size, *(x._array + _size));
				return *this;
			}
			template <class InputIterator>
			void assign(InputIterator first, typename enable_if<Identify<typename std::iterator_traits<InputIterator>::iterator_category>::is_true, InputIterator>::type last)
			{
				clear();
				difference_type ret = _distance(first, last, typename std::iterator_traits<InputIterator>::iterator_category());
				if (ret != -1)
				{
					if (_array)
						_alloc.deallocate(_array, _capacity);
					_capacity = (size_type)ret;
					_array = _alloc.allocate(_capacity);
				}
				for (; first != last; first++)
					push_back(*first);
			}
			void assign (size_type n, const value_type& val)
			{
				clear();
				if (n > _capacity)
				{
					if (_array)
						_alloc.deallocate(_array, _capacity);
					_capacity = n;
					_array = _alloc.allocate(_capacity);
				}
				for (_size = 0; _size < n; _size++)
					_alloc.construct(_array + _size, val);
			}
			allocator_type get_allocator() const{return _alloc;}


			// iterators:
			iterator begin(){return iterator(_array);}
			const_iterator begin()const{return const_iterator(_array);}
			iterator end(){return iterator(_array + _size);}
			const_iterator end()const{return const_iterator(_array + _size);}
			reverse_iterator rbegin(){return reverse_iterator(end());}
			const_reverse_iterator rbegin() const{return const_reverse_iterator(end());}
			reverse_iterator rend(){return reverse_iterator(begin());}
			const_reverse_iterator rend() const{return const_reverse_iterator(begin());}

            // 23.2.4.2 capacity:
			size_type   size() const{return _size;}
			size_type   max_size() const{return _alloc.max_size();} // is the theoretical maximum number of items that could be put in your vector
            size_type	capacity() const{return _capacity;}
			void resize (size_type n, value_type value = value_type())
            {
				if (n > _alloc.max_size())
					throw std::length_error("vector");
                if (n < _size)
                {
                    for (size_type i = n; i < _size; i++)
                        _alloc.destroy(_array + i);
                    _size = n;
                }
                else if (n <= _capacity )
                {
                    for (;_size < n; _size++)
					    _alloc.construct(_array + _size, value);
                }
                else
                {
					// size_type new_cap = _capacity*2 < n ? n : _capacity*2; //TODO : check the behaviour of the standard vector in this case
					pointer _new = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(_new + i, _array[i]);
						_alloc.destroy(_array + i);
					}
					for (;_size < n; _size++)
						_alloc.construct(_new + _size, value_type());
					if (_array) // in case capacity == 0
						_alloc.deallocate(_array, _capacity);
					_array = _new;
					_capacity = n;
                }
            }
			bool        empty()const{return !_size;}
			void        reserve(size_type n)
			{
				if (n > _alloc.max_size())
					throw std::length_error("vector");
				else if (n > _capacity)
				{
					pointer _new = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(_new + i, _array[i]);
						_alloc.destroy(_array + i);
					}
					_alloc.deallocate(_array, _capacity);
					_array = _new;
					_capacity = n;	
				}
			}
			// element access:
			reference       operator[](size_type n){return _array[n];} 
			const_reference operator[](size_type n) const{return _array[n];}
			const_reference at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				else
					return (_array[n]);
			}
			reference       at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				else
					return (_array[n]);
			}
			reference       front(){return _array[0];}
			const_reference front() const{return _array[0];}
			reference       back(){return _array[_size - 1];}
			const_reference back() const{return _array[_size - 1];}

			// 23.2.4.3 modifiers:
			void push_back (const value_type& val)
			{
				if (_capacity == 0 && (_capacity = 1))
					_array = _alloc.allocate(_capacity);
				if (_size < _capacity)
					_alloc.construct(_array + _size, val);
				else
				{
					pointer _new = _alloc.allocate(_capacity * 2);
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(_new + i, _array[i]);
						_alloc.destroy(_array + i);
					}
					_alloc.deallocate(_array, _capacity);
					_array = _new;
					_capacity *= 2;
					_alloc.construct(_array + _size, val);
				}
				_size++;
			}
			void pop_back()
			{
				if (_size > 0)
				{
					_alloc.destroy(_array + _size);
					_size--;
				}
			}
			iterator insert (iterator position, const value_type& val)
			{
				if (_capacity == 0 && (_capacity = 1) && (_size = 1))
				{
					_array = _alloc.allocate(_capacity);
					_alloc.construct(_array, val);
					return iterator(_array);
				}
				size_type pos = position - this->begin();
				if (_size < _capacity)
				{	
					size_type _end = _size;
					_size++;
					for (; _end != pos; _end--)
					{
						_alloc.construct(_array + _end, _array[_end - 1]);
						_alloc.destroy(_array + _end - 1);
					}
					_alloc.construct(_array + _end, val);
				}
				else
				{
					pointer _new = _alloc.allocate(_capacity * 2);
					size_type i = 0;
					for (; i < pos; i++)
						_alloc.construct(_new + i, _array[i]);
					_alloc.construct(_new + i, val);
					i++;
					for (; i < _size + 1; i++)
						_alloc.construct(_new + i, _array[i - 1]);
					clear();
					_alloc.deallocate(_array, _capacity);
					_size = i;
					_capacity *= 2;
					_array = _new;
				}
				return iterator(_array + pos);
			}
    		void insert (iterator position, size_type n, const value_type& val)
			{
				if (_capacity == 0 && (_capacity = n))
				{
					_array = _alloc.allocate(_capacity);
					for (_size = 0; _size < n; _size++)
						_alloc.construct(_array + _size, val);
				}
				else if (n + _size > _capacity)
				{
					size_type pos = position - this->begin();
					size_type cap = _capacity * 2;
					if (cap < n + _size)
						cap = n + _size;
					pointer _new = _alloc.allocate(cap);
					size_type i = 0;
					//fill the first part
					for (; i < pos; i++)
						_alloc.construct(_new + i, _array[i]);
					//fill the range
					size_type x = i;
					for (; i < x + n; i++)
						_alloc.construct(_new + i, val);
					//fill the second part
					for (; i < _size + n; i++)
						_alloc.construct(_new + i, _array[i - x]);
					// assing _new to _array
					clear();
					_alloc.deallocate(_array, _capacity);
					_size = i;
					_array = _new;
					_capacity = cap;
				}
				else
				{
					size_type pos = position - this->begin();
					size_type _end = _size + n;
					for (; _end != pos + n - 1; _end--)
					{
						_alloc.construct(_array + _end, _array[_end - n]);
						_alloc.destroy(_array + _end - n);
					}
					for (; _end != pos - 1; _end--)
						_alloc.construct(_array + _end, val);
					_size += n;
				}
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, typename enable_if<Identify<typename std::iterator_traits<InputIterator>::iterator_category>::is_true, InputIterator>::type last)
			{
				difference_type dist = _distance(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
				pointer _new;
				size_type pos = position - this->begin();
				size_type i = 0;
				size_type cap = _capacity;
				size_type sz = _size;

				if (dist != -1 && _size + dist > _capacity)
						cap = _size + dist;
				_new = _array;
				_size = 0;
				_array = _alloc.allocate(cap);
				for (;i < pos; i++)
					push_back(_new[i]);
				for (; first != last; first++)
					push_back(*first);	
				for (; i < sz; i++)
					push_back(_new[i]);
				// free _new
				for (i = 0; i < sz; i++)
					_alloc.destroy(_new + i);
				_alloc.deallocate(_new, _capacity);
				_capacity = cap;
			}
			iterator erase(iterator position)
			{
				size_type pos = position - this->begin();
				size_type i = pos;
				_alloc.destroy(_array + i);
				for (; i < _size; i++)
				{
					_alloc.construct(_array + i, _array[i + 1]);
					_alloc.destroy(_array + i + 1);
				}
				_size--;
				return iterator(_array + pos);
			}
			iterator erase(iterator first, iterator last)
			{
				size_type sz = last - first;
				size_type pos = first - this->begin();
				_alloc.destroy(_array + pos);
				_size -= sz;
				for (size_type i = pos; i < _size; i++)
				{
					_alloc.construct(_array + i, _array[i + sz]);
					if (i < pos + sz)
						_alloc.destroy(_array + i + 1);
				}
				return iterator(_array + pos);
			}
			void swap (vector& x)
			{
				vector tmp(x);
				x = *this;
				*this = tmp;
			}
			void     clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_array + i);
				_size = 0;
			}

		private:
			pointer			_array;
			size_type		_size;
			size_type   	_capacity;
			allocator_type	_alloc;

			template <class InputIterator>
			difference_type _distance(InputIterator first, InputIterator last, std::random_access_iterator_tag) {
				return std::distance(first, last);
			}

			template <class InputIterator>
			difference_type _distance(InputIterator first, InputIterator last, std::bidirectional_iterator_tag) {
				return std::distance(first, last);
			}

			template <class InputIterator>
			difference_type _distance(InputIterator first, InputIterator last, std::forward_iterator_tag) {
				return std::distance(first, last);
			}

			template <class InputIterator>
			difference_type _distance(InputIterator first, InputIterator last, std::input_iterator_tag) {
				return -1;
			}
			
	};

	template <class InputIterator1, class InputIterator2>
		bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) 
		{
			while (first1!=last1) {
				if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
				return false;
				++first1; ++first2;
			}
			return true;
		}
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  		bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
		{
			while (first1!=last1) {
				if (!pred(*first1,*first2))   // or: if (!pred(*first1,*first2)), for version 2
				return false;
				++first1; ++first2;
			}
			return true;
		}
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1)
				return false;
			else if (*first1<*first2) 
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1!=last1)
		{
			if (first2==last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2)) 
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	template <class T, class Allocator>
		bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			if (x.size() == y.size()){
				return (ft::equal(x.begin(), x.end(), y.begin()));
			}
			return false;
		}
	template <class T, class Allocator>
		bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			if (x.size() == y.size()){
				return (!ft::equal(x.begin(), x.end(), y.begin()));
			}
			return true;
		}
	template <class T, class Allocator>
		bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		}
	template <class T, class Allocator>
		bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end());
		}
	template <class T, class Allocator>
		bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return !(ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
		}
	template <class T, class Allocator>
		bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return !(ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end()));
		}

	// specialized algorithms:
	template <class T, class Allocator>
	void swap(vector<T,Allocator>& x, vector<T,Allocator>& y)
	{
		x.swap(y);
	}
}

#endif