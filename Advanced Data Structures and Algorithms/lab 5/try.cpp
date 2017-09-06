#include<iostream>
#include "Dictionary.hpp"
#include "BSTree.hpp"
using namespace abc;
using namespace std;
int main(void)
{
  BSTree<int,int> bst;
  bst.put(15,1);
  bst.put(6,2);
  bst.put(18,3);
  bst.put(3,4);
  bst.put(7,5);
  bst.put(2,6);
  bst.put(4,7);
  bst.put(13,8);
  bst.put(9,9);
  bst.put(14,10);
  bst.put(17,11);
  bst.put(20,12);
  bst.remove(14);
  bst.put(20,100);
  //bst.remove(15);
  std::cout<<"minimum : "<<bst.minimum()<<"\n";
  std::cout<<"maximum : "<<bst.maximum()<<"\n";
  std::cout<<"successor(6) : "<<bst.successor(6)<<"\n";
  std::cout<<"successor(7) : "<<bst.successor(7)<<"\n";
  std::cout<<"successor(9) : "<<bst.successor(9)<<"\n";
  std::cout<<"successor(13) : "<<bst.successor(13)<<"\n";
  //std::cout<<"successor(20) : "<<bst.successor(20)<<"\n";
  std::cout<<"successor(4) : "<<bst.successor(4)<<"\n";
  std::cout<<"predecessor(6) : "<<bst.predecessor(6)<<"\n";
  std::cout<<"predecessor(7) : "<<bst.predecessor(7)<<"\n";
  std::cout<<"predecessor(9) : "<<bst.predecessor(9)<<"\n";
  std::cout<<"predecessor(13) : "<<bst.predecessor(13)<<"\n";
  std::cout<<"predecessor(20) : "<<bst.predecessor(20)<<"\n";
  std::cout<<"predecessor(4) : "<<bst.predecessor(4)<<"\n";
  //std::cout<<"predecessor(2) : "<<bst.predecessor(2)<<"\n";
  std::cout<<"has(9) : "<<bst.has(9)<<"\n";
  //std::cout<<"has(14) : "<<bst.has(14)<<"\n";
  //std::cout<<"has(100) : "<<bst.has(100)<<"\n";
  std::cout<<"get(20) : "<<bst.get(20)<<"\n";
  //std::cout<<"get(100) : "<<bst.get(100)<<"\n";
  bst.print_pre_order();
  std::cout<<bst.size()<<"\n";
  std::cout<<bst.getHeight()<<"\n";
  return 0;
}
