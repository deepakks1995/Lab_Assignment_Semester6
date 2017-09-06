#include<stdio.h>
int main()
{
int i;
	printf("Generating Graphs ...........\n");
	char *cmdgnuplot[] = {"set term x11 0" ,"set xlabel \"Size\"","set ylabel \" Time(sec)\"","set title\" Selection_Sort\"","set key outside","plot for [col=3:5] 'selection_sort.txt' using 2:col with line title columnheader"};
	FILE *gnuplot = popen("gnuplot -persistent","w");
	for( i=0;i<6;i++)
	{
		fprintf(gnuplot,"%s\n",cmdgnuplot[i]);
	}
	fclose(gnuplot);
}
