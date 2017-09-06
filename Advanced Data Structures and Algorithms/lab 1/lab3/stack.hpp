/*
 * stack.hpp
 *
 */

#ifndef STACK_HPP_
#define STACK_HPP_
namespace /*Your namespace here*/
{
  template<class T>
    class stack
    {
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
}

#endif