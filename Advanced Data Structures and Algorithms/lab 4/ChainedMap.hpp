#include "vector.hpp"
#include "list.hpp"
#include "Dictionary.hpp"
#include<sstream>
#include<iostream>
#include<cstddef>
#ifndef CHAINEDMAP_HPP_
#define CHAINEDMAP_HPP_
using namespace abc;
using namespace std;
namespace abc
{

	template<class Key, class Value>
		class pair
		{
			template<class k,class v> friend class ChainedMap;
			Key key;
			Value value;
			public:
			bool operator==(pair p)
			{
				return this->key==p.key;
			}
			void operator = (pair p)
			{
				key = p.key;
				value = p.value;
			}
		};

	template<class Key, class Value>
		class ChainedMap  : public Dictionary<Key,Value>
	{
		/*
		 * Function rehash:
		 * Resizes the has table to the next convenient size.
		 * Called when all the slots are full and a new element needs to be inserted.
		 */
		void rehash();
		public:
		/*
		 * Constructor: ChainedMap
		 * Creates a Chained Hash Table with some default size.
		 * NOTE: Please try to ensure that the size is a prime number for better performance.
		 */
		ChainedMap();
		/*
		 * Constructor:ChainedMap
		 * Creates an empty Chained Map with the ability to hold atleast num Key value pairs.
		 */
		ChainedMap(const int& num);
		/*
		 * Constructor: Chained Map
		 * Creates a new Hash Table which is the exact copy of the given hash table.
		 **/
		ChainedMap(ChainedMap<Key, Value>& ht);
		/*
		 * Destructor
		 * Deletes the memory acquired by the given Hash Map.
		 */
		~ChainedMap(){}
		/*
		 * A convenience wrapper operator.
		 * Returns a reference to the value corresponding to the given key.
		 * If the key does'nt exist, then inserts the key in the table,
		 * with the default value of the Value type.
		 * This should enable you to write code like this:
		 * ChainedHashMap<int,int> ht;
		 * ht[1] = 2;
		 * ht[1] = 4;
		 * ht[2] = 3;
		 */
		Value& operator[](const Key& key);

		int hash_func(const Key& key);
		bool isprime(int num);
		void put (const Key& key, const Value& value);
		int length();
		bool has(const Key& key);
		Value get(const Key& key);
		void remove(const Key& key);
		protected:
		vector<list<pair<Key,Value> > >& get_table();

		private:
		vector<list<pair<Key,Value > > > *table;
		int size;
		int index;
	};

	template<class Key, class Value>
		void ChainedMap<Key, Value>::rehash()
		{
			int n = 2*(table->size())+1;
			while(!isprime(n)) 
				n+=2;
			vector<list<pair<Key, Value> > > *table2;
			table2 = table;
			table = new vector<list<pair<Key,Value > > >;
			table->resize(n);
			for(int i=0;i<n;i++)
			{
				list<pair<Key,Value> > *temp = new list<pair<Key,Value> >;
				table->push_back(*temp);	
			}
			for(int i=0;i<table2->size();i++)
			{
				list<pair<Key, Value> > temp = (*table2)[i];
				list<pair<Key,Value> > *itr = &temp;
				while(!itr->empty())
				{
					pair<Key,Value> p = itr->top();
					put(p.key,p.value);
					itr->remove(p);
				}
			}	
			delete table2;
		}

	template <class Key, class Value>
		ChainedMap<Key,Value>::ChainedMap()
		{
			this->size = 5;
			table = new vector<list<pair<Key,Value> > >;
			table->resize(5);
			for(int i=0;i<5;i++)
			{
				list<pair<Key,Value> > *temp = new list<pair<Key,Value> >;
				table->push_back(*temp);
			}
		}

	template <class Key, class Value>
		ChainedMap<Key, Value>::ChainedMap(const int& num)
		{
			this->size = num;
			table = new vector<list<pair<Key,Value> > >;
			table->resize(num);
			for(int i=0;i<size;i++)
			{
				list<pair<Key, Value> > *temp = new list<pair<Key, Value> >;
				table->push_back(*temp);
			}
		}

	template <class Key, class Value>
		ChainedMap<Key, Value>::ChainedMap(ChainedMap <Key, Value>& ht)
		{
			this->size = ht.length();
			table = new vector<list<pair<Key, Value> > >;
			table->resize(size);
			vector<list<pair<Key,Value> > > *table2 = &(ht.get_table());
			for(int i=0;i<size;i++)
			{
				list<pair<Key,Value> > *temp = new list<pair<Key, Value> >;
				table->push_back(*temp);
			}
			for(int i=0;i<table2->size();i++)
			{
				list<pair<Key,Value > > temp = (*table2)[i];
				list<pair<Key,Value > > *itr = &temp;
				while(itr!=NULL)
				{
					pair<Key, Value> p = itr->top();
					put(p.key, p.value);
					itr->remove(p);
				}
			}
		}

	template <class Key, class Value>
		int ChainedMap<Key, Value> :: hash_func(const Key& key)
		{
			stringstream ss;
			ss << key;
			string s = ss.str();
			int num=0,MOD =(int)1e9+7,x = 1;
			for(int i=0; i<s.length() ; i++)
			{
				num = (num%MOD + (s[i]*x)%MOD)%MOD;
				x = (x*39)%MOD;
			}
			return num % table->size();
		}

	template <class Key, class Value>
		bool ChainedMap<Key, Value>::isprime(int num)
		{
			for(int i=2;i*i<=num;i++)
			{
				if(num%i==0)
					return 0;
			}
			return 1;
		}

	template <class Key, class Value>
		void ChainedMap<Key, Value>::put(const Key& key, const Value& value)
		{
			int partition = hash_func(key);
			pair<Key,Value> p1;
			p1.key = key;
			p1.value = value;
			(*table)[partition].append(p1);
			index++;
			if((*table)[partition].length() >= (table->size()/2))
				rehash();
		}

	template <class Key, class Value>
		int ChainedMap<Key,Value>:: length()
		{
			return table->size();
		}

	template <class Key, class Value>
		bool ChainedMap<Key,Value>::has(const Key& key)
		{
			int partition  = hash_func(key);
			list<pair<Key, Value > > temp = (*table)[partition];
			pair<Key,Value> p;
			p.key = key;
			return temp.search(p);
		}

	template <class Key, class Value>
		Value ChainedMap<Key,Value>::get(const Key& key)
		{
			int partition = hash_func(key);
			list<pair<Key, Value > > temp = (*table)[partition];
			try
			{
				if(has(key)==0)
					throw ("Key not found\n");
				else
				{
					pair <Key,Value> p1;
					p1.key = key;
					pair<Key,Value> p = temp.get_data(p1);
					return p.value;
				}
			}
			catch(const char* x)
			{
				cout<<x;
				return 0;
			}
		}

	template<class Key, class Value>
		Value& ChainedMap<Key, Value>:: operator[](const Key& key)
		{
			int partition = hash_func(key);
			list<pair<Key,Value > > *temp = &(*table)[partition];
			if(temp->empty())
				put(key,(Value)0);
				
			pair<Key, Value> p;
			p.key = key;
			return temp->get_data(p).value;
		}

	template<class Key, class Value>
		void ChainedMap<Key,Value>::remove(const Key& key)
		{
			int partition = hash_func(key);
			if(!has(key))
				std::cout<<"Element does not exists";
			else
			{	
				pair<Key, Value> p;
				p.key = key;
				(*table)[partition].remove(p);
				--index;
			}
		}

	template<class Key, class Value>
		vector<list<pair<Key, Value> > >& ChainedMap<Key, Value>::get_table()
		{
			return *table;
		}
}
#endif /* CHAINEDMAP_HPP_ */
