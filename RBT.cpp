#include <string>       // std::string
#include <iostream>
#include "map.hpp"
#include "pair.hpp"


int main()
{

    // ft::map<int, std::string> tree;

    
    // ft::pair<int, std::string> p = ft::make_pair(10, "alae");
    // tree.insert(p);
    // tree.print();

    // // ft::map<int, std::string> tree2;
    // // tree2 = tree;
    // // tree2.print();

    // p = ft::make_pair(15, "coucou");
    // tree.insert(p);
    // // tree.print();
    // // tree2.print();

    // ft::map<int, std::string>::iterator it = tree.begin();
    // std::cout << it->first << std::endl;
    // --it;
    // std::cout << it->first << std::endl;
    // std::cout << tree[15] << " tree.size : " << tree.size() << std::endl;
    // tree[15] = "fofo";
    // std::cout << tree[15] << " tree.size : " << tree.size() << std::endl;
    // std::cout << tree[3] << " tree.size : " << tree.size() << tree[3] << std::endl;
    // tree.print();


    ft::map<char,int> mymap;

    mymap['x']=1001;
    mymap['y']=2002;
    mymap['z']=3003;

    std::cout << "mymap contains:\n";

    ft::pair<char,int> highest = *mymap.rbegin();          // last element

    ft::map<char,int>::iterator it = mymap.begin();
    do {
        std::cout << it->first << " => " << it->second << '\n';
    } while ( mymap.value_comp()(*it++, highest) );

    return 0;
    // ft::RB_tree<int> tree;
    // tree.insert(11);
    // tree.insert(2);
    // tree.insert(14);
    // tree.insert(1);
    // tree.insert(15);
    // tree.insert(7);
    // tree.insert(5);
    // tree.insert(8);
    // tree.print_tree();
    // tree.insert(4);
    // tree.print_tree();
    // tree.remove(7);
    // tree.print_tree();
     // std::cout


    // ft::Node<int>* s = tree.search(23);
    // std::cout << s->key << std::endl;
    // tree.left_rotate(s);
    // tree.print_tree();
    // s = tree.search(30);
    // std::cout << s->key << std::endl;

    // tree.right_rotate(s);
    // tree.print_tree();
    
}
