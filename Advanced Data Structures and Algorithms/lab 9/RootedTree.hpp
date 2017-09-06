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
	void MAKE_SET(T x);
	Root_Node<T>* FIND_SET(T x);
	void UNION(T x, T y);
	bool has(T x);
protected:
	void LINK(Root_Node<T>* x, Root_Node<T>* y);
};

template <class T>
RootedTree<T>::RootedTree()
{
	vec = NULL;
}

template <class T>
void RootedTree<T>::MAKE_SET(T x)
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
bool RootedTree<T>::has(T x)
{
	for(int i=0;i<vec->size();i++)
		if((*vec)[i]->data == x)
			return true;
	return false;
}
template <class T>
Root_Node<T> * RootedTree<T>::FIND_SET(T x)
{
	int i;
	bool check=0;
	for(i=0;i<vec->size();i++)
		if((*vec)[i]->data == x)
		{
			check=1;
			break;
		}
	if(check)	
	{
		Root_Node<T> *node = (*vec)[i];
		while(node!=node->parent)
			node = node->parent;
		return node;
	}
	else throw "Node not found in the set\n";
}

template <class T>
void RootedTree<T>::UNION(T x, T y)
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