#include <iostream>
#include "RBTree.hpp"
//#include "BSTree.hpp"
using namespace abc;
using namespace std;

int main()
{
	try{

		int t;
		int temp;
		RBTree<int, int> dict;
		temp = 1;
		bool check =0;
		while(check!=1)
		{
			cout<<"\t\t\t  R E D   B L A C K   T R E E\n";
			cout<<"\t\t[1] Insert a key\n\t\t[2] Search for a key\n\t\t[3] Delete a key along withh color.\n\t\t[4] Display all the keys along with color and black height as obserbed in inorder traversal\n\t\t[5] Display all the keys along with color and black height as obserbed in preorder traversal\n\t\t[6] Display all the keys along with color and black height as obserbed in postorder traversal\n\t\t[7] Display all the keys along with color and black height as obserbed in levelorder traversal\n\t\t[8] Display the minimum key along with color and black height in a tree\n\t\t[9] Display the maximum key along with color and black height in a tree\n\t\t[10] Display the succesor of a key along with color and black height\n\t\t[11] Display the predecessor of a key along with color and black height\n\t\t[12] Display the height of a tree\n\t\t[13] Display the black height of a tree\n\t\t[14] EXIT\n";
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
												if(dict.size()==0)
						{
							cout<<"Tree is Empty\n";
							break;
						}
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
												if(dict.size()==0)
						{
							cout<<"Tree is Empty\n";
							break;
						}
						cout<<"Enter Key to be deleted\n";
						int key;
						cin>>key;
						if(!dict.has(key))
							cout<<"Key not found\n";
						else
							dict.remove(key);
						cout<<endl;
						break;
					}
				case 4:
					{
						if(dict.size()==0)
						{
							cout<<"Tree is Empty\n";
							break;
						}
						cout<<"Inorder Traversal\n";
						dict.print_in_order();
						cout<<endl;
						break;
					}
				case 5: 
					{
						if(dict.size()==0)
						{
							cout<<"Tree is Empty\n";
							break;
						}
						cout<<"Preorder Traversal\n";
						dict.print_pre_order();
						cout<<endl;
						break;
					}
				case 6:
					{
						if(dict.size()==0)
						{
							cout<<"Tree is Empty\n";
							break;
						}
						cout<<"PostOrder Traversal\n";
						dict.print_post_order();
						cout<<endl;
						break;
					}
				case 7:
					{
						if(dict.size()==0)
						{
							cout<<"Tree is Empty\n";
							break;
						}
						cout<<"Levelorder Traversal\n";
						dict.print_level_order();
						cout<<endl;
						break;
					}
				case 8:
					{
						if(dict.size()==0)
						{
							cout<<"Tree is Empty\n";
							break;
						}
						dict.minimum_key();
						cout<<endl;
						break;
					}
				case 9:
					{
						if(dict.size()==0)
						{
							cout<<"Tree is Empty\n";
							break;
						}
						dict.maximum_key();
						cout<<endl;
						break;
					}
				case 10:
					{
						if(dict.size()==0)
						{
							cout<<"Tree is Empty\n";
							break;
						}
						cout<<"Enter Key to find the successor\n";
						int key;
						cin>>key;
						if(!dict.has(key))
							cout<<"Key not found\n";
						else
							dict.successor_key(key);
						cout<<endl;
						break;
					}
				case 11:
					{
						if(dict.size()==0)
						{
							cout<<"Tree is Empty\n";
							break;
						}
						cout<<"Enter Key to find the predecessor\n";
						int key;
						cin>>key;
						if(!dict.has(key))
							cout<<"Key not found\n";
						else
							dict.predecessor_key(key);
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
						if(dict.size()==0)
						{
							cout<<"Tree is Empty\n";
							break;
						}
						cout<<"Black Height of Tree: "<<dict.blackHeighttree();
						cout<<endl;
						break;
					}
				case 14:
					{
						cout<<"Exiting............\n";
						check=1;
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
