#include<stdio.h> 
#include<string.h>   
#include<stdlib.h>
#include <sys/types.h> 
#include <unistd.h>
#include<sys/socket.h> 
#include<arpa/inet.h> 
 
int main(int argc , char *argv[])
{
    int height= 0;
    int max_height = 2;
    int pid;
    
    do{
        pid = fork();
        if(pid!=0){
            pid = fork();
            if(pid!=0){
                height=max_height;
            }else{
                height++;
            }
        }
        else{
            height++;
        }

    }while(height<max_height);
    printf("%d:%d\n",getppid(),getpid());
    
    sleep(10);

 
    return 0;
}
