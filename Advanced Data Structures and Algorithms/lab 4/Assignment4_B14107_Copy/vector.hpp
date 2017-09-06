/*
 * vector.hpp
 *
 * A template file for implementing a resizable vector. 
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <new>

namespace abc{
	template<class Item> 
		class vector{
			private:
				Item* v;        //pointer to vector
				int n;          //size of vector
				int capacity;   //max capacity

			public:
				vector();      //default constructor
				vector(const int& isize);       //constructor with argument
				vector(const int& isize, const Item& ival);     //constructor with argument
				vector(vector &obj);		//copy constructor
				void vector_copy(vector &obj);
				~vector();     //destructor
				inline Item& operator[](const int& i);     //return stored value at index i
				void push_back(const Item& item);      //insert value at the end of vector
				bool empty();      //check for empty vector
				int size();        //return size of vector
				int get_capacity();
				void setn(const int nval);   
				void fill(const Item& item);      //replace all value of vector by item
				void print();       //print current vector
				void pop_back();

				class iterator{		//for iteration
					private:
						Item * p;
					public:

						void operator++(){
							++p;
						}

						void operator--(){
							--p;
						}

						bool operator==(Item *t){
							return p == t;

						}
						bool operator!=(Item *t){
							return p != t;
						}

						void operator=(Item *t){
							p = t;
						}

						void operator=(const iterator &it){
							p = it.p;
						}

						Item& operator*(){
							return *p;
						}

				};

				Item* begin();
				Item* end();
		};

	template<class Item>
		vector<Item>::vector(){
			v=NULL;
			n=0;
			capacity=0;
		}

	template<class Item>
		vector<Item>::vector(const int& isize){
			n=isize;
			v=new Item[isize];
			capacity=isize;
			for(int i=0;i<isize;++i)
				v[i]=0;
		}

	template<class Item>
		vector<Item>::vector(const int& isize, const Item& ival){
			n=isize;
			capacity=isize;
			v=new Item[isize];
			for(int i=0;i<isize;++i)
				v[i]=ival;
		}

	template<class Item>
		vector<Item>::vector(vector<Item> &obj)
		{
			//delete[] v;
			v = new Item[obj.size()];
			for(int i=0;i<obj.size();++i)
				v[i]=obj[i];
			//*v = *obj.v;		//copies the values
			n = obj.size();
			capacity = obj.get_capacity();
		}

	template<class Item>
		void vector<Item>::vector_copy(vector<Item> &obj)
		{
			if(v!=NULL)
				delete[] v;
			v = new Item[obj.size()];
			for(int i=0;i<obj.size();++i)
				v[i]=obj[i];
			//*v = *obj.v;		//copies the values
			n = obj.size();
			capacity = obj.get_capacity();
		}

	template<class Item>
		vector<Item>::~vector(){
			delete[] v;
		}

	template<class Item>
		inline Item& vector<Item>::operator[](const int& i){
			return v[i];
		}

	template<class Item>
		void vector<Item>::push_back(const Item& item){
			if(capacity==0)
			{
				v=new Item;
				capacity=1;
				n=1;
				v[0]=item;
			}    
			else
			{
				if(capacity==n)
				{
					Item* temp=new Item[capacity*2];
					capacity=capacity*2;
					int i=0;
					while(i<n)
					{
						temp[i]=v[i];
						++i;
					}
					delete[] v;
					v=temp;
				}

				v[n]=item;
				++n;
			}

		}

	template <class Item> 
		void vector<Item>::pop_back()
		{
			--n;
		}

	template<class Item>
		bool vector<Item>::empty(){
			if(n==0)
				return 1;
			else
				return 0;
		}

	template<class Item>
		int vector<Item>::size(){
			return n;
		}

	template<class Item>
		int vector<Item>::get_capacity(){
			return capacity;
		}

	template <class Item>
		void vector<Item>::setn(const int nval)
		{
			n=nval;
		}

	template<class Item>
		void vector<Item>::fill(const Item& item){
			for(int i=0;i<n;++i)
				v[i]=item;
		}

	template<class Item>
		void vector<Item>::print(){
			for(int i=0;i<n;++i)
				std::cout<<v[i]<<"\n";
		}

	template<class Item>
		Item* vector<Item>::begin(){
			return v;
		}

	template<class Item>
		Item* vector<Item>::end(){
			return v+n;
		}



}
#endif
