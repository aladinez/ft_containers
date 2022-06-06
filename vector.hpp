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
			//TODO : enable_if
			template <class InputIterator>
         		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()): _array(), _alloc(alloc), _size(), _capacity()
				{
					typedef std::iterator_traits<InputIterator> traits;
					if (typeid(typename traits::iterator_category)==typeid(std::random_access_iterator_tag)
					|| typeid(typename traits::iterator_category)==typeid(std::bidirectional_iterator_tag)
					|| typeid(typename traits::iterator_category)==typeid(std::forward_iterator_tag))
    				{
						_capacity = std::distance(first, last);
						_array = _alloc.allocate(_capacity);
					}
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
			void assign(InputIterator first, InputIterator last);
			void assign(size_type n, const T& u);
			allocator_type get_allocator() const;


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
			iterator insert (iterator position, const value_type& val);
    		void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);
			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
			void     swap(vector<T,Allocator>&);
			void     clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_array + i);
				_size = 0;
			}

		private:
			pointer     _array;
			size_type   _size;
			size_type   _capacity;
			Allocator   _alloc;
			
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
	

	template <class T, class Allocator>
		bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			if (x.size() == y.size()){
				return (equal(x.begin(), x.end(), y.begin()));
			}
			return false;
		}
	template <class T, class Allocator>
		bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			if (x.size() == y.size()){
				return (!equal(x.begin(), x.end(), y.begin()));
			}
			return true;
		}
	template <class T, class Allocator>
		bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	template <class T, class Allocator>
		bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	// specialized algorithms:
	template <class T, class Allocator>
	void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
}

#endif