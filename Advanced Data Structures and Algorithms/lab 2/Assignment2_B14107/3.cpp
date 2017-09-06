#include<iostream>
#include<cstdio>
#include"vector.hpp"
#include<malloc.h>
#include "sorter.hpp"
#include "timer.hpp"
using namespace abc;
using namespace sort;
int main()
{
	sorter<int> s;
	timer t;
	FILE *p = fopen("unsort.txt","r");
	char name[10][150];
	int i,size=7,tmp,count=1;
	for(i=0;i<size;i++)
		fscanf(p,"%s\n",name[i]);
	FILE *op[size];
	FILE *wp ;
	if((wp=fopen("rank_opt4.txt","a+"))==NULL)
	{
		std::cout<<"Error in output\n";
	}
	for(i=0;i<size;i++)
	{
		op[i]=fopen(name[i],"r");
		if(op[i]==NULL)
			std::cout<<"Error in opening file "<<name[i]<<std::endl;
	}
	fprintf(wp,"unsorted\n");
	fprintf(wp,"Sno\tSize\tTime\n");
	for(i=0;i<size;i++)
	{
		vector<int> vec;
		while(fscanf(op[i],"%d\n",&tmp)!=EOF)
			vec.push_back(tmp);
		std::cout<<count<<" "<<vec.size()<<std::endl;
		t.start();
		s.opt_rank_sort(vec,0,vec.size()-1);
		t.stop();
		t.print();
		fprintf(wp,"%d\t%d\t%f\n",count++,vec.size(),t.last_timing());
	}
	fprintf(wp,"\n\n");
		
}




