/*
 * COMP 3271 - Computer Networks
 * Project Part 1 - UDP Time Server - server implementation
 */

#include <stdio.h>		/* I/O functions */
#include <string.h>		/* string functions */
#include <stdlib.h>		/* C standard functions */
#include <sys/socket.h>	/* socket functions */
#include <sys/types.h>	/* library of basic types */
#include <netinet/in.h>	/* library of Internet address functions */
#include <arpa/inet.h>	/* Internet operations */
#include <time.h>		/* time functions */

/* Project Requirement: Change server port to 9988 */
#define PORT 9988		/* server port # */
#define BUFFSIZE 200	/* buffer size */

int main()
{
	int sockfd;
	int addrlen;
	char buffer[BUFFSIZE];
    char response[BUFFSIZE * 2]; /* ADDED: Buffer to hold the combined echo and time */
	struct sockaddr_in server;
	struct sockaddr_in client;
	time_t current_time;

    /* Project Requirement: Added status print statement */
    printf("Initializing server data structures...\n");
	/* Populate socket data structures with IP address and port number */
	memset((char *) &server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    printf("Creating UDP socket...\n");
	/* Create a UDP socket; returns -1 on failure */
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sockfd == -1) {
		printf("Socket error\n");
		exit(1); /* Exit on error */
	}

    printf("Binding socket to port %d...\n", PORT);
	/* Bind the socket address */
	if ((bind(sockfd,(struct sockaddr*)&server,sizeof(struct sockaddr_in))) == -1) {
		printf("Server bind error\n");
		exit (1); /* Exit on error */
	}

	/* Helpful status message */
	printf("Server is listening on port: %d\n", PORT);
	printf("Waiting for client request...\n");
	printf("Press CTRL + C to exit\n\n");
	
	while(1) {
		addrlen = sizeof(struct sockaddr_in);
		recvfrom(sockfd, buffer,BUFFSIZE, 0,(struct sockaddr *)&client, (socklen_t *)&addrlen);
		
        /* Project Requirement: Added logging print statements */
        printf("--------------------------------------------------\n");
        printf("Client request received!\n");
        printf("Client Payload: %s\n", buffer); 
        
		current_time = time(NULL);
        
        /* Project Requirement: Ensure server echoes name and student number alongside time */
		snprintf(response, sizeof(response), "Echo: %s Current Time: %s", buffer, ctime(&current_time));
        
        printf("Sending echo and timestamp back to client...\n");
		sendto(sockfd, response, strlen(response) + 1, 0, (struct sockaddr *)&client, addrlen);
        
        printf("Response sent successfully. Waiting for next request...\n");
        printf("--------------------------------------------------\n\n");
	}
	exit(0);

} /* End of time server program */