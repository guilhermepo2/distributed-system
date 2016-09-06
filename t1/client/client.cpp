/*
  My HTTP CLient that uses a Distributed File System server
 */

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXDATASIZE 1024

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
  int sockfd, numbytes;
  char buf[MAXDATASIZE];
  struct addrinfo hints, *servinfo, *p;
  int rv;
  char s[INET6_ADDRSTRLEN];
  std::string host, port;
  
  // getting command line arguments, hostname and port
  if(argc != 3)
    {
      std::cout << "client usage: client hostname port" << std::endl;
      exit(1);
    }
  else
    {
      host = argv[1];
      port = argv[2];
      std::cout << "Connecting on: " << host << ":" << port << std::endl;
    }

  // doing all the cleanup thing
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if((rv = getaddrinfo(host.c_str(), port.c_str(), &hints, &servinfo)) != 0)
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return 1;
    }
  else
    {
      std::cout << "successful call: getaddrinfo()" << std::endl;
    }

  // doing all that looping thing, but, we're not going to use sockopt and binding, instead we're going to connect to the server
  for(p = servinfo; p != NULL; p = p->ai_next)
    {
      if((sockfd = socket(p->ai_family, p->ai_socktype,
			  p->ai_protocol)) == -1)
	{
	  perror("CLIENT: socket");
	  continue;
	}
      else
	{
	  std::cout << "successful call: socket()" << std::endl;
	}

      if(connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
	{
	  close(sockfd);
	  perror("CLIENT: Connection Error");
	  continue;
	}
      else
	{
	  std::cout << "sucessful call: connect()" << std::endl;
	}

      break;
    }

  if(p == NULL)
    {
      fprintf(stderr, "CLIENT: failed to connect\n");
      return 2;
    }
  else
    {
      std::cout << "CLIENT: Connected!" << std::endl;
    }

  inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
	    s, sizeof s);
  std::cout << "CLIENT: Connected to: " << s << std::endl;

  freeaddrinfo(servinfo); // we're done with the structure

  // at this point on the program we're connected with the server
  // now we have to send and/or receive messages
  
  // first let's try receiving one, maybe the server sent us a welcome message, right?
  /*
    Actually I don't care I don't need a message
    if((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1)
    {
    perror("CLIENT: Error at Receiving");
    exit(1);
    }
    buf[numbytes] = '\0';
    std::cout << "CLIENT: Received message: \n" << buf << std::endl;
  */

  // now we have to send our own message...
  // first we have to get the message right?
  // but how... ?
  // who cares, let's just hardcode it.
  
  std::string post_example = "POST /obladi/oblada HTTP/1.1\nHost: 127.0.0.1\nContent-length: 10\n\n123456789\n\n";
  std::string put_example = "PUT /obladi/oblada HTTP/1.1\nHost: 127.0.0.1\nContent-length: 10\n\n0987654321\n\n";
  std::string get_example = "GET / HTTP/1.1\nHost: 127.0.0.1\n\n";
  std::string another_get_example = "GET /obladi/oblada HTTP/1.1\nHost: 127.0.0.1\n\n";
  // now send one of them!
  // the message should be encoded?
  if(send(sockfd, post_example.c_str(), post_example.size(), 0) == -1)
    perror("send");
  else
    std::cout << "CLIENT: Message sent." << std::endl;

  // now we wait for the response and process it

  close(sockfd);
  return 0;
}


