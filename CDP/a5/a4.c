#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[500];

int m1[500][500],m2[500][500],mres1[500][500],mres2[500][500];

void* doSomeThing(void *arg){
    int colB = *(int*)arg;
    //printf("got col no %d\n",colB);
    int r,c;
    for(r=0;r<500;r++){
        int mulvalue=0;
        for(c=0;c<500;c++){
            mulvalue+=m1[r][c]*m2[c][colB];
        }
        mres1[r][colB]=mulvalue;
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

    int err;
    int x=0;
    for(x=0;x<500;x++){
        err = pthread_create(&(tid[cli[x]]), NULL, &doSomeThing, &cli[x]);
        if (err != 0){
            printf("\ncan't create thread :[%s]", strerror(err));
        }
        else{
            //printf("\n Thread created successfully\n");
        }
    }

    for(x=0;x<500;x++){
        (void) pthread_join(tid[cli[x]], NULL);    
    }
    
    //multiply();
    /*
    for(r=0;r<500;r++){
        for(c=0;c<500;c++){
            if(mres1[r][c]!=mres2[r][c]){
                printf("not same\n");
                return 0;
            }
            printf("%d",mres1[r][c]);
        }
    }
    //printf("same\n");
    */
    return 0;
}