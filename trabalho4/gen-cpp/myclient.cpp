#include "SimpleDB.h"  // As an example

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

#include <iostream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int main(int argc, char **argv) {
  try {
    std::cout << "oi" << std::endl;
    boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    SimpleDBClient client(protocol);
    transport->open();
    File f;
    client.get(f, "teste");
    transport->close();
  } catch(apache::thrift::transport::TTransportException e) {
    std::cout << "server is dead." << std::endl;
  }
  return 0;
}
