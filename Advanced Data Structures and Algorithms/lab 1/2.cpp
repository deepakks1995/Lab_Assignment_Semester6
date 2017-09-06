#include<iostream>
//#include "vector.hpp"
/***********************************************************************
Name: Deepak Sharma
Roll_No: B14107
Object: To create a resizable array class named vector in c++ language;
 ************************************************************************/

    #ifndef VECTOR_HPP_
    #define VECTOR_HPP_
 
    namespace abc {					// namespace declaration
    	template<class Item>
    		class vector {			
    			private:				// member declaration
    				int _capacity;
    				int _size;
    				Item *data;
    			public:					// function declaration
    				vector();
 
    				vector(const int& isize);
 
    				vector(const int& isize, const Item& ival);
 
    				~vector();
 
    				inline Item& operator[](const int& i);
 
    				void push_back(const Item& item);
 
    				bool empty();
 
    				int size();
 
    				void fill(const Item& item);
 
    				class vector_Iterator		
    				{
    					private:
    						Item *buffer;
    					public:
    						vector_Iterator()
    						{
    						}
 
    						vector_Iterator(Item * location)
    						{
    							buffer=location;
    						}
 
    						bool operator !=(vector_Iterator  itr)
    						{
    							if(this->buffer != itr.buffer)
    								return true;
    							else
    								return false;
    						}
    						void operator =(vector_Iterator a)
    						{
    							buffer=a.buffer;
    						}
 
    						bool operator ==(vector_Iterator& itr)
    						{
    							if(this->buffer==itr.buffer)
    								return true;
    							else
    								return false;
    						}
 
    						void operator ++()
    						{
    							buffer++;
    						}
 
    						void  operator ++(int unused_parameter)
    						{
    							buffer++;
    						}
 
    						void operator --()
    						{
    							buffer--;
    						}
 
    						void operator --(int unused_parameter)
    						{
    							--buffer;
    						}
 
    						Item operator*()
    						{
    							return *buffer;
    						}
    				};
 
 
    				vector_Iterator begin()
    				{
    					return vector_Iterator(data);
    				}
 
    				vector_Iterator end()
    				{
    					return vector_Iterator(data + _size+1);
    				}
 
    				vector_Iterator rbegin()
    				{
    					return vector_Iterator(data + _size);
    				}
 
    				vector_Iterator rend()
    				{
    					return vector_Iterator(data-1);
    				}
    		};
 
    	template<class Item>
    		vector<Item>::vector()
    		{
    			_capacity=2;
    			_size=-1;
    			data=new Item[_capacity];
    		}
 
    	template<class Item>
    		vector<Item>::vector(const int& isize)
    		{
    			_capacity=isize;
    			_size=-1;
    			data = new Item[_capacity];
    			for(int i=0;i<=_capacity;i++)
    				data[i]=0;
    		}
 
    	template<class Item>
    		vector<Item>::vector(const int& isize,const Item& ival)
    		{
    			_size=isize-1;
    			_capacity=isize;
    			data = new Item[_capacity];
    			for(int i=0;i<=_size;i++)
    				data[i]=ival;
    		}
 
    	template<class Item>
    		vector<Item>::~vector()
    		{
    			delete[ ] data;
    		}
 
    	template<class Item>
    		inline Item& vector<Item>::operator [] (const int& i)
    		{
    			if(i>_size || i<0)
    				std::cout<<"Array Index out of Bounds\n";
    			else
    				return data[i];
    		}
 
    	template<class Item>
    		void vector<Item>::push_back(const Item& item)
    		{
    			if(_size==_capacity-1)
    			{
    				_capacity*=2;
    				Item *new_data = new Item[_capacity];
    				for(int i=0;i<=_size;i++)
    					new_data[i]=data[i];
    				delete [] data;
    				data =new_data;
    			}
    			data[++_size]=item;
    		}
 
    	template<class Item>
    		bool vector<Item>::empty()
    		{
    			if(_size==-1)
    				return true;
    			else
    				return false;
    		}
 
    	template<class Item>
    		int vector<Item>::size()
    		{
    			return _size+1;
    		}
 
    	template<class Item>
    		void vector<Item>::fill(const Item& item)
    		{
    			for(int i=0;i<=_size;i++)
    				data[i]=item;
    		}
 
    }
#endif
using std::cin;
using std::cout;
using namespace abc;
int main()
{
	vector <int> myvector;
	vector<int> ve(3);
	cout<<ve.size()<<"\n";
	cout<<myvector.empty()<<"\n";;
	cout<<myvector.size()<<"\n";
	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);

	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);
myvector.push_back(1);

	myvector.push_back(2);
	myvector.push_back(5);
	myvector.push_back(7);
	myvector.push_back(8);
	myvector.push_back(11);
	myvector.push_back(15);
	myvector.push_back(14);
	myvector.push_back(16);   
	cout<<myvector.size()<<"\n";
	/*
	vector<int>::vector_Iterator end = myvector.end();
	vector<int>::vector_Iterator* tmp = &end;*/
	vector<int>::vector_Iterator itr;
	cout<<"\n";
	myvector[0]=6;
	for(itr=myvector.rbegin();itr!=myvector.rend();itr--)
	{
		cout<<*itr<<"\t";
	}/*
	cout<<"\n";
	for(it:myvector)
		cout<<it<<" ";
	cout<<"\n";*/
	return 0;
}
