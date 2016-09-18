#ifndef HTTP_HEADER
#define HTTP_HEADER

#include <iostream>
#include <vector>
#include "../file_system/file_system.hpp"

namespace HTTP
{
  void initFileSystem();                                    // EM TESE OK
  std::string handleGET(std::vector<std::string> tokens);   // OK
  std::string handleHEAD(std::vector<std::string> tokens);  // OK
  std::string handlePUT();                                  // PROXIMO
  std::string handlePOST();
  std::string handleDELETE();
  std::string notImplemented();                             // OK
}

#endif
