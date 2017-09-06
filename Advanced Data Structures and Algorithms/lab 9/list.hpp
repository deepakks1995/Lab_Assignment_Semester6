#include<iostream>
#include<cstddef>
#ifndef LIST_HPP
#define LIST_HPP
namespace abc
{
	template<class T>
		class node
		{
			template<class U> friend class list;
			private:
			T data;
			node<T> *link;
		public:
			T& getData()
			{
				return data;
			}
			node<T> * getlink()
			{
				return link;
			}
		};
	template<class T>
		class list
		{
			private:
				node<T> *top;
				node<T> *bottom;
				int size;
			public:
				void operator = (const list &l);
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
				T topElement();
				bool search(const T& t);
				T& getListElement(const T& t);
				void updateListElement(const T& t);
				node<T>* topNode()
				{
					return top;
				}
		};
		template<class T>
		void list<T>::updateListElement(const T& t)
		{
			node<T> *temp = top;
			while(temp)
			{
				if(temp->data == t)
				{
					temp->data = t;
					return;
				}
				temp = temp->link;
			}
			append(t);
		}
		template<class T>
		T& list<T>::getListElement(const T& t)
		{
				node<T> *temp = top;
				if(!top)
					throw("List is Empty..\n");
				else
				{
					while(temp)
					{
						if(temp->data == t)
							return temp->data;
						temp = temp->link;
					}
					throw("Element Not Present in the List..\n");
				}
		}
		template<class T>
		bool list<T>::search(const T& t)
		{
			node<T> *temp = top;
			while(temp)
			{
				if(temp->data == t)
					return 1;
				temp = temp->link;
			}
			return 0;
		}
		template<class T>
		void list<T>::operator = (const list &x)
		{
			top = NULL;
			bottom = NULL;
			size = 0;
			if(x.top == NULL)
			{
				top = NULL;
				bottom = NULL;
				size = 0;
			}
			else
			{
				node<T> *iter = x.top;
				while(iter != NULL)
				{
					append(iter->data);
					iter = iter->link;
				}
			}
		}
	template<class T>
		list<T>::list()
		{
			top = NULL;
			bottom = NULL;
			size = 0;
		}
	template<class T>
		list<T>::list(const list<T> &x)
		{
			top = NULL;
			bottom = NULL;
			size = 0;
			if(x.top == NULL)
			{
				top = NULL;
				bottom = NULL;
				size = 0;
			}
			else
			{
				node<T> *iter = x.top;
				while(iter != NULL)
				{
					append(iter->data);
					iter = iter->link;
				}
			}
		}
	template<class T>
		list<T>::~list()
		{
			//std::cout<<"list Destructor Invoked..\n";
			node<T> *temp;
			while(top!=NULL)
			{
				temp = top;
				top = top->link;
				delete temp;
			}
		}
	template<class T>
		void list<T>::append(const T &value)
		{
			node<T> *temp = new node<T>;
			temp->data = value;
			temp->link = NULL;
			size++;
			if(top == NULL)
			{
				top = temp;
				bottom = temp;;
			}
			else
			{
				bottom->link = temp;
				bottom = temp;
			}
		}
	template<class T>
		inline int list<T>::length()
		{
			return size;
		}
	template<class T>
		inline bool list<T>::empty()
		{
			return (size==0);
		}
	template<class T>
		void list<T>::cons(const T &value)
		{
			node<T> *temp = new node<T>;
			temp->data = value;
			temp->link = NULL;
			size++;
			if(top == NULL)
			{
				top = temp;
				bottom = temp;
			}
			else
			{
				temp->link = top;
				top = temp;
			}
		}
	template<class T>
		void list<T>::remove(const T &value)
		{
			if(top->data == value && top!=NULL)
			{
				node<T> *temp = top;
				top = top->link;
				delete temp;
				size--;
			}
			else if(top!=NULL)
			{
				node<T> *iter = top;
				bool flag = 1;
				while(iter->link)
				{
					if(iter->link->data == value)
					{
						node<T> *temp = iter->link;
						iter->link = temp->link;
						if(temp == bottom)
							bottom = iter;
						delete temp;
						size--;
						break;
					}
					iter = iter->link;
				}
			}
		}
	template<class T>
		void list<T>::append(list<T> &x)
		{
			node<T> *iter = x.top;
			while(iter!=NULL)
			{
				append(iter->data);
				iter = iter->link;
			}
		}
	template<class T>
		void list<T>::print()
		{
			node<T> *iter = top;
			while(iter)
			{
				std::cout<<iter->data<<"\t";
				iter = iter->link;
			}
		}
	template<class T>
		T list<T>::topElement()
		{
			return top->data;
		}
}

#endif
