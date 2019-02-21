#include "utils.hpp"

void find(map<pair<string, string>, int > mapping, string nome, string snome){
	map < pair<string, string>, int > :: iterator it;
	it = mapping.find( pair<string, string> (nome, snome) );

	cout << it->second << endl;
}

void printMap(map<pair<string, string>, int > mapping){
    map <pair<string, string>, int > :: iterator it;

    cout << "=====" << endl << endl;
    for(it = mapping.begin(); it != mapping.end(); it++){
    	cout << "  Key: " << it->second << endl;
    	cout << " Nome: " << it->first.first << endl;
    	cout << "SNome: " << it->first.second << endl;
    	cout << "---" << endl;
    }
    cout << "=====" << endl;
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

int hashStr(string str)
{
    unsigned long hash = 5381;
    int c;

    for (int i = 0; i< (int)str.size(); i++){
		c=str[i];
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
    return hash%1000;
}
