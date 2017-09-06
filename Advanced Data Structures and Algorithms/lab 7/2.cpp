#include <iostream>
#include "AdjacencyMatrix.hpp"
void work(int& j)
{
  std::cout<<"Vertex id is ..\t"<<j<<endl;
}
using namespace std;
int main()
{
	AdjacencyMatrix adj(5,5);
	adj.add( 0, 1);
	adj.add( 0, 4);
	adj.add( 1, 2);
	adj.add( 1, 3);
	adj.add( 1, 4);
	adj.add( 2, 3);
	adj.add( 3, 4);
		adj.add( 1,0);
	adj.add( 4,0);
	adj.add( 2,1);
	adj.add( 3,1);
	adj.add( 4,1);
	adj.add( 3,2);
	adj.add( 4,3);/*
	cout<<adj.edgeExits(3,50)<<endl;
	cout<<adj.edgeExits(3,4)<<endl;
	cout<<adj.edgeExits(1,2)<<endl;
	cout<<adj.edgeExits(3,5)<<endl;
	cout<<adj.edgeExits(0,5)<<endl;
	cout<<adj.edgeExits(0,4)<<endl;*/
	cout<<adj.vertices()<<endl;
	cout<<adj.edges()<<endl;
	cout<<"degree "<<adj.degree(1)<<endl;
	adj.remove(3,4);
	adj.remove(0,4);
	adj.remove(1,4);
		cout<<"r   "<<adj.edgeExits(0,4)<<endl;
	cout<<adj.vertices()<<endl;
	cout<<adj.edges()<<endl;
	adj.bfs(work);
}
