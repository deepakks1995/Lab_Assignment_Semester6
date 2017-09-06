#include<iostream>
#include "vector.hpp"
#include "sorter.hpp"


using std::cin;
using std::cout;
using namespace abc;
using namespace sort;

int main()
{
	vector <int> myvector;
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
	sorter<int> s;
	s.counting_sort(myvector,0,myvector.size()-1);
	/*
	vector<int>::vector_Iterator end = myvector.end();
	vector<int>::vector_Iterator* tmp = &end;*/
	vector<int>::vector_Iterator itr;
	cout<<"\n";
	for(itr=myvector.begin();itr!=myvector.end();++itr)
	{
		cout<<*itr<<"\t";
	}
	cout<<"\n";
	return 0;
}
