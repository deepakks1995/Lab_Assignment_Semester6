
namespace abc
{
	enum Color { RED, BLACK };
	template <class Key, class Value>
	class RBTree_Node : public Node<Key, Value>
	{
		private:
			template<class k, class v> friend class RBTree;
			Color color;
		public:
			RBTree_Node()
			{
				color = RED;
			}
			RBTree_Node(Color c)
			{
				color = c;
			}
	};
}
