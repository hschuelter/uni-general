all: client server

chat.h: chat.x
		rpcgen chat.x

chat_svc.c chat_clnt.c main.c: chat.h

client: main.o chat_clnt.o
	cc -o client main.o chat_clnt.o  -lnsl -pthread

server: chat_server.o chat_svc.o
	cc -o server chat_server.o chat_svc.o -lnsl

.PHONY: clean

clean:
	-rm *.o
	-rm client*
	-rm server*
	-rm chat.h
	-rm chat_clnt.c
	-rm chat_svc.c
