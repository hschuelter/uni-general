// g++ -Wall -std=c++11 -o lin_search main.cpp utils.cpp && ./lin_search
#include "utils.hpp"

int main(void){
    vector < tuple < string,string,int > > vetorBL;
    ifstream read;
    ofstream write;
    read.open("Entradas/entrada-5.txt");
    write.open("Saidas/saida-5.txt");

    int num;
    int key;
    string nome;
    string snome;

    auto Start = high_resolution_clock::now(); /* Cronometro de execucao total*/

    /* Inserindo elementos */
    read >> num;
    auto iStart = high_resolution_clock::now(); /* Cronometro para a inserção*/
    for(int i =0; i < num; i++ ){
    	read >> key;
    	read >> nome;
    	read >> snome;

        //pair <pair<string,string>,int> par ((nome,snome),key);
        tuple <string,string,int> t (nome,snome,key);
        vetorBL.push_back(t);
        //cout << get<2> (vetorBL[i]) << endl;

    }
    auto iStop = high_resolution_clock::now(); /* Cronometro para a inserção*/


    /* Buscando elementos no map */
    read >> num;
    auto fStart = high_resolution_clock::now();

    for(int i =0; i < num; i++ ){
    	read >> nome;
    	read >> snome;

        for(int j=0;j<(int)vetorBL.size();j++){

            if(get<0> (vetorBL[j])==nome && get<1> (vetorBL[j])==snome){
                write << get<2> (vetorBL[j]) << endl;
                //cout << get<2> (vetorBL[j]) << endl;
                break;
            }
        }


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
