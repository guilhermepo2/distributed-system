/*
** server.c -- a stream socket server demo
*/

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
#include <iostream>

#define BACKLOG 10	 // how many pending connections queue will hold

void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char * argv[])
{

  // getting port via command line
  char * port;
  if(argc < 2)
    {
      std::cout << "usage: ./server port" << std::endl;
      exit(1);
    }
  else
    {
      port = argv[1];
      std::cout << "port: " << port << std::endl;
    }
  
  
  int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
  struct addrinfo hints, *servinfo, *p;
  struct sockaddr_storage their_addr; // connector's address information
  socklen_t sin_size;
  struct sigaction sa;
  int yes=1;
  char s[INET6_ADDRSTRLEN];
  int rv;
  
  memset(&hints, 0, sizeof hints); // clean the struct, making sure its empty
  hints.ai_family = AF_UNSPEC;     // dont care if IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // SOCK_STREAM = TCP
  hints.ai_flags = AI_PASSIVE;     // use my IP

  // getaddrinfo() - prepare to launch!
  // does all kind of good stuff for you
  if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }

  // loop through all the results and bind to the first we can

  // socket()
  // feed the result of getaddrinfo() to socket()
  // you use sockets for later system calls using the network
  
  for(p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype,
			 p->ai_protocol)) == -1) {
      perror("server: socket");
      continue;
    }

    // if theres a socket remaining in the port (from previous use)
    // please free it
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
		   sizeof(int)) == -1) {
      perror("setsockopt");
      exit(1);
    }
    
    // bind()
    // associate the socket with a local port
    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("server: bind");
      continue;
    }
    
    break;
  }

  // if p == null no socket could be binded
  if (p == NULL)  {
    fprintf(stderr, "server: failed to bind\n");
    return 2;
  }

  // free the linked list obtained in getaddrinfo()
  // we already binded it, so who cares
  freeaddrinfo(servinfo);

  //Listen() Will Somebody please Call Me?
  if (listen(sockfd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  }
  
  sa.sa_handler = sigchld_handler; // reap all dead processes
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }
  
  printf("server: waiting for connections...\n");
  
  while(1) {  // main accept() loop
    sin_size = sizeof their_addr;

    // accept() - Thank you for calling
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
      perror("accept");
      continue;
    }

    // ntop = network to presentation
    inet_ntop(their_addr.ss_family,
	      get_in_addr((struct sockaddr *)&their_addr),
	      s, sizeof s);
    printf("server: got connection from %s\n", s);
    
    if (!fork()) { // this is the child process
      close(sockfd); // child doesn't need the listener

      /* ============================================ */
      // CONNECTION ESTABILISHED HERE
      std::string msg = "You are connected!";
      if (send(new_fd, msg.c_str(), msg.size(), 0) == -1)
	perror("send");

      //note: see that how the message is sent, it is created as as c++ string, but the send function requires a char * string, we can achieve that using the c_str() function on the c++ string, and also, to inform how many bytes are going over the network we have just to get the size from the c++ string

      // now we can listen to the client and send acks!
      std::string ack = "ACK";
      char buf[1024];
      
      int size;
      // wait for a message, prints it and sends an ack
      if(recv(new_fd, buf, 1024, 0) == -1)
	perror("receive");
      
      std::cout << "received:" << buff << std::endl;
      
      if(send(new_fd, ack.c_str(), ack.size(), 0) == -1)
	 perror("send");
      /* ============================================ */
      // GOODBYE CLIENT SEE YOU
      close(new_fd);
      exit(0);  // note that the CHILD process will end here
                // the parent will still be running, so the server too
    }
    
    close(new_fd);  // parent doesn't need this
  }
  
  return 0;
}
