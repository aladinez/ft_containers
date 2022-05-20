#include <memory>
#include <cstddef>
// #include "Iterator.hpp"

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
		public: 
			typedef typename Allocator::reference           reference;
			typedef typename Allocator::const_reference     const_reference;
			// typedef ft::iterator<T>                  			iterator;
			// typedef ft::const_iterator                		const_iterator;

			typedef typename Allocator::size_type			size_type;
			// typedef implementation defined                  difference_type;

			typedef T                                       value_type;
			typedef Allocator                               allocator_type;
			typedef typename Allocator::pointer             pointer;
			typedef typename Allocator::const_pointer       const_pointer;

            // 23.2.4.1 construct/copy/destroy:
            explicit vector(const allocator_type& alloc = Allocator()) : _alloc(alloc), _array(), _size(), _capacity(){}
			explicit vector(size_type n, const T& value = T(), const allocator_type& alloc = Allocator()): _alloc(alloc), _size(n), _capacity(n)
			{
				_array = _alloc.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_array + i, value);
			}
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last, const Allocator& = Allocator());
			// vector(const vector<T,Allocator>& x);
			~vector(){}

            // 23.2.4.2 capacity:
			size_type   size() const{return _size;}
			size_type   max_size() const{return _alloc.max_size();} // is the theoretical maximum number of items that could be put in your vector
            size_type	capacity() const{return _capacity;}
			void resize (size_type n, value_type value = value_type())
            {
                if (n < _size)
                {
                    for (size_type i = n; i < _size; i++)
                        _alloc.destroy(_array + i);
                    _size = n;
                }
                if (n > _size)
                {
                    for (size_type i = _size; i < n; i++)
						push_back(value);
					    // _alloc.construct(_array + i, value);
                }
                // else if (n > _size && n > _capacity)
                // {

                // }
            }
			bool        empty()const{return !_size;}
			void        reserve(size_type n);

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
				{
					_array = _alloc.allocate(_capacity);
					_alloc.construct(_array, val);
				}
				else if (_size < _capacity)
					_alloc.construct(_array + _size, val);
				//TODO : realloc double capacity for array
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
				_alloc.destroy(_array + _size);
				_size--;
			}


			// iterator insert(iterator position, const T& x);
			// void insert(iterator position, size_type n, const T& x);
			// template <class InputIterator>
			// void insert(iterator position, InputIterator first, InputIterator last);
			// iterator erase(iterator position);
			// iterator erase(iterator first, iterator last);
			void     swap(vector<T,Allocator>&);
			void     clear();

            private:
                pointer     _array;
                size_type   _size;
                size_type   _max_size;
                size_type   _capacity;
                Allocator   _alloc;
			
	};

}