/*
 * DoubleHashMap.hpp
 *
 * This is an interface for a hash table using Double Hashing.
 */

#ifndef DOUBLEHASHMAP_HPP_
#define DOUBLEHASHMAP_HPP_

#include<iostream>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include "vector.hpp"
#include "struct1.hpp"
#include<cstring>
#define SIZE 119

using namespace abc;
using namespace std;

namespace abc
{
	template<class Key, class Value>
		class DoubleHashMap : public Dictionary<Key,Value> 
	{

		//void rehash();
		private:
			hash1 hash2_tab[SIZE];
			int factor;
		public:

			DoubleHashMap();   
			DoubleHashMap(const int& num);   
			DoubleHashMap(DoubleHashMap<Key, Value>& ht);    
			~DoubleHashMap();    
			Value& operator[](const Key& key);
			bool has(const Key& key);    
			void remove(const Key& key);   
			Value get(const Key& key);   
			void put(const Key& key, const Value& value);
			int code(const Key& key);
			int code1(const Key& key);
			void Display();
	};

	template<class Key, class Value>
		DoubleHashMap<Key,Value>::DoubleHashMap(){
			//hash1 hash2_tab[SIZE];
			for(int i=0;i<SIZE;i++){
				hash2_tab[i].probe=0;
				hash2_tab[i].capacity=SIZE;
			}
			factor=SIZE;
		}


	template<class Key, class Value>
		DoubleHashMap<Key,Value>::DoubleHashMap(const int& num){
			for(int i=0;i<num;i++){
				hash2_tab[i].probe=0;
				hash2_tab[i].capacity=num;

			}
			factor=num;
		}
	template<class Key, class Value>
		Value& DoubleHashMap<Key,Value>:: operator[](const Key& key){
			return get(key);
		}
	template<class Key, class Value>
		DoubleHashMap<Key,Value>::DoubleHashMap(DoubleHashMap<Key, Value>& ht){
			int i=0;
			// while(ht[i].probe!=1){
			//        i++;
			//}           
			int si=ht[i].capacity;
			factor=si;
			for(i=0;i<si;i++){
				if(ht[i].probe!=0){
					hash2_tab[i].probe=ht[i].probe;
					hash2_tab[i].key.push_back(ht[i].key[0]);
					hash2_tab[i].value.push_back(ht[i].value[0]);
					hash2_tab[i].capacity=si;
				}
			}
		}
	template<class Key, class Value>
		DoubleHashMap<Key,Value>::~DoubleHashMap(){
			for(int i=0;i<SIZE;i++){
				if(hash2_tab[i].probe==1){
					hash2_tab[i].key.pop_back();
					hash2_tab[i].value.pop_back();
				}
			}
		}
	template<class Key, class Value>
		bool DoubleHashMap<Key,Value>::has(const Key& key){
			int index=code(key);
			int c=0;
			int flag=0;
			if(hash2_tab[index].probe==0)
				return 0;
			if(hash2_tab[index].probe==1){
				flag=1;
				return 1;
			}

			while(flag!=1){
				index=(index+code1(key))%SIZE;

				if(hash2_tab[index].probe==1){
					if(key==hash2_tab[index].key[0]){
						flag=1;
						return 1;
					}
				}
				c++;
				if(c==SIZE)
					return 0;
			}
		}
	template<class Key, class Value>
		void DoubleHashMap<Key,Value>::remove(const Key& key){
			int index=code(key);
			int c=0;
			int flag=0;
			if(hash2_tab[index].probe==0)
				return;
			if(hash2_tab[index].probe==1){
				flag=1;
				hash2_tab[index].probe=-1;
				hash2_tab[index].key.pop_back();
				hash2_tab[index].value.pop_back();
			}

			while(flag!=1){
				index=(index+code1(key))%SIZE;

				if(hash2_tab[index].probe==1){
					if(key==hash2_tab[index].key[0]){
						flag=1;
						hash2_tab[index].probe=-1;
						hash2_tab[index].key.pop_back();
						hash2_tab[index].value.pop_back();
					}
				}
				c++;
				if(c==SIZE)
					return ;
			}
		}
	template<class Key, class Value>
		Value DoubleHashMap<Key,Value>::get(const Key& key){
			int index=code(key);
			int c=0;
			int flag=0;
			//cout<<index<<endl;
			if(hash2_tab[index].probe==0)
				return "Not Found";
			if(hash2_tab[index].probe==1){
				flag=1;
				return hash2_tab[index].value[0];
			}

			c++;
			while(flag!=1){
				index=(index+code1(key))%SIZE;

				if(hash2_tab[index].probe==1){
					if(key==hash2_tab[index].key[0]){
						flag=1;
						return hash2_tab[index].value[0];
					}
				}
				//index++;
				c++;
				if(c==SIZE)
					return "Not Found";
			}
		}
	template<class Key, class Value>
		void DoubleHashMap<Key,Value>::put(const Key& key, const Value& value){
			int index=code(key);
			int c=0;
			int flag=0;
			if((hash2_tab[index].probe==0)||(hash2_tab[index].probe==-1)){
				hash2_tab[index].key.push_back(key);
				hash2_tab[index].value.push_back(value);
				hash2_tab[index].probe=1;
				flag=1;
				c++;
			}
			else {
				index=(index+code1(key))%SIZE;
			}

			while(flag!=1){
				if((hash2_tab[index].probe==0)||(hash2_tab[index].probe==-1)){
					hash2_tab[index].key.push_back(key);
					hash2_tab[index].value.push_back(value);
					hash2_tab[index].probe=1;
					flag=1;
				}
				else {
					index=(index+code1(key))%SIZE;
					//index++;
				}
				c++;

				if(c==SIZE)
					return;
			}
		}
	template<class Key, class Value>
		int DoubleHashMap<Key,Value>::code(const Key& key){
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
		int DoubleHashMap<Key,Value>::code1(const Key& key){
			long long int k=0;
			int i=0;
			while(key[i]!='\0'){
				i++;
			}
			int c=i;
			c=c-1;
			for(int j=0;j<i;j++)
				k=k+pow(41,j)*(int)key[c-j];
			return k%factor;
		}
	template<class Key, class Value>
		void DoubleHashMap<Key,Value>::Display(){
			for(int i=0;i<SIZE;i++){
				if(hash2_tab[i].probe==1){
					cout<<hash2_tab[i].key[0]<<" : "<<hash2_tab[i].value[0]<<endl;                 
				}
			}
		}

}

#endif 
