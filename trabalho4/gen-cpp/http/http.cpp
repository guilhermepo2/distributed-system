#include "http.hpp"
#include <sstream>

namespace HTTP
{
  std::string get_full_message(std::vector<std::string> tokens)
  {
    std::string msg = "";
    
    #if DEBUG
    for(int i = 0; i < tokens.size(); i++)
      {
	if(tokens[i] == "\r")
	  std::cout << "token " << i << ": " << tokens[i] << std::endl;
      }
    #endif

    int i;
    for(i = 0; (tokens[i] != "\r" && i < tokens.size()); i++);

    for(; i < tokens.size() - 1; i++)
      msg += (tokens[i] + " ");

    msg += tokens[tokens.size() - 1];

    if(msg.size() > 1024)
      {
	msg.erase(msg.begin()+1024, msg.end());
      }
    
    return msg;
  }
  
  void checkFSRoot()
  {
    std::cout << "CHECKING FILE SYSTEM ROOT" << std::endl;
    std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
    std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
    std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
    std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
    std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
    std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
    std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
    std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
    std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
    std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  }
  
  std::string notfound(std::string content)
  {
    std::string message = "HTTP/1.1 404 NOT FOUND\nContent-type: text/html\nConnection: Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>404 Not Found</title></head><body><h1>404 Not Found</h1><p>The path " + content + " is invalid or does not exist</p></body></html>";

    return message;
  }

  std::string badrequest(std::string content)
  {
    std::string message = "HTTP/1.1 400 BAD REQUEST\nContent-type: text/html\nConnection: Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>400 Bad Request</title></head><body><h1>400 Bad Request</h1><p>" + content + "</p></body></html>";

    return message;
  }
  
  std::string handleGET(std::vector<std::string> tokens)
  {
    Node * result = FileSystem::instance()->search(tokens[1]);
    
    if(result == NULL)
      {
	return notfound(tokens[1]);
      }

    std::ostringstream version;
    version << result->get_version();
    std::ostringstream creation;
    creation << result->get_creation();
    std::ostringstream modification;
    modification << result->get_modification();
    std::ostringstream content_length;
    content_length << result->get_data().size();


    return "HTTP/1.1 200 OK\nVersion: "+version.str()+"\nCreation: "+creation.str()+"\nModification: "+modification.str()+"\nContent Length: "+content_length.str()+"\nContent-type: text/html\nConnection:Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>200 OK</title></head><body><h1>GET 200 OK</h1><p>"+result->get_data()+"</p></body></html>";
  }
  
  std::string handleHEAD(std::vector<std::string> tokens)
  {
    Node * result = FileSystem::instance()->search(tokens[1]);
    
    if(result == NULL)
      {
	return notfound(tokens[1]);
      }
    
    std::ostringstream version;
    version << result->get_version();
    std::ostringstream creation;
    creation << result->get_creation();
    std::ostringstream modification;
    modification << result->get_modification();
    std::ostringstream content_length;
    content_length << result->get_data().size();
    
    
    return "HTTP/1.1 200 OK\nVersion: "+version.str()+"\nCreation: "+creation.str()+"\nModification: "+modification.str()+"\nContent Length: "+content_length.str()+"\nContent-type: text/html\nConnection:Closed\r\n\r\n";
  }
  
  std::string handlePUT(std::vector<std::string> tokens)
  {
    // get full message from tokens
    std::string full_message = get_full_message(tokens);
    
    Node * result = FileSystem::instance()->edit(tokens[1], full_message);
    if(result == NULL)
      {
	return notfound(tokens[1]);
      }
    
    std::ostringstream version;
    version << result->get_version();
    std::ostringstream creation;
    creation << result->get_creation();
    std::ostringstream modification;
    modification << result->get_modification();

    return "HTTP/1.1 200 OK\nVersion: "+version.str()+"\nCreation: "+creation.str()+"\nModification: "+modification.str()+"\nContent-type: text/html\nConnection:Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>200 OK</title></head><body><h1>PUT 200 OK</h1><p>Edited "+tokens[1]+" to content: "+full_message+"</p></body></html>";
  }

  std::string handlePOST(std::vector<std::string> tokens)
  {
    #if DEBUG
    std::cout << "Inserting: " << tokens[1] << " with content: " << tokens[tokens.size()-1] << std::endl;
    #endif

    // get full message from tokens
    std::string full_message = get_full_message(tokens);
    
    // return the new inserted children
    Node * result = FileSystem::instance()->insert(tokens[1], full_message);

    // something went wrong
    if(result == NULL)
      {
	return badrequest("Path is invalid or already exist");
      }
    
    std::ostringstream version;
    version << result->get_version();
    std::ostringstream creation;
    creation << result->get_creation();
    std::ostringstream modification;
    modification << result->get_modification();

    return "HTTP/1.1 200 OK\nVersion: "+version.str()+"\nCreation: "+creation.str()+"\nModification: "+modification.str()+"\nContent-type: text/html\nConnection:Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>200 OK</title></head><body><h1>POST 200 OK</h1><p>Created "+result->get_name().c_str()+" with content: "+full_message+"</p></body></html>";
  }
  
  std::string handleDELETE(std::vector<std::string> tokens)
  {
    Node * rs = FileSystem::instance()->remove(tokens[1]);

    if (rs == NULL)
      return badrequest("Invalid path or non leaf node");
    
    return "HTTP/1.1 200 OK\nContent-type: text/html\nConnection: Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>200 OK</title></head><body><h1>DELETE 200 OK</h1><p>Node deleted.</p></body></html>";
  }

  std::string notImplemented()
  {
    return "HTTP/1.1 501 Not Implemented\nContent-type: text/html\nConnection: Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>501 Not Implemented</title></head><body><h1>501 Not Implemented</h1><p>What you are asking for is not implemented.</p></body></html>";
  }
}
