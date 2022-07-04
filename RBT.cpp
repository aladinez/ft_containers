#include <string>       // std::string
#include <iostream>
#include "map.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include <vector>
#include <map>
int _ratio = 10000;
void func(const ft::map<char,int> mymap)
{
    for(ft::map<char,int>::const_iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << it->first << std::endl;

}

    template <class T, class V>
    void clear_test(ft::map<T, V> mp) {
    std::vector<int> v;
    mp.clear();
    int i, j;
    for ( i = 0, j = 0; i < 25 * _ratio; ++i, ++j)
        mp.insert(ft::make_pair(i, j));
    v.push_back(mp.size());
    mp.clear();
    v.push_back(mp.size());
    typename ft::map<T, V>::iterator it = mp.begin();
    if (it == mp.end())
        v.push_back(1);
    }
int main()
{

    
    // ft::map<int, int> my_map;
    // clear_test(my_map);

    // compilation error in mosan's tester
    // ft::map<int, char>::iterator my_it, my_it1, tmp;
    // ft::map<int, char>::const_iterator c_it, c_ob(my_it);

    std::map<char,int> mymap;

    mymap['a']=10;
    mymap['b']=20;
    mymap['c']=30;

    std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
    ret = mymap.equal_range(4);

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';

    return 0;
    
}
