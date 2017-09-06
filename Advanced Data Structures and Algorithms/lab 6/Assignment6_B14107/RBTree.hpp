#ifndef RBTree_HPP_
#define RBTree_HPP_ 1
#include "BSTree.hpp"
#include "queue.hpp"
#include "Color.hpp"
using namespace abc;
namespace abc
{

	template <class Key, class Value>
		void PRINT(Key key, Value value, Color color, int height);

	template <class Key, class Value>
		class RBTree : public BSTree<Key, Value> 
	{
		public:
			int blackHeighttree();
			void print_in_order();
			void print_pre_order();
			void print_post_order();
			void print_level_order();
			void in_order(void (*fun)(const Key& key, const Value& value, Color color, int height));
			void pre_order(void (*fun)(const Key& key, const Value& value, Color color, int height));
			void post_order(void (*fun)(const Key& key, const Value& value, Color color, int height));
			void level_order(void (*fun)(const Key& key, const Value& value, Color color, int height));
			void minimum_key();
			void maximum_key();
			void successor_key(const Key& key);
			void predecessor_key(const Key& key);
			void put(const Key& key, const Value& value);
			void remove(const Key& key);
		protected:
			void IN_ORDER(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value, Color color, int height));
			void PRE_ORDER(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value, Color color, int height));
			void POST_ORDER(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value, Color color, int height));
			int blackHeight(Node<Key, Value> *node);
			int assign_height(Node<Key, Value> *node);
			void RBTransplant(Node<Key,Value> *u,Node<Key,Value> *v);
			void rightRotate(Node<Key, Value> *node);
			void leftRotate(Node<Key, Value> *node);
			void insertRBFixup(Node<Key, Value> *node);
			void deleteRBFixup(Node<Key, Value> *x, Node<Key, Value> *v);
			using BSTree<Key, Value>::root;
			using BSTree<Key, Value>::_size;
	};

	template <class Key, class Value>
		int RBTree<Key, Value>::blackHeighttree()
		{
			return root->height;
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::print_in_order()
		{
			in_order(PRINT);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::print_pre_order()
		{
			pre_order(PRINT);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::print_post_order()
		{
			post_order(PRINT);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::print_level_order()
		{
			level_order(PRINT);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::in_order(void (*fun)(const Key& key, const Value& value, Color color, int height))
		{
			if(root == NULL)
				throw ("Tree is empty\n");
			IN_ORDER(root,fun);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::IN_ORDER(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value, Color color, int height))
		{
			if(node == NULL)
				return;
			IN_ORDER(node->left,fun);
			fun(node->key, node->value,((RBTree_Node<Key, Value> *)node)->color,node->height);
			IN_ORDER(node->right, fun);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::pre_order(void (*fun)(const Key& key, const Value& value, Color color, int height))
		{
			if(root == NULL)
				throw ("Tree is empty\n");
			PRE_ORDER(root, fun);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::PRE_ORDER(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value, Color color, int height))
		{
			if(node == NULL)
				return ;
			fun(node->key, node->value,((RBTree_Node<Key, Value> *)node)->color,node->height);
			PRE_ORDER(node->left, fun);
			PRE_ORDER(node->right, fun);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::post_order(void (*fun)(const Key& key, const Value& value, Color color, int height))
		{
			if(root == NULL)
				throw ("Tree is empty\n");
			POST_ORDER(root, fun);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::POST_ORDER(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value, Color color, int height))
		{
			if( node == NULL)
				return ;
			POST_ORDER(node->left , fun);
			POST_ORDER(node->right, fun);
			fun(node->key, node->value,((RBTree_Node<Key, Value> *)node)->color,node->height);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::level_order(void (*fun)(const Key& key, const Value& value, Color color, int height))
		{
			queue<RBTree_Node<Key, Value> *> que;
			RBTree_Node<Key, Value> *node = NULL;
			if(root == NULL)
				return ;
			que.push(((RBTree_Node<Key, Value> *) this->root));
			while(!que.empty())
			{
				node = que.pop();
				fun(((Node<Key, Value> *) node)->key, ((Node<Key, Value> *) node)->value, node->color,((Node<Key, Value> *) node)->height);
				if( node->left!=NULL)
					que.push(((RBTree_Node<Key, Value> *) node->left));
				if(node->right!=NULL)
					que.push(((RBTree_Node<Key, Value> *) node->right));
			}
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::minimum_key()
		{
			try{
				Key k = this->minimum();
				Node<Key, Value> *node = &(this->get_Node(k));
				std::cout<<"Minimum Key: "<<k<<" Color: "<<(((RBTree_Node<Key, Value>*)node)->color==0 ? "RED" : "BLACK")<<" BlackHeight: "<<node->height<<std::endl;
			}
			catch(const char* c)
			{
				throw c;
			}
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::maximum_key()
		{
			try{
				Key k = this->maximum();
				Node<Key, Value> *node = &(this->get_Node(k));
				std::cout<<"Maximum Key: "<<k<<" Color: "<<(((RBTree_Node<Key, Value>*)node)->color==0 ? "RED" : "BLACK")<<" BlackHeight: "<<node->height<<std::endl;
			}
			catch(const char* c)
			{
				throw c;
			}
		}	

	template <class Key, class Value>
		void RBTree<Key, Value>::successor_key(const Key& key)
		{
			try{
				Key k = this->successor(key);
				Node<Key, Value> *node = &(this->get_Node(k));
				std::cout<<"Successor: "<<k<<" Color: "<<(((RBTree_Node<Key, Value>*)node)->color==0 ? "RED" : "BLACK")<<" BlackHeight: "<<node->height<<std::endl;
			}
			catch(const char* c)
			{
				throw c;
			}
		}		

	template <class Key, class Value>
		void RBTree<Key, Value>::predecessor_key(const Key& key)
		{
			try{
				Key k = this->predecessor(key);
				Node<Key, Value> *node = &(this->get_Node(k));
				std::cout<<"Predecessor: "<<k<<" Color: "<<(((RBTree_Node<Key, Value>*)node)->color==0 ? "RED" : "BLACK")<<" BlackHeight: "<<node->height<<std::endl;
			}
			catch(const char* c)
			{
				throw c;
			}
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::put(const Key& key, const Value& value)
		{
			if(this->root == NULL)
			{
				this->root = new RBTree_Node<Key, Value>();
				this->root->key = key;
				this->root->value = value;
				((RBTree_Node<Key, Value> *) this->root)->color = BLACK;
				this->_size++;
			}
			else
			{
				Node<Key, Value> *node = new RBTree_Node<Key, Value>();
				node->key = key;
				node->value = value;
				((RBTree_Node<Key, Value>*) node)->color = RED;
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
				Node<Key, Value> *itr=this->root;
				for(;;)
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
							this->_size++;
							insertRBFixup(node);
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
							insertRBFixup(node);
							break;
						}
						else
							itr = itr->left;
					}
				}
			}
			assign_height(root);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::insertRBFixup(Node<Key, Value> *node)
		{
			Node<Key, Value> *grand_parent = NULL;
			Node<Key, Value> *parent = NULL;
			while(node!=root && ((RBTree_Node<Key, Value> *)node)->color!=BLACK && ((RBTree_Node<Key, Value> *)node->parent)->color == RED)
			{
				if(node->parent!=NULL)
				{
					parent = node->parent;
					if(parent->parent!=NULL)
						grand_parent = parent->parent;
				}
				//CASE 1;
				if(grand_parent->left == parent && ((RBTree_Node<Key, Value> *)parent)->color==RED && (grand_parent->right!=NULL && ((RBTree_Node<Key, Value> *)grand_parent->right)->color==RED))
				{
					((RBTree_Node<Key, Value> *)parent)->color=BLACK;
					((RBTree_Node<Key, Value> *)grand_parent->right)->color=BLACK;
					((RBTree_Node<Key, Value> *)grand_parent)->color = RED;
					node = grand_parent;
				}
				// Case 4:
				else if(grand_parent->right == parent && ((RBTree_Node<Key, Value> *)parent)->color==RED && (grand_parent->left!=NULL && ((RBTree_Node<Key, Value> *)grand_parent->left)->color== RED))
				{
					((RBTree_Node<Key, Value> *)parent)->color= BLACK;
					((RBTree_Node<Key, Value> *)grand_parent->left)->color = BLACK;
					((RBTree_Node<Key, Value> *)grand_parent)->color = RED;
					node = grand_parent;
				}
				// Case 2:
				else if(parent->right==node && grand_parent->left == parent && ((RBTree_Node<Key, Value> *)parent)->color==RED && (grand_parent->right==NULL || ((RBTree_Node<Key, Value> *)grand_parent->right)->color==BLACK))
				{
					leftRotate(parent);
					node = parent;
					parent = node->parent;
				}
				// Case 3:
				else if(parent->left == node && grand_parent->left == parent && ((RBTree_Node<Key, Value> *)parent)->color==RED && (grand_parent->right==NULL || ((RBTree_Node<Key, Value> *)grand_parent->right)->color==BLACK))
				{
					rightRotate(grand_parent);
					((RBTree_Node<Key, Value> *)parent)->color = BLACK;
					((RBTree_Node<Key, Value> *)parent->left)->color = RED;
					((RBTree_Node<Key, Value> *)parent->right)->color = RED;
					node = parent;
				}
				// Case 5:
				else if(parent->left == node && grand_parent->right==parent && ((RBTree_Node<Key, Value> *)parent)->color==RED && (grand_parent->left==NULL || ((RBTree_Node<Key, Value> *)grand_parent->left)->color == BLACK))
				{
					rightRotate(parent);
					node = parent;
					parent = node->parent;
				}
				// Case 6:
				else if(parent->right == node && grand_parent->right==parent && ((RBTree_Node<Key, Value> *)parent)->color==RED && (grand_parent->left==NULL || ((RBTree_Node<Key, Value> *)grand_parent->left)->color==BLACK))
				{
					leftRotate(grand_parent);
					((RBTree_Node<Key, Value> *)parent)->color = BLACK;
					((RBTree_Node<Key, Value> *)parent->left)->color = RED;
					((RBTree_Node<Key, Value> *)parent->right)->color = RED;
					node = parent;
				}
				((RBTree_Node<Key, Value> *)root)->color = BLACK;
			}
		}

	template<class Key, class Value>
		void RBTree<Key, Value>::remove(const Key& key)
		{
			Node<Key,Value> *z = &(this->get_Node(key));
			if(z != NULL)
			{
				Node<Key,Value> *y = z;
				Node<Key,Value> *x = NULL;
				Node<Key,Value> *p = NULL;
				Color origColor = ((RBTree_Node<Key, Value> *)y)->color;
				if(z->left == NULL)
				{
					x = z->right;
					RBTransplant(z,x);
					p = z->parent;
				}
				else if(z->right == NULL)
				{
					x = z->left;
					RBTransplant(z,x);
					p = z->parent;
				}
				else
				{
					y = &(this->get_Node(this->successor(key)));
					origColor = ((RBTree_Node<Key, Value> *)y)->color;
					x = y->right;
					p = y;
					if(y->parent == z)
					{
						if(x != NULL)
						{
							x->parent = y;
						}
						p = y;
					}
					else
					{
						RBTransplant(y,y->right);
						p = y->parent;
						y->right = z->right;
						y->right->parent = y;
					}
					RBTransplant(z,y);
					y->left = z->left;
					y->left->parent = y;
					((RBTree_Node<Key, Value> *)y)->color = ((RBTree_Node<Key, Value> *)z)->color;
				}
				if(origColor == BLACK)
					deleteRBFixup(x,p);
				cout<<"Key with color "<<(origColor == 0 ? "RED" : "BLACK")<<" deleted successfully........\n";
				delete z;
			}
			assign_height(root);
			_size--;
		}


	template<class Key,class Value>
		void RBTree<Key,Value>::deleteRBFixup(Node<Key,Value>* x,Node<Key,Value>* p)
		{
			while(x!=root && ((x!=NULL)?(((RBTree_Node<Key, Value> *)x)->color == BLACK):(1)) && p != NULL)
			{
				if(x == p->left)
				{
					Node<Key,Value>* w = p->right;
					if((w != NULL)?(((RBTree_Node<Key, Value> *)w)->color == RED):(0))
					{
						((RBTree_Node<Key, Value> *)w)->color = BLACK;
						((RBTree_Node<Key, Value> *)p)->color = RED;
						leftRotate(p);
						w = p->right;
					}
					if(((w->left != NULL)?(((RBTree_Node<Key, Value> *)(w->left))->color == BLACK):(1)) && ((w->right != NULL)?(((RBTree_Node<Key, Value> *)(w->right))->color == BLACK):(1)))
					{
						((RBTree_Node<Key, Value> *)w)->color = RED;
						x = p;
						p = p->parent;
					}
					else
					{
						if(((w->left != NULL)?(((RBTree_Node<Key, Value> *)(w->left))->color == BLACK):(1)) || ((w->right != NULL)?(((RBTree_Node<Key, Value> *)(w->right))->color == BLACK):(1)))
						{
							((RBTree_Node<Key, Value> *)w)->color = RED;
							rightRotate(w);
							w = p->right;
						}
						((RBTree_Node<Key, Value> *)w)->color = ((RBTree_Node<Key, Value> *)p)->color;
						((RBTree_Node<Key, Value> *)p)->color = BLACK;
						((RBTree_Node<Key, Value> *)(w->right))->color = BLACK;
						leftRotate(p);
						x = root;
						p = NULL;
					}
				}
				else
				{
					Node<Key,Value>* w = p->left;
					if((w != NULL)?(((RBTree_Node<Key, Value> *)w)->color == RED):(0))
					{
						((RBTree_Node<Key, Value> *)w)->color = BLACK;
						((RBTree_Node<Key, Value> *)p)->color = RED;
						rightRotate(p);
						w = p->left;
					}
					if(((w->left != NULL)?(((RBTree_Node<Key, Value> *)(w->left))->color == BLACK):(1)) && ((w->right != NULL)?(((RBTree_Node<Key, Value> *)(w->right))->color == BLACK):(1)))
					{
						((RBTree_Node<Key, Value> *)w)->color = RED;
						x = p;
						p = p->parent;
					}
					else
					{
						if(((w->left != NULL)?(((RBTree_Node<Key, Value> *)(w->left))->color == BLACK):(1)) && ((w->right != NULL)?(((RBTree_Node<Key, Value> *)(w->right))->color == BLACK):(1)))
						{
							((RBTree_Node<Key, Value> *)w)->color = RED;
							leftRotate(w);
							w = p->right;
						}
						((RBTree_Node<Key, Value> *)w)->color = ((RBTree_Node<Key, Value> *)p)->color;
						((RBTree_Node<Key, Value> *)p)->color = BLACK;
						((RBTree_Node<Key, Value> *)(w->left))->color = BLACK;
						rightRotate(p);
						x = root;
						p = NULL;
					}
				}
			}
			if(x != NULL)
				((RBTree_Node<Key, Value> *)x)->color = BLACK;
			assign_height(root);
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::rightRotate(Node<Key, Value> *node)
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
		}

	template <class Key, class Value>
		void RBTree<Key, Value>::leftRotate(Node<Key, Value> *node)
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
		}

	template <class Key, class Value>
		int RBTree<Key, Value>::blackHeight(Node<Key, Value> *node)
		{
			return node->height;
		}

	template <class Key, class Value>
		int RBTree<Key, Value>::assign_height(Node<Key, Value> *node)
		{
			if(node==NULL)
				return 1;
			node->height = max(assign_height(node->left),assign_height(node->right));
			if(((RBTree_Node<Key,Value> *) node)->color==RED)
				return node->height;
			else
				return node->height + 1;
		}

	template<class Key,class Value>
		void RBTree<Key,Value>::RBTransplant(Node<Key,Value> *u,Node<Key,Value> *v)
		{
			if(u->parent == NULL)
				root = v;
			else if(u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			if(v!=NULL)
				v->parent = u->parent;
		}

	template <class Key, class Value>
		void PRINT(Key key, Value value, Color color, int height)
		{
			std::cout<<"Key: "<<key<<"  Value: "<<value<<"  Color: ";
			if(color==0)
				cout<<"RED";
			else
				cout<<"BLACK";
			cout<<"   BlackHeight: "<<height<<std::endl;
		}

}
#endif /* ifndef RBTree_HPP_ */
