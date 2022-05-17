#include "vector.hpp"
#include <iostream>
#include <vector>

int main()
{
    // ft::vector<int> second(4,100);
    // std::cout << second.capacity() << std::endl;

    ft::Vector<int> myvector;
    std::cout << "\ncapacity: " << myvector.capacity() << "\nsize : " << myvector.size()<< '\n';
    myvector.push_back(1);
    std::cout << "\ncapacity: " << myvector.capacity() << "\nsize : " << myvector.size()<< '\n';

  // set some initial content:
    for (int i=1;i<10;i++) myvector.push_back(i);

    myvector.resize(10, 88);
    myvector.resize(8,100);
    myvector.resize(18);

    std::cout << "myvector contains:";
    for (int i=0;i<myvector.size();i++)
        std::cout << ' ' << myvector[i];
    std::cout << "\ncapacity: " << myvector.capacity() << "\nsize : " << myvector.size()<< '\n';

    myvector.pop_back();
    myvector.pop_back();
    myvector.pop_back();

    std::cout << "myvector contains:";
    for (int i=0;i<myvector.size();i++)
        std::cout << ' ' << myvector[i];
    std::cout << "\ncapacity: " << myvector.capacity() << "\nsize : " << myvector.size()<< '\n';

    std::cout << !myvector.empty() << std::endl;
    return (0);    
}