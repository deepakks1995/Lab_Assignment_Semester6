#include<iostream>
#include "vector.hpp"
using std::cin;
using std::cout;
using namespace abc;
int main()
{
	vector <int> myvector;
	vector<int> ve(3);
	cout<<ve.size()<<"\n";
	cout<<myvector.empty()<<"\n";;
	cout<<myvector.size()<<"\n";
	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);

	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);

	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);   
	cout<<myvector.size()<<"\n";
	/*
	vector<int>::vector_Iterator end = myvector.end();
	vector<int>::vector_Iterator* tmp = &end;*/
	vector<int>::vector_Iterator itr;
	cout<<"\n";
	myvector[0]=6;
	for(itr=myvector.rbegin();itr!=myvector.rend();--itr)
	{
		cout<<*itr<<"\t";
	}/*
	cout<<"\n";
	for(it:myvector)
		cout<<it<<" ";
	cout<<"\n";*/
	return 0;
}
