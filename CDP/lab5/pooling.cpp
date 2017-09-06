#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<queue>

pthread_mutex_t count_mutex;
int count=0;
pthread_t tid[500][500];
std::queue<int*> Q;
int m1[500][500],m2[500][500],mres1[500][500],mres2[500][500];

void* doSomeThing(void *x){
    while(true){
        pthread_mutex_lock(&count_mutex);
        if(Q.size()==0){
            //printf("breaking\n");
            pthread_mutex_unlock(&count_mutex);
            break;
        }
        int *arg=Q.front();
        Q.pop();
        count++;
        pthread_mutex_unlock(&count_mutex);
        int colB = *((int*)(arg));
        int rowA = *((int*)(arg)+1);
        int c;
        int mulvalue=0;
        for(c=0;c<500;c++){
            mulvalue+=m1[rowA][c]*m2[c][colB];
        }
        mres1[rowA][colB]=mulvalue;
        //printf("%d\n",count);
    }
    return NULL;
}

void multiply(){
    int r1,c2,c1;
    for(r1=0;r1<500;r1++){
        for(c2=0;c2<500;c2++){
            int sum=0;
            for(c1=0;c1<500;c1++){
                sum+=m1[r1][c1]*m2[c1][c2];
            }
            mres2[r1][c2]=sum;
        }
    } 
}

int main(void){
    int r,c;
    int cli[500];
    for(r=0;r<500;r++){
        cli[r]=r;
        for(c=0;c<500;c++){
            m1[r][c]=1;
            m2[r][c]=1;
            mres1[r][c]=0;
            mres2[r][c]=0;
        }
    }
	
    int err1,err2,err3,err4;
    int count=0;
    int x=0,y=0;
    for(x=0;x<500;x++){
        for(y=0;y<500;y++){
            count++;
            int *arr=(int*)malloc(2*sizeof(int));
            *(arr)=x;
            *(arr+1)=y;
            //printf("pushing %d %d\n",x,y);
            Q.push(arr);   
        }
        
    }
clock_t start = clock(), diff;
    err1 = pthread_create(&(tid[0][0]), NULL, &doSomeThing,NULL);
    err1 = pthread_create(&(tid[0][1]), NULL, &doSomeThing,NULL);
    err1 = pthread_create(&(tid[0][2]), NULL, &doSomeThing,NULL);
    err1 = pthread_create(&(tid[0][3]), NULL, &doSomeThing,NULL);
    
    for(x=0;x<4;x++){
            (void) pthread_join(tid[0][x], NULL);
            //printf("joining\n");    
    }
diff = clock() -start;
     int ms = (diff*1000)/CLOCKS_PER_SEC;
     printf("Time taken for threads: %d sec %d ms\n",ms/1000,ms%1000);
    /*
    for(r=0;r<500;r++){
        for(c=0;c<500;c++){
            printf(" %d ",mres1[r][c]);
        }
        printf("\n");
    }
    */


    //printf("same\n");
    
    return 0;
}
