#include "vector.hpp"
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> second(4,100);
    std::cout << second.max_size() << std::endl;
    return (0);    
}