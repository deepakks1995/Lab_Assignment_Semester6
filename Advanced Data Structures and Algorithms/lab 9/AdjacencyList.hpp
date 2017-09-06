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
#include "RootedTree.hpp"
#include "Heap.hpp"
#include <cstdio>
using namespace abc;
using namespace std;

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
  void Prims();
  void display_sort();
  int give_weight(vertex*  ,vertex *);

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

void AdjacencyList::display_sort()
{
  this->sort_edges();
  for(int i=0;i<edge_list.size(); i++)
  {
    vertex *child = edge_list[i].child;
    vertex *parent = edge_list[i].parent;
    cout<<"Child: "<<child->name<<" Parent: "<<parent->name<<" Weight: "<<edge_list[i].weight<<endl;

  }
}

int AdjacencyList::give_weight(vertex* u, vertex* v)
{
  Edges ed;
  for(int i=0;i<edge_list.size();i++)
  {
    ed = edge_list[i];
    if(ed.child==u && ed.parent==v)
      return ed.weight;
  }
}

void AdjacencyList::Prims()
{
  binary_heap<abc::pair<vertex*, int > > heap;
  RootedTree<vertex *> *set = new RootedTree<vertex *>;
  int src;
  cout<<"Enter the source vertex: ";
  cin>>src;
  for( int i=0;i<vec->size();i++)
  {
    abc::pair<vertex *, int> p;
    p.first = (*vec)[i].topElement();
    if(i==src)
      p.second = 0;
    else p.second = INT_MAX;
    heap.insert(p);
  }
  abc::pair<vertex *, int> p,*p2,p3;
  p.first = (*vec)[src].topElement();
  p.second = 0;
  int weight;
  heap.Heap_Decrease_Key(p);
  vertex * n= NULL;
  node<vertex *> *itr;
  int parent[vec->size()];
  for(int i=0;i<vec->size();i++)
    parent[i] = i;
 // heap.display();
  while(!heap.empty())
  {

    p = heap.Extract_min();
    set->MAKE_SET(p.first);
    itr= (*vec)[p.first->name].topNode();
    itr = itr->getlink();
    while(itr!=NULL)
    {
      n= itr->getData();
      p3.first = n;
      p3.second = 0;
      if(set->has(n)==false)
      {
        weight = give_weight(p.first,n);
        p2 = heap.Search_Key(p3);
        if(p2->second > weight)
            p2->second = weight;
        parent[p2->first->name] = p.first->name;
        heap.Heap_Decrease_Key(*p2);
      }
      itr = itr->getlink();
    }
  }
  for (int i = 1; i < vec->size(); ++i)
      printf("%d - %d weigth: ", parent[i], i);
}


#endif /* ifndef ADJACENCY_LIST */