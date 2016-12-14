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

        print client.get_list("/doggos/shiberino")

        transport.close()

if __name__ == '__main__':
    dbClient = DBClient()
    dbClient.run()
