#include <iostream>       // std::cerr
#include <stdexcept>      // std::length_error
#include "vector.hpp" 
#include <vector>       // std::vector


bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

int main (void)
{
    /* resize test
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

   /*
    ft::vector<int> vec;
    std::vector<int> second;
    std::vector<int> third;

    // vec.assign (7,100);
    for (int i=0;i<vec.size();i++)
        std::cout << ' ' << vec[i];
    std::cout << "\ncapacity: " << vec.capacity() << "\nsize : " << vec.size()<< '\n';

    vec.assign (myvector.begin(), myvector.end());
    std::cout << "vec contains:";
    for (int i=0;i<vec.size();i++)
        std::cout << ' ' << vec[i];
    std::cout << "\ncapacity: " << vec.capacity() << "\nsize : " << vec.size()<< '\n';
    */

/* erase

  // set some values (from 1 to 10)
  for (int i=1; i<=10; i++) myvector.push_back(i);

  // erase the 6th element
  myvector.erase (myvector.begin()+5);
    std::cout << "\ncapacity: " << myvector.capacity() << "\nsize : " << myvector.size()<< '\n';


  // erase the first 3 elements:
  myvector.erase (myvector.begin(),myvector.begin()+3);
    std::cout << "\ncapacity: " << myvector.capacity() << "\nsize : " << myvector.size()<< '\n';

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

*/
  //  std::vector<int> myvector;
  ft::vector<int> first(7, 100);
  ft::vector<int>::iterator it = first.begin();
  it += 4;
  int a = 2;

  first.insert(it, a);
  
  
    return 0;
}