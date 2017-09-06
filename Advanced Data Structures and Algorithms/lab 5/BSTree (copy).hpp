#ifndef BSTREE_HPP
#define BSTREE_HPP 1
#include "Dictionary.hpp"
#include "Node.hpp"
using namespace abc;

template <Key, Value>
class BSTree : public Dictionary<Key, Value> {
	public:
		/*
		 * This method returns the current height of the binary search tree.
		 */
		virtual int getHeight();
		/*
		 * This method returns the total number of elements in the binary search tree.
		 */
		virtual int size();
		/*
		 * This method prints the key value pairs of the binary search tree, sorted by
		 * their keys.
		 */
		virtual void print();
		/*
		 *This method takes as an argument a function func.
		 *Then it traverses along the tree in in-order traversal, and calls func
		 *with every key value pair in the BSTree.
		 */
		virtual void in_order(void (*fun)(const Key& key, const Value& value));
		/*
		 *This method takes as an argument a function func.
		 *Then it traverses along the tree in pre-order traversal, and calls func
		 *with every key value pair in the BSTree.
		 */
		virtual void pre_order(void (*fun)(const Key& key, const Value& value));
		/*
		 *This method takes as an argument a function func.
		 *Then it traverses along the tree in post-order traversal, and calls func
		 *with every key value pair in the BSTree.
		 */
		virtual void post_order(void (*fun)(const Key& key, const Value& value));

		/*
		 *This method print all the key value pairs of the binary search tree, as
		 *observed in an in order traversal.
		 */
		virtual void print_in_order();
		/*
		 *This method print all the key value pairs of the binary search tree, as
		 *observed in an pre order traversal.
		 */
		virtual void print_pre_order();
		/*
		 *This method print all the key value pairs of the binary search tree, as
		 *observed in a post order traversal.
		 */
		virtual void print_post_order();
		/*
		 *This method returns the minimum element in the BST.
		 */
		virtual Key minimun();
		/*
		 * This method returns the maximum element in the BST.
		 */
		virtual Key maximum();
		/*
		 *This method returns the successor, i.e, the next larget element in the
		 *BSTree, after Key.
		 */
		virtual Key successor(const Key& key);
		/*
		 * This method returns the predessor, ie, the next smallest element in the
		 * BSTree, after Key.
		 */
		virtual Key predecessor(const Key& key);
}

#endif /* ifndef BSTREE_HPP */
