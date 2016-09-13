#ifndef HTTP_HEADER
#define HTTP_HEADER

namespace HTTP
{
  void handleGET(std::vector<std::string> tokens);
  void handleHEAD();
  void handlePUT();
  void handleDELETE();
  void handleTRACE();
  void handleOPTIONS();
  void handleCONNECT();
  void handlePATCH();
}

#endif
