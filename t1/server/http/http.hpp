#ifndef HTTP_HEADER
#define HTTP_HEADER

#include <iostream>
#include <vector>
#include "../file_system/file_system.hpp"

namespace HTTP
{
  void checkFSRoot();
  std::string handleGET(std::vector<std::string> tokens);   // OK
  std::string handleHEAD(std::vector<std::string> tokens);  // OK
  std::string handlePUT(std::vector<std::string> tokens);   // OK
  std::string handlePOST(std::vector<std::string> tokens);  // OK (em tese)
  // o ponteiro da raiz as vezes se perde aleatoriamente, a mesma requisicao feita varias vezes no mesmo contexto gera resultados diferentes
  std::string handleDELETE(std::vector<std::string> tokens); // OK
  std::string notImplemented();                             // OK
}

#endif
