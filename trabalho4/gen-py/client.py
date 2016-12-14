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

        # Teses para o protocolo de 2-step commit
        # Inserindo os nos necessarios
        '''
        Doggos -> Gabe      -> bork
                            -> keep-borking
               -> Pupper    -> sleep-tight
                            -> study-test
               -> Shiberino -> wows
                            -> such-protocol
                            -> very-coding
        '''

        # Testando o 2 step commit criando uma url grande de uma vez
        # ok
        client.add_tw("/doggos/love/distributed/systems", "right?")
        print client.get("/doggos/love/distributed/systems")
        print "Se o arquivo nao esta vazio e porque a insercao deu certo."


        client.add_tw("/doggos/gabe", "Gabe, The Dog")
        client.add_tw("/doggos/gabe/bork", "gabe can bork")
        client.add_tw("/doggos/gabe/keep-borking", "gabe can bork even more")

        client.add_tw("/doggos/pupper", "Pupper Pupperino")
        client.add_tw("/doggos/pupper/sleep-tight", "to be blessed with cozy restful sleeps")
        client.add_tw("/doggos/pupper/study-test", "grant you good grades for the rest of your life")

        client.add_tw("/doggos/shiberino", "Mr. Shiba Shiber")
        client.add_tw("/doggos/shiberino/wows", "WOW")
        client.add_tw("/doggos/shiberino/such-protocol", "SUCH PROTOCOL VERY COMMIT")
        client.add_tw("/doggos/shiberino/very-coding", "We all love shibas")

        # Dando get em todo mundo pra ver se ta certinho
        a = client.get("/doggos/gabe")
        b = client.get("/doggos/gabe/bork")
        c = client.get("/doggos/gabe/keep-borking")
        if(a.name == ""):
            print "Hm? Gabe is not here :("
        else:
            print "We have a Doggo! His name is {0} AKA {1}, he can {2}({3}) and {4}({5})".format(a.name, a.content, b.name, b.content, c.name, c.content)

        a = client.get("/doggos/pupper/")
        b = client.get("/doggos/pupper/sleep-tight/")
        c = client.get("/doggos/pupper/study-test/")
        if(a.name == ""):
            print "Hm? Pupper is not here :("
        else:
            print "We have a Doggo! His name is {0} AKA {1}, he can {2}({3}) and {4}({5})".format(a.name, a.content, b.name, b.content, c.name, c.content)

        a = client.get("/doggos/shiberino/")
        b = client.get("/doggos/shiberino/wows")
        c = client.get("/doggos/shiberino/such-protocol")
        d = client.get("/doggos/shiberino/very-coding")
        if(a.name == ""):
            print "Hm? Shiberino is not here :("
        else:
            print "We have a Doggo! His name is {0} AKA {1}, he can {2}({3}), {4}({5}) and {6}({7})".format(a.name, a.content, b.name, b.content, c.name, c.content, d.name, d.content)


        # testando o delete_file_tw    


        transport.close()

if __name__ == '__main__':
    dbClient = DBClient()
    dbClient.run()
