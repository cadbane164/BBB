// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	struct sockaddr_in servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 

	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 

	int n, len,stop = 0; 

	while(stop==0)
	{
		char a[15];
		scanf("%s",a);

		if(strcmp(a,"count")==0)
		{
			sendto(sockfd, (const char *)a, strlen(a), 
					MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
					sizeof(servaddr)); 
		}
		else if(strcmp(a,"get")==0 || strcmp(a,"first")==0 || strcmp(a,"last")==0)
		{
			sendto(sockfd, (const char *)a, strlen(a), 
					MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
					sizeof(servaddr)); 
			char num[2];
			scanf("%s",num);
			sendto(sockfd, (const char *)num, strlen(num), 
					MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
					sizeof(servaddr)); 
		}
		else if(strcmp(a,"stop")==0)
		{
			stop=1;
		}
	}

	close(sockfd); 
	return 0; 
} 

