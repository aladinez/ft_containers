#include "vector.hpp"
#include <iostream>
#include <vector>
#define mine ft
#define other std

// #include "Iterator.hpp"

int main()
{
    // ft::vector<int> second(4,100);
    // std::cout << second.capacity() << std::endl;
  other::vector<int> myvector (3,100);
  other::vector<int>::iterator it;

std::cout << "\nmyvector contains: cap= " << myvector.capacity() << "\n";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );


  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();


  other::vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  std::cout << "\nmyvector contains: cap= " << myvector.capacity() << "\n";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);
  myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "\nmyvector contains: cap= " << myvector.capacity() << "\n";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';
   
    return (0);    
}