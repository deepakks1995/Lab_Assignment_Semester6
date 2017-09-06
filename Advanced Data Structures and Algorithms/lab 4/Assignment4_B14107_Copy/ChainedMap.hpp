/*
 * ChainedMap.hpp
 *
 */

#ifndef CHAINEDMAP_HPP_
#define CHAINEDMAP_HPP_


#include "list.hpp"
#include "Dictionary.hpp"
#include<iostream>
#include<stdlib.h>
#define SIZE 119
using namespace abc;
using namespace std;

namespace abc
{
	template<class Key, class Value>
		class ChainedMap : public Dictionary<Key,Value>
	{
		//void rehash();
		private:
			//vector<string> *M[SIZE];
			list<string> L[SIZE];
			int factor;
			//int l[SIZE];
		public:

			bool has(const Key& key);    
			void remove(const Key& key);    
			Value get(const Key& key);
			void put(const Key& key, const Value& value) ;
			ChainedMap();
			ChainedMap(const int& num);    
			ChainedMap(ChainedMap<Key, Value>& ht);    
			~ChainedMap();
			Value& operator[](const Key& key);
			int code(const Key& key);
			void Display();
	};

	template<class Key, class Value>
		ChainedMap<Key,Value>::ChainedMap(){
			//for(int i=0;i<num;i++)
			//     l[i]=0;
			factor=SIZE;
		}

	template<class Key, class Value>
		Value& ChainedMap<Key,Value>:: operator[](const Key& key){
			return get(key);
		}

	template<class Key, class Value>
		ChainedMap<Key,Value>::ChainedMap(ChainedMap<Key, Value>& ht){
			for(int i=0;i<SIZE;i++)
				L[i].append(ht[i]);
			//for(int i=0;i<num;i++)
			//   l[i]=0;

			factor=SIZE;
		}

	template<class Key, class Value>
		ChainedMap<Key,Value>::~ChainedMap(){
			for(int i=0;i<SIZE;i++){
				if(L[i].empty()!=1){
					int j=L[i].length();
					for(int i=1;i<=j;i++)
						L[i].remove(i);
				}
			}
			factor=SIZE;
		}

	template<class Key, class Value>
		ChainedMap<Key,Value>::ChainedMap(const int& num){
			//for(int i=0;i<num;i++)
			//     l[i]=0;
			factor=num;

		}

	template<class Key, class Value>
		void ChainedMap<Key,Value>::put(const Key& key, const Value& value){
			int index=code(key);
			L[index].cons(key,value);
			// l[index]++;
			//if(l[index]>SIZE/2)
			//     rehash();

		}
	template<class Key, class Value>
		bool ChainedMap<Key,Value>::has(const Key& key){
			int index=code(key);
			list<string> temp;
			temp.append(L[index]);
			int flag=0;
			int j=0;
			int c=L[index].length();
			while((flag!=1)&&(j!=c)){
				if(key==temp.next1()){
					flag=1;
					return 1;
				}
				j++;
				//cout<<L[index].next1();

			}
			return 0;
		}
	template<class Key, class Value>
		Value ChainedMap<Key,Value>::get(const Key& key){
			int index=code(key);
			list<string> temp;
			list<string> temp1;
			//string key1;
			temp.append(L[index]);
			temp1.append(L[index]);
			int flag=0;
			int j=0;
			int c=L[index].length();
			cout<<c<<endl;
			while((flag!=1)&&(j!=c)){
				if(key==temp.next1()){
					flag=1;
					//key1=temp1.next2();
					return temp1.next2();
				}
				j++;

			}
			return 0;
		}
	template<class Key, class Value>
		void ChainedMap<Key,Value>::remove(const Key& key){
			int index=code(key);
			list<string> temp;
			temp.append(L[index]);
			int flag=0;
			int j=0;
			int g=0;
			int c=L[index].length();
			while((flag!=1)&&(j!=c)){
				if(key==temp.next1()){
					flag=1;
					c++;
					//return temp.next();
				}
				g++;
			}
			//return 0;
			if(flag==1)
				L[index].remove(g);
			// L[index]--;

		}
	template<class Key, class Value>
		int ChainedMap<Key,Value>::code(const Key& key){
			long long int k=0;
			int i=0;
			while(key[i]!='\0'){
				i++;
			}
			int c=i;
			c=c-1;
			for(int j=0;j<i;j++)
				k=k+pow(39,j)*(int)key[c-j];
			return k%factor;
		}
	template<class Key, class Value>
		void ChainedMap<Key,Value>::Display(){
			for(int i=0;i<SIZE;i++){
				if(L[i].length()!=0)
					L[i].dump();               
			}
		}

}

#endif /* CHAINEDMAP_HPP_ */
