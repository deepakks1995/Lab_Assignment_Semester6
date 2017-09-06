#include<iostream>
#include "BSTree.hpp"
#include "Dictionary.hpp"
#include "list.hpp"




using namespace abc;
//using namespace node;
using namespace std;
void print(const int& key, const int& value)
	{
		cout<<"Key: "<<key<<"  Value: "<<value<<endl;
	}
int main()
{
	BSTree<int,int> bst;
	bst.put(15,1);
	bst.put(6,2);
	bst.put(18,3);
	bst.put(3,4);
	bst.put(7,5);
	bst.put(17,6);
	bst.put(20,7);
	bst.put(2,8);
	bst.put(4,9);
	bst.put(13,10);
	bst.put(9,11);
	

	try{
/*
		bst.remove(20);
		bst.remove(3);
		bst.remove(4);
		bst.remove(95);
		bst.remove(7);
		cout<<bst.has(15)<<endl;
		cout<<bst.getHeight()<<endl;
		cout<<bst.get(15)<<endl;
		cout<<bst.get(6)<<endl;
		cout<<bst.get(18)<<endl;
		cout<<bst.get(3)<<endl;
		cout<<bst.get(7)<<endl;
		cout<<bst.get(17)<<endl;
		cout<<bst.get(20)<<endl;
		cout<<bst.get(2)<<endl;
		cout<<bst.get(4)<<endl;
		cout<<bst.get(13)<<endl;
		cout<<bst.get(9)<<endl<<endl;*/
		bst.print_level_order();
		cout<<endl<<endl;
		bst.remove(6);
		bst.print_level_order();
	}
	catch(const char* c)
	{
		cout<<c<<endl;
	}

	/*
	   bst.put("hi",5);
	   bst.put("abc",6);
	   bst.put("cbd",7);
	   bst.put("zhgsj",8);
	   cout<<bst.get("cbde");*/
}
