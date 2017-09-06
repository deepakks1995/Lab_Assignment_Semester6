#include<iostream>
#include "AVL.hpp"
#include "Dictionary.hpp"
//#include "BSTree.hpp"
using namespace abc;
using namespace std;


int main()
{
	AVL<int, int> a;
	a.put(10,1);
	a.put(5,2);
	a.put(20,3);
	a.put(3,4);
	a.put(7,5);
	a.put(15,6);
	a.put(30,7);
	a.put(2,8);
	a.put(4,9);
	a.put(8,10);
	a.put(40,11);
	a.put(1,12);
	cout<<a.maximum()<<endl;

try{
/*
		a.remove(20);
		a.remove(3);
		a.remove(4);
		a.remove(95);
		a.remove(7);*/
		//cout<<a.has(15)<<endl;
		cout<<a.getHeight()<<endl;
		a.print_level_order();
		a.remove(10);
		a.remove(5);

		//a.remove(30);
		cout<<a.size()<<endl<<endl;
		cout<<a.getHeight()<<endl;;
		a.print_in_order();
	}
	catch(const char* c)
	{
		cout<<c<<endl;
	}
}

