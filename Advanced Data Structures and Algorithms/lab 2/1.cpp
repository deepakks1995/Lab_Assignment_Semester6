#include<iostream>
#include"vector.hpp"
#include"sorter.hpp"
using std::cin;
using std::cout;
using namespace abc;


using namespace sort;
int main()
{
	vector<int> vec;
	vec.push_back(18);
	vec.push_back(19);
	vec.push_back(20);
	vec.push_back(15);
	vec.push_back(14);
	vec.push_back(13);
	vec.push_back(12);
	vec.push_back(11);
	vec.push_back(10);
	vec.push_back(9);
	vec.push_back(8);
	vec.push_back(7);
	vec.push_back(6);
	vec.push_back(5);
	vec.push_back(4);
	vec.push_back(3);
	vec.push_back(2);
	vec.push_back(1);
	vec.push_back(18);

	sorter<int> s;
	cout<<vec.size()<<"\n";
	s.opt_bubble_sort(vec,0,vec.size()-1);
	vector<int>::vector_Iterator it = vec.begin();
	for(;it!=vec.end();it++)
		cout<<*it<<"  ";
}
