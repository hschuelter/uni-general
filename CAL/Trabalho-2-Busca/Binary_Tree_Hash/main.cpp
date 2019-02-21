
// g++ -Wall -std=c++11 -o btree_hash main.cpp utils.cpp && ./btree_hash
#include "utils.hpp"

int main(void){
    map < pair<string, string>, int > btree;
    vector <map < pair<string, string>, int >> TreeList;
    ifstream read;
    ofstream write;
    read.open("Entradas/entrada-5.txt");
    write.open("Saidas/saida-5.txt");

    int num;
    int key;
    string nome;
    string snome;

    auto Start = high_resolution_clock::now(); /* Cronometro de execucao total*/

    /* Inserindo elementos na lista de Btrees */
    read >> num;
    for(int j=0; j< 1000;j++){
        TreeList.push_back(btree);
    }
    auto iStart = high_resolution_clock::now(); /* Cronometro para a inserção*/
    for(int i =0; i < num; i++ ){
    	read >> key;
    	read >> nome;
    	read >> snome;
        //cout << hashStr(nome) << endl;
    	TreeList[hashStr(nome)].insert( pair< pair<string, string>, int > (pair<string, string> (nome, snome), key ));
    }
    auto iStop = high_resolution_clock::now(); /* Cronometro para a inserção*/


    /* Buscando elementos no map */
    read >> num;
    auto fStart = high_resolution_clock::now();

    for(int i =0; i < num; i++ ){
    	read >> nome;
    	read >> snome;

    	write << (TreeList[hashStr(nome)].find(pair<string, string> (nome, snome)) )->second << endl;
        //cout << (TreeList[hashStr(nome)].find(pair<string, string> (nome, snome)) )->second << endl;
    }
    auto fStop = high_resolution_clock::now(); /* Termina cronometro para a busca*/

    auto Stop = high_resolution_clock::now();

    auto iDur = duration_cast<microseconds>(iStop - iStart);
    auto fDur = duration_cast<microseconds>(fStop - fStart);
    auto Dur = duration_cast<microseconds>(Stop - Start);

    system("clear");
    cout << "==========" << endl;
    cout << "Finalizado!" << endl;
    cout << "\tTempo de insercao: " << iDur.count() << " (microssegundos)" << endl;
	cout << "\tTempo de busca: " << fDur.count() << " (microssegundos)" << endl << endl;
	cout << "\tTempo Total: " << Dur.count() << " (microssegundos)" << endl;
    cout << "==========" << endl;

    return 0;
}
