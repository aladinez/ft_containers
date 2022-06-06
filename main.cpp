#include "vector.hpp"
#include <iostream>
#include <vector>

// #include "Iterator.hpp"

int main()
{
    // ft::vector<int> second(4,100);
    // std::cout << second.capacity() << std::endl;

    ft::vector<int>  myvector;
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

    // myvector.pop_back();
    // myvector.pop_back();
    // myvector.pop_back();

    // std::cout << "myvector contains:";
    // for (int i=0;i<myvector.size();i++)
    //     std::cout << ' ' << myvector[i];
    // std::cout << "\ncapacity: " << myvector.capacity() << "\nsize : " << myvector.size()<< '\n';

    // std::cout << !myvector.empty() << std::endl;

    ft::vector<int> vec(myvector.begin(), myvector.end());
    std::cout << "vec contains:";
    for (int i=0;i<vec.size();i++)
        std::cout << ' ' << vec[i];
    std::cout << "\ncapacity: " << vec.capacity() << "\nsize : " << vec.size()<< '\n';

    ft::vector<int>::reverse_iterator it1 = myvector.rbegin();
    ft::vector<int>::reverse_iterator it2 = vec.rbegin();


    while (it1 != myvector.rend())
    {
        std::cout << *it1 << " : " << *it2 << std::endl;
        ++it1;
        ++it2;
    }
    
    if (vec == myvector) 
        std::cout << "Equal\n";
    //iterator tests:
    // ft::vector<int>::iterator it = myvector.begin();
    // std::cout << *it << std::endl;
    // it++;
    // it++;
    // std::cout << *it << std::endl;
    
    // std::cout << *(it + 4) << std::endl;
    return (0);    
}