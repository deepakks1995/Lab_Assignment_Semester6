#include<iostream>
#include "vector.hpp"
#include "ChainedMap.hpp"
#include "Dictionary.hpp"
//#include "list.hpp"
using namespace abc;
//using namespace node;
using namespace std;



int main()
{


	ChainedMap<int,int> ch(8);
	ch.put(1,5);
	ch.put(25,50);
	ch.put(9,68);
	cout<<"length: "<<ch.length()<<endl;
	ch.put(1,5);
	ch.put(25,50);
	ch.put(9,68);
	cout<<ch[9];
	ch[9] = 100;
	cout<<ch.get(9);
	
cout<<"length: "<<ch.length()<<endl;
}
