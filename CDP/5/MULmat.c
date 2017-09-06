/*
    C socket server example, handles multiple clients using threads
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<pthread.h> //for threading , link with lpthread
 
//the thread function
typedef struct Pair{
    int i; int j;
} pair;
#define SIZE 1000
#define NUM_THREADS 4

void *multiplier(void* pair1);
int matA[SIZE][SIZE];
int matB[SIZE][SIZE];
int matC[SIZE][SIZE];
int size; 
int main(int argc , char *argv[])
{       
    int i,j;
     pthread_t sniffer_thread;
     clock_t start = clock(), diff;
     scanf("%d",&size);
     //printf("Matrix A:\n");
     for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            matA[i][j] = rand()%1000;
            
        }
        //putchar('\n');
     }

     //printf("Matrix B:\n");
     for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            matB[i][j] = rand()%1000;
            
        }
        //putchar('\n');
     }
     putchar('\n');
     
    for(i=0;i<size;i++) {
        
        for(j=0;j<size;j++){
            pair* thisPair = (pair*)malloc(sizeof(pair));
            thisPair->i = i;
            thisPair->j = j;
            if( pthread_create( &sniffer_thread , NULL ,  multiplier , (void*)thisPair) < 0)
            {
                perror("could not create thread");
                return 1;
            }
        }
    }
     pthread_join( sniffer_thread , NULL);
     diff = clock() -start;
     int ms = (diff*1000)/CLOCKS_PER_SEC;
     printf("Time taken for threads: %d sec %d ms\n",ms/1000,ms%1000);
     // for(i=0;i<size;i++){
     //    for(j=0;j<size;j++){
     //        printf("%d ",matC[i][j]);
     //    }
     //    putchar('\n');
     // }
    return 0;
}
 
/*
 * This will handle connection for each client
 * */
void *multiplier(void *thisPair)
{
    int i = ((pair*)thisPair)->i;
    int j =  ((pair*)thisPair)->j;
    int k = 0;

    matC[i][j] = 0;
    for (k=0;k<size;k++){
        matC[i][j] += matA[i][k]*matB[k][j];
    }
    // printf("#%d - Thread Done\n",*((int*)num));
    return 0;
}