/*
 * OpenMap.hpp
 *
 */

#ifndef OPENMAP_HPP_
#define OPENMAP_HPP_

#include<iostream>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include "vector.hpp"
#include "struct1.hpp"
#include<cstring>
#include "Dictionary.hpp"
#define SIZE 119

using namespace abc;
using namespace std;

namespace eni
{

	template<class Key, class Value>
		class OpenMap  : public Dictionary<Key,Value> 
	{
		private:

			hash1 hash1_tab[SIZE];
			int factor;

		public: 



			OpenMap();   
			OpenMap(const int& num);    
			OpenMap(OpenMap<Key, Value>& ht);    
			~OpenMap();    
			Value& operator[](const Key& key);        
			bool has(const Key& key);    
			void remove(const Key& key);   
			Value get(const Key& key);   
			void put(const Key& key, const Value& value);
			int code(const Key& key);
			void Display();
	};

	template<class Key, class Value>
		OpenMap<Key,Value>::OpenMap(){
			//hash1 hash1_tab[SIZE];
			for(int i=0;i<SIZE;i++){
				hash1_tab[i].probe=0;
				hash1_tab[i].capacity=SIZE;
			}
			factor=SIZE;
		}


	template<class Key, class Value>
		OpenMap<Key,Value>::OpenMap(const int& num){
			for(int i=0;i<num;i++){
				hash1_tab[i].probe=0;
				hash1_tab[i].capacity=num;

			}
			factor=num;
		}
	template<class Key, class Value>
		Value& OpenMap<Key,Value>:: operator[](const Key& key){
			return get(key);
		}
	template<class Key, class Value>
		OpenMap<Key,Value>::OpenMap(OpenMap<Key, Value>& ht){
			int i=0;
			while(ht[i].probe!=1){
				i++;
			}           
			int si=ht[i].capacity;
			factor=si;
			for(i=0;i<si;i++){
				if(ht[i].probe!=0){
					hash1_tab[i].probe=ht[i].probe;
					hash1_tab[i].key.push_back(ht[i].key[0]);
					hash1_tab[i].value.push_back(ht[i].value[0]);
					hash1_tab[i].capacity=si;
				}
			}
		}
	template<class Key, class Value>
		OpenMap<Key,Value>::~OpenMap(){
			for(int i=0;i<SIZE;i++){
				if(hash1_tab[i].probe==1){
					hash1_tab[i].key.pop_back();
					hash1_tab[i].value.pop_back();
				}

			}
		}
	template<class Key, class Value>
		bool OpenMap<Key,Value>::has(const Key& key){
			int index=code(key);
			int c=index;
			int flag=0;
			if(hash1_tab[index].probe==0)
				return 0;
			if(hash1_tab[index].probe==1)
				return 1;

			while(flag!=1){
				if(index==SIZE-1)
					index=0;
				else index++;

				if(hash1_tab[index].probe==1){
					if(key==hash1_tab[index].key[0]){
						flag=1;
						return 1;
					}
				}
				if(c==index)
					return 0;
			}
		}
	template<class Key, class Value>
		void OpenMap<Key,Value>::remove(const Key& key){
			int index=code(key);
			int c=index;
			int flag=0;
			if(hash1_tab[index].probe==0)
				return;
			if(hash1_tab[index].probe==1){
				hash1_tab[index].probe=-1;
				hash1_tab[index].key.pop_back();
				hash1_tab[index].value.pop_back();
				flag=1;
			}

			while(flag!=1){
				if(index==SIZE-1)
					index=0;
				else index++;

				if(hash1_tab[index].probe==1){
					if(key==hash1_tab[index].key[0]){
						flag=1;
						hash1_tab[index].probe=-1;
						hash1_tab[index].key.pop_back();
						hash1_tab[index].value.pop_back();
					}
				}
				if(c==index)
					return ;
			}
		}
	template<class Key, class Value>
		Value OpenMap<Key,Value>::get(const Key& key){
			int index=code(key);
			int c=index;
			int flag=0;
			if(hash1_tab[index].probe==0)
				return "Not Found";
			if(hash1_tab[index].probe==1)
				return hash1_tab[index].value[0];

			while(flag!=1){
				if(index==SIZE-1)
					index=0;
				else index++;

				if(hash1_tab[index].probe==1){
					if(key==hash1_tab[index].key[0]){
						flag=1;
						return hash1_tab[index].value[0];
					}
				}
				if(c==index)
					return "Not Found";
			}
		}
	template<class Key, class Value>
		void OpenMap<Key,Value>::put(const Key& key, const Value& value){
			int index=code(key);
			int c=index;
			int flag=0;
			if((hash1_tab[index].probe==0)||(hash1_tab[index].probe==-1)){
				hash1_tab[index].key.push_back(key);
				hash1_tab[index].value.push_back(value);
				hash1_tab[index].probe=1;
				flag=1;
			}
			else index++;

			while(flag!=1){
				if((hash1_tab[index].probe==0)||(hash1_tab[index].probe==-1)){
					hash1_tab[index].key.push_back(key);
					hash1_tab[index].value.push_back(value);
					hash1_tab[index].probe=1;
					flag=1;
				}
				if(index==SIZE-1)
					index=0;
				else index++;

				if(c==index)
					return;
			}
		}
	template<class Key, class Value>
		int OpenMap<Key,Value>::code(const Key& key){
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
		void OpenMap<Key,Value>::Display(){
			for(int i=0;i<SIZE;i++){
				if(hash1_tab[i].probe==1){
					cout<<hash1_tab[i].key[0]<<" : "<<hash1_tab[i].value[0]<<endl;                 
				}
			}
		}
}







#endif /* OpenMap_HPP_ */
