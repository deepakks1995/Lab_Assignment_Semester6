/*
 * queue.hpp
 *
 */
#include"list.hpp"
#ifndef QUEUE_HPP_
#define QUEUE_HPP_

using namespace abc;
namespace abc
{
	template <class T>
		class queue
		{
			private:
				list<T> l;	
			public:
				/*
				 * Constructs a new queue.
				 */
				queue();
				/*
				 * Pushes t to at the back of the queue.
				 */
				void push(const T& t);
				/*
				 * Returns the element at the front of the queue.
				 * Also removes the front element from the queue.
				 */
				T pop();
				/*
				 * Returns the element at the front of the queue.
				 * Does not remove the front element.
				 */
				T front();
				/*
				 * Returns the number of elements currently in the queue.
				 */
				inline int size();
				/*
				 * Returns a boolean indicating whether the queue is empty or not.
				 */
				inline bool empty();
				/*
				 * Destructor
				 * Fress the memory occupied by the queue elements.
				 */
				~queue();
				void print();
		};
	template<class T>
		queue<T>::queue()
		{
		}
	template<class T>
		void queue<T>::push(const T &t)
		{
			l.append(t);
		}
	template<class T>
		T queue<T>::pop()
		{
			T temp = l.topElement();
			l.remove(temp);
			return temp;
		}
	template<class T>
		T queue<T>::front()
		{
			return l.topElement();
		}
	template<class T>
		inline int queue<T>::size()
		{
			return l.length();
		}
	template<class T>
		inline bool queue<T>::empty()
		{
			return (l.length()==0);
		}
	template<class T>
		queue<T>::~queue()
		{
		}
	template<class T>
		void queue<T>::print()
		{
			l.print();
		}
}
#endif
