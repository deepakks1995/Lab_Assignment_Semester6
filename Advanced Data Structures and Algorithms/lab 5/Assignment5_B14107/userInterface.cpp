#include <iostream>
#include "AVL.hpp"
//#include "BSTree.hpp"
using namespace abc;
using namespace std;

int main()
{
	try{

		int t;
		int temp;
		AVL<int, int> dict;
		temp = 1;
		bool check =0;
		while(check!=1)
		{
			cout<<"\t\t1. Insert a key\n\t\t2. Search for a key\n\t\t3. Delete a key\n\t\t4. Display all the keys as obserbed in inorder traversal\n\t\t5. Display all the keys as obserbed in preorder traversal\n\t\t6. Display all the keys as obserbed in postorder traversal\n\t\t7. Display all the keys as obserbed in levelorder traversal\n\t\t8. Display the minimum key in a tree\n\t\t9. Display the maximum key in a tree\n\t\t10. Display the succesor of a key\n\t\t11. Display the predecessor of a key\n\t\t12. Display the height of a tree\n\t\t13. Exit\n";
			cin>>t;
			switch(t)
			{
				case 1: 
					{
						cout<<"Enter Key and Value respectively\n";
						int key ,value;
						cin>>key>>value;
						dict.put(key, value);
						cout<<endl;
						break;
					}
				case 2:
					{
						cout<<"Enter Key to search\n";
						int key;
						cin>>key;
						if(!dict.has(key))
							cout<<"Key not found\n";
						else
							cout<<"Value: "<<dict.get(key);
						cout<<endl;
						break;
					}
				case 3:
					{
						cout<<"Enter Key to be deleted\n";
						int key;
						cin>>key;
						if(!dict.has(key))
							cout<<"Key not found\n";
						else
						{
							dict.remove(key);
							cout<<"Key deleted successfully........\n";
						}
						cout<<endl;
						break;
					}
				case 4:
					{
						cout<<"Inorder Traversal\n";
						dict.print_in_order();
						cout<<endl;
						break;
					}
				case 5: 
					{
						cout<<"Preorder Traversal\n";
						dict.print_pre_order();
						cout<<endl;
						break;
					}
				case 6:
					{
						cout<<"PostOrder Traversal\n";
						dict.print_post_order();
						cout<<endl;
						break;
					}
				case 7:
					{
						cout<<"Levelorder Traversal\n";
						dict.print_level_order();
						cout<<endl;
						break;
					}
				case 8:
					{
						cout<<"Minimum Key: "<<dict.minimum()<<endl;
						cout<<endl;
						break;
					}
				case 9:
					{
						cout<<"Maximum Key: "<<dict.maximum()<<endl;
						cout<<endl;
						break;
					}
				case 10:
					{
						cout<<"Enter Key to find the successor\n";
						int key;
						cin>>key;
						if(!dict.has(key))
							cout<<"Key not found\n";
						else
							cout<<"Successor: "<<dict.successor(key);
						cout<<endl;
						break;
					}
				case 11:
					{
						cout<<"Enter Key to find the predecessor\n";
						int key;
						cin>>key;
						if(!dict.has(key))
							cout<<"Key not found\n";
						else
							cout<<"Predecessor: "<<dict.predecessor(key);
						cout<<endl;
						break;
					}
				case 12:
					{
						cout<<"Height of Tree: "<<dict.getHeight();
						cout<<endl;
						break;
					}
				case 13:
					{
						cout<<"Exiting...........\n";
						check=1;
						cout<<endl;
						break;
					}
				default :
					{
						cout<<"Invalid option\n";
						cout<<endl;
						break;
					}
			}
		}
	}
	catch(const char* c)
	{
		cout<<c<<endl;
	}
}
