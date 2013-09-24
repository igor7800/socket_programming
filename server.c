#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h> 

void error(char *msg)
{
  perror(msg);
  exit(0);
}

/**
 * Creates a socket with communication style, namespace and 
 * protocol, prints error if socket not created
 * @param namespace 
 * @param style
 * @param protocol
 * @return sockfd 
 */
int create_socket(int namespace, int style, int protocol,struct sockaddr_in serv_addr)
{
  int sockfd;
  sockfd = socket(namespace, style, protocol); 
  if(sockfd <0) error("ERROR opening socket");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  return sockfd;
}

/**
 * bind a socket to server address and port
 * @param sockfd socket
 * @param serv_addr 
 */
void bind_socket(int sockfd, struct sockaddr_in serv_addr)
{
  if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    error("ERROR on binding");
}

/**
 *
 * @param sockfd socket
 * @param number number of clients
 */
void listen_for_connection(int sockfd,int number)
{
  listen(sockfd,number);
}

/**
 * Accept the connection 
 *
 */
int accept_connection(int sockfd, struct sockaddr_in cli_addr, int clilen )
{
  int newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
  if (newsockfd < 0) error("ERROR on accept");
  return newsockfd;
}

/**
 * sending data to the client socket
 *
 */
void send_data(int newsockfd,char *buf)
{
  int n = write(newsockfd,buf,strlen(buf));
  if (n < 0) error("ERROR writing to socket");
}

/**
 *
 *@param size size of data to be recived
 */
void recive_data(int newsockfd, char *buffer,int size)
{
  bzero(buffer,sizeof(buffer));
  int n = read(newsockfd,buffer,size);
  if (n < 0) error("ERROR reading from socket");
}


int main(int argc, char *argv[])
{
  int sockfd, newsockfd, portno, clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  portno = atoi(argv[1]); //make portnumber as second argument
  if (argc < 2)           //check for port argument
    {
      fprintf(stderr,"ERROR, no port provided\n");
      exit(1);
    }

  sockfd=create_socket(AF_INET,SOCK_STREAM,0,serv_addr);
  
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  
  bind_socket(sockfd,serv_addr);
  listen_for_connection(sockfd,1);
  clilen = sizeof(cli_addr);  
  newsockfd = accept_connection(sockfd,cli_addr,clilen);
  recive_data(newsockfd,buffer,255);
  printf("Here is the message: %s\n",buffer);
  send_data(newsockfd,"I got your message");
  return 0;
}


