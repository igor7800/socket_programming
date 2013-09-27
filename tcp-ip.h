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
 * @param portno 
 * @return sockfd 
 */
int create_socket(int namespace, int style, int protocol,struct sockaddr_in serv_addr)
{
  int sockfd = socket(namespace, style, protocol); 
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
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");
}

/**
 *
 * @param sockfd socket
 * @param number number of clients
 */
void listen_for_connection(int sockfd,int number)
{
  if(listen(sockfd,number) <0)
    error("ERROR, listening failed");
  
}

/**
 * Connecting to server
 * 
 */
void connect_to_server(int sockfd, struct sockaddr_in serv_addr)
{
  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    error("ERROR connecting");
}



/**
 * Accepting the connection 
 *
 */
int accept_connection(int sockfd, struct sockaddr_in cli_addr, int clilen )
{
   clilen = sizeof(cli_addr);  
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
  bzero(buffer,strlen(buffer));
  int n = read(newsockfd,buffer,size);
  if (n < 0) error("ERROR reading from socket");
}

