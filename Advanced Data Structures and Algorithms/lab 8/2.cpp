#include <iostream>
//#include "UndirectedGraph.hpp"

#ifndef ROOTED_TREE
#define ROOTED_TREE 1
#include "vector.hpp"
using namespace abc;

template <class T>
class Root_Node
{
private:
	template <class U> friend class RootedTree;
	T data;
	Root_Node *parent;
	int rank;
public:
	Root_Node()
	{
		parent = NULL;
		rank = 0;
	}
	bool operator != (Root_Node<T> x)
	{
		return data!=x.data;
	}
};


template <class T>
class RootedTree
{
private:
	vector<Root_Node<T> *> *vec;
public:
	RootedTree();
	void MAKE_SET(T& x);
	Root_Node<T>* FIND_SET(T& x);
	void UNION(T& x, T& y);
protected:
	void LINK(Root_Node<T>* x, Root_Node<T>* y);
};

template <class T>
RootedTree<T>::RootedTree()
{
	vec = NULL;
}

template <class T>
void RootedTree<T>::MAKE_SET(T& x)
{
	bool check=0;
	if(vec==NULL)
		vec = new vector<Root_Node<T> *>;
	for(int i=0;i<vec->size();i++)
		if((*vec)[i]->data==x)
			check=1;
	if(!check)
	{	
		Root_Node<T> *node = new Root_Node<T>;
		node->data = x;
		node->parent = node;
		vec->push_back(node);
	}
}

template <class T>
Root_Node<T> * RootedTree<T>::FIND_SET(T& x)
{
	int i;
	for(i=0;i<vec->size();i++)
		if((*vec)[i]->data == x)
			break;
	Root_Node<T> *node = (*vec)[i];
	while(node!=node->parent)
		node = node->parent;
	return node;
}

template <class T>
void RootedTree<T>::UNION(T& x, T& y)
{
	LINK(this->FIND_SET(x), this->FIND_SET(y));
}

template <class T>
void RootedTree<T>::LINK(Root_Node<T>* x, Root_Node<T>* y)
{
	if(x->rank > y->rank)
		y->parent = x;
	else 
	{
		x->parent = y;
		if(x->rank==y->rank)
			y->rank++;
	}
}

#endif  // ROOTED_TREE

#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST 1
#include "GraphAdjacencyBase.hpp"
#include "vector.hpp"
#include "Vertex.hpp"
#include "list.hpp"
#include "queue.hpp"
#include <climits>
#include "stack.hpp"
#include "sorter.hpp"
//#include "RootedTree.hpp"
using namespace abc;

class AdjacencyList : public GraphAdjacencyBase {

public:
	AdjacencyList();
 	~AdjacencyList(){};
	AdjacencyList(const int& isize);
	void add(int i, int j,int w);
	bool edgeExits(int i, int j);
	int vertices();
	int edges();
	void remove(int i, int j);
	int degree(int i);
  int indegree(int i);
	void bfs(void (*work)(int&,int&));
	void dfs(void (*work)(int&));
  void sort_edges();
  void MST(void(*work)(int&,int&,int&));

private:
	friend class UndirectedGraph;
	vector <list<vertex *> > *vec;
  int edg;
	vector <Edges > edge_list;
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

void AdjacencyList::add(int i, int j,int w)
{
	while(vec->size()-1 < ( i>=j ? i : j ) )
	{
		list<vertex *> *temp = new list<vertex *>;
		vec->push_back(*temp);
	}
  Edges ed(w);
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
    ed.parent = (*vec)[i].topElement();
    ed.child = (*vec)[j].topElement();
    ed.weight = w;
		edg++;
    edge_list.push_back(ed);
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
		if((*vec)[i].length()>1)
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
  Edges ed;
  ed.parent = (*vec)[i].topElement();
  ed.child = (*vec)[j].topElement();
  edge_list.remove(ed);
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

void AdjacencyList::dfs(void (*work)(int&))
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
  int time=0;
  while(!stk.empty())
  {
  	u = stk.pop();
    u->distance = time++;
  	work(u->name);
  	u->color = BLACK;
  	node<vertex *>  *itr ;
    itr = (*vec)[u->name].topNode();
  	while(itr!=NULL)
  	{
  		n = itr->getData();
  		if(n->color == WHITE)
  		{
  			n->color = GRAY;
  			//n->distance = u->distance + 1;
  			n->pre = NULL;
  			stk.push(n);
  		}
  		itr = itr->getlink();
  	}
  }
}

void AdjacencyList::sort_edges()
{
  sorter<Edges > s;
  s.merge_sort(edge_list,0,edge_list.size()-1);
}

void AdjacencyList::MST(void(*work)(int&,int&,int&))
{
  RootedTree<vertex *> *T = new RootedTree<vertex *> ;
  vertex *node = NULL;
  for(int i=0;i<vec->size();i++)
  {
      node = (*vec)[i].topElement();
      T->MAKE_SET(node);
  }
  sort_edges();
  vertex *parent = NULL;
  vertex *child = NULL;
  for(int i=0;i<edge_list.size();i++)
  {
    parent = edge_list[i].parent;
    child = edge_list[i].child;
    if(T->FIND_SET(parent) != T->FIND_SET(child))
    {
      T->UNION(parent, child);
      work(parent->name,child->name,edge_list[i].weight);
    }
  }
}

#endif /* ifndef ADJACENCY_LIST */


#ifndef UNDIRECTED_GRAPH
#define UNDIRECTED_GRAPH 1

#include "AbstractGraph.hpp"
//#include "AdjacencyList.hpp"
#include "AdjacencyMatrix.hpp"


using namespace abc;
class UndirectedGraph : public AbstractGraph {
 public:
  UndirectedGraph();
  UndirectedGraph(int vertices, char mode);
  int degree(int i);
  void add(int i, int j,int w);
  bool edgeExits(int i, int j);
  int edges();
  int vertices();
  void remove(int i, int j);
  void bfs(void (*work)(int&,int&));
  void dfs(void (*work)(int&));
  int indegree(int i);
  int outdegree(int i);
  void MST(void(*work)(int&,int&,int&));

private:
  GraphAdjacencyBase *graph;

};

UndirectedGraph::UndirectedGraph()
{
    graph = new AdjacencyList(2);

}

UndirectedGraph::UndirectedGraph(int vertices, char mode)
{
  if(mode=='l' || mode=='L')
    graph = new AdjacencyList(vertices);
  else if(mode=='m' || mode=='M')
    graph = new AdjacencyMatrix(vertices,vertices);
  else
    throw "Error! Invalid Mode passed\n";

}

int UndirectedGraph::degree(int i)
{
  return graph->degree(i);
}

void UndirectedGraph::add(int i, int j,int w)
{
  try{
    graph->add(i,j,w);
    graph->add(j,i,w);
  }
  catch(const char* c)
  {
    std::cout<<c<<std::endl;
  }
}

bool UndirectedGraph::edgeExits(int i, int j)
{
  try{
    return graph->edgeExits(i,j);
  }
  catch(const char* c){
    std::cout<<c<<std::endl;
  }
}

int UndirectedGraph::edges()
{
  try{
    return graph->edges()/2;
  }
  catch(const char* c){
    std::cout<<c<<std::endl;
  } 
}

int UndirectedGraph::vertices()
{
  try{
    return graph->vertices();
  }
  catch(const char* c){
    std::cout<<c<<std::endl;
  }  
}

void UndirectedGraph::remove( int i, int j)
{
 try{
   graph->remove( i, j);
   graph->remove(j ,i);
  }
  catch(const char* c){
    std::cout<<c<<std::endl;
  } 

}

void UndirectedGraph::bfs(void (*work)(int&,int&))
{
  graph->bfs(work);
}

void UndirectedGraph::dfs(void (*work)(int&))
{
  graph->dfs(work);
}

int UndirectedGraph::indegree(int i)
{
  return graph->degree(i);
}

int UndirectedGraph::outdegree(int i)
{
  return graph->degree(i);
}

void UndirectedGraph::MST(void(*work)(int&,int&,int&))
{
  graph->MST(work);
}

#endif /* ifndef UNDIRECTED_GRAPH */

using namespace std;
using namespace abc;




void print2(int& i, int& j,int& d)
{
	cout<<"Source: "<<i<<"   Dest: "<<j<<"  Distance from Source: "<<d<<endl;
}
int main()
{
	UndirectedGraph g;
	g.add(7,6,1);  //
	g.add(8,2,2);
	g.add(6,5,2);
	g.add(0,1,4);
	g.add(8,6,6);
	g.add(2,3,7);
	g.add(7,8,7);  
	g.add(0,7,8);
	g.add(1,2,8);
	g.add(3,4,9);
	g.add(5,4,10);
	g.add(1,7,11);
	g.add(3,5,14);

	g.add(6,7,1);  //
	g.add(2,8,2);
	g.add(5,6,2);
	g.add(1,0,4);
	g.add(6,8,6);
	g.add(3,2,7);
	g.add(8,7,7);
	g.add(7,0,8);
	g.add(2,1,8);
	g.add(4,3,9);
	g.add(4,5,10);
	g.add(7,1,11);
	g.add(5,3,14);

	g.MST(print2);

}