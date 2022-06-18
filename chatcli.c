#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("\nConnected...");
    char buf[50];
    while(1)
    {
       bzero(buf,50);
       printf("\nClient:");
       n = 0;
       while ((buf[n++] = getchar()) != '\n');
       write(sockfd,buf,sizeof(buf));
       bzero(buf,50);
       read(sockfd, buf, sizeof(buf));
       printf("\n\t\tserver:%s",buf);
       if(strncmp(buf,"bye",3)==0)
       {
          printf("\nClient exit...");
          break;
       }
    }
    close(sockfd);
}


















