#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST 1
#include "GraphAdjacencyBase.hpp"
#include "vector.hpp"
#include "Vertex.hpp"
#include "list.hpp"
#include "queue.hpp"
#include <climits>
#include "stack.hpp"
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
  int indegree(int i);
	void bfs(void (*work)(int&,int&));
	void dfs(void (*work)(int&,int&));


private:
	friend class UndirectedGraph;
	vector <list<vertex *> > *vec;
	int edg;
};


AdjacencyList::AdjacencyList()
{
	vec = new vector <list<vertex *> >;
	vec->resize(2);
	edg = 0;
	for(int i=0; i<2; i++)
	{
		list<vertex *>  *temp  = new list<vertex *> ;
		vec->push_back(*temp);
	}
}

AdjacencyList::AdjacencyList(const int& isize)
{
	vec = new vector <list<vertex *> >;
	vec->resize(isize);
	edg = 0;
	for(int i=0; i<isize; i++)
	{
		list<vertex *>  *temp  = new list<vertex *> ;
		vec->push_back(*temp);
	}
}

void AdjacencyList::add(int i, int j)
{
	while(vec->size()-1 < ( i>=j ? i : j ) )
	{
		list<vertex *> *temp = new list<vertex *>;
		vec->push_back(*temp);
	}
	vertex *node1 = new vertex;
	node1->name = j;
	vertex *node2 = new vertex;
	node2->name = i;
	if((*vec)[i].empty()==1)
		(*vec)[i].append(node2);
	if((*vec)[j].empty()==1)
		(*vec)[j].append(node1);
	if(!((*vec)[i].search((*vec)[j].topElement())))
	{
		(*vec)[i].append((*vec)[j].topElement());
		edg++;
	}
}

bool AdjacencyList::edgeExits(int i, int j)
{	
	if(vec->size() -1 < ( i >= j ? i: j ))
		return 0;
	vertex *node = new vertex;
	node->name = j;
	if((*vec)[i].search((*vec)[j].topElement()))
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
	if(!((*vec)[i].search((*vec)[j].topElement())))
		throw "Edges does not exist\n";
	(*vec)[i].remove((*vec)[j].topElement());
	edg--;	
}

int AdjacencyList::degree(int i)
{
	return (*vec)[i].length()-1;
}

int AdjacencyList::indegree(int i)
{
  int count=0;
  for(int j=0;j<vec->size();j++)
  {
    if((*vec)[j].empty()==0 && j!=i)
    {
        if((*vec)[j].search((*vec)[i].topElement()))
          count++;
    }
  }
  return count;
}


void AdjacencyList::bfs(void (*work)(int&,int&))
{
  std::cout<<"Enter the source vertex for BFS"<<std::endl;
  int src;
  std::cin>>src;
  for(int i=0;i<vec->size();i++)
  {
    if(!((*vec)[i].empty()))
    {
      vertex *n=((*vec)[i].topElement());
      n->color = WHITE;
      n->distance = INT_MAX;
      n->pre = NULL;
    }
  }
  if((*vec)[src].empty() || src>vec->size()-1)
    throw "Error! Source vertex does not exist\n";
  vertex *n = (*vec)[src].topElement();
  n->color = GRAY;
  n->pre = NULL;
  n->distance = 0;
  queue<vertex *> que;
  n =(*vec)[src].topElement(); 
  que.push(n);

  while(!que.empty())
  {
    vertex *u = que.pop();
    work(u->name,u->distance);
    u->color = BLACK;
    node<vertex *>  *itr ;
    itr = (*vec)[u->name].topNode();
    while(itr!=NULL)
    {
      n = itr->getData();
      if(n->color==WHITE)
      {
        n->color = GRAY;
        n->distance = u->distance + 1;
        n->pre = u;
        que.push(n);
      }
      itr = itr->getlink();
    }
  }
}

void AdjacencyList::dfs(void (*work)(int&,int&))
{
	vertex *n;
  for(int i=0;i<vec->size();i++)
  {
    if(!((*vec)[i].empty()))
    {
      n=((*vec)[i].topElement());
      n->color = WHITE;
      n->distance = INT_MAX;
      n->pre = NULL;
    }
  }
  n = (*vec)[0].topElement();
  n->color = WHITE;
  n->distance = 0;
  n->pre = NULL;
  stack<vertex *> stk;
  stk.push((*vec)[0].topElement());
  vertex *u;
  while(!stk.empty())
  {
  	u = stk.pop();
  	work(u->name, u->distance);
  	u->color = BLACK;
  	node<vertex *>  *itr ;
    itr = (*vec)[u->name].topNode();
  	while(itr!=NULL)
  	{
  		n = itr->getData();
  		if(n->color == WHITE)
  		{
  			n->color = GRAY;
  			n->distance = u->distance + 1;
  			n->pre = NULL;
  			stk.push(n);
  		}
  		itr = itr->getlink();
  	}
  }
}

#endif /* ifndef ADJACENCY_LIST */