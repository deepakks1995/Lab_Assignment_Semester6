#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<errno.h>
#define BUFFER 10
int main(int argc,char **argv)
{
	int counter=0;
	if(argc !=3)
	{
		printf("Enter the command in format ./client ip port.\nServer is running on port 10000\n");
		exit(-1);
	}
	printf("Connecting to %s:%s......\n",argv[1],argv[2]);
	while(1)
	{
	int sock,rec;
	struct sockaddr_in server;
	int i=0,j;
	char mesg[BUFFER],output[BUFFER];	
	for( i=0;i<5;i++)
	mesg[i]='A';
	mesg[5]='\0';
		sock=socket(AF_INET,SOCK_STREAM,0);
		server.sin_family=AF_INET;
		server.sin_port=htons(atoi(argv[2]));
		inet_pton(AF_INET,argv[1],&(server.sin_addr.s_addr));
		bzero(&server.sin_zero,8);

		if(connect(sock,(struct sockaddr *)&server,sizeof(server))==-1)
		{
			perror("connect\n");
			exit(-1);
		}	
	//printf("%d\n",i);
	//printf("Connected\n\n.Type quit to close connection\n");
		send(sock,mesg,BUFFER,0);
		rec=recv(sock,output,BUFFER,0);
		//output[rec]='\0';
		//printf("%s",output);
	close(sock);
	//printf(".....\nConnection terminated\n");
	}
	
}


