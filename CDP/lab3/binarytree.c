#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int depth;
int counter = 0;
void create(){
    pid_t pid=fork();
    pid_t pid1=10;
    if(pid>0)pid1=fork();
    if(pid>0 && pid1>0){
        exit(1);
    }
    if(pid==0){
        printf("i am process in level -> %d \n",counter);
    }
    if(pid1==0){
        printf("i am process in level -> %d \n",counter);
    }

}

int main(int argc, char **argv)
{
   
    counter=0;
    printf("Enter depth of binary tree :\n");
    scanf("%d",&depth);
    while(counter<depth){
        counter++;
        create();
        
    }

    return 0;
}