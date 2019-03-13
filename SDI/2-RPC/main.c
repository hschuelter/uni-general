#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <rpc/rpc.h>
#include "chat.h"

void writeMessage(char * name);
int receiveMessage(int comeco);
void* thread_func(void* arg);

CLIENT* cl;
pthread_t threads[1];
int line;
int loop = 1;

int main (int argc, char *argv[]) {
	system("clear");
	char** p;
	char* s = (char*) malloc(sizeof(char) * 256);
	int* n;
	int a;

	if (argc != 2) {
		printf("Error: insert client hostname\n");
		exit(1);
	}

	cl = clnt_create(argv[1], HELLO_WORLD_PROG, HELLO_WOLRD_VERS, "tcp");
	if (cl == NULL) {
		clnt_pcreateerror(argv[1]);
		exit(1);
	}

	printf("Digite seu nome: ");
	scanf("%s", s);

	n = start_1(&s, cl);
	line = *n;
	pthread_create(&(threads[0]), NULL, thread_func, NULL);
	writeMessage(s);

	return 0;
}

void writeMessage(char* name){
	system("clear");
	size_t size = 256;
	char* msg = (char*) malloc(sizeof(char)*256);
	char* pack = (char*) malloc(sizeof(char)*256);

	getline(&msg, &size, stdin);
	printf("Bem-vindo(a) %s!\n", name);

	while(1){
		fgets ( msg, 256, stdin );

		strcpy(pack, name);
		strcat(pack, ": ");
		strcat(pack, msg);
		printf("%s", pack);
		sendmessage_1(&pack, cl);
		receiveMessage(line);
		printf(">>\n");

		if(strcmp(msg, ".quit\n") == 0){
			loop = 0;
			break;
		}
	}
	return;
}

int receiveMessage(int comeco){
	system("clear");
	char** msg;
	int *n;

	comeco--;
	while(1){
		n = &(comeco);
		msg = getmessages_1(n, cl);
		if(strcmp(*msg, "") == 0){
			break;
		}
		printf("%s", *msg);
		comeco++;
	}
}

void* thread_func(void* arg){
	while(loop){
		receiveMessage(line);
		printf(">>\n");
		sleep(3);
	}
}
