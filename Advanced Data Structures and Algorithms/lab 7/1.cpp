#include <iostream>
#include "AdjacencyList.hpp"
using namespace abc;
using namespace std;
int main()
{
	AdjacencyList adj;
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
	adj.add( 4,3);
	try{
	adj.remove(3,4);
		adj.remove(4,3);
	adj.remove(0,4);
		adj.remove(4,0);
	adj.remove(4,1);
	adj.remove(1,4);
}catch(const char* c){
    std::cout<<c<<std::endl;
  }
	cout<<adj.edges()/2<<endl;
	cout<<adj.edgeExits(2,3)<<endl;
		cout<<adj.vertices()<<endl;
		cout<<adj.degree(3)<<endl;

	cout<<endl;
	/*cout<<adj.edgeExits(3,4)<<endl;
	cout<<adj.edgeExits(1,2)<<endl;
	cout<<adj.edgeExits(3,5)<<endl;
	cout<<adj.edgeExits(0,5)<<endl;
	cout<<adj.edgeExits(0,4)<<endl;
	cout<<adj.vertices()<<endl;
	cout<<adj.edges()<<endl;
	cout<<adj.degree(4)<<endl;
	adj.remove(3,4);
	adj.remove(0,4);
	adj.remove(1,4);
	adj.set_all_white();
		cout<<"r   "<<adj.edgeExits(0,4)<<endl;
	cout<<adj.vertices()<<endl;
	cout<<adj.edges()<<endl;*/
}
