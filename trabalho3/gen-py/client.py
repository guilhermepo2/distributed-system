import sys
import glob
sys.path.append('gen-py')
sys.path.append('/usr/local/include')
sys.path.append('/usr/local/lib')

from simpledb import SimpleDB
from simpledb.ttypes import File

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

class DBClient:
    def __init__(self):
        pass

    def run(self, hostname = 'localhost', portNumber=9090):
        transport = TSocket.TSocket(hostname, portNumber)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocol(transport)

        client = SimpleDB.Client(protocol)

        transport.open()

        # TESTES

        x = client.add("/teste", "conteudo teste")
        x2 = client.add("/teste/a1", "filho1")
        x3 = client.add("/teste/a2", "filho2")


        f1 = client.get("/")
        print f1

        f1 = client.get("teste")
        print f1

        f2 = client.get_list("teste")
        print f2

        f3 = client.update("/teste/a1", "conteudo diferente")
        print f3

        f2 = client.get_list("teste")
        print f2

        print "DELETANDO"
        f4 = client.delete_file("/teste/a1")
        print f4

        f2 = client.get_list("teste")
        print f2

        print "update with version"
        f10 = client.update_with_version("/teste/a2","novo conteudo 2", 0)
        print f10
        f10 = client.update_with_version("/teste/a2","novo conteudo 3", 0)
        print f10

        f2 = client.get_list("teste")
        print f2
        # f2 = client.get_list("url")
        # f3 = client.add("url", "content")
        # f4 = client.update("url", "content")
        # f5 = client.delete_file("url")
        # f6 = client.update_with_version("url","content",0)
        # f7 = client.delete_with_version("url", 0)


        f1 = client.delete_with_version("/teste/a2", 0)
        print f1

        f2 = client.get_list("teste")
        print f2


        f1 = client.delete_with_version("/teste/a2", 1)
        print f1

        f2 = client.get_list("teste")
        print f2

        transport.close()

if __name__ == '__main__':
    dbClient = DBClient()
    dbClient.run()
