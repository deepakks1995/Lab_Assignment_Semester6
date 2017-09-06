#include <iostream>
#include "UndirectedGraph.hpp"

using namespace std;
void work(int& name)
{
  std::cout<<name<<std::endl;
}
int main()
{
	UndirectedGraph adj(5,'l');
	adj.add( 1,2);
	adj.add( 2,3);
	adj.add( 3,4);
	adj.add( 4,5);
	adj.add( 5,6);
	adj.add( 4,6);
	adj.add( 5,7);
	adj.add( 6,8);
	adj.add( 7,8);
		adj.add( 2,1);
	adj.add( 3,2);
	adj.add( 4,3);
	adj.add( 5,4);
	adj.add( 6,5);
	adj.add( 6,4);
	adj.add( 7,5);
	adj.add( 8,6);
	adj.add( 8,7);
		adj.bfs(work);

	/*
	cout<<adj.edgeExits(3,50)<<endl;
	cout<<adj.edgeExits(3,4)<<endl;
	cout<<adj.edgeExits(1,2)<<endl;
	cout<<adj.edgeExits(3,5)<<endl;
	cout<<adj.edgeExits(0,5)<<endl;
	cout<<adj.edgeExits(0,4)<<endl;
	cout<<"v  "<<adj.vertices()<<endl;
	cout<<adj.edges()<<endl;
	cout<<adj.degree(1)<<endl;
	adj.remove(3,4);
	adj.remove(0,4);
	adj.remove(1,4);
		cout<<"r   "<<adj.edgeExits(0,4)<<endl;
	cout<<adj.vertices()<<endl;
	cout<<adj.edges()<<endl;*/

}
