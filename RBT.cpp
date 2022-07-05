#include <string>       // std::string
#include <iostream>
#include "map.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include <vector>
#include <map>
int _ratio = 10000;



template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

int main()
{
    bool cond(true);
    std::map<int, std::string> m2;
    ft::map<int, std::string> ft_m2;

    for (size_t i = 0; i < 1e5; i++)
    {
        m2.insert(std::make_pair(i, "string1"));
        ft_m2.insert(ft::make_pair(i, "string1"));
    }

    std::map<int, std::string>::reverse_iterator it2 = m2.rbegin();
    ft::map<int, std::string>::reverse_iterator ft_it2 = ft_m2.rbegin();

    m2.erase(m2.begin());
    ft_m2.erase(ft_m2.begin());
    std::cout << "cond1 is : " << cond << std::endl;

    cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

    m2.erase(it2->first);
    ft_m2.erase(ft_it2->first);

    std::cout << "cond2 is : " << cond << std::endl;
    cond = cond  && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());
    //  && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end())

    std::cout << "cond3 is : " << cond << std::endl;


    return 0;
    
}
