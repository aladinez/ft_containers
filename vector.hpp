#include <memory>

namespace ft {
    template <class T, class Allocator = std::allocator<T> >
    class vector {
        private:
            pointer array;
        public: 
            typedef typename Allocator::reference           reference;
            typedef typename Allocator::const_reference     const_reference;
            // typedef implementation defined                  iterator;
            // typedef implementation defined                  const_iterator;
            // typedef implementation defined                  size_type;
            // typedef implementation defined                  difference_type;
            typedef T                                       value_type;
            typedef Allocator                               allocator_type;
            typedef typename Allocator::pointer             pointer;
            typedef typename Allocator::const_pointer       const_pointer
            typedef std::reverse_iterator<iterator>         reverse_iterator;
            typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;


            // 23.2.4.1 construct/copy/destroy:
            explicit vector(const Allocator& = Allocator());
            explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator());
            template <class InputIterator>
            vector(InputIterator first, InputIterator last, const Allocator& = Allocator());
            vector(const vector<T,Allocator>& x);
            ~vector();
            vector<T,Allocator>& operator=(const vector<T,Allocator>& x);
            template <class InputIterator>
            void assign(InputIterator first, InputIterator last);
            void assign(size_type n, const T& u);
            allocator_type get_allocator() const;
            
            // iterators:
            iterator begin();
            const_iterator begin()const;
            iterator end(); const_iterator end()const;
            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            reverse_iterator rend();
            const_reverse_iterator rend() const;

            // 23.2.4.2 capacity:
            size_type   size() const;
            size_type   max_size() const;
            void        resize(size_type sz, T c = T()); size_type capacity() const;
            bool        empty()const;
            void        reserve(size_typen);


            // element access:
            reference       operator[](size_typen);
            const_reference operator[](size_type n) const;
            const_reference at(size_type n) const;
            reference       at(size_typen);
            reference       front();
            const_reference front() const;
            reference       back();
            const_reference back() const;

            // 23.2.4.3 modifiers:
            void push_back(const T& x);
            void pop_back();
            iterator insert(iterator position, const T& x);
            void insert(iterator position, size_type n, const T& x);
            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last);
            iterator erase(iterator position);
            iterator erase(iterator first, iterator last);
            void     swap(vector<T,Allocator>&);
            void     clear();
    };      

            
    template <class T, class Allocator>
        bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
    template <class T, class Allocator>
        bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
    template <class T, class Allocator>
        bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
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