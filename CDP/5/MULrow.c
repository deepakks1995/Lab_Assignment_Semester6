/*
    C socket server example, handles multiple clients using threads
*/
 #include<time.h>
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
    srand(time(NULL));
    int i,j;
     pthread_t sniffer_thread;
     clock_t start = clock(), diff;
     scanf("%d",&size);
     printf("Enter Matrix A:\n");
     for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            matA[i][j] = rand()%1000;
            //scanf("%d",&matA[i][j]);
        }
        //putchar('\n');
     }

     printf("Enter Matrix B:\n");
     for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            matB[i][j] = rand()%1000;
            //scanf("%d",&matB[i][j]);
        }
        //putchar('\n');
     }
     putchar('\n');
    for(i=0;i<size;i++){
        int *ptr = (int*)malloc(sizeof(int));
        *ptr = i;
        pthread_create(&sniffer_thread,NULL,multiplier,(void*)ptr);
        pthread_create(&sniffer_thread,NULL,multiplier,(void*)ptr);
    }
     pthread_join( sniffer_thread , NULL);
     diff = clock() -start;
     int ms = (diff*1000)/CLOCKS_PER_SEC;
    
     printf("Time taken for threads: %d sec %d ms\n",ms/1000,ms%1000);
     putchar('\n');
int k;
     for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            for(k = 0;k<size;k++){
                matD[i][j]+=matA[i][k] * matB[k][j];
            }
            if(2*matD[i][j]!=matC[i][j]){
                //printf("Error at %d,%d index\t%d\t%d\t%d\n",i,j,2*matD[i][j],matD[i][j],matC[i][j]);
                if(matD[i][j]!=matC[i][j]){
                    //printf("Not even Single\n");
                    printf("Error at %d,%d index\t%d\t%d\t%d\n",i,j,2*matD[i][j],matD[i][j],matC[i][j]);
                }
            }
        }
        //putchar('\n');
     }
     
    return 0;
}
 
/*
 * This will handle connection for each client
 * */
void *multiplier(void *row)
{
    int i = *((int*)row);
    int j = 0;
    int k = 0;

    for(j=0;j<size;j++){
        //matC[i][j] = 0;
        for (k=0;k<size;k++){
            matC[i][j] += matA[i][k]*matB[k][j];
        }    
    }
    
    // printf("#%d - Thread Done\n",*((int*)num));
    return 0;
}