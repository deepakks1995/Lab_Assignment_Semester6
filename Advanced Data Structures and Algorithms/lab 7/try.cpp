#include<iostream>
//#include "UndirectedGraph.hpp"
#include "DirectedGraph.hpp"

using namespace std;

void work(int& j,int&d)
{
  std::cout<<"Vertex id is ..\t"<<j<<"Distance: "<<d<<endl;;
}

int main(void)
{
  DirectedGraph u(8,'l');
  //DirectedGraph u(8,'l');
  /*u.addVertex(1);
  u.addVertex(2);
  u.addVertex(3);
  u.addVertex(4);
  u.addVertex(5);
  u.addVertex(6);
  u.addVertex(7);
  u.addVertex(8);*/
  u.add(0,1);
  u.add(1,2);
  u.add(2,3);
  u.add(3,4);
  u.add(3,5);
  u.add(4,5);
  u.add(5,7);
  u.add(4,6);
  u.add(6,7);

  /*u.add(1,0);
  u.add(2,1);
  u.add(3,2);
  u.add(4,3);
  u.add(5,3);
  u.add(5,4);
  u.add(7,5);
  u.add(6,4);
  u.add(7,6);
  std::cout<<"indegree of Vertex 1..\t"<<u.indegree(1)<<"\n";
  std::cout<<"indegree of Vertex 2..\t"<<u.indegree(2)<<"\n";
  std::cout<<"indegree of Vertex 3..\t"<<u.indegree(3)<<"\n";
  std::cout<<"indegree of Vertex 4..\t"<<u.indegree(4)<<"\n";
  std::cout<<"indegree of Vertex 5..\t"<<u.indegree(5)<<"\n";
  std::cout<<"indegree of Vertex 6..\t"<<u.indegree(6)<<"\n";
  std::cout<<"indegree of Vertex 7..\t"<<u.indegree(7)<<"\n";
  std::cout<<"indegree of Vertex 0..\t"<<u.indegree(0)<<"\n";*/
  std::cout<<"Vertices..\t"<<u.vertices()<<"\n";
  std::cout<<"Edges..\t"<<u.edges()<<"\n";
  u.bfs(work);
  std::cout<<"\n\n\n";
  u.dfs(work);
  std::cout<<"\n\n\n\n"<<u.edgeExits(3,5)<<"\n"<<u.edgeExits(1,6);
  return 0;
}
