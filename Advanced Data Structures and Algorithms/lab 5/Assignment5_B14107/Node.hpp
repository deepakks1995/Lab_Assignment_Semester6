
namespace abc
{
	template <class Key, class Value>
		class Node
		{
			template <class K, class V> friend class BSTree;
			template <class k, class v> friend class AVL;
			private:		
				Key key;
				Value value;
				int height;
				Node<Key, Value>  *parent;
				Node<Key, Value>  *left;
				Node<Key, Value>  *right;
			Node()
			{
				height = -1;
				parent = NULL;
				left = NULL;
				right = NULL;
			}
		};
}
