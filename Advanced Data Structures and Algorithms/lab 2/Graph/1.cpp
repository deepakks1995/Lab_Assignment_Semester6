#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	printf("Generating Graphs ...........\n");
	char *cmdgnuplot[] = {"set term x11 1","set xlabel \"Time(sec)\"","set ylabel \" Size\"","set title\" Insertion_Sort\"","set key outside","plot for [col=3:5] 'insertion_sort.txt' using 2:col with line"};
	FILE *gnuplot = popen("gnuplot -persistent","w");
	for(int i=0;i<6;i++)
	{
		fprintf(gnuplot,"%s\n",cmdgnuplot[i]);
	}
	fclose(gnuplot);
}
