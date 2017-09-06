#include <iostream>
#include "AVL.hpp"
//#include "BSTree.hpp"
using namespace abc;
using namespace std;
template <class Key, class Value>
void solve(Dictionary<Key, Value> *dict, int temp);
int main()
{
	int t;
	cout<<"\t\tSelect Key Value Types: \n\n\t\t1.Integer, Integer\n\t\t2.String, String\n\t\t3.Integer, String\n\t\t4.String, Integer\n";
	cin>>t;
	int temp;
	if(t==1)
	{	Dictionary<int, int> *dict = new AVL<int, int>;
		temp = 1;
		solve(dict,temp);
	}
	else if(t==2)
	{
		Dictionary<string, string> *dict = new AVL<string, string>;
		temp = 2;
		solve(dict,temp);
	}
	else if(t==3)
	{
		Dictionary<int, string> *dict = new AVL<int, string>;
		temp = 3;
		solve(dict,temp);
	}
	else if(t==4)
	{
		Dictionary<string, int> *dict = new AVL<string, int>;
		temp = 4;
		solve(dict,temp);
	}
	else
		cout<<"Invalid input\n";
}

template<class Key, class Value>
void solve(Dictionary<Key, Value> *dict, int temp)
{
	int t;
	bool check =0;
	while(check!=1)
	{
		cout<<"1. Insert a key\n2. Search for a key\n3. Delete a key\n4. Display all the keys as obserbed in inorder traversal\n5. Display all the keys as obserbed in preorder traversal\n6. Display all the keys as obserbed in postorder traversal\n7. Display all the keys as obserbed in levelorder traversal\n8. Display the minimum key in a tree\n9. Display the maximum key in a tree\n10. Display the succesor of a key\n11. Display the predecessor of a key\n12. Display the height of a tree\n13. Exit\n";
		cin>>t;
		switch(t)
		{
			case 1: 
				{
					cout<<"Enter Key and Value respectively\n";
					if(temp==1)
					{
						int key ,value;
						cin>>key>>value;
						dict->put(key, value);
					}
					else if(temp==2)
					{
						string value,key;
						cin>>key;
						cin>>value;
						dict->put(key,value);
					}
					else if(temp == 3)
					{
						int key;
						string value;
						cin>>key>>value;
						dict->put(key, value);
					}
					else
					{
						int value;
						string key;
						cin>>key>>value;
						dict->put(key, value);
					}
					break;
				}
			case 2:
				{
					cout<<"Enter Key to search\n";
					if(temp==1 || temp==3)
					{
						int key;
							cin>>key;
							if(!dict->has(key))
								cout<<"Key not found\n";
							else
								cout<<"Value: "<<dict->get(key);
					}
					else
					{
						string key;
						cin>>key;
						if(!dict->has(key))
							cout<<"Key not found\n";
						else 
							cout<<"Value: "<<dict->get(key);
					}
					break;
				}
			case 3:
				{
					cout<<"Enter Key to be deleted\n";
					if(temp==1 || temp==3)
					{
						int key;
							cin>>key;
							if(!dict->has(key))
								cout<<"Key not found\n";
							else
							{
								dict->remove(key);
								cout<<"Key deleted successfully........\n";
							}
					}
					else
					{
						string key;
						cin>>key;
						if(!dict->has(key))
							cout<<"Key not found\n";
						else 
						{
							dict->remove(key);
							cout<<"Key deleted successfully..........\n";
						}
					}
					break;
				}
			case 4:
				{
					cout<<"Inorder Traversal\n";
					dict->print_in_order();
					break;
				}
			case 5: 
				{
					cout<<"Preorder Traversal\n";
					dict->print_pre_order();
					break;
				}
			case 6:
				{
					cout<<"PostOrder Traversal\n";
					dict->print_post_order();
					break;
				}
			case 7:
				{
					cout<<"Levelorder Traversal\n";
					//dict->print_level_order();
					break;
				}
			case 8:
				{
					cout<<"Minimum Key: "<<dict->minimum()<<endl;
					break;
				}
			case 9:
				{
					cout<<"Maximum Key: "<<dict->maximum()<<endl;
					break;
				}
			case 10:
				{
					cout<<"Enter Key to find the successor\n";
					if(temp==1 || temp==3)
					{
						int key;
							cin>>key;
							if(!dict->has(key))
								cout<<"Key not found\n";
							else
								cout<<"Successor: "<<dict->successor(key);
					}
					else
					{
						string key;
						cin>>key;
						if(!dict->has(key))
							cout<<"Key not found\n";
						else 
							cout<<"Successor: "<<dict->successor(key);
					}
					break;
				}
			case 11:
				{
					cout<<"Enter Key to find the predecessor\n";
					if(temp==1 || temp==3)
					{
						int key;
							cin>>key;
							if(!dict->has(key))
								cout<<"Key not found\n";
							else
								cout<<"Predecessor: "<<dict->predecessor(key);
					}
					else
					{
						string key;
						cin>>key;
						if(!dict->has(key))
							cout<<"Key not found\n";
						else 
							cout<<"Predecessor: "<<dict->predecessor(key);
					}
					break;
				}
			case 12:
				{
					cout<<"Height of Tree: "<<dict->getHeight();
					break;
				}
			case 13:
				{
					cout<<"Exiting...........\n";
					check=1;
					break;
				}
			default :
				{
					cout<<"Invalid option\n";
					break;
				}
		}
	}
}
