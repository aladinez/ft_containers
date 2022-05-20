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
            typedef std::random_acess_iterator_tag  iterator_category;

            iterator(): _ptr(){}
            iterator(pointer ptr): _ptr(ptr){}
            ~iterator(){}

            iterator(iterator const& it)
            {
                _ptr = it._ptr;
            }

            iterator &operator=(iterator const& it)
            {
                _ptr = it._ptr;
                return *this;
            }

            bool operator==(iterator const& it){return _ptr == it._ptr;}
            bool operator==(iterator const& it){return _ptr != it._ptr;}

            iterator  operator++(int) /* postfix */         {iterator it(*this); _ptr++; return it;}
            iterator& operator++()    /* prefix */          {_ptr++; return *this;}
            reference operator* () const                    {return *_ptr;}
            pointer   operator->() const                    {return _ptr;}
            iterator  operator+ (difference_type diff)const {return _ptr + diff;}
        
        private:
            pointer _ptr;

    };
}
