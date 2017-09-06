#ifndef DIRECTED_GRAPH
#define DIRECTED_GRAPH 1
#include "AbstractGraph.hpp"
#include "AdjacencyList.hpp"
#include "AdjacencyMatrix.hpp"
/*
 * A class to represent a directed graph.
 */
class DirectedGraph : public AbstractGraph {
 public:
  /*
   * Constructor: DirectedGraph
   *
   * Parameters: mode
   * Used to decide which representation to use
   * 'm' for AdjacencyMatrix
   * 'l' for AdjacencyList
   */
  DirectedGraph(int vertices, char mode);
  /*
   * Function: indegree
   * Returns the indegree of a vertex
   */
  int indegree(int i);
  /*
   * Function: outdegree
   * Returns the outdegree of a vertex.
   */
  int outdegree(int j);
  void add(int i, int j);
  bool edgeExits(int i, int j);
  int edges();
  int vertices();
  void remove( int i, int j);
  void bfs(void (*work)(int&,int&));
  void dfs(void (*work)(int&,int&));
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

void DirectedGraph::add(int i, int j)
{
  try{
    graph->add(i,j);
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

void DirectedGraph::dfs(void (*work)(int&,int&))
{
  graph->dfs(work);
  
}
#endif /* ifndef DIRECTED_GRAPH */