#include <memory>
#include <cstddef>

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
		public: 
			typedef typename Allocator::reference           reference;
			typedef typename Allocator::const_reference     const_reference;

			typedef typename std::size_t					size_type;
			// typedef implementation defined                  difference_type;

			typedef T                                       value_type;
			typedef Allocator                               allocator_type;
			typedef typename Allocator::pointer             pointer;
			typedef typename Allocator::const_pointer       const_pointer;

            // 23.2.4.1 construct/copy/destroy:
            explicit vector(const Allocator& = Allocator()) : _array(), _size(), _capacity(){}
			explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator()): _size(n), _capacity(n)
			{
				// _array = _alloc.allocate(_size);
                
				for(int i = 0; i < _size; i++)
					_array[i] = value;
			}
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last, const Allocator& = Allocator());
			// vector(const vector<T,Allocator>& x);
			~vector(){}

            // 23.2.4.2 capacity:
			size_type   size() const{return _size;}
			size_type   max_size() const{return _max_size;} // is the theoretical maximum number of items that could be put in your vector


            private:
                pointer     _array;
                size_type   _size;
                size_type   _max_size;
                size_type   _capacity;
                Allocator   _alloc;
			
	};

}