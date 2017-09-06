#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "AbstractGraph.hpp"
#include "DirectedGraph.hpp"
#include "UndirectedGraph.hpp"

using namespace std;
void print(int& i, int& d)
{
	cout<<"Vertex: "<<i<<"  Distance from Source: "<<d<<endl;
}
void print1(int& i)
{
	cout<<"Vertex: "<<i<<endl;
}
int main()
{
	try{
	AbstractGraph *graph = NULL;
	int t1,t2,vertices;
	cout<<"Select the type of graph to be implemented\n1.Undirected Graph\n2.Directed Graph\n";
	cin>>t1;
	cout<<"Select the way to represent the Graph\n1.Adjacency List\n2.Adjacency Matrix\n";
	cin>>t2;
	if(t1==1)
	{
		cout<<"Enter the number of vertices in the graph\n";
		cin>>vertices;
		if(t2==1)
			graph = new UndirectedGraph(vertices,'l');
		else if(t2==2)
			graph = new UndirectedGraph(vertices,'m');
		else 
			cout<<"Invalid Entry\n";
	}
	else if(t1==2)
	{
		cout<<"Enter the number of vertices in the graph\n";
		cin>>vertices;
		if(t2==1)
			graph = new DirectedGraph(vertices,'l');
		else if(t2==2)
			graph = new DirectedGraph(vertices,'m');
		else 
			cout<<"Invalid Entry\n";
	}
	else
		cout<<"Invalid Entry\n";
	int t4,t5;
	cout<<"Want to read input from file\n1. Yes\n2. NO\n";
	cin>>t4;
	if(t4==1)
	{
		FILE *p;
		if((p = fopen("input.txt","r"))==NULL)
			throw "File not opened successfully\n";
		for(int k=0;k<vertices;k++)
		{
			for(int m=0;m<vertices;m++)
			{
				fscanf(p,"%d",&t5);
				if(t5)
					graph->add(k,m);
			}
		}
	}
	int t3;
	int i,j;
	bool check=0;
	while(!check)
	{
		cout<<endl;
		if(t1==1)
		{
			cout<<"\t\tU N D I R E C T E D   G R A P H\n";
			cout<<"\t\t...............................\n\n";
		}
		else
		{
			cout<<"\t\tD I R E C T E D   G R A P H\n";
			cout<<"\t\t...........................\n\n";
		}
				
			cout<<"Select an option to continue.....\n\t[1] Add and edge in the graph\n\t[2] Search for an edge in the graph\n\t[3] Remove an Edge from the graph\n\t[4] Total Number of edges entered\n\t[5] Total Number of vertices\n\t[6] Print the vertices using BFS algorithm\n\t[7] Print the vertices using DFS algorithm\n\t[8] Indegree\n\t[9] OutDegree\n\t[10] Degree\n\t[11] EXIT\n";
		cin>>t3;
		switch(t3)
		{
			case 1:
			{
				cout<<"Enter the vertices of the edges\n";	
				cin>>i>>j;
				if(i==j)
					throw "Error! Both vertices cannot be same\n";
				graph->add(i,j);
				break;
			}
			case 2:
			{
				cout<<"Enter the vertices of the edge to be searched\n";
				cin>>i>>j;
				if(i==j)
					throw "Error! Both vertices cannot be same\n";
				if(graph->edgeExits(i,j))
					cout<<"Edge Exists\n";
				else cout<<"Edge does not exists\n";
				break;
			}
			case 3:
			{
				cout<<"Enter the vertices of the edge to be remove\n";
				cin>>i>>j;
				if(i==j)
					throw "Error! Both vertices cannot be same\n";
				if(graph->edgeExits(i,j))
				{
					graph->remove(i,j);
					cout<<"Edge removed successfully\n";
				}
				else cout<<"Edge does not exists\n";
				break;
			}
			case 4:
			{
				cout<<"Total Edges: "<<graph->edges()<<endl;;
				break;
			}
			case 5:
			{
				cout<<"Total Vertices: "<<graph->vertices()<<endl;;
				break;			
			}
			case 6:
			{
				graph->bfs(print);
				break;
			}
			case 7:
			{
				graph->dfs(print1);
				break;
			}
			case 8:
			{
				int v;
				cout<<"Enter vertex to find indegree: ";
				cin>>v;
				 cout<<graph->indegree(v);
				break;
			}
			case 9:
			{
				int v;
				cout<<"Enter vertex to find Outdegree: ";
				cin>>v;
				 cout<<graph->outdegree(v);
				break;
			}
			case 10:
			{
				int v;
				cout<<"Enter vertex to find degree: ";
				cin>>v;
				cout<<graph->degree(v);
				break;
			}			
			case 11:
			{
				check = 1;
				break;
			}
		}

	}
}catch(const char*c)
{
	cout<<c<<endl;
}
}
