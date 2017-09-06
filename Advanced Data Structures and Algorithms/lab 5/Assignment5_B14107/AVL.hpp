
#ifndef AVL_HPP
#define AVL_HPP 1
#include "BSTree.hpp"
#include <iostream>
using namespace abc;
namespace abc
{
	template <class Key, class Value>
		class AVL : public BSTree<Key, Value> {
			/*
			 * Inherit as much functionality as possible from the BSTree class.
			 * Then provide custom AVL Tree functionality on top of that.
			 * The AVL Tree should make use of as many BST functions as possible.
			 * Override only those methods which are extremely necessary.
			 */
			/*
			 * Apart from that, your code should have the following four functions:
			 * getBalance(node) -> To get the balance at any given node;
			 * doBalance(node) -> To fix the balance at the given node;
			 * rightRotate(node) -> Perform a right rotation about the given node.
			 * leftRotate(node) -> Perform a left rotation about the given node.
			 *
			 * The signature of these functions are not provided in order to provide you
			 * some flexibility in how you implement the internals of your AVL Tree. But
			 * make sure these functions are there.
			 */
			public:
			void rightRotate(Node<Key, Value> *node);
			void leftRotate(Node<Key, Value> *node);
			int getBalance(Node<Key, Value> *node);
			void doBalance(Node<Key, Value> *node);
			void put(const Key& key, const Value& value);
			void remove(const Key& key);
			void checkBalance(Node<Key, Value> *node);
			int getHeight();
			using BSTree<Key, Value>::root;
			using BSTree<Key, Value>::_size;
		};
	
	template <class Key, class Value>
		int AVL<Key, Value>::getHeight()
		{
			if (root == NULL)
				return -1;
			return root->height;
		}

	template <class Key, class Value>
		void AVL<Key, Value>::doBalance(Node<Key, Value> *node)
		{
			int BF = getBalance(node);
			if(BF == 2)
			{
				if(getBalance(node->left)==1 || getBalance(node->left)==0)
					rightRotate(node);
				else if(getBalance(node->left)==-1)
				{
					leftRotate(node->left);
					rightRotate(node);
				}
			}
			else if(BF == -2)
			{ 
				if(getBalance(node->right) == -1 || getBalance(node->right)==0 )
					leftRotate(node);
				else if( getBalance(node->right) == 1 )
				{
					rightRotate(node->right);
					leftRotate(node);
				}

			}
		}

	template <class Key, class Value>
		void AVL<Key, Value>::checkBalance(Node<Key, Value> *node)
		{
			while(node!=NULL)
			{
				int diff = getBalance(node);
				if( (-1>= diff || diff>=1) && node!=NULL)
				{
					doBalance(node);
					this->assign_height(root);
				}
				node = node->parent;
			}
		}

	template <class Key, class Value>
		void AVL<Key, Value>::put(const Key& key, const Value& value)
		{
			if(root == NULL)
			{
				root = new Node<Key, Value>();
				root->key = key;
				root->value = value;
				root->height = -1;
				_size++;
			}
			else
			{
				Node<Key, Value> *node = new Node<Key, Value>();
				node->key = key;
				node->value = value;
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
				Node<Key, Value> *itr=root;
				while(true)
				{
					if(this->compare(key, itr->key)==0)
					{
						itr->value = value;
						break;
					}

					else if(this->compare(key, itr->key)==1)
					{
						if(itr->right==NULL)
						{
							itr->right = node;
							node->parent = itr;
							_size++;
							checkBalance(node);
							break;
						}
						else
							itr = itr->right;
					}
					else
					{
						if(itr->left==NULL)
						{
							itr->left = node;
							node->parent = itr;
							_size++;
							checkBalance(node);
							break;
						}
						else
							itr = itr->left;
					}
				}
			}
			this->assign_height(root);
		}

	template<class Key, class Value>
		int AVL<Key, Value>::getBalance(Node<Key, Value> *node)
		{
			if(node->left==NULL && node->right==NULL)
				return 0;
			else if(node->left==NULL || node->right==NULL)
			{
				if(node->left==NULL)
					return -1 - node->right->height;
				else
					return node->left->height + 1;
			}
			else
				return (node->left->height - node->right->height);
		}

	template <class Key, class Value>
		void AVL<Key, Value>::rightRotate(Node<Key, Value> *node)
		{
			Node<Key, Value> *temp=NULL;
			if(node == root)
				root = node->left;
			else
			{
				if(node->parent->right==node)
					node->parent->right = node->left;
				else
					node->parent->left = node->left;
			}
			node->left->parent = node->parent;
			temp = node->left->right;
			node->parent = node->left;
			node->left->right = node;
			node->left = temp;
			if(temp!=NULL)
			node->left->parent = node;
			this->assign_height(root);
		}

	template <class Key, class Value>
		void AVL<Key, Value>::leftRotate(Node<Key, Value> *node)
		{
			if(node == root)
				root = node->right;
			else
			{	
				if(node->parent->left == node)
					node->parent->left = node->right;
				else
					node->parent->right = node->right;
			}
			Node<Key, Value> *temp=NULL;
			node->right->parent = node->parent;
			temp = node->right->left;
			node->parent = node->right;
			node->right->left = node;
			node->right = temp;
			if(temp!=NULL)
			node->right->parent = node;
			this->assign_height(root);
		}

	template<class Key, class Value>
		void AVL<Key, Value>::remove(const Key& key)
		{
			Node<Key, Value> *itr = &(this->get_Node(key));
			if(itr->left==NULL && itr->right==NULL)
			{
				if(itr == root)
				{	root = NULL;
					delete itr;
				}
				if(itr->parent->left==itr)
				{
					itr->parent->left=NULL;
					this->assign_height(root);					
					checkBalance(itr);
					delete itr;
				}
				else if(itr->parent->right==itr)
				{
					itr->parent->right=NULL;
					this->assign_height(root);
					checkBalance(itr);
					delete itr;
				}
			}
			else if(itr->left==NULL || itr->right==NULL)
			{
				if(itr->parent==NULL)
				{
					if(itr->left==NULL)
					{
						root = itr->right;
						root->parent = NULL;
					}
					else
					{
						root = itr->left;
						root->parent = NULL;
					}
				}
				else if(itr->left==NULL)
				{
					if(itr->parent->left==itr)
					{
						itr->parent->left=itr->right;
						itr->right->parent = itr->parent;
						this->assign_height(root);
						checkBalance(itr->right);
					}
					else
					{
						itr->parent->right=itr->right;
						itr->right->parent = itr->parent;
						this->assign_height(root);
						checkBalance(itr->right);
					}
				}
				else
				{
					if(itr->parent->left==itr)
					{
						itr->parent->left=itr->left;
						itr->left->parent = itr->parent;
						this->assign_height(root);
						checkBalance(itr->left);
					}
					else
					{
						itr->parent->right=itr->left;
						itr->left->parent = itr->parent;
						this->assign_height(root);
						checkBalance(itr->left);
					}
				}
				delete itr;
			}
			else
			{
				Node<Key,Value> *succ = &(this->get_Node(this->successor(itr->key)));
				itr->key = succ->key;
				itr->value = succ->value;
				if(succ->parent->right == succ)
					succ->parent->right = NULL;
				else
					succ->parent->left = NULL;
				this->assign_height(root);
				checkBalance(succ->parent);
				delete succ;
			}
			_size--;
		}
}

#endif /* ifndef AVL_HPP */

