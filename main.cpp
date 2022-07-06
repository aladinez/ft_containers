#include "vector.hpp"
#include <iostream>
#include <vector>
#define mine ft
#define other std

// #include "Iterator.hpp"

int main()
{
	std::vector<std::string> res;
	std::vector<std::string> res2;

	res.push_back(typeid(std::vector<int>::iterator::iterator_type).name());
	res2.push_back(typeid(ft::vector<int>::iterator::iterator_type).name());

  std::cout << *(res.begin()) << std::endl;
  std::cout << *(res2.begin()) << std::endl;
  
   
    return (0);    
}