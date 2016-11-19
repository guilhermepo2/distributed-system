// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "SimpleDB.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class SimpleDBHandler : virtual public SimpleDBIf {
 public:
  SimpleDBHandler() {
    // Your initialization goes here
  }

  void get(File& _return, const std::string& url) {
    // Your implementation goes here
    printf("get\n");
  }

  void get_list(std::vector<File> & _return, const std::string& url) {
    // Your implementation goes here
    printf("get_list\n");
  }

  version_t add(const std::string& url, const std::string& content) {
    // Your implementation goes here
    printf("add\n");
  }

  version_t update(const std::string& url, const std::string& content) {
    // Your implementation goes here
    printf("update\n");
  }

  void delete_file(File& _return, const std::string& url) {
    // Your implementation goes here
    printf("delete_file\n");
  }

  version_t update_with_version(const std::string& url, const std::string& content, const version_t version) {
    // Your implementation goes here
    printf("update_with_version\n");
  }

  void delete_with_version(File& _return, const std::string& url, const version_t version) {
    // Your implementation goes here
    printf("delete_with_version\n");
  }

  void update_server() {
    // Your implementation goes here
    printf("update_server\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<SimpleDBHandler> handler(new SimpleDBHandler());
  shared_ptr<TProcessor> processor(new SimpleDBProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
