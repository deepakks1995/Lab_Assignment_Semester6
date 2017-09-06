#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<errno.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#define BUFFER 1024
int count =0;
void* reply(void *arg)
{
	
	count++;
	char mesg[BUFFER];
	int bytes_read;
	int client = *(int *)arg;
   
        bytes_read = recv(client, mesg, BUFFER, 0);
        send(client, mesg, bytes_read, 0);
    close(client);
    return arg;
}



int main(int argc,char **argv)
{
	struct sockaddr_in ser,cli;
	int sock;
	char ip4[INET_ADDRSTRLEN];
	sock=socket(AF_INET,SOCK_STREAM,0);
	ser.sin_family=AF_INET;
	ser.sin_port=htons(10002);
	ser.sin_addr.s_addr=INADDR_ANY;
	bzero(&ser.sin_zero,8);

	if((bind(sock,(struct sockaddr *)&ser,sizeof(ser)) == -1))
	{
		perror("bind:\n");
		exit(-1);
	}
	listen(sock,10);
		while(1)
		{
			int new ,len=sizeof(ser);
			pthread_t child;
			if((new=accept(sock,(struct sockaddr*)&cli,&len))==-1)
			{
				perror("accept:\n");
				exit(-1);
			}
			inet_ntop(AF_INET, &(cli.sin_addr),ip4, INET_ADDRSTRLEN);
		
			printf("Client connected %s:%d\n",ip4,ntohs(cli.sin_port));
			pthread_create(&child,NULL,reply,&new);
			printf("%d\n",count);		
		
		}
		
		return 0;
}
