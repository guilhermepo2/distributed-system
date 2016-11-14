dependencies:
	g++ -std=c++11 -c common/tokenizer.cpp -o common/tokenizer.o;
	g++ -std=c++11 -c file_system/node.cpp -o file_system/node.o;
	g++ -std=c++11 -c file_system/file_system.cpp -o file_system/file_system.o;
	g++ -std=c++11 -c http/http.cpp -o http/http.o

simpledb:
	make dependencies;
	g++ -Wall -std=c++11 -I/usr/local/include/ -c SimpleDB.cpp -o simpledb.o;
	g++ -Wall -std=c++11 -I/usr/local/include -c SimpleDB_server.cpp -o simpledb_server.o;
	g++ -Wall -std=c++11 -I/usr/local/include -c services_constants.cpp -o constants.o;
	g++ -Wall -std=c++11 -I/usr/local/include -c services_types.cpp -o types.o

linkdb:
	g++ -Wall -std=c++11 -L/usr/local/lib common/tokenizer.o file_system/node.o file_system/file_system.o http/http.o simpledb.o simpledb_server.o constants.o types.o -o MEUBELOSERVER -lthrift

client:
	g++ -Wall -std=c++11 -I/usr/local/include/thrift -I/usr/local/include -c myclient.cpp -o client.o

linkclient:
	g++ -Wall -std=c++11 -L/usr/local/lib client.o simpledb.o constants.o types.o -o MEUBELOCLIENT -lthrift

all:
	make simpledb;
	make linkdb;
	make client;
	make linkclient
