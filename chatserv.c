#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 8086
int main()
{
   int sockfd, connfd,n;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr =htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("\nBinding...");
    listen(sockfd,5);
    printf("\nListening...");
    int len = sizeof(cli);
    connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
    printf("\nAccepted...");
    char buf[50];
    while(1)
    {
       bzero(buf,50);
       read(connfd,buf,sizeof(buf));
       printf("\nClient:%s",buf);
       bzero(buf,sizeof(buf));
       printf("\t\tServer:");
       n = 0;
       while ((buf[n++] = getchar()) != '\n');
       write(connfd,buf,sizeof(buf));
         if(strncmp(buf,"bye",3)==0)
       {
          printf("\nServer exit...");
          break;
       }
    }
    close(sockfd);
    close(connfd);
}
