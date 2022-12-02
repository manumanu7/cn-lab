#include<stdio.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd)
{
char buff[MAX];
int n;
for(;;) {
bzero(buff, MAX);
//read the message from client and copy it in buffer
read(connfd,buff,sizeof(buff));
//print buffer which contains client contents
printf("From Client:%s\t To client: ", buff);
bzero(buff, MAX);
n=0;
//copy server message in the buffer
while((buff[n++]=getchar())!='\n')
;
//send that buffer to client
write(connfd,buff,sizeof(buff));
//if msg contains "Exit" then server exit
if(strncmp("exit",buff,4)==0) {
printf("Server Exit...\n");
break;
}
}
}
int main()
{
 int sockfd,connfd,len;
struct sockaddr_in servaddr, cli;

//socket create and verification
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd==-1) {
printf("socket creation failed....\n");
exit(0);
}
else
printf("socket Successfully created..\n");
bzero(&servaddr,sizeof(servaddr));
//assign IP, PORT
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(PORT);
//binding newly created socket to given IP
if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr)))!=0)
{ printf("socket bind failed...\n");
exit(0);
}
else
printf("socket successfully binded..\n");
// now server is ready to listen and verification
if((listen(sockfd,5))!=0)
{
printf("listen failed..\n");
exit(0);
}
else
printf("Server listening...\n");
len=sizeof(cli);
//accpet data packet from client and verify
connfd=accept(sockfd,(SA*)&cli,&len);
if(connfd<0){
printf("server accept failed..\n");
exit(0);
}
else
printf("aserver accept the client...\n");
//function for chatting between clent and server
func(connfd);
//close socjket
close(sockfd);
}
