#include "tcp-ip.h"

int main(int argc, char *argv[])
{
  int sockfd, newsockfd, portno, clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  //make portnumber as second argument
  portno = atoi(argv[1]);
  sockfd=create_socket(AF_INET,SOCK_STREAM,0,serv_addr);
  //add values to the struct serv addr
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  bind_socket(sockfd,serv_addr);
  printf ("Server is open at port %d\n",portno);
  for (;;) {
  listen_for_connection(sockfd,1);
  newsockfd = accept_connection(sockfd,cli_addr,clilen);
  recive_data(newsockfd,buffer,255);
  printf("Here is the message: %s\n",buffer);
  send_data(newsockfd,"I got your message");
  }
  return 0;
}


