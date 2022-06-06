#include <iostream>       // std::cerr
#include <stdexcept>      // std::length_error
#include "vector.hpp" 
#include <vector>       // std::vector

int main (void)
{
    ft::vector<int> myvector;
    for (int i=1;i<18;i++) myvector.push_back(i);
    std::cout << "\ncapacity: " << myvector.capacity() << "\nsize : " << myvector.size()<< '\n';
    myvector.resize(33, 0);
    std::cout << "myvector contains:";
    for (int i=0;i<myvector.size();i++)
        std::cout << ' ' << myvector[i];
    std::cout << "\ncapacity: " << myvector.capacity() << "\nsize : " << myvector.size()<< '\n';




    return 0;
}