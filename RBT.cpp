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
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2){
        if (first1->first != first2->first || first1->second != first2->second)
        {
            std::cout << "false \n" << std::endl;
            std::cout << "first1 : " <<first1->first << " first2 : " << first2->first << std::endl;
            std::cout << "second1 : " << first1->second << " second2 : " << first2->second << "\n" << std::endl;
            // return false;
        }
        else {
            std::cout << " true \n" << std::endl;
            std::cout << "first1 : " <<first1->first << " first2 : " << first2->first << std::endl;
            std::cout << "second1 : " << first1->second << " second2 : " << first2->second << "\n" << std::endl;
        }
    }
    return true;
}

int main()
{
    bool cond(true);
    std::map<int, std::string> m2;
    ft::map<int, std::string> ft_m2;

    for (size_t i = 0; i < 5; i++)
    {
        m2.insert(std::make_pair(i, "string1"));
        ft_m2.insert(ft::make_pair(i, "string1"));
    }

    std::map<int, std::string>::reverse_iterator it2 = m2.rbegin();
    ft::map<int, std::string>::reverse_iterator ft_it2 = ft_m2.rbegin();

    std::map<int, std::string>::iterator it22 = m2.begin();
    ft::map<int, std::string>::iterator ft_it22 = ft_m2.begin();

    it22++;
    ft_it22++;

    std::cout << " rev it 2 : " << it2->first << std::endl;
    std::cout << " rev it 2 : " << ft_it2->first << std::endl << std::endl;
    std::cout << " m2 begin : " << it22->first << std::endl;
    std::cout << " ft_m2 begin : " << ft_it22->first << std::endl;
    
    m2.erase(m2.begin());
    ft_m2.erase(ft_m2.begin());

    ft_m2.print();

    std::cout << std::endl;

    std::cout << "rev it 2 : " << it2->first << std::endl;
    std::cout << "rev it 2 : " << ft_it2->first << std::endl << std::endl;
    std::cout << "m2 begin : " << it22->first << std::endl;
    std::cout << "ft_m2 begin : " << ft_it22->first << std::endl;
    
    // m2.erase(it2->first);
    // ft_m2.erase(ft_it2->first);
    // it22++;
    // ft_it22++;

    for (; it2 != m2.rend(); it2++)
    {
        std::cout << "it 2 : " << it2->first << std::endl;
    }
    std::cout << std::endl;
    for (; ft_it2 != ft_m2.rend(); ft_it2++)
    {
        std::cout << "ft_it 2 : " << ft_it2->first << std::endl;
    }

    std::cout << std::endl;


    for (; it22 != m2.end(); it22++)
    {
        std::cout << "it 2 : " << it22->first << std::endl;
    }
    std::cout << std::endl;
    for (; ft_it22 != ft_m2.end(); ft_it22++)
    {
        std::cout << "ft_it 2 : " << ft_it22->first << std::endl;
    }
    

    // for (; it2 != m2.rend(); it2++)
    // {
    //     std::cout << "it 2 : " << it2->first << std::endl;
    //     m2.erase(it2->first);
    // }
    // std::cout << std::endl;
    // for (; ft_it2 != ft_m2.rend(); ft_it2++)
    // {
    //     std::cout << "it 2 : " << ft_it2->first << std::endl;
    //     ft_m2.erase(ft_it2->first);
    // }

    // m2.erase(m2.begin());
    // ft_m2.erase(ft_m2.begin());
    // std::cout << "cond1 is : " << cond << std::endl;

    // // cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());
    // std::cout << "it 2 : " << it2->first <<  "size : " << m2.size() << std::endl;
    // std::cout << "ft it 2 : " << ft_it2->first<<  "size : " << ft_m2.size() << std::endl;




    // m2.erase(it2->first);
    // ft_m2.erase(ft_it2->first);

    // std::cout << "cond2 is : " << cond << std::endl;
    // cond = cond  && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());
    // //  && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end())

    // std::cout << "cond3 is : " << cond << std::endl;


    return 0;
    
}
