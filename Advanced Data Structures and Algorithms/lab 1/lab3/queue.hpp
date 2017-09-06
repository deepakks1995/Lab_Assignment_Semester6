/*
 * queue.hpp
 *
 */

#ifndef QUEUE_HPP_
#define QUEUE_HPP_


namespace /*Your namespace here*/
{
  template <class T>
    class queue
    {
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
    };
}
#endif