CC=g++
CFLAGS=-g
TARGET:main.exe
LIBS=-lpthread -lws2_32
OBJS= network_utils.o           \
	  TcpClientDataBaseManager.o \
	  TcpclientServiceManager.o  \
	  TcpNewConnectionAcceptor.o  \
	  TcpServerController.o \
	  tcp_client.o \

main.exe:main.o ${OBJS}
	${CC} ${CFLAGS} ${OBJS} main.o -o main.exe ${LIBS}

#TCpClient.exe:TCpClient.o ${OBJS}
main.o:main.cpp
	${CC} ${CFLAGS} -c main.cpp -o main.o

TcpClientDataBaseManager.o:TcpClientDataBaseManager.cpp
	${CC} ${CFLAGS} -c TcpClientDataBaseManager.cpp -o TcpClientDataBaseManager.o

TcpclientServiceManager.o:TcpclientServiceManager.cpp
	${CC} ${CFLAGS} -c TcpclientServiceManager.cpp -o TcpclientServiceManager.o

TcpNewConnectionAcceptor.o:TcpNewConnectionAcceptor.cpp
	${CC} ${CFLAGS} -c TcpNewConnectionAcceptor.cpp -o TcpNewConnectionAcceptor.o

TcpServerController.o:TcpServerController.cpp
	${CC} ${CFLAGS} -c TcpServerController.cpp -o TcpServerController.o

network_utils.o:network_utils.cpp
	${CC} ${CFLAGS} -c network_utils.cpp -o network_utils.o

tcp_client.o:tcp_client.cpp
	${CC} ${CFLAGS} -c tcp_client.cpp -o tcp_client.o

CommandParser/libcli.a:
	(cd CommandParser; make)
clean:
	rm -f *.o
	rm -f *exe

#### In order to run TCPClient need to execute the following command "g++ .\TCpClient.cpp -g -o TCpClient.exe -lws2_32".