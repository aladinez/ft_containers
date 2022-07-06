#pragma once

namespace ft 
{
    template <class T>
    struct is_integral
    {
        static const bool value = false;
        operator bool() {return value;}
    };
    template <>
    struct is_integral<bool> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<char> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<char16_t> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<char32_t> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<wchar_t> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<signed char> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<short int> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<int> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<long int> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<long long int> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<unsigned char> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<unsigned short int> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<unsigned int> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<unsigned long int> {static const bool value = true;
        operator bool(){return value;}};
    template <>
    struct is_integral<unsigned long long int> {static const bool value = true;
        operator bool(){return value;}};

	template <class T>
	class Identify
	{
		public:
			static const bool is_true = true;
	};

	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { 
		typedef T type; 
	};
	
	template <class Iterator> 
	class iterator_traits
	{
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T> 
	class iterator_traits<T*>
	{
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};
	
	template <class T>
	class iterator_traits<const T*>
	{
		public:	
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};
}

namespace ft
{
        template <class Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator                                                iterator_type;
            typedef typename iterator_traits<Iterator>::value_type          value_type;
            typedef typename iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename iterator_traits<Iterator>::pointer             pointer;   
            typedef typename iterator_traits<Iterator>::reference           reference;
            typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;


            //constructors
            reverse_iterator(): _base(){}
            explicit reverse_iterator (iterator_type it): _base(it) {}
            template <class Iter>
                reverse_iterator (const reverse_iterator<Iter>& rev_it): _base(rev_it.base()){}

            // base
            iterator_type base() const {return iterator_type(_base);}

            //operators
            reference operator*() const
            {
                iterator_type tmp(_base);
                --tmp;
                return *tmp;
            }
            reverse_iterator operator+ (difference_type n) const {return reverse_iterator(iterator_type(_base - n));}
            reverse_iterator& operator++(){_base--; return *this;}
            reverse_iterator  operator++(int)
            {
                reverse_iterator temp = *this;
                ++(*this);
                return temp;
            }
            reverse_iterator& operator+= (difference_type n){_base -= n; return *this;}
            reverse_iterator operator- (difference_type n) const {return reverse_iterator(iterator_type(_base + n));}
            reverse_iterator& operator--(){_base++; return *this;}
            reverse_iterator  operator--(int)
            {
                reverse_iterator temp = *this;
                --(*this);
                return temp;
            }
            reverse_iterator& operator-= (difference_type n) {_base += n; return *this;}
            pointer operator->() const {return &(operator*());}
            reference operator[] (difference_type n) const {return *(_base -n - 1);}

        private:
            iterator_type _base;
    };
    template <class Iterator>
        bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() == rhs.base();}

    template <class Iterator>
        bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() != rhs.base();}

    template <class Iterator>
        bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() > rhs.base();}

    template <class Iterator>
        bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() >= rhs.base();}

    template <class Iterator>
        bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() < rhs.base();}

    template <class Iterator>
        bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() <= rhs.base();}

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (rhs.base() - lhs.base());
    }
    template <class Iterator>
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
    {
        return (rev_it + n);
    }
}

namespace ft
{
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
}

namespace ft {
    template <class T1, class T2>
        struct pair
        {
            typedef T1		first_type;
            typedef T2		second_type;

            first_type first;
            second_type second;

            pair(): first(), second() {}
            pair (const first_type& a, const second_type& b): first(a), second(b) {}
            template<class U, class V>
            pair (const pair<U,V>& pr): first(pr.first), second(pr.second){}

            pair& operator= (const pair& pr)
            {
                first = pr.first;
                second = pr.second;
                return *this;
            }
        };
        template <class T1, class T2>
        bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return lhs.first==rhs.first && lhs.second==rhs.second; }

        template <class T1, class T2>
        bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return !(lhs==rhs); }

        template <class T1, class T2>
        bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

        template <class T1, class T2>
        bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return !(rhs<lhs); }

        template <class T1, class T2>
        bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return rhs<lhs; }

        template <class T1, class T2>
        bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return !(lhs<rhs); }
    
    template <class T1,class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return ( pair<T1,T2>(x,y) );
    }
}