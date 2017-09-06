#ifndef VERTEX
#define VERTEX 1

enum COLOR {WHITE,GRAY,BLACK};

class vertex
{
public:

	friend class AdjacencyMatrix;
	friend class AdjacencyList;
	friend class UndirectedGraph;
	
	COLOR color;
	int distance;
	vertex *pre;
	int name;

public:

	vertex()
	{
		color = WHITE;
		distance = 0;
		pre = NULL;
		name = -1;
	}

	bool operator == (vertex *v)
	{
		return name==v->name;
	}
	void operator = (vertex v)
	{
		color = v.color;
		name = v.name;
		distance = v.distance;
		pre = v.pre;
	}
	void changecolor(COLOR color)
	{
		this->color = color;
	}
	void changepre(vertex *pre)
	{
		this->pre = pre;
	}
	void changedistance(int d)
	{
		this->distance = d;
	}
};

class Edges
{
private:
	friend class AdjacencyList;
	friend class UndirectedGraph;
	int weight;
	vertex *child;
	vertex *parent;

public:
	Edges()
	{
		weight= 0;
		child = NULL;
		parent = NULL;
	}
	Edges(int w)
	{
		weight = w;
		child = NULL;
		parent = NULL;
	}
	bool operator == (Edges ed)
	{
		if(parent == ed.parent && child == ed.child)
			return true;
		else return false;
	}
	bool operator <= (Edges ed)
	{
		if(weight<=ed.weight)
			return true;
		else return false;
	}
	void operator = (Edges ed)
	{
		weight = ed.weight;
		parent = ed.parent;
		child = ed.child;
	}
};
namespace abc
{
template <class T, class U>
class pair
{
public:
	T first;
	U second;
	bool operator == (pair p)
	{
		return first == p.first;
	}
	bool operator <= (pair p)
	{
		return second <= p.second;
	}
	bool operator >=(pair p)
	{
		return second >= p.second;
	}
	bool operator< (pair p)
	{
		return second < p.second;
	}
	bool operator> (pair p)
	{
		return second > p.second;
	}
	void operator = (pair p)
	{
		second = p.second;
		first = p.first;
	}
};

}
#endif
