#include "http.hpp"
#include <sstream>

namespace HTTP
{
  FileSystem * fs = NULL;

  void initFileSystem()
  {
    if (fs == NULL)
      fs = new FileSystem;

    fs->insert("/obladi/oblada");
  }
  
  std::string notfound(std::string content)
  {
    std::string message = "HTTP/1.1 404 NOT FOUND\nContent-type: text/html\nConnection: Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>404 Not Found</title></head><body><h1>404 Not Found</h1><p>The path " + content + " is invalid or does not exist</p></body></html>";

    return message;
  }
  
  std::string handleGET(std::vector<std::string> tokens)
  { 
    Node * result = fs->search(tokens[1]);
    
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
    Node * result = fs->search(tokens[1]);
    
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
  
  std::string handlePUT()
  {
    return "HTTP/1.1 200 OK\nContent-type: text/html\nConnection: Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>200 OK</title></head><body><h1>PUT 200 OK</h1><p>It Works.</p></body></html>";
  }

  std::string handlePOST()
  {
    return "HTTP/1.1 200 OK\nContent-type: text/html\nConnection: Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>200 OK</title></head><body><h1>POST 200 OK</h1><p>It Works.</p></body></html>";
  }
  
  std::string handleDELETE()
  {
    return "HTTP/1.1 200 OK\nContent-type: text/html\nConnection: Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>200 OK</title></head><body><h1>DELETE 200 OK</h1><p>It Works.</p></body></html>";
  }

  std::string notImplemented()
  {
    return "HTTP/1.1 501 Not Implemented\nContent-type: text/html\nConnection: Closed\r\n\r\n<!DOCTYPE HTML PUBLIC><html><head><title>501 Not Implemented</title></head><body><h1>501 Not Implemented</h1><p>What you are asking for is not implemented.</p></body></html>";
  }
}
