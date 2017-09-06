/*
    C socket server example, handles multiple clients using threads
*/
#include<bits/stdc++.h>
#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<pthread.h> //for threading , link with lpthread
 
using namespace std;
//the thread function

#define SIZE 1000
#define NUM_THREADS 10

void *multiplier(void* a);
int matA[SIZE][SIZE];
int matB[SIZE][SIZE];
int matC[SIZE][SIZE];
int size; 
pthread_mutex_t Q_mutex;


queue<pair<int,int> > pool;


int main(int argc , char *argv[])
{       
    int i,j;
     pthread_t sniffer_thread[NUM_THREADS];
     clock_t start = clock(), diff;
     scanf("%d",&size);
     // putchar('\n');
     // printf("Matrix A:\n");
     for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            matA[i][j] = 0;
            if(i==j)
                matA[i][j] = 1;
            // printf("%d ",matA[i][j]);
        }
        // putchar('\n');
     }
     // putchar('\n');
     // printf("Matrix B:\n");
     for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            matB[i][j] = rand()%10;
            // printf("%d ",matB[i][j]);
        }
        // putchar('\n');
     }
     // putchar('\n');
     
    for(i=0;i<size;i++) {
        
        for(j=0;j<size;j++){
            pair<int,int>* thisPair = new pair<int,int>(i,j);
            pool.push(*thisPair);
        }
    }
    for(i = 0;i<NUM_THREADS;i++)
    {
        int * ind = new int(i);
        pthread_create( &sniffer_thread[i] , NULL ,  multiplier , &i);
            
    }
    
     for (int i = 0; i < NUM_THREADS; ++i)
     {
         // pthread_join( sniffer_thread[i] , NULL);
     }
     diff = clock() -start;
     int ms = (diff*1000)/CLOCKS_PER_SEC;
     // printf("Time taken for threads: %d sec %d ms\n",ms/1000,ms%1000);
     // printf("\nMatric C is :\n");
     for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            // printf("%d ",matC[i][j]);
        }
        // putchar('\n');
     }
    return 0;
}
 
/*
 * This will handle connection for each client
 * */
void *multiplier(void* a)
{
    
    pair<int,int> temp;
    int i,j,k;

    while(!pool.empty()){
       pthread_mutex_lock(&Q_mutex);
        temp = pool.front();
            
        
        i = temp.first;
        j =  temp.second;
        k = 0;

        matC[i][j] = 0;
        for (k=0;k<size;k++){
            matC[i][j] += matA[i][k]*matB[k][j];
        }
        pool.pop();
        pthread_mutex_unlock(&Q_mutex);
    }

    
    // printf("#%d - Thread Done\n",*((int*)num));
    return 0;
}