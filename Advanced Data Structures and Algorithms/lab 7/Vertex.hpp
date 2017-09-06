#ifndef VERTEX
#define VERTEX 1

enum COLOR {WHITE,GRAY,BLACK};

class vertex
{
private:

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
#endif
