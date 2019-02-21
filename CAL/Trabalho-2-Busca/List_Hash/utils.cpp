#include "utils.hpp"

int hashing(string str)
{
    unsigned long hash = 5381;
    int c;

    for (int i = 0; i< (int)str.size(); i++){
		c=str[i];
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
    return hash%1000;
}


void swap(int* a, int* b){
	int* aux;
	aux = a;
	a = b;
	b = aux;
}

int randomNumber(int upper){
	srand(time(NULL));
	return rand() % upper;
}
