#include<iostream>
#include<cstdio>
#include"vector.hpp"
#include"sorter.hpp"
#include"timer.hpp"
using std::cin;
using std::cout;
using namespace abc;
using namespace sort;
int main(int argc, char **argv)
{
	cout<<"1.Enter value from File\n"<<"2.Enter value from user\n";
	int t1;
	cin>>t1;
	vector<int> vec;
	timer t;
	sorter<int> s;
	FILE *p;
	int tmp;
	switch(t1)
	{
		case 1:
			{
				char *name= new char[150];
				cout<<"Enter the name of File: ";
				cin>>name;
				p = fopen(name,"r");
				while((fscanf(p,"%d\n",&tmp))!=EOF)
					vec.push_back(tmp);
				cout<<"Data Read Successfully......\nSize of vector: "<< vec.size()<<std::endl;
				break;
			}
		case 2:
			{
				int n;
				cout<<"Enter number of values\n";
				cin>>n;
				for(int i=0;i<n;i++)
				{
					cin>>tmp;
					vec.push_back(tmp);
				}
				break;
			}
		default:
			{
				cout<<"Invalid Input\nExiting...................";
				return 0;
			}
	}
	cout<<"1. Insertion Sort\n2. Merge Sort\n3. Rank Sort\n4. Selection Sort\n5. Quick Sort\n6. Bubble Sort\n7. Opt_Bubble Sort\n8. Opt_Rank Sort\n";
	cin>>t1;
	switch(t1)
	{
		case 1:
			{
			    cout<<"Insertion Sort.......\n";
				t.start();
				s.insertion_sort(vec,0,vec.size()-1);
				t.stop();
				t.print();
				break;
			}
		case 2:
			{
			    cout<<"Merge Sort.......\n";
				t.start();
				s.merge_sort(vec,0,vec.size()-1);
				t.stop();
				t.print();
				break;
			}
		case 3:
			{
			    cout<<"Rank Sort.......\n";
				t.start();
				s.rank_sort(vec,0,vec.size()-1);
				t.stop();
				t.print();
				break;
			}
		case 4:
			{
			    cout<<"Selection Sort.......\n";
				t.start();
				s.selection_sort(vec,0,vec.size()-1);
				t.stop();
				t.print();
				break;
			}
		case 5:
			{
			    cout<<"Quick Sort.......\n";
				t.start();
				s.quick_sort(vec,0,vec.size()-1);
				t.stop();
				t.print();
				break;
			}
		case 6:
			{
			    cout<<"Bubble Sort.......\n";
				t.start();
				s.bubble_sort(vec,0,vec.size()-1);
				t.stop();
				t.print();
				break;
			}
		case 7:
			{
			    cout<<"Opt_Bubble Sort.......\n";
				t.start();
				s.opt_bubble_sort(vec,0,vec.size()-1);
				t.stop();
				t.print();
				break;
			}
		case 8:
			{
			    cout<<"Opt_Rank Sort.......\n";
				t.start();
				s.opt_rank_sort(vec,0,vec.size()-1);
				t.stop();
				t.print();
				break;
			}
		default:
			{
				cout<<"Invalid Input\nExiting............\n";
				return 0;
			}
	}
	FILE *op = fopen("output.txt","w");
	vector<int>::vector_Iterator it;
	for(it=vec.begin();it!=vec.end();it++)
		fprintf(op,"%d\n",*it);
}
