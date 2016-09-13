#include "http.hpp"

namespace HTTP
{
  void handleGET(std::vector<std::string> tokens)
  {
    std::cout << "GET" << std::endl;
  }
  
  void handleHEAD()
  {
    std::cout << "HEAD" << std::endl;
  }
  
  void handlePUT()
  {
    std::cout << "PUT" << std::endl;
  }

  void handlePOST()
  {
    std::cout << "POST" << std::endl;
  }
  
  void handleDELETE()
  {
    std::cout << "DELETE" << std::endl;
  }
  
  void handleTRACE()
  {
    std::cout << "TRACE" << std::endl;
  }
  
  void handleOPTIONS()
  {
    std::cout << "OPTIONS" << std::endl;
  }
  
  void handleCONNECT()
  {
    std::cout << "CONNECT" << std::endl;
  }
  
  void handlePATCH()
  {
    std::cout << "PATCH" << std::endl;
  }
}
