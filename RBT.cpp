#include <string>       // std::string
#include <iostream>
#include "map/map.hpp"
#include "set/set.hpp"
#include "vector/vector.hpp"
#include "Utility.hpp"
#include <vector>
#include <map>
#include <set>

#define _ns ft

int main() 
{ 

    // ------- std::set -------- //
    {
      int myints[]= {10,20,30,40,50};
      _ns::set<int> first(myints,myints+5);                           // empty set of ints
      _ns::set<int>::iterator it;

      for (it = first.begin(); it != first.end(); it++)
      {
          std::cout << *it << " ";
      }
      std::cout << "\n";
      for (int i = 0; i < 1000; i++)
        first.insert(i);

      for (it = first.begin(); it != first.end(); it++)
      {
          std::cout << *it << " ";
      }
      std::cout << "\n";
      

    }
    {
      _ns::map<char,int> mymap;
      // first insert function version (single parameter):
      mymap.insert ( ft::pair<char,int>('a',100) );
      mymap.insert ( ft::pair<char,int>('z',200) );

      _ns::pair<_ns::map<char,int>::iterator,bool> ret;
      ret = mymap.insert ( _ns::pair<char,int>('z',500) );
      if (ret.second==false) {
        std::cout << "element 'z' already existed";
        std::cout << " with a value of " << ret.first->second << '\n';
      }

      // second insert function version (with hint position):
      std::map<char,int>::iterator it = mymap.begin();
      mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
      mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting

      // third insert function version (range insertion):
      std::map<char,int> anothermap;
      anothermap.insert(mymap.begin(),mymap.find('c'));

      // showing contents:
      std::cout << "mymap contains:\n";
      for (it=mymap.begin(); it!=mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

      std::cout << "anothermap contains:\n";
      for (it=anothermap.begin(); it!=anothermap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
    }

    return 0;
}