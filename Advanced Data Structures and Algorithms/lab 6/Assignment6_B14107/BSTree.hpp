#ifndef BSTREE_HPP
#define BSTREE_HPiP 1
#include "Dictionary.hpp"
#include "Node.hpp"
#include "queue.hpp"
#include<cstring>
#include <iostream>
using namespace abc;
using namespace std;
namespace abc
{
	template <class Key, class Value>
		void PRINT(const Key& key, const Value& value);

	template <class Key, class  Value>
		class BSTree : public Dictionary<Key, Value> {
			public:
				BSTree();

				~BSTree(){};

				int getHeight();

				int size();

				void print();

				void in_order(void (*fun)(const Key& key, const Value& value));

				void pre_order(void (*fun)(const Key& key, const Value& value));

				void post_order(void (*fun)(const Key& key, const Value& value));

				void level_order(void(*fun)(const Key& key, const Value& value));

				void print_in_order();

				void print_pre_order();

				void print_post_order();

				void print_level_order();

				Key minimum();

				Key maximum();

				Key successor(const Key& key);

				Key predecessor(const Key& key);

				void put(const Key& key, const Value& value);

				bool has(const Key& key);

				Value get(const Key& key);

				void remove(const Key& key);

			protected:
				Node<Key, Value>& get_Node(const Key& key);

				int compare(const Key& key1, const Key& key2);

				int compare(char* key1, char* key2);

				int recurr_height(Node<Key, Value> *node);

				int assign_height(Node<Key, Value> *node);

				void IN_ORDER(Node<Key, Value> *node , void (*fun)(const Key& key, const Value& value));

				void PRE_ORDER(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value));

				void POST_ORDER(Node<Key, Value>*node , void (*fun)(const Key& key, const Value& value));

			private:
				template <class K, class V> friend class RBTree;
				Node<Key, Value> *root;
				int _size;
		};

	template <class Key, class Value>
		BSTree<Key, Value>::BSTree()
		{
			root = NULL;
			_size = 0;
		}

	template<class Key, class Value>
		int BSTree<Key, Value>::getHeight()
		{
			return recurr_height(root);
		}

	template<class Key, class Value>
		int BSTree<Key, Value>::recurr_height(Node<Key, Value> *node)
		{
			if(node==NULL)
				return -1;
			return 1 + max(recurr_height(node->left), recurr_height(node->right));
		}

	template <class Key, class Value>
		int BSTree<Key, Value>::assign_height(Node<Key, Value> *node)
		{
			if(node==NULL)
				return -1;
			node->height = 1 + max(assign_height(node->left) , assign_height(node->right));
			return node->height;
		}

	template <class Key, class Value>
		int BSTree<Key, Value>::size()
		{
			return _size;
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::print()
		{
			print_in_order();
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::print_in_order()
		{
			in_order(PRINT);
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::print_pre_order()
		{
			pre_order(PRINT);
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::print_post_order()
		{
			post_order(PRINT);
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::print_level_order()
		{
			level_order(PRINT);
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::in_order(void (*fun)(const Key& key, const Value& value))
		{
			if(root == NULL)
				throw ("Tree is empty\n");
			IN_ORDER(root,fun);
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::IN_ORDER(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value))
		{
			if(node == NULL)
				return;
			IN_ORDER(node->left,fun);
			fun(node->key, node->value);
			IN_ORDER(node->right, fun);
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::pre_order(void (*fun)(const Key& key, const Value& value))
		{
			if(root == NULL)
				throw ("Tree is empty\n");
			PRE_ORDER(root, fun);
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::PRE_ORDER(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value))
		{
			if(node == NULL)
				return ;
			fun(node->key, node->value);
			PRE_ORDER(node->left, fun);
			PRE_ORDER(node->right, fun);
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::post_order(void (*fun)(const Key& key, const Value& value))
		{
			if(root == NULL)
				throw ("Tree is empty\n");
			POST_ORDER(root, fun);
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::POST_ORDER(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value))
		{
			if( node == NULL)
				return ;
			POST_ORDER(node->left , fun);
			POST_ORDER(node->right, fun);
			fun(node->key, node->value);
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::level_order(void(*fun)(const Key& key, const Value& value))
		{
			queue<Node<Key, Value>* > que;
			Node<Key, Value> *node;
			if(root==NULL)
				return;
			que.push(root);
			while(!que.empty())
			{
				node = que.pop();
				fun(node->key, node->value);
				if(node->left!=NULL)
					que.push((node->left));
				if(node->right!=NULL)
					que.push((node->right));
			}
		}

	template<class Key, class Value>
		Key BSTree<Key, Value>::minimum()
		{
			Node<Key, Value> *itr = root;
			Key min = root->key;
			while(itr!=NULL)
			{
				min = min >= itr->key ? itr->key: min;
				itr = itr->left;
			}
			return min;
		}

	template<class Key, class Value>
		Key BSTree<Key, Value>::maximum()
		{
			Node<Key, Value> *itr = root;
			Key max = root->key;
			while(itr!=NULL)
			{
				max = max >= itr->key ? max : itr->key;
				itr = itr->right;
			}
			return max;
		}


	template<class Key, class Value>
		Key BSTree<Key, Value>::successor(const Key& key)
		{
			if(key == maximum() )
				throw "No Successor is present\n";
			Node<Key, Value> *itr = &get_Node(key);
			if(itr->right!=NULL)
			{
				itr = itr->right;
				Key min = itr->key;
				while(itr!=NULL)
				{
					min = min >= itr->key ? itr->key : min;
					itr = itr->left;
				}
				return min;
			}
			else
			{
				Node<Key, Value> *ancestor=itr->parent;
				while(ancestor->right==itr && ancestor!=NULL)
				{
					itr = ancestor;
					ancestor = ancestor->parent;
				}
				return ancestor->key;
			}
		}

	template<class Key, class Value>
		Key BSTree<Key, Value>::predecessor(const Key& key)
		{
			if(key == minimum() )
				throw ("No Predessor exists \n");
			Node<Key, Value> *itr = &get_Node(key);
			if(itr->left!=NULL)
			{
				itr = itr->left;
				Key max = itr->key;
				while(itr!=NULL)
				{
					max = max >= itr->key ? max : itr->key;
					itr = itr->right;
				}
				return max;
			}
			else
			{
				Node<Key, Value> *ancestor = itr->parent;
				while(ancestor->left == itr && ancestor!=NULL)
				{
					itr = ancestor;
					ancestor = ancestor->parent;
				}
				return ancestor->key;
			}
		}

	template <class Key, class Value>
		void BSTree<Key, Value>::put(const Key& key, const Value& value)
		{
			if(this->root == NULL)
			{
				this->root = new Node<Key, Value>();
				this->root->key = key;
				this->root->value = value;
				this->_size++;
			}
			else
			{
				Node<Key, Value> *node = new Node<Key, Value>();
				node->key = key;
				node->value = value;
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
				Node<Key, Value> *itr=this->root;
				for(;;)
				{
					if(compare(key, itr->key)==0)
					{
						itr->value = value;
						break;
					}

					else if(compare(key, itr->key)==1)
					{
						if(itr->right==NULL)
						{
							itr->right = node;
							node->parent = itr;
							this->_size++;
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
							this->_size++;
							break;
						}
						else
							itr = itr->left;
					}
				}
			}
		}

	template<class Key, class Value>
		bool BSTree<Key, Value>::has(const Key& key)
		{
			Node<Key, Value> *itr = root;
			while(true)
			{
				if(itr == NULL)
					return false;
				if(compare(key, itr->key)==0)
					return true;
				else if(compare(key, itr->key)==1)
					itr = itr->right;
				else
					itr = itr->left;
			}
		}

	template<class Key, class Value>
		Value BSTree<Key, Value>::get(const Key& key)
		{
			return get_Node(key).value;
		}

	template<class Key, class Value>
		void BSTree<Key, Value>::remove(const Key& key)
		{
			Node<Key, Value> *itr = &get_Node(key);
			if(itr->left==NULL && itr->right==NULL)
			{
				if(itr == root)
				{
					root = NULL;
					delete itr;
				}
				if(itr->parent->left==itr)
				{
					itr->parent->left=NULL;
					delete itr;
				}
				else if(itr->parent->right==itr)
				{
					itr->parent->right=NULL;
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
					}
					else
					{
						itr->parent->right=itr->right;
						itr->right->parent = itr->parent;
					}
				}
				else
				{
					if(itr->parent->left==itr)
					{
						itr->parent->left=itr->left;
						itr->left->parent = itr->parent;
					}
					else
					{
						itr->parent->right=itr->left;
						itr->left->parent = itr->parent;
					}
				}
				delete itr;
			}
			else
			{
				Node<Key,Value> *succ = &get_Node(successor(itr->key));
				itr->key = succ->key;
				itr->value = succ->value;
				if(succ->parent->left == succ)
					succ->parent->left = NULL;
				else
					succ->parent->right = NULL;
				delete succ;
			}
			_size--;
		}


	template <class Key, class Value>
		Node<Key, Value>& BSTree<Key, Value>::get_Node(const Key& key)
		{
			Node<Key, Value> *itr = this->root;
			while(itr!=NULL)
			{
				if(compare(key, itr->key)==0)
					return *itr;
				else if(compare(key, itr->key)==1)
					itr = itr->right;
				else
					itr = itr->left;
			}
			if(itr==NULL)
				throw ("Key is not present\n");
		}

	template<class Key, class Value>
		int BSTree<Key, Value>::compare(const Key& key1, const Key& key2)
		{
			return key1>key2 ? 1 : (key1==key2 ? 0 : -1);
		}

	template<class Key, class Value>
		int BSTree<Key, Value>::compare(char* key1, char* key2)
		{
			return strcmp(key1,key2);
		}
	
	template<class Key,class Value>
		void PRINT(const Key& key,const Value& value)
		{
			std::cout<<"Key "<<key<<"\tValue "<<value<<"\n";
		}
	
}
#endif /* ifndef BSTREE_HPP */
