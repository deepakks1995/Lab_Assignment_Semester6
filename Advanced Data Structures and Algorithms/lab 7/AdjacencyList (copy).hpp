#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST 1
#include "GraphAdjacencyBase.hpp"
#include "vector.hpp"
#include "Vertex.hpp"
#include "list.hpp"
using namespace abc;

class AdjacencyList : public GraphAdjacencyBase {

public:
	AdjacencyList();
 	~AdjacencyList(){};
	AdjacencyList(const int& isize);
	void add(int i, int j);
	bool edgeExits(int i, int j);
	int vertices();
	int edges();
	void remove(int i, int j);
	int degree(int i);
	void set_all_white();

private:
	friend class UndirectedGraph;
	vector <list<vertex > > *vec;
	int edg;
};

void AdjacencyList::set_all_white()
{
	for(int i=0;i<vec->size();i++)
	{
		if(!((*vec)[i].empty()))
		{
			vertex node=((*vec)[i].topElement());
			(*vec)[i].remove(node);
			node.color=WHITE;
			(*vec)[i].cons(node);
		}
	}
}

AdjacencyList::AdjacencyList()
{
	vec = new vector <list<vertex > >;
	vec->resize(2);
	edg = 0;
	for(int i=0; i<2; i++)
	{
		list<vertex >  *temp  = new list<vertex > ;
		vec->push_back(*temp);
	}
}

AdjacencyList::AdjacencyList(const int& isize)
{
	vec = new vector <list<vertex > >;
	vec->resize(isize);
	edg = 0;
	for(int i=0; i<isize; i++)
	{
		list<vertex >  *temp  = new list<vertex > ;
		vec->push_back(*temp);
	}
}

void AdjacencyList::add(int i, int j)
{
	while(vec->size()-1 < ( i>=j ? i : j ) )
	{
		list<vertex > *temp = new list<vertex >;
		vec->push_back(*temp);
	}
	vertex node1;
	node1.name = j;
	vertex node2;
	node2.name = i;
	if((*vec)[i].empty()==0)
		(*vec)[i].append(node2);
	if((*vec)[j].empty()==0)
		(*vec)[j].append(node1);
	if(!((*vec)[i].search(node1)))
	{
		(*vec)[i].append(node1);
		(*vec)[j].append(node2);
		edg++;
	}
}

bool AdjacencyList::edgeExits(int i, int j)
{	
	if(vec->size() -1 < ( i >= j ? i: j ))
		return 0;
	vertex node;
	node.name = j;
	if((*vec)[i].search(node))
		return 1;
	else
		return 0;
}

int AdjacencyList::vertices()
{
	int count=0;
	for(int i=0;i<vec->size();i++)
		if(!(*vec)[i].empty())
			count++;
	return count;
}

int AdjacencyList::edges()
{
	return edg;
}

void AdjacencyList::remove(int i, int j)
{
	vertex node1;
	vertex node2;
	node1.name = j;
	if(!((*vec)[i].search(node1)))
		throw "Edges does not exist\n";
	(*vec)[i].remove(node1);
	node2.name = i;
	(*vec)[j].remove(node2);
	edg--;	
}

int AdjacencyList::degree(int i)
{
	return (*vec)[i].length();
}

#endif /* ifndef ADJACENCY_LIST */