#include <cstddef>
#include <iostream>
#ifndef LIST_HPP
#define LIST_HPP 1
using namespace std;
namespace abc
{
	template<class T>
		class listNode
		{
			template<class U> friend class list;		
			private:
			
				T data;
				listNode<T> *link;
		};

	template<class T>
		class list
		{
			private:
				listNode<T> *first;
				listNode<T> *last;
				int size;
			public:
				/*
				 * Primary contructor.
				 * Should construct an empty list.
				 * Size of the created list should be zero.
				 */
				list();
				/*
				 * Seondary constructor.
				 * Creates a new list which is a copy of the provided list.
				 */
				list(const list<T> & x);
				/*
				 * Destructor.
				 * Frees all the memory acquired by the list.
				 */
				~list();
				/*
				 * adds value at the end of the list.
				 */
				void append(const T& value);
				/*
				 * Returns the length of the list.
				 */
				inline int length();
				/*
				 * Returns a boolean indicating whether the list is empty.
				 */
				inline bool empty();
				/*
				 * Adds a value to the front of the list.
				 */
				void cons(const T& value);
				/*
				 * Removes the first occurence of the value from list.
				 */
				void remove(const T & x);
				/*
				 * Appends the given list x at the end of the current list.
				 */
				void append(list<T>& x);
				
				void print();
			
				bool search(const T& x);

				T& get_data(const T& x);

				T top();
				
				listNode<T>& next_Node();

		};

	template<class T>
		list<T>::list()
		{
			first = NULL;
			last = NULL;
			size=0;
		}

	template<class T>
		list<T>::list(const list<T>& x)
		{
			first = NULL;
			last = NULL;
			size=0;
			if(x.first == NULL)
			{
				first = NULL;
				last = NULL;
			}
			else
			{
				listNode<T> *p = x.first;
				while(p!=NULL)
				{
					append(p->data);
					p = p->link;		
				}
			}
		}

	template<class T>
		list<T>::~list()
		{
			listNode<T> *next;
			while(first)
			{
				next = first->link;
				delete first;
				first = next;
			}
		}

	template<class T>
		void list<T>::append(const T& value)
		{
			listNode<T> *temp = new listNode<T>;
			temp->data = value;
			temp->link = NULL;
			if(first==NULL)
			{
				first = temp;
				last = temp;
			}
			else
			{
				last->link = temp;
				last = temp;
			}
			size++;
		}

	template<class T>
		inline int list<T>::length()
		{
			return size;
		}

	template<class T>
		bool list<T>::empty()
		{
			return size==0;
		}

	template<class T>
		void list<T>::cons(const T& value)
		{
			if(first==NULL)
			{
				first = new listNode<T>;
				first->data=value;
				first->link=NULL;
				last = first;
			}
			else
			{
				listNode<T> *temp = new listNode<T>;
				temp->data = value;
				temp->link = first;
				first = temp;
			}
			size++;
		}

	template<class T>
		void list<T>::remove(const T& x)
		{
			bool check=0;
			if(first==NULL)
			check=2;
			if(check==0 && first->data == x )
			{
				check=1;
				listNode<T> *temp;
				temp = first;
				first = first->link;
				delete temp;
			}
			listNode<T> *p = first;
			while(check==0 && p->link!=NULL)
			{
				if(p->link->data == x)
				{
					check=1;
					listNode<T> *temp = p->link;
					p->link = temp->link;
					delete temp;
				}
				p = p->link;
			}
			if(check==1)
				size--;
		}
	template<class T>
		void list<T>::append(list<T>& x)
		{
			listNode<T> *next = x.first;
			while(next!=NULL)
			{
				listNode<T> *temp = new listNode<T>;
				temp->data = next->data;
				temp->link = NULL;
				if(first==NULL)
				{
					first=temp;
					last=temp;
				}
				else
				{
					last->link=temp;
					last=temp;
				}
				next = next->link;
				size++;
			}
		}

	template<class T>
		void list<T>::print()
		{
			listNode<T> *temp=first;
			while(temp!=NULL)
			{
				std::cout<<temp->data<<"  ";
				temp = temp->link;
			}
		}

	template<class T>
		T list<T>::top()
		{
			return first->data;
		}

	template<class T>
		bool list<T>::search(const T& x)
		{	
			if(size==0)
				return 0;
			else
			{
				listNode<T> *temp = first;
				while(temp)
				{
					if(temp->data==x)
						return 1;
					temp = temp->link;
				}
				return 0;
			}
		}

	template<class T>
		T& list<T>::get_data(const T& x)
		{
			if(size==0)
				throw "List is Empty\n";
			else
			{
				listNode<T> *temp = first;
				while(temp)
				{
					if(temp->data==x)
						return temp->data;
					temp = temp->link;
				}
				throw "Data not found\n";
			}
		}

	template<class T>
		listNode<T>& list<T>::next_Node()
		{
			listNode<T> *temp = first;
			return temp->link;
		}
}
#endif
