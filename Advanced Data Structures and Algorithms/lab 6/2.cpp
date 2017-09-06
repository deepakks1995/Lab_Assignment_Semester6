#include<iostream>
#include "RBTree.hpp"
#include "Dictionary.hpp"
//#include "BSTree.hpp"
using namespace abc;
using namespace std;

int main()
{
	RBTree<int, int> a;
	/*a.put(1,1);
	a.put(2,1);
	a.put(3,1);
	a.put(4,1);
	a.put(5,1);*/
	a.put(25,1);
	a.put(14,2);
	a.put(31,3);
	a.put(10,4);
	a.put(16,5);
	a.put(27,6);
	a.put(33,7);
	a.put(7,8);
	a.put(12,9);
	a.put(15,10);
	a.put(18,11);
	a.put(30,12);
	cout<<a.size()<<endl<<endl;
	a.put(13,5);
	a.put(29,5);
	a.print_level_order();
	a.remove(12);
	a.remove(13);
	a.remove(25);
	cout<<endl<<endl;
	a.print_level_order();	
try{	}
	catch(const char* c)
	{
		cout<<c<<endl;
	}
}



