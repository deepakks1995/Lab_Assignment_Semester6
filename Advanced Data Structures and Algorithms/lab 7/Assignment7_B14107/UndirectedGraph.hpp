#ifndef UNDIRECTED_GRAPH
#define UNDIRECTED_GRAPH 1

#include "AbstractGraph.hpp"
#include "AdjacencyList.hpp"
#include "AdjacencyMatrix.hpp"


using namespace abc;
class UndirectedGraph : public AbstractGraph {
 public:
  UndirectedGraph();
  UndirectedGraph(int vertices, char mode);
  int degree(int i);
  void add(int i, int j);
  bool edgeExits(int i, int j);
  int edges();
  int vertices();
  void remove(int i, int j);
  void bfs(void (*work)(int&,int&));
  void dfs(void (*work)(int&));
  int indegree(int i);
  int outdegree(int i);

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

void UndirectedGraph::add(int i, int j)
{
  try{
    graph->add(i,j);
    graph->add(j,i);
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

#endif /* ifndef UNDIRECTED_GRAPH */