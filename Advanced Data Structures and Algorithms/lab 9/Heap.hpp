
#ifndef HEAP_HPP_
#define HEAP_HPP_
#include "vector.hpp"
#include <climits>
#include <cstring>
using namespace abc;
using namespace std;


	template <class T>
	class binary_heap
	{
	private:
		//friend class AdjacencyList;
		vector<T> *data;
		int size;
		int parent(const int& index);
		int left(const int& index);
		int right(const int& index);
		void swap(T& A, T& B);
		int compare(T& A, T& B);
		int compare(char* str1, char* str2);
		void build_heap(T arr[], int lo, int hi);
		void heapify(int index);
	public:
		binary_heap();
		bool empty();
		void insert(T& x);
		T* Search_Key(T& key);
		void Decrease_Key(int index, T key);
		T Extract_min();
		void heap_sort(T arr[], int lo, int hi);
		int Heap_Decrease_Key(T& key);
		T min();
		//void display();		// function for printing all elements in the heap (Only for debuging purposes).......
	};

	template <class T>
	binary_heap<T>::binary_heap()
	{
		data = NULL;
		size = 0;
	}

	template <class T>
	void binary_heap<T>::insert(T& x)
	{
		if(data==NULL)
		{
			data = new vector<T>;
			data->push_back(x);	// for making heap 1 based indexing............
		}
		size++;
		if(data->size()==size)
			data->push_back(x);
		else (*data)[size] = x;
		Decrease_Key(size, x);
	}

	template <class T>
	void binary_heap<T>::Decrease_Key(int index, T key)
	{
		(*data)[index] = key;
		while(index > 1 && compare((*data)[parent(index)], (*data)[index])==1)
		{
			swap((*data)[parent(index)], (*data)[index]);
			index = parent(index);
		}
	}

	template <class T>
	T * binary_heap<T>::Search_Key(T& key)
	{
		int i;
		bool check = 0;
		for( i=0;i<size; i++)
		{
			std::cout<<"Data: "<<(*data)[i].first->name;
			if(key == (*data)[i])
			{
				check = 1;
				break;
			}
		}
		if(check)
			return &(*data)[i];
		else 
			throw "Element not found Search_Key\n";
	}

	template <class T>
	int binary_heap<T>::Heap_Decrease_Key(T& key)
	{
		int i;
		bool check = 0;
		for( i=0;i<size; i++)
			if(key == (*data)[i])
			{
				check = 1;
				break;
			}
		if(check)
			Decrease_Key(i,key);
		else 
			throw "Element not found\n";
	}

	template <class T>
	void binary_heap<T>::heapify(int index)
	{
		int l = left(index);
		int r = right(index);
		int smallest = index;
		if(l<=size && (*data)[index] <= (*data)[l])
			smallest = index;
		else if(l<=size) 
			smallest = l;
		if(r<=size && (*data)[smallest] > (*data)[r])
			smallest = r;
		if(smallest!=index)
		{
			swap((*data)[smallest],(*data)[index]);
			heapify(smallest);
		}
	}

	template <class T>
	T binary_heap<T>::Extract_min()
	{
		T min = (*data)[1];
		(*data)[1] = (*data)[size];
		size--;
		heapify(1);
		return min;
	}


	template <class T>
	void binary_heap<T>::build_heap(T arr[], int lo, int hi)
	{
		if(data == NULL)
		{
			data = new vector<T>(hi-lo+2,0);
			(*data)[0] = INT_MIN;			//	to make 1 based indexing in heap so that 0th index cannot be used
		}

		if(data->size()<hi-lo+1)
			data->resize(hi-lo+2);		//	managing the size of vector in the case if their are previous entries in heap data-structure

		for(int i=lo,j=1; i<=hi; i++,j++)
		{
			(*data)[j] = arr[i];
			size++;
		}
		for(int i= int(size)/2; i>=1; i--)
			heapify(i);
	}

	template <class T>
	void binary_heap<T>::heap_sort(T arr[], int lo, int hi)
	{
		if(size!=0)
			throw "Heap Sort can be implemented on empty vector\n";
		build_heap(arr,lo,hi);
		for(int i = size; i>=2; i--)
		{
			swap((*data)[1], (*data)[i]);
			size--;
			heapify(1);
		}
		for(int i = lo,j=1;i<=hi; i++,j++)
			arr[i] = (*data)[j];
	}

	template <class T>
	int binary_heap<T>::parent(const int& index)
	{
		return (int)index/2;
	}

	template <class T>
	int binary_heap<T>::left(const int& index)
	{
		return 2*index;
	}

	template <class T>
	int binary_heap<T>::right(const int& index)
	{
		return 2*index + 1;
	}

	template <class T>
	void binary_heap<T>::swap(T& A, T& B)
	{
		T temp = A;
		A = B;
		B = temp;
	}		

	template <class T>
	int binary_heap<T>::compare(T& A,T& B)
	{
		if(A < B)
			return -1;
		else if( A > B )
			return 1;
		else return 0;
	}

	template <class T>
	int binary_heap<T>::compare(char* str1, char* str2)
	{
		return strcmp(str1, str2);
	}

	template <class T>
	bool binary_heap<T>::empty()
	{
		return size==0;
	}

/*	template <class T>
	void binary_heap<T>::display()
	{
		for(int i=1;i<=size;i++)
			std::cout<<(*data)[i]<<"  ";
	}*/


#endif
