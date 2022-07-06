#include <string>       // std::string
#include <iostream>
#include "map.hpp"
#include "vector.hpp"
#include "Utility.hpp"
#include <vector>
#include <map>

// #include <iostream>
 
// template<typename T> // primary template
// class is_void
// : public std::false_type 
// {};
// template<>           // explicit specialization for T = void
// class is_void<void>
// : public std::true_type 
// {};
 
// int main()
// {
//     // for any type T other than void, the class is derived from false_type
//     std::cout << is_void<char>::value << '\n'; 
//     // but when T is void, the class is derived from true_type
//     std::cout << is_void<void>::value << '\n';
// }


// template <bool>
// struct foo;

// template <>
// struct foo<true>
//  { typedef int myType1; }; // or using myType1 = int;

// template <>
// struct foo<false>
//  { };

// template <class T> struct is_integral_base
// {
//     X<float, int, 10> a;
//     if (a.f())
//         typedef
// }





// template<class T, class U, int I> struct X
//   { bool f() { return false; } };

// template<class T, int I> struct X<T, T*, I>
//   { bool f() { return true;
//   } };

// template<class T, class U, int I> struct X<T*, U, I>
//   { bool f() { return true;
//   } };

// template<class T> struct X<int, T*, 10>
//   { bool f() { return true;
//   } };

// template<class T, class U, int I> struct X<T, U*, I>
//   { bool f() { return true;
//   } };

int main() {
//    X<float, int, 10> a;
// //    X<int, int*, 5> b;
// //    X<int*, float, 10> c;
// //    X<int, char*, 10> d;
// //    X<float, int*, 10> e;
// //   X<int, int*, 10> f;
//    a.f(); 
// //    b.f(); c.f(); d.f(); e.f();

  std::cout << std::boolalpha;
  std::cout << "is_integral:" << std::endl;
  std::cout << "char: " << ft::is_integral<char>::value << std::endl;
  std::cout << "int: " << ft::is_integral<int>::value << std::endl;
  std::cout << "float: " << ft::is_integral<float>::value << std::endl;  

}
