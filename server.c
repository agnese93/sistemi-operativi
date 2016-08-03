/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

char messaggi[] = "Messaggio 1\nMessaggio 2\n";

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int leggiPorta(int argc, char *argv[]){
    if (argc < 2) {
        fprintf(stdout,"no port provided: using 10000 port\n");
		return 10000;
    }
	else {
 		return atoi(argv[1]);
 	}
}


int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
	 
	 portno = leggiPorta(argc, argv);
		 
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
			  
	  while(1 == 1){
	      listen(sockfd,5);
	      clilen = sizeof(cli_addr);
	      newsockfd = accept(sockfd, 
	                  (struct sockaddr *) &cli_addr, 
	                  &clilen);
	      if (newsockfd < 0) 
	           error("ERROR on accept");
	      bzero(buffer,256);


	      n = write(newsockfd, messaggi, sizeof(messaggi));
	  }

	 
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0; 
}