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

    def run(self, hostname = 'localhost', portNumber=8000):
        transport = TSocket.TSocket(hostname, portNumber)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocol(transport)

        client = SimpleDB.Client(protocol)

        transport.open()

        # TESTES
        '''
        client.add("/teste1/teste2/teste3", "conteudo")

        x = client.get("/teste1")
        print x
        x = client.get("/teste1/teste2")
        print x
        x = client.get("/teste1/teste2/teste3")
        print x

        '''


        #client.add("/please", "please")
        #client.add("/please/nerf", "please nerf")
        #client.add("/please/nerf/this", "POR FAVOR NUNCA TE PEDI NADA")
        #client.add("/please/nerf/mei", "AGORA")
        #client.add("/please/i/love/d-va", " carinha triste ")
        x = client.get_list("/please")
        print x
        x = client.get_list("/please/nerf")
        print x

        x = client.get("/please/nerf/mei")
        print x
        #x = client.update_with_version("/please/nerf/mei", "nerfa a mai ai pfvr", 0)

        #x = client.delete_file("/please/nerf/mei")
        print x





        '''
        print "adicionando /teste"
        x = client.add("/teste", "conteudo teste")
        print "adicionando /teste/a1"
        x2 = client.add("/teste/a1", "filho1")
        print "adicionando /teste/a2"
        x3 = client.add("/teste/a2", "filho2")
        print ""

        print "get /"
        f1 = client.get("/")
        print f1

        print "get /teste"
        f1 = client.get("teste")
        print f1

        print "get list /teste"
        f2 = client.get_list("teste")
        print f2

        print "update em /teste/a1"
        f3 = client.update("/teste/a1", "conteudo diferente")
        print f3

        print "delete /teste/a1"
        f4 = client.delete_file("/teste/a1")
        print f4

        print "get list /teste"
        f2 = client.get_list("teste")
        print f2

        print "update with version a2 com versao 0"
        f10 = client.update_with_version("/teste/a2","novo conteudo 2", 0)
        print f10
        print "update with version a2 com versao 0"
        f10 = client.update_with_version("/teste/a2","novo conteudo 3", 0)
        print f10

        print "get list /teste"
        f2 = client.get_list("teste")
        print f2

        print "delete a2 with version 0"
        f1 = client.delete_with_version("/teste/a2", 0)
        print f1

        print "get list /teste"
        f2 = client.get_list("teste")
        print f2

        print "delete a2 with version 1"
        f1 = client.delete_with_version("/teste/a2", 1)
        print f1

        print "get list /teste"
        f2 = client.get_list("teste")
        print f2
        '''

        transport.close()

if __name__ == '__main__':
    dbClient = DBClient()
    dbClient.run()
