#ifndef _REV_ITERATOR_HPP
#define _REV_ITERATOR_HPP

#include "iterator_traits.hpp"

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
                reverse_iterator (const reverse_iterator<Iter>& rev_it): _base(rev_it._base){}

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
}

#endif