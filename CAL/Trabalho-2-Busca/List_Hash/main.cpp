// g++ -Wall -std=c++11 -o btree main.cpp utils.cpp && ./btree
#include "utils.hpp"

int main(void){
    v2d hashMap = v2d (1000, v1d(0));
    int hash;
    int num, key;
    string nome, snome;
    data temp;

    ifstream read;
    read.open("Entradas/entrada-5.txt");

    ofstream write;
    write.open("Saidas/saida-5.txt");
    //write.open("Saidas/teste.txt");

    auto Start = high_resolution_clock::now();

    read >> num;
    auto iStart = high_resolution_clock::now();
    for(int i = 0; i < num; i++ ){
    
        read >> key;
        read >> nome;
        read >> snome;

        temp = data(key, full_name(nome, snome));
        hash = hashing(temp.second.first);

        hashMap[ hash ].push_back(temp);
    }
    auto iStop = high_resolution_clock::now();


    auto fStart = high_resolution_clock::now();

    
    read >> num;
    for(int i =0; i < num; i++ ){
        read >> nome;
        read >> snome;

        hash = hashing(nome);

        for(int j = 0; j < (int) hashMap[hash].size(); j++){
            if( (nome == hashMap[hash][j].second.first) && (snome == hashMap[hash][j].second.second) )
                write << hashMap[hash][j].first << endl;
        }
    }
    

    auto fStop = high_resolution_clock::now();

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
    

    //for(int i = 0; i < (int) hashMap.size(); i++)
    //    write << "[" << i << "] Size: " << hashMap[i].size() << endl;
    



    return 0;
}
