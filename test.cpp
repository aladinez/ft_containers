#include <iostream>       // std::cerr
#include <stdexcept>      // std::length_error
#include "vector.hpp" 
#include <vector>       // std::vector

int main (void)
{
    //  resize test
    ft::vector<int> myvector;
    for (int i=1;i<18;i++) myvector.push_back(i);
    std::cout << "\ncapacity: " << myvector.capacity() << "\nsize : " << myvector.size()<< '\n';
    myvector.resize(10, 0);
    std::cout << "myvector contains:";
    for (int i=0;i<myvector.size();i++)
        std::cout << ' ' << myvector[i];
    std::cout << "\ncapacity: " << myvector.capacity() << "\nsize : " << myvector.size()<< '\n';
    // */

    /* operator=
    ft::vector<int> vec;
    for (int i=1;i<18;i++) vec.push_back(i + 4);
    vec = myvector;
    std::cout << "myvector contains:";
    for (int i=0;i<vec.size();i++)
        std::cout << ' ' << vec[i];
    std::cout << "\ncapacity: " << vec.capacity() << "\nsize : " << vec.size()<< '\n';
    */

    ft::vector<int> vec;
    std::vector<int> second;
    std::vector<int> third;

    vec.assign (7,100); 
    for (int i=0;i<vec.size();i++)
        std::cout << ' ' << vec[i];
    std::cout << "\ncapacity: " << vec.capacity() << "\nsize : " << vec.size()<< '\n';

    vec.assign (myvector.begin(), myvector.end());
    for (int i=0;i<vec.size();i++)
        std::cout << ' ' << vec[i];
    std::cout << "\ncapacity: " << vec.capacity() << "\nsize : " << vec.size()<< '\n';

    return 0;
}