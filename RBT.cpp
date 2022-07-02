#include <string>       // std::string
#include <iostream>
#include "map.hpp"
#include "pair.hpp"


int main()
{

    ft::map<int, std::string> tree;

    
    ft::pair<int, std::string> p = ft::make_pair(10, "alae");
    tree.insert(p);
    tree.print();

    // ft::map<int, std::string> tree2;
    // tree2 = tree;
    // tree2.print();

    p = ft::make_pair(15, "coucou");
    tree.insert(p);
    // tree.print();
    // tree2.print();

    ft::map<int, std::string>::iterator it = tree.begin();
    std::cout << it->first << std::endl;
    --it;
    std::cout << it->first << std::endl;
    std::cout << tree[15] << " tree.size : " << tree.size() << std::endl;
    tree[15] = "fofo";
    std::cout << tree[15] << " tree.size : " << tree.size() << std::endl;
    std::cout << tree[3] << " tree.size : " << tree.size() << tree[3] << std::endl;
    tree.print();

    ft::map<char,int> mymap;
  // first insert function version (single parameter):
    mymap.insert ( ft::pair<char,int>('a',100) );
    mymap.insert ( ft::pair<char,int>('z',200) );

    ft::pair<ft::map<char,int>::iterator,bool> ret;
    ret = mymap.insert ( ft::pair<char,int>('z',500) );
    if (ret.second==false) {
        std::cout << "element 'z' already existed";
        std::cout << " with a value of " << ret.first->second << '\n';
    }

    // second insert function version (with hint position):
    ft::map<char,int>::iterator it1 = mymap.begin();
    mymap.insert (it1, ft::pair<char,int>('b',300));  // max efficiency inserting
    mymap.insert (it1, ft::pair<char,int>('c',400));

    mymap.print();

    // third insert function version (range insertion):
    ft::map<char,int> anothermap;
    // anothermap.insert(mymap.begin(),mymap.find('c'));
    anothermap.insert(mymap.begin(),--mymap.end());

    // std::cout << (mymap.find('c'))->second << std::endl;

    // showing contents:
    std::cout << "mymap contains:\n";
    for (it1=mymap.begin(); it1!=mymap.end(); ++it1)
        std::cout << it1->first << " => " << it1->second << '\n';

    std::cout << "anothermap contains:\n";
    for (it1=anothermap.begin(); it1!=anothermap.end(); ++it1)
        std::cout << it1->first << " => " << it1->second << '\n';



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
