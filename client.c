#include "tcp-ip.h"


int main(int argc, char *argv[])
{
  int sockfd, portno,n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];
  portno = atoi(argv[2]);
  server=gethostbyname(argv[1]);
  printf ("Connected to the server %s ",argv[1]);
  printf ("at port %d \n",portno);
  for(;;){
  sockfd= create_socket(AF_INET,SOCK_STREAM,0,serv_addr);
  if(server==NULL){
    fprintf(stderr,"ERROR, no such host \n");
    exit(0);
  }
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);
  connect_to_server(sockfd,serv_addr);
  printf("Please enter the message: ");
  bzero(buffer,256);
  fgets(buffer,255,stdin);
  send_data(sockfd,buffer);
  recive_data(sockfd,buffer,255);
  printf("%s\n",buffer);
  }
  return 0;
}
