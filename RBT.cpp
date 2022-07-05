#include <string>       // std::string
#include <iostream>
#include "map.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include <vector>
#include <map>
int _ratio = 10000;





int main()
{
    /*
    {

        ft::map<int, int> mp;
        std::vector<int> v;
        ft::map<int, int, std::greater<int> > mp2;
        mp.insert(ft::make_pair(10, 10));
        mp2.insert(ft::make_pair(10, 10));
        if (mp.lower_bound(11) == mp.end())
            v.push_back(1);
        if (mp2.lower_bound(1) == mp2.end())
            v.push_back(1);
        mp.insert(ft::make_pair(20, 20));
        mp.insert(ft::make_pair(30, 30));
        mp.insert(ft::make_pair(40, 40));
        mp.insert(ft::make_pair(50, 50));
        mp.insert(ft::make_pair(60, 60));
        mp2.insert(ft::make_pair(20, 20));
        mp2.insert(ft::make_pair(30, 30));
        mp2.insert(ft::make_pair(40, 40));
        mp2.insert(ft::make_pair(50, 50));
        mp2.insert(ft::make_pair(60, 60));
        ft::map<int, int>::iterator it;
        for (int i = 1; i < 60; i += 10) {
            it = mp.lower_bound(i);
            v.push_back(it->first);
        }
        for (int i = 11; i < 70; i += 10) {
            it = mp2.lower_bound(i);
            v.push_back(it->first);
        }
        ft::map<int, int> mp3;
        for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
            mp3.insert(ft::make_pair(i, j));
        }
        mp3.lower_bound(49 *_ratio);
        std::cout << "v1 size : " << v.size() << '\n';
        for (size_t i = 0; i < v.size(); i++) {
            std::cout << v[i] << ' ';
        }
        std::cout << '\n';
    }
    {
        std::map<int, int> mp;
        std::vector<int> v;
        std::map<int, int, std::greater<int> > mp2;
        mp.insert(std::make_pair(10, 10));
        mp2.insert(std::make_pair(10, 10));
        if (mp.lower_bound(11) == mp.end())
            v.push_back(1);
        if (mp2.lower_bound(1) == mp2.end())
            v.push_back(1);
        mp.insert(std::make_pair(20, 20));
        mp.insert(std::make_pair(30, 30));
        mp.insert(std::make_pair(40, 40));
        mp.insert(std::make_pair(50, 50));
        mp.insert(std::make_pair(60, 60));
        mp2.insert(std::make_pair(20, 20));
        mp2.insert(std::make_pair(30, 30));
        mp2.insert(std::make_pair(40, 40));
        mp2.insert(std::make_pair(50, 50));
        mp2.insert(std::make_pair(60, 60));
        std::map<int, int>::iterator it;
        for (int i = 1; i < 60; i += 10) {
            it = mp.lower_bound(i);
            v.push_back(it->first);
        }
        for (int i = 11; i < 70; i += 10) {
            it = mp2.lower_bound(i);
            v.push_back(it->first);
        }
        std::map<int, int> mp3;
        for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
            mp3.insert(std::make_pair(i, j));
        }
        mp3.lower_bound(49 *_ratio);
        std::cout << "v1 size : " << v.size() << '\n';
        for (size_t i = 0; i < v.size(); i++) {
            std::cout << v[i] << ' ';
        }
        std::cout << '\n';
    }/*/
    
    {
        ft::map<int, int> mp;
        mp.insert(ft::make_pair(20, 20));
        mp.insert(ft::make_pair(30, 30));
        mp.insert(ft::make_pair(40, 40));
        mp.insert(ft::make_pair(50, 50));
        mp.insert(ft::make_pair(60, 60));
        
        ft::map<int, int>::iterator it;
        for (int i = 1; i < 60; i += 10) {
            it = mp.lower_bound(i);
            std::cout << it->first << std::endl;
        }
        std::cout << '\n';
    }
    {
        std::map<int, int> mp;
        mp.insert(std::make_pair(20, 20));
        mp.insert(std::make_pair(30, 30));
        mp.insert(std::make_pair(40, 40));
        mp.insert(std::make_pair(50, 50));
        mp.insert(std::make_pair(60, 60));
        
        std::map<int, int>::iterator it;
        for (int i = 1; i < 60; i += 10) {
            it = mp.lower_bound(i);
            std::cout << it->first << std::endl;
        }
    } 

    std::map<char,int> mymap;
    std::map<char,int>::iterator itlow,itup;

    mymap['a']=20;
    mymap['b']=40;
    mymap['c']=60;
    mymap['d']=80;
    mymap['e']=100;

    itlow=mymap.lower_bound ('c');  // itlow points to b
    itup=mymap.upper_bound ('c');   // itup points to e (not d!)

    std::cout << "lowr : " << itlow->first << std::endl;
    std::cout << "upp : " << itup->first << std::endl;
    // ft::map<int, int> my_map;
    // lower_bound_test(my_map);

    // compilation error in mosan's tester
    ft::map<int, char>::iterator my_it, my_it1, tmp;
    ft::map<int, char>::const_iterator c_it, c_ob(my_it);

    // std::map<char,int> mymap;

    // mymap['a']=10;
    // mymap['b']=20;
    // mymap['c']=30;

    // std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
    // ret = mymap.equal_range(120);

    // std::cout << "lower bound points to: ";
    // std::cout << ret.first->first << " => " << ret.first->second << '\n';

    // std::cout << "upper bound points to: ";
    // std::cout << ret.second->first << " => " << ret.second->second << '\n';
    
    
    // ft::map<char,int> mymap;
    // ft::map<char,int>::iterator itlow,itup;

    // mymap['a']=20;
    // mymap['b']=40;
    // mymap['c']=60;
    // mymap['d']=80;
    // mymap['e']=100;

    // itlow=mymap.lower_bound ('a');  // itlow points to b
    // itup=mymap.upper_bound ('d');   // itup points to e (not d!)

    // std::cout << itlow->first << std::endl;

    // mymap.erase(itlow,itup);        // erases [itlow,itup)

    // // print content:
    // for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    //     std::cout << it->first << " => " << it->second << '\n';



    return 0;
    
}
