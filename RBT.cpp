#include <string>       // std::string
#include <iostream>
#include "map.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include <map>

void func(const ft::map<char,int> mymap)
{
    for(ft::map<char,int>::const_iterator it = mymap.begin(); it != mymap.end(); it++)
        std::cout << it->first << std::endl;

}
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

    ft::map<char,int> foo,bar, bir;
    foo['a']=100;
    foo['b']=200;
    bar['a']=10;
    bar['z']=1000;
    bir = foo;
    // foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
    if (foo==bir) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

    // std::map<char,int>::const_iterator it = mymap.begin();
    // std::cout << it->first << std::endl;
    // it++;
    // std::cout << it->first << std::endl;
    // for (c='a'; c<'h'; c++)
    // {
    //     std::cout << c;
    //     if (mymap.count(c)>0)
    //     std::cout << " is an element of mymap.\n";
    //     else 
    //     std::cout << " is not an element of mymap.\n";
    // }
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
