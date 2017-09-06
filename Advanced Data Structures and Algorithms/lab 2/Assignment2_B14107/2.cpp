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
	sorter<int> s;
	timer t;
	FILE *p = fopen("input.txt","r");
	char name[10][150];
	int i,size=9,tmp,count=1;
	for(i=0;i<size;i++)
		fscanf(p,"%s\n",name[i]);
	FILE *op[size];
	FILE *wp ;
	if((wp=fopen("output.txt","w"))==NULL)
	{
		std::cout<<"Error in output\n";
	}
	for(i=0;i<size;i++)
	{
		op[i]=fopen(name[i],"r");
		if(op[i]==NULL)
			std::cout<<"Error in opening file "<<name[i]<<std::endl;
	}
	fprintf(wp,"Sno\tSize\tTime\n");	
	for(i=0;i<size;i++)
	{
		vector<int> vec;
		while(fscanf(op[i],"%d\n",&tmp)!=EOF)
			vec.push_back(tmp);
		vector<int> vec1 = vec;
		t.start();
		s.rank_sort(vec1,0,vec1.size()-1);
		t.stop();
		t.print();
		fprintf(wp,"%d\t%d\t%f\t",count++,vec1.size(),t.last_timing());
		
		vector<int> vec2 = vec;

		t.start();
		s.selection_sort(vec2,0,vec2.size()-1);
		t.stop();
		t.print();
		fprintf(wp,"%d\t%f\t",vec2.size(),t.last_timing());

		vector<int> vec3 = vec;		
		t.start();
		s.opt_bubble_sort(vec3,0,vec3.size()-1);
		t.stop();
		t.print();
		fprintf(wp,"%d\t%f\n",vec3.size(),t.last_timing());
		
	}
	fprintf(wp,"\n\n");
}
