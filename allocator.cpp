#include <iostream>
#include <memory>


int main()
{
  
    // allocator for integer values
    std::allocator<int> myAllocator;
  
    // allocate space for five ints
    int* arr = myAllocator.allocate(10);
  
    // construct arr[0] and arr[3]
    myAllocator.construct(arr, 50);
    arr[3] = 99;
    int i = -1;
    while (arr[++i])
        std::cout << arr[i] << std::endl;
    // std::cout << arr[3] << std::endl;
    // std::cout << arr[0] << std::endl;
  std::vector<int, ALOC> vec()
    // deallocate space for five ints 
    myAllocator.deallocate(arr, 5);
  
    return 0;
}