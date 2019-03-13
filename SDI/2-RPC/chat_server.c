#include <rpc/rpc.h>
#include "chat.h"
int* num;

char** hw_1_svc(void *a, struct svc_req *req) {
	static char msg[256];
	static char *p;

	printf("getting ready to return value\n");
	strcpy(msg, "Hello world3");
	p = msg;
	printf("Returning...\n");

	return(&p);
}

int* start_1_svc(char** msg, struct svc_req *req){
	FILE *file;
	static int* n;
	int lines = 0;
	char ch;
	n = 0;

	file = fopen("chat.txt", "r");
	if(file == NULL){
		printf("Criando arquivo...\n");
		file = fopen("chat.txt", "w+");
	}else{
		fclose(file);
		file = fopen("chat.txt", "a+");
	}
	fprintf(file, "%s se conectou!\n", *msg);
	fclose(file);

	file = fopen("chat.txt", "r");
	while(1){
		if(feof(file)) break;

		ch = fgetc(file);
		if (ch == '\n')
			lines++;
	}
	fclose(file);
	n = &lines;
	return n;
}

int* sendmessage_1_svc(char** msg, struct svc_req *req){
	FILE *file;
	static int* n;
	int a = 0;
	n = &a;

	file = fopen("chat.txt", "a");
	fprintf(file, "%s", *msg);
	fclose(file);
	return n;
}

char** getmessages_1_svc(int* line, struct svc_req *req){
	FILE *file;
	static char msg[256];
	static char *ret;
	int num = *line;
	char ch;

	file = fopen("chat.txt", "r");
	strcpy(msg, "");
	while(num--){
		while(ch = fgetc(file) ){
			if(ch == '\n')
				break;
		}
	}
	fgets(msg, sizeof(msg), file);
	fclose(file);

	ret = msg;
	return &ret;
}


int* pot_1_svc(int *n, struct svc_req *req){
	printf("Retornando o quadrado de %d\n", *n);
	*n = (*n) * (*n);
	return n;
}
