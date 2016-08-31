/*
  My HTTP Server that Handles a Distributed File System

 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define BACKLOG 10 // maximum pending connections

// sigchld thing handler
// also i dont know what this is tbh lads
void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

// function get in addr
// in stands for INPUT i guess...
// basically it gets if its a IPv4 or a IPv6 address
void * get_in_addr(struct sockaddr * sa)
{
  if(sa->sa_family == AF_INET)
    {
      return &(((struct sockaddr_in*)sa)->sin_addr);
    }

  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char * argv[])
{
  // GETTING PORT VIA COMMAND LINE
  std::string port;
  if(argc < 2)
    {
      std::cout << "usage: server port" << std::endl;
    }
  else
    {
      port = argv[1];
      std::cout << "Will listen on port: " << port << std::endl;
    }

  // STUFF WE NEED FOR THE CONNECTION
  int sockfd, new_fd;                // listen on sock_fd, new connections on new_fd
  // ADDRINFO STRUCT is used to prep the socket address structure to subsequente use
  struct addrinfo hints, *servinfo, *p;
  // SOCKADDR_STORAGE STRUCT holds IPv4 and IPv6
  struct sockaddr_storage their_addr; // connector`s adress information
  socklen_t sin_size;
  struct sigaction sa;
  int yes = 1;
  char s[INET6_ADDRSTRLEN];
  int rv;
  
  memset(&hints, 0, sizeof hints);   // clean the structure, making sure it's empty
  hints.ai_family = AF_UNSPEC;       // we dont care if its IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;   // its a TCP connection
  hints.ai_flags = AI_PASSIVE;       // using my IP

  // GETADDRINFO() - PREPARE TO LAUNCH!
  if ((rv = getaddrinfo(NULL, port.c_str(), &hints, &servinfo)) != 0)
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return 1;
    }
  else
    {
      std::cout << "successful call: getaddrinfo()" << std::endl;
    }

  // LOOPING THROUGH EVERY PIECE OF INFORMATION OBTAINED ON THE GETADDRINFO() AND BIND ON THE FIRST RESULT WE CAN
  for(p = servinfo; p != NULL; p = p->ai_next)
    {
      if((sockfd = socket(p->ai_family, p->ai_socktype,
			  p->ai_protocol)) == -1)
	{
	  perror("server: socket"); // could not bind to this one
	  continue;
	}
      else
	{
	  std::cout << "successful call: socket() - got the socket descriptor" << std::endl;
	}

      // making sure there are not sockets leftovers on ports
      if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
		    sizeof(int)) == -1)
	{
	  perror("setsockopt");
	  exit(1);
	}
      else
	{
	  std::cout << "successful call: setsockopt() - cleaned port" << std::endl;
	}

      // if there was a success, bind.
      if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
	{ // if we could not bind
	  close(sockfd);
	  perror("error on bind");
	  continue;
	}
      std::cout << "successful call: bind() - binded successfully" << std::endl;

      break;
    }

  // if p is NULL we couldn't find any socket or couldn't bind one
  if(p == NULL)
    {
      fprintf(stderr, "server: failed to bind\n");
      return 2;
    }

  // don't need the addrinfo anymore, can free it
  freeaddrinfo(servinfo);

  // now we play the waiting game
  // LISTEN() - WILL SOMEBODY PLEASE CALL ME?
  if(listen(sockfd, BACKLOG) == -1)
    {
      perror("listen");
      exit(1);
    }
  else
    {
      std::cout << "Listening on port: " << port << std::endl;
    }

  // sigaction thing
  // i don't know what this is tbh fam
  sa.sa_handler = sigchld_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if(sigaction(SIGCHLD, &sa, NULL) == -1)
    {
      perror("siaction");
      exit(1);
    }
  else
    {
      std::cout << "successful call: sigaction()" << std::endl;
    }

  std::cout << "SERVER ON!" << std::endl;
  std::cout << "SERVER: Waiting for connections..." << std::endl;

  // everything set
  // NOW we play the waiting game...
  while(1)
    { // main accept() loop
      sin_size = sizeof their_addr;

      // ACCEPT() - Thank you for calling
      new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
      if(new_fd == -1)
	{
	  perror("accept");
	  continue;
	}

      // ntop = network to presentation
      // why am I doing this again?
      inet_ntop(their_addr.ss_family,
		get_in_addr((struct sockaddr *)&their_addr),
		s, sizeof s);
      std::cout << "SERVER: got connection from: " << s << std::endl;

      if(!fork())
	{ // the child process will handle the connection
	  // NOW WE HANDLE EVERYTHING
	  // we have to receive a HTTP Protocol Based message and so something
	  // with it
	  std::string response = "GET 200 OK\nVersion: 2\nCreation: 1450879900184\nModification: 1450879901000\nContent-length:10\n\n0987654321";
	  std::string sample_html_response = "<html>\n<head><title>Hello World</title></head>\n<body><h1>Hello World</h1></body>\n</html>";
	  if(send(new_fd, sample_html_response.c_str(), sample_html_response.size(), 0) == -1)
	    perror("send");
	  else
	    std::cout << "response sent!" << std::endl;
	  
	} // end of child process

      close(new_fd); // the parent doesn't need the connection, it will just keep listening
    }

  return 0;
}

