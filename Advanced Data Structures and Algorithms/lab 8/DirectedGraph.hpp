#ifndef DIRECTED_GRAPH
#define DIRECTED_GRAPH 1
#include "AbstractGraph.hpp"
#include "AdjacencyList.hpp"
#include "AdjacencyMatrix.hpp"

class DirectedGraph : public AbstractGraph {
 public:

  DirectedGraph(int vertices, char mode);
  int indegree(int i);
  int outdegree(int j);
  int degree(int i);
  void add(int i, int j,int w);
  bool edgeExits(int i, int j);
  int edges();
  int vertices();
  void remove( int i, int j);
  void bfs(void (*work)(int&,int&));
  void dfs(void (*work)(int&));
  void MST(void(*work)(int&,int&,int&));
  
private:
  GraphAdjacencyBase *graph;

};

int DirectedGraph::indegree(int i)
{
  return graph->indegree(i);
}

int DirectedGraph::outdegree(int i)
{
  return graph->degree(i);
}


DirectedGraph::DirectedGraph(int vertices, char mode)
{
  if(mode=='l' || mode=='L')
    graph = new AdjacencyList(vertices);
  else if(mode=='m' || mode=='M')
    graph = new AdjacencyMatrix(vertices,vertices);
  else
    throw "Error! Invalid Mode passed\n";
}

void DirectedGraph::add(int i, int j,int w)
{
  try{
    graph->add(i,j,w);
  }
  catch(const char* c)
  {
    std::cout<<c<<std::endl;
  }
}

bool DirectedGraph::edgeExits(int i, int j)
{
  try{
    return graph->edgeExits(i,j);
  }
  catch(const char* c){
    std::cout<<c<<std::endl;
  }
}

int DirectedGraph::edges()
{
  try{
    return graph->edges();
  }
  catch(const char* c){
    std::cout<<c<<std::endl;
  } 
}

int DirectedGraph::vertices()
{
  try{
    return graph->vertices();
  }
  catch(const char* c){
    std::cout<<c<<std::endl;
  }  
}

void DirectedGraph::remove( int i, int j)
{
 try{
   graph->remove( i, j);
  }
  catch(const char* c){
    std::cout<<c<<std::endl;
  } 

}

void DirectedGraph::bfs(void (*work)(int&,int&))
{
  graph->bfs(work);
}

void DirectedGraph::dfs(void (*work)(int&))
{
  graph->dfs(work);
  
}

int DirectedGraph::degree(int i)
{
  return graph->degree(i);
}

void DirectedGraph::MST(void(*work)(int&,int&,int&))
{
  graph->MST(work);
}
#endif /* ifndef DIRECTED_GRAPH */