#include "list.hpp"

#ifndef STACK_HPP_
#define STACK_HPP_
using namespace node;
namespace stk
{
	template<class T>
		class stack
		{
			private:
				list<T> li;
			public:
				/*
				 * Constructs a new stack.
				 */
				stack();
				/*
				 * Pushes t to on the top of the stack.
				 */
				void push(const T& t);
				/*
				 * Returns the element at the top of the stack.
				 * Also removes the top element from the stack.
				 */
				T pop();
				/*
				 * Returns the element at the top of the stack.
				 * Does not remove the top element.
				 */
				T top();
				/*
				 * Returns the number of elements currently in the stack.
				 */
				int size();
				/*
				 * Returns a boolean indicating whether the stack is empty or not.
				 */
				inline bool empty();
				/*
				 * Destructor
				 * Fress the memory occupied by the stack elements.
				 */
				~stack();
		};

	template<class T>
		stack<T>::stack()
		{
			
		}

	template<class T>
		void stack<T>::push(const T& t)
		{
			li.cons(t);
		}

	template<class T>
		T stack<T>::pop()
		{
			T top = li.top();
			li.remove(top);
			return top;
		}
	
	template<class T>
		T stack<T>::top()
		{
			return li.top();
		}

	template<class T>
		int stack<T>::size()
		{
			return li.length();
		}

	template<class T>
		inline bool stack<T>::empty()
		{
			return li.length()==0;
		}
	template<class T>
		stack<T>::~stack()
		{

		}
}

#endif
