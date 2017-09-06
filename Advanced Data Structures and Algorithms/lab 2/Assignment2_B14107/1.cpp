#include<iostream>
#include"vector.hpp"
#include"sorter.hpp"
#include<fstream>
#include<cstdio>
#include<stdlib.h>
#include"timer.hpp"
using namespace abc;
using namespace std;
using namespace sort;


double* sort1(vector<int> b)
{
	sorter<int> s;
	timer t;
	double *time = new double[8];
	for(int i =0;i<8;i++)
		time[i] = 0;

	for(int ch = 2;ch<=8;ch++)
	{
		vector<int> a = b;
		switch(ch)
		{
		
			case 2:
				{
					t.start();
					s.selection_sort(a,0,a.size()-1);
					t.stop();
					break;
				}
			case 3:
				{
					t.start();
					s.bubble_sort(a,0,a.size()-1);
					t.stop();
					break;
				}
			case 4:
				{
					t.start();
					s.rank_sort(a,0,a.size()-1);
					t.stop();
					break;
				}
			case 5:
				{
					t.start();
					s.merge_sort(a,0,a.size()-1);
					t.stop();
					break;
				}
			case 6:
				{
					t.start();
					s.quick_sort(a,0,a.size()-1);
					t.stop();
					break;
				}
			case 7:
				{
					t.start();
					s.opt_bubble_sort(a,0,a.size()-1);
					t.stop();
					break;
				}
			case 8:
				{
					t.start();
					s.opt_rank_sort(a,0,a.size()-1);
					t.stop();
					break;
				}
			default:
				cout<<"\nInvalid option chosen...Exiting..\n";
				exit(0);
		}
		time[ch-1] = t.last_timing();
	}
	return time;
}

int main(int argc,char *argv[])
{
	cout<<"Welcome to Sorting Program...\n";
	if(argc == 1)
	{
		short int ch;
		ch=2;
		switch(ch)
		{
			case 1:
				{
					int size;
					int temp;
					cout<<"Enter No. of elements = \n";
					cin>>size;
					vector<int> a(size);
					cout<<"Enter Elements\n";
					for(int i = 0;i<size;i++)
					{
						cin>>temp;
						a.push_back(temp);
					}
					sort1(a);
					break;
				}
			case 2:
				{
					short int num;
					cout<<"\nEnter No. of files...\n";
					cin>>num;
					FILE *outfile = fopen("caltime.txt","w");
					for(int i = 0 ;i<num;i++)
					{
						char str[200];
						char cas[200];
						cout<<"Enter Name of File..: \n";
						cin>>str;
						cout<<"Enter case .. :\n";
						cin>>cas;
						FILE *infile;
						infile = fopen(str,"r");
						if(infile == NULL)
						{
							cout<<"\nError Opening File..Exiting..\n";
							exit(0);
						}
						vector<int> a;
						int b;
						while(fscanf(infile,"%d\n",&b) == 1)
						{
							a.push_back(b);
						}
						double *time = sort1(a);
						fclose(infile);
						fprintf(outfile,"%2d%7d%7s",i+1,a.size(),cas);
						for(int j = 0;j<8;j++)
							fprintf(outfile,"\t%lf",time[j]);
						fprintf(outfile,"\n");
					}
					fclose(outfile);
					break;
				}
			default:
				cout<<"\nInvalid choice chosen...Exiting...\n";
				exit(0);
		}
	}
	else if(argc == 2)
	{
		FILE *infile = fopen(argv[1],"r");
		if(infile == NULL)
		{
			cout<<"\nError opening file..Exiting.\n";
			exit(0);
		}
		int b;
		vector<int> a;
		while((fscanf(infile,"%d\n",&b)!=EOF))
		{
			a.push_back(b);
		}
		sort1(a);
		fclose(infile);
	}
	else
	{
		cout<<"\nToo many command line arguments...Exiting..\n";
		exit(0);
	}
	return 0;
}
