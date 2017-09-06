#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
int size = 500;
int A[1000][1000],B[1000][1000];
int result[1000][1000];

void init_matrix()
{
  int i, j, val = 0;
  for (i = 0; i < size; i++)
  {
    for (j = 0; j < size; j++)
      {
      	B[i][j] = A[i][j] = 1;
      	result[i][j] = 0;
      }
  }
}

void * multiplier (void *param) {
	int *arr = (int *) param;
	int j;
		for(j=0;j<size;++j) {
				result[arr[0]][arr[1]] += A[arr[0]][j]*B[j][arr[1]];
			}
	return 0;

}


int main()
{	
  int i=0,j=0;
	pthread_t **thread = (pthread_t *) malloc(size*sizeof(pthread_t *));
  for( i = 0; i< size ; ++i){
    thread[i] = (pthread_t ) malloc (size*sizeof(pthread_t));
  }
	
	for (i = 0; i < size; i++)
  	{
    	for (j = 0; j < size; j++)
      	{
      		A[i][j] = 2;
      		result[i][j] = 0;
      		B[i][j] = 2;
      	}
  	}/*
  	for (i = 0; i < size; i++)
  	{
    	for (j = 0; j < size; j++)
      	{
      		printf("%d ",A[i][j]);
      	}
      	printf("\n");
  	}*/
        clock_t start = clock(), diff;
  for(i=0; i<size; ++i) {
  	for(j=0;j<size;++j)
	   {
        int arr[2] ;
        arr[0] = i;
        arr[1] = j;
  			if(pthread_create(&thread[i][j],NULL,multiplier,(void *)arr)!=0  ) 
  			 {
			 	       printf("Can't create thread");
          			return 0;
		  	 }
         pthread_join (thread[i][j], NULL);
      }
    }
    int msec1 = diff * 1000 / CLOCKS_PER_SEC;
/*
 	for (i = 0; i < size; i++)
  	{
    	for (j = 0; j < size; j++)
      	{
      		printf("%d ",result[i][j]);
      	}
      	printf("\n");
  	}
*/
    printf("Time taken for 1000 X 1000 thread %d seconds %d milliseconds\n", msec1/1000, msec1%1000);
 			//print_matrix(A);
 		//print_matrix(result);
}
