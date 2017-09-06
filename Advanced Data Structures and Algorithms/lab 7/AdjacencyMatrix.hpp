#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX 1
#include "GraphAdjacencyBase.hpp"
#include "queue.hpp"
#include <climits>
#include "vector.hpp"
#include "Vertex.hpp"
using namespace std;

class AdjacencyMatrix : public GraphAdjacencyBase {

public:
  
  AdjacencyMatrix();
  ~AdjacencyMatrix(){};
  AdjacencyMatrix(int N, int M);
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
  
  int **matrix;
  int edg;
  int N,M;
  vector<vertex *> *list;
};

int AdjacencyMatrix::indegree(int i)
{
	int count = 0;
	for(int j =0 ;j<M;j++)
	{
		if(j!=i &&  matrix[j][i])
			count++;
	}
	return count;
}

AdjacencyMatrix::AdjacencyMatrix()
{
	matrix = NULL;
	edg = 0;
}

AdjacencyMatrix::AdjacencyMatrix(int N, int M)
{
	this->N = N;
	this->M = M;
	matrix = new int*[N];
	for(int i=0;i<N;i++)
		matrix[i] = new int [M];
	list = new vector<vertex *>;
	list->resize(M);
	for(int i=0;i<M;i++)
	{
		vertex *temp = new vertex;
		temp->name = i;
		temp->color = WHITE;
		temp->pre = NULL;
		list->push_back(temp);
	}
	edg = 0;
}

void AdjacencyMatrix::add(int i, int j)
{
	if(i>=N || j>=M )
		throw "Invalid entry\n";
	if(!matrix[i][j])
	{
		matrix[i][j] = 1;
		edg++;
	}
}

bool AdjacencyMatrix::edgeExits(int i, int j)
{
	if(i>=N || j>=M )
		return 0;
	if(matrix[i][j])
		return 1;
	else return 0;
}

int AdjacencyMatrix::vertices()
{
	int count=0;
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++)
			if(matrix[i][j])
				{
					count++;
					break;
				}
	return count;
}

void AdjacencyMatrix::remove(int i, int j)
{
	if(i>=N || j>=M )
		throw "Invalid entry\n";
	if(matrix[i][j])
	{
		edg--;
		matrix[i][j]=0;
	}
	else
	throw "Error! : Edge does not exists\n";	
}

int AdjacencyMatrix::edges()
{
	return edg;
}

int AdjacencyMatrix::degree(int i)
{
	int count=0;
	for(int j=0;j<M;j++)
		if(matrix[i][j]==1)
			count++;
	return count;
}

void AdjacencyMatrix::bfs(void (*work)(int&,int&))
{
	vertex *temp;
  	for(int i=0;i<list->size();i++)
  	{	
  		(*list)[i]->color = WHITE;
  		(*list)[i]->distance = INT_MAX;
  		(*list)[i]->pre = NULL;
  	}
  	std::cout<<"Enter the source vertex for BFS"<<std::endl;
  	int src;
 	std::cin>>src;
 	(*list)[src]->color = GRAY;
 	(*list)[src]->distance = 0;
 	(*list)[src]->pre = NULL;
 	queue<vertex *> que;
 	que.push((*list)[src]);
 	while(!que.empty())
 	{
 		temp = que.pop();
 		temp->color = BLACK;
 		work(temp->name,temp->distance);
 		for(int j=0;j<M;j++)
 		{
 			if(matrix[temp->name][j])
 			{
 				if((*list)[j]->color == WHITE)
 				{
 					(*list)[j]->color = GRAY;
 					(*list)[j]->distance = temp->distance + 1;
 					(*list)[j]->pre = temp;
 					que.push((*list)[j]);
 				}
 			}
 		}
 	}
}

void AdjacencyMatrix::dfs(void (*work)(int&,int&))
{
	vertex *temp;
  	for(int i=0;i<list->size();i++)
  	{	
  		(*list)[i]->color = WHITE;
  		(*list)[i]->distance = INT_MAX;
  		(*list)[i]->pre = NULL;
  	}
  	int src=0;
 	(*list)[src]->color = GRAY;
 	(*list)[src]->distance = 0;
 	(*list)[src]->pre = NULL;
 	stack<vertex *> stk;
 	stk.push((*list)[src]);
 	while(!stk.empty())
 	{
 		temp = stk.pop();
 		temp->color = BLACK;
 		work(temp->name,temp->distance);
 		for(int j=0;j<M;j++)
 		{
 			if(matrix[temp->name][j])
 			{
 				if((*list)[j]->color == WHITE)
 				{
 					(*list)[j]->color = GRAY;
 					(*list)[j]->distance = temp->distance + 1;
 					(*list)[j]->pre = temp;
 					stk.push((*list)[j]);
 				}
 			}
 		}
 	}	
}

#endif /* ifndef ADJACENCY_MATRIX */