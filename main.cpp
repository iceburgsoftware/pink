#include "pink.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    // Declare everything
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    // Set up the buffer, 255 character maximum message size.
    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    
    // Set up the socket
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    // Done with Prep work, moving on to the real handling loop
    while(1) {
	printf("Please enter the message: ");
	bzero(buffer,256);
	fgets(buffer, 255, stdin);
	n = send(sockfd, buffer, strlen(buffer), 0);
	if (n < 0) 
	    error("ERROR writing to socket");
	bzero(buffer, 256);
	n = recv(sockfd, buffer, 255, 0);
	if (n < 0) 
	    error("ERROR reading from socket");
	else 
	    cout << buffer << endl;
    }
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}
