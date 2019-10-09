// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include<math.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

int isprime(int n)
{
	int i,c=1;
	for(i=2;i<=sqrt(n);i++)
	{
		if(n%i==0)
		{
			c=0;
			break;
		}
	}
	return c;
}


// Driver code 
int main() { 
	int primes[26],i,l=0;

	for(i=2;i<=100;i++)
	{
		if(isprime(i)==1)
		{
			primes[l]=i;
			l++;
		}
	}
	int sockfd; 
	char buffer[MAXLINE]; 

	struct sockaddr_in servaddr, cliaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 

	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 

	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
				sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	int len, n,stop=0,num; 
	while(stop==0)
	{
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len);
		buffer[n]='\0';
		if(strcmp(buffer,"count")==0)
		{
			printf("%d\n",l);
		}
		else if(strcmp(buffer,"get")==0)
		{
			char a[3];
			n = recvfrom(sockfd, (char *)a, 3, 
					MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
					&len);
			a[n]='\0';
		//	printf("a is: %s\n",a);
			if(strlen(a)==2)
				num=(a[0]-'0')*10+(a[1]-'0');
			else
				num = (a[0]-'0');
			printf("%d\n",primes[num-1]);
		}
		else if(strcmp(buffer,"last")==0)
		{
			char a[3];
			n = recvfrom(sockfd, (char *)a,3, 
					MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
					&len);
			a[n]='\0';
			if(strlen(a)==2)
				num=(a[0]-'0')*10+(a[1]-'0');
			else
				num = (a[0]-'0');
			for(i=num-1;i>=0;i--)
			{
				printf("%d ",primes[l-i-1]);
			}
			printf("\n");
		}
		else if(strcmp(buffer,"first")==0)
		{
			char a[3];
			n = recvfrom(sockfd, (char *)a, 3, 
					MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
					&len);
			a[n]='\0';
			if(strlen(a)==2)
				num=(a[0]-'0')*10+(a[1]-'0');
			else
				num = (a[0]-'0');
			for(i=0;i<num;i++)
			{
				printf("%d ",primes[i]);
			}
			printf("\n");
		}
		else if(strcmp(buffer,"stop") == 0)
		{
			stop=1;
		}
	}
	return 0; 
} 

