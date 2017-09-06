#include<iostream>
#include "queue.hpp"

#include "list.hpp"



using namespace que;
using namespace std;
int main()
{
	queue<int> s;
	std::cout<<s.size()<<endl;;
	s.push(1);
	s.push(2);

	s.push(3);
	s.push(4);
	s.push(5);
	s.push(6);
	s.push(7);
	s.push(8);
	s.push(9);
	s.push(10);
	s.push(111);
	s.push(121);
	cout<<s.pop()<<endl;
	cout<<s.size();

}

