#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;

string estadoInicial;
vector <string> estados;
vector <string> estadosFinais;
vector <char> alfabeto;
vector < vector < vector <string> > > transicoes;
vector < vector <string> > transicoesAFD;
vector < vector <string> > automatoMinimo;
vector <string> estadosN;



bool compare(string a, string b) {
    if(a.size() != b.size())
        return a.size()<b.size();
    else
        return a < b;
 }

int findState(string a){
    int i=0;
    for(i = 0; i< (int) estados.size(); i++){
        //cout << "Comparando >" << a << "< Com >" << estados[i] << "<" << endl;
        if (a.compare(estados[i])==0){
            return i;
        }
    }
    return -1;
}

int findSymbol(char a){
    int i;
    for(i = 0; i< (int) alfabeto.size() ; i++){
        //cout << "Comparando >" << a << "< Com >" << alfabeto[i] << "<" << endl;
        if(a==alfabeto[i]){
        return i;
        }
    }
    return -1;
}

void trans(){
    // Cria os novos estados
    estadosN = estados;
    string e1,e2,e3,en;
    string aux;
    int i,j,k,t=0;
    int pos;
    int flagRepeticao = 0;

    /*
    for(i=0;i<estados.size();i++){
        e1=estados[i];
        //cout << "e1: " << e1 << endl;
        for(k = i+1; k < estados.size(); k++){
            en = e1;
            e2 = estadosN[k];
            en = en+e2;

            for(t=0; t<estadosN.size(); t++){
                if(estadosN[t].find(en) != -1) flagRepeticao = 1;
            }
            if(flagRepeticao == 0) estadosN.push_back(en);
            flagRepeticao = 0;

            for(j=k+1;j<estados.size()  &&  i < j;j++){
                e3 = estadosN[j];
                en += e3;
                estadosN.push_back(en);
            }
        }
    }*/

    for(i=0; i< (int) estadosN.size(); i++){
        e1 = estadosN[i];
        cout << "i: " << e1 << endl;
        for(j=0; j<estados.size(); j++){
            if(i == j) continue;
            flagRepeticao = 0;
            e1 = estadosN[i];
            e2 = estados[j];
            cout << "\tj: " << e2 << endl;
            e1 += e2;

            for(k=0; k<estadosN.size(); k++){
                if(estadosN[k].compare(e1) == 0) flagRepeticao = 1;
            }

            if(flagRepeticao == 0) estadosN.push_back(e1);
        }
    }

    //sort(estadosN.begin(), estadosN.end(),compare);
    for (i=0;i<estadosN.size();i++){
        cout << "estadosN[" << i << "]: " << estadosN[i] << endl;
    }


    // VERSÃO 1 DE ACHAR ESTADOS DENTRO DE ESTADOS
    /*
    for(i=0;i<estadosN.size();i++){
        e1=estadosN[i];
        cout << "estado: " << e1 << endl;
        for(j=0;j<e1.size();j++){
            e2=e1[j];
            if(e2=="q"){
                k1=0;
                for(k=1;k<(e1.size()-j);k++){
                    e3=e1[j+k];
                    if(e3=="q"){
                        break;
                    }
                    e2=e2+e3;
                    k1++;
                }
            j=j+k1;
            //find trans e2 TESTES
            cout << "find[e2.1]: >" << e2 << "<" << endl;
            //estados.find
            }
            else{
            //find e2 TESTES
            cout << "find[e2.2]: >" << e2 << "<" << endl;
            }

            }
        cout << "fim de estado" << endl;
        }
        */

        // VERSÃO 2 DE ACHAR ESTADOS DENTRO DE ESTADOS

    /*
       string t1,t2;
        cout << "TESTE 2 ME MATA.EXE" << endl << endl;

        for(i=0;i<estadosN.size();i++){
            e1=estadosN[i];
            cout << "estado: " << e1 << endl;
            for(j=0;j<estados.size();j++){
                e2=estados[j];
                if(e1.find(e2)!=-1){
                    cout << "find[e2v2]: >" << e2 << "<" << endl;
                }
            }
            cout << "fim de estado" << endl;
        }

    */








}

void inicializaAutomato(string a){
    ifstream read;
    string line;
    char ch;
    int i,j, cont=0;

    read.open(a.c_str());

    /* ADICIONANDO O ESTADO INICIAL */

    getline(read, line);
    estadoInicial = line;
    //cout << estadoInicial << endl;

    /* ADICIONANDO OS ESTADOS NO VECTOR DE ESTADOS */
    getline(read, line, ' ');

    for (i=0; i<line.size(); i++){
        ch = line[i];
        cont = cont*10 + (ch - '0');
    }

    for(i = 0; i<cont; i++){
        if(i < cont -1){
            getline(read, line,' ');
            estados.push_back(line);
        }
        else{
            getline(read, line,'\n');
            estados.push_back(line);
        }
    }

    //for(i=0; i<estados.size(); i++) cout << estados[i];
    //cout << endl;

    /* ADICIONANDOS OS ESTADOS FINAIS NO VECTOR estadosFinais */

    getline(read, line, ' ');
    cont = 0;
    for (i=0; i<line.size(); i++){
        ch = line[i];
        cont = cont*10 + (ch - '0');
    }

    for(i = 0; i<cont; i++){
        if(i < cont -1){
            getline(read, line,' ');
            estadosFinais.push_back(line);
        }
        else{
            getline(read, line,'\n');
            estadosFinais.push_back(line);
        }
    }

    //for(i=0; i<estadosFinais.size(); i++) cout << estadosFinais[i];
    //cout << endl;

    /* ADICIONANDO OS SIMBOLOS DO ALFABETO NO VECTOR alfabeto */

    getline(read, line, ' ');
    cont = 0;
    for (i=0; i<line.size(); i++){
        ch = line[i];
        cont = cont*10 + (ch - '0');
    }
    for(i = 0; i<cont; i++){
        if(i < cont -1){
            getline(read, line,' ');
            alfabeto.push_back(line[0]);
        }
        else{
            getline(read, line,'\n');
            alfabeto.push_back(line[0]);
        }
    }

    //for(i=0; i<alfabeto.size(); i++) cout << alfabeto[i];
    //cout << endl;


    /* ADICIONANDO AS TRANSICOES NO VECTOR transicoes */

    vector <string> vetorAux;
    vector < vector <string> > matrizAux;

    int t;
    string auxiliar = "-";
    read >> t;
    read.get(ch);
    /*for (i=0; i<line.size(); i++){
        ch = line[i];
        cont = cont*10 + (ch - '0');
    }
    */

    for(i = 0; i < (int)estados.size(); i++){
        for(j=0; j < (int)alfabeto.size(); j++){
            vetorAux.push_back(auxiliar);
            matrizAux.push_back(vetorAux);
            vetorAux.clear();
        }
        transicoes.push_back(matrizAux);
        matrizAux.clear();
    }



    string org,simb,dest;
    int l=-2,c=-2;
    for(i=0; i< t;i++){
        getline(read,org,' ');
        getline(read,simb,' ');
        getline(read,dest,'\n');
        //cout << org << " " << simb[0] << " " << dest << endl;
        l=findState(org);
        c=findSymbol(simb[0]);
        //cout << l << " " << c << endl;

        if(transicoes[l][c][0] == "-")  transicoes[l][c][0] = dest;
        else    transicoes[l][c].push_back(dest);

    }

    printf("\nTransicoes:\n");
    printf("\t");
    for(i = 0; i<alfabeto.size(); i++)  printf("%c\t\t", alfabeto[i]);
    printf("\n");
    int k;
    for(i = 0; i< estados.size(); i++){
        cout << estados[i] << "\t";
        for(j = 0; j<alfabeto.size(); j++){
            for(k = 0; k < transicoes[i][j].size(); k++){
                if(k == transicoes[i][j].size()-1) {
                  cout << transicoes[i][j][k];
                }else {
                  cout << transicoes[i][j][k] << ",";
                }
            }
        printf("\t\t");
        }
        cout << endl;
    }
}

void verificaPalavra(){

    int i,j;
    int npalavras;
    cout << endl << "Quantas palavras deseja verificar? ";
    cin >> npalavras;
    cout << endl;

    for (j=0;j<npalavras;j++){
        int verificador;
        string palavra;
        cout << endl << "(" << j+1 << ")" <<"Digite a palavra que deseja verificar: ";
        cin >> palavra;
        cout << endl;

        int posState, posSymbol;
        char ch;
        string state;

        state = estados[0];

        for(i=0; i < palavra.size(); i++){
            ch = palavra[i];

            posState = findState(state);
            posSymbol = findSymbol(ch);

            cout << "Iteracao: " << i << endl;
            cout << estados[posState] << " -" << alfabeto[posSymbol] << "-> " << transicoes[posState][posSymbol][0] << endl << endl;


            state = transicoes[posState][posSymbol][0];

            if(transicoes[posState][posSymbol][0].compare("-")==0){
                verificador = -1;
                break;
            }
        }
        if(verificador != -1){
            for(i=0; i < estadosFinais.size(); i++){
                if(!state.compare(estadosFinais[i])){
                    verificador = 1;
                    cout << ">" << estadosFinais[i] << "<" << endl << ">" << state << "<" << endl;
                }else{
                    verificador = 0;
                }
            }
        }
        /*for(i=0; i < estadosFinais.size(); i++){
            cout << ">" << estadosFinais[i] << "<" << endl << ">" << state << "<" << endl;
        }*/
        if(verificador == 1) cout << "Palavra aceita!" << endl;
        if(verificador == 0) cout << "Palavra rejeitada!" << endl;
        if(verificador == -1) cout << "Palavra rejeitada! (Automato morreu por indefinicao)" << endl;

    }
    trans();
}

void minimizaAutomato(string nome){
    vector <string> vetorMinimizacao;
    vector <string> vetorFinais;
    vector <string> vetorAux;
    vector <int> verificaInutil;
    string alfa[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L","M","N","O","P","Q","R","S","T","U","V","W", "X", "Y", "Z"};
    string auxLinha, auxColuna, eLinha, eColuna, eLinhaRes, eColunaRes, eForm,eFinalForm;
    string eLinhaResRes, eColunaResRes;
    string linhaMini, colunaMini;
    string transicaoVazia = "qV";
    string e1;
    string aux;



    int flagVazio = 0;
    int flagLinha = 0, flagColuna = 0;
    int flagRepeticao = 0;
    int flagMinimizado = 0;
    int i, j, k, l, m, n;
    int res1, res2;


    /* INICIALIZANDO A TABELA MINIMA */

    cout << endl;
    vetorAux.clear();
    for(i=0; i< (int) estados.size(); i++){
        for(j=0 ; j < (int) alfabeto.size(); j++){
            if(transicoes[i][j][0] == "-"){
                flagVazio = 1;
                vetorAux.push_back(transicaoVazia);
            }
            else vetorAux.push_back(transicoes[i][j][0]);
        }
        transicoesAFD.push_back(vetorAux);
        vetorAux.clear();
    }

    if(flagVazio == 1){
        estados.push_back(transicaoVazia);
        vetorAux.clear();
        for(i=0; i < (int) alfabeto.size(); i++){
            vetorAux.push_back(transicaoVazia);
        }
        transicoesAFD.push_back(vetorAux);
        vetorAux.clear();
    }

    printf("\nTransicoes(AFD):\n");
    printf("\t");
    for(i = 0; i< (int) alfabeto.size(); i++)  printf("%c\t\t", alfabeto[i]);
    printf("\n");
    for(i = 0; i< (int) estados.size(); i++){
        cout << estados[i] << "\t";
        for(j = 0; j< (int) alfabeto.size(); j++){
            cout << transicoesAFD[i][j];
            printf("\t\t");
        }
        cout << endl;
    }

    vector <string> tabelaMinimizacao[estados.size()][estados.size()];


    for(i = 0; i < (int) estados.size(); i++){
        auxLinha = estados[i];
        for (j=0; j < (int) estados.size() && i >= j; j++){
            auxColuna = estados[j];
            flagLinha = 0;
            flagColuna = 0;

            if(i == j)  tabelaMinimizacao[i][j].push_back("O");
            else{
                for(k = 0; k < (int) estadosFinais.size(); k++){
                    if(!auxLinha.compare(estadosFinais[k]) && flagLinha == 0)   flagLinha = 1;
                    if(!auxColuna.compare(estadosFinais[k]) && flagColuna == 0) flagColuna = 1;
                }

                if(flagLinha == flagColuna) tabelaMinimizacao[i][j].push_back("-");
                else                        tabelaMinimizacao[i][j].push_back("X");
            }
        }
    }

    printf("\n\nTabela Minima:\n");
    printf("\n");
    for(i = 0; i< (int) estados.size(); i++){
        cout << estados[i] << "\t";
        for(j = 0; j< (int) estados.size() && i >= j; j++){
            cout << tabelaMinimizacao[i][j][0];
            printf("\t");
        }
        cout << endl ;
    }
    printf("\t");
    for(i = 0; i< (int) estados.size(); i++)  cout << estados[i] << "\t";


    /* ALGORITMO DE MINIMIZAÇÃO */

    for(i=0; i < (int) estados.size(); i++){
        for(j=0; j< (int) estados.size() && i >= j; j++){
            if(tabelaMinimizacao[i][j][0] == "-"){
                eLinha = estados[i];
                eColuna = estados[j];
                eForm = eLinha + eColuna;

                for(k=0; k < (int) alfabeto.size(); k++){
                    eLinhaRes = transicoesAFD[findState(eLinha)][k];
                    eColunaRes = transicoesAFD[findState(eColuna)][k];
                    flagRepeticao = 0;

                    if(findState(eLinhaRes) >= findState(eColunaRes)){
                        eFinalForm = eLinhaRes + eColunaRes;
                    }
                    else if(findState(eColunaRes) > findState(eLinhaRes)){
                        eFinalForm = eColunaRes + eLinhaRes;
                        aux = eColunaRes;
                        eColunaRes = eLinhaRes;
                        eLinhaRes = aux;
                    }

                    if(eForm == eFinalForm){}
                    else if(tabelaMinimizacao[findState(eLinha)][findState(eColuna)][0] == "-") tabelaMinimizacao[findState(eLinha)][findState(eColuna)][0] = eFinalForm;
                    else if(tabelaMinimizacao[findState(eLinha)][findState(eColuna)][0] != "-") {
                        flagRepeticao = 0;
                        for(l=0; l< (int) tabelaMinimizacao[findState(eLinha)][findState(eColuna)].size(); l++){
                            if(eFinalForm == tabelaMinimizacao[findState(eLinha)][findState(eColuna)][l]){
                                flagRepeticao = 1;
                            }
                        }
                        if(flagRepeticao == 0){
                            tabelaMinimizacao[findState(eLinha)][findState(eColuna)].push_back(eFinalForm);
                        }
                    }

                    if(eLinhaRes == eColunaRes) tabelaMinimizacao[i][j].erase(tabelaMinimizacao[i][j].begin()+k);

                }
            }
        }
    }

    /* VERIFICA SE ALGUM ELEMENTO DA TABELA MINIMA DEPENDE DE UM ESTADO "q0q0" */

    for(i=0; i < (int) estados.size(); i++){
        for(j=0; j < (int) estados.size(); j++){
            if( (int) tabelaMinimizacao[i][j].size() == 0) tabelaMinimizacao[i][j].push_back("O");
        }
    }



    flagMinimizado = 0;

    while(flagMinimizado == 0){
        printf("\n\nTabela Minima Secundaria:\n");
        printf("\n");
        for(i = 0; i< (int) estados.size(); i++){
            cout << estados[i] << "\t";
            for(j = 0; j< (int) estados.size() && i >= j; j++){
                for(k=0; k< (int) tabelaMinimizacao[i][j].size(); k++){
                    if(k ==  (int) tabelaMinimizacao[i][j].size()-1)   cout << tabelaMinimizacao[i][j][k];
                    else cout << tabelaMinimizacao[i][j][k] << ",";

                }
                printf("\t\t");
            }
            cout << endl;
        }
        printf("\t");
        for(i = 0; i< (int) estados.size(); i++)  cout << estados[i] << "\t\t";


        cout << endl << endl;

        flagMinimizado = 1;

        for(i=0; i< (int) estados.size(); i++){
            for(j = 0; j< (int) estados.size() && i > j; j++){
                for(m=0; m< (int) tabelaMinimizacao[i][j].size(); m++){

                    if(tabelaMinimizacao[i][j][m] != "X" && tabelaMinimizacao[i][j][m] != "O"){

                        for(k=0; k < (int) tabelaMinimizacao[i][j].size();k++){
                            for(l = (int) estados.size() -1; l >= 0; l--){
                                if(tabelaMinimizacao[i][j][k].find(estados[l]) == 0){
                                    eLinhaRes = estados[l];
                                }
                                else if( (int) tabelaMinimizacao[i][j][k].find(estados[l]) != -1){
                                    eColunaRes = estados[l];
                                }
                            }
                            eLinha = estados[i];
                            eColuna = estados[j];

                            cout << endl << endl;
                            cout << "~~~~~~~~~~~~" << endl;
                            cout <<  "i: " << eLinha << "||j: " << eColuna << endl;
                            cout << "k: " << k << endl;
                            cout << "tabelaMinimizacao[i][j][k]: " << tabelaMinimizacao[i][j][k] << endl;
                            cout << "eLinhaRes: " << eLinhaRes << endl;
                            cout << "eColunaRes: " << eColunaRes << endl;
                            cout << ">" << tabelaMinimizacao[i][j][k] << "<";



                            if(tabelaMinimizacao[findState(eLinhaRes)][findState(eColunaRes)][k] == "X"){
                                cout << endl << "entrei no if 1";
                                tabelaMinimizacao[i][j].clear();
                                tabelaMinimizacao[i][j].push_back("X");
                                cout << " X" << endl;

                            }
                            else if(tabelaMinimizacao[findState(eLinhaRes)][findState(eColunaRes)][k] == "O"){
                                cout << endl << "entrei no else if";
                                tabelaMinimizacao[i][j][k] = "O";
                                cout << " O" << endl;
                            }


                            else{
                                cout << endl << "entrei no else";
                                for(l = (int) estados.size() -1; l >= 0; l--){
                                    if(tabelaMinimizacao[findState(eLinhaRes)][findState(eColunaRes)][k].find(estados[l]) == 0){
                                        eLinhaResRes = estados[l];
                                    }
                                    else if( (int) tabelaMinimizacao[findState(eLinhaRes)][findState(eColunaRes)][k].find(estados[l]) != -1){
                                        eColunaResRes = estados[l];
                                        break;
                                    }
                                }
                                res1 = findState(eLinhaResRes);
                                res2 = findState(eColunaResRes);

                                cout << endl << endl;
                                cout << "------------" << endl ;
                                cout <<  "i: " << eLinhaRes << "||j: " << eColunaRes << endl;
                                cout << "k: " << k << endl;
                                cout << "tabelaMinimizacao[res1][res2][k]: " << tabelaMinimizacao[findState(eLinhaRes)][findState(eColunaRes)][k] << endl;
                                cout << "findState(eLinhaResRes): " << res1 << endl;
                                cout << "findState(eColunaResRes): " << res2 << endl;
                                cout << "eLinhaResRes: " << estados[res1] << endl;
                                cout << "eColunaResRes: " << estados[res2] << endl;
                                cout << ">" << tabelaMinimizacao[res1][res2][k] << "<" << endl;


                                for(n = 0; n < (int) tabelaMinimizacao[res1][res2].size(); n++){

                                    for(l = (int) estados.size() -1; l >= 0; l--){
                                        if(tabelaMinimizacao[findState(eLinhaRes)][findState(eColunaRes)][n].find(estados[l]) == 0){
                                            eLinhaResRes = estados[l];
                                        }
                                        else if( (int) tabelaMinimizacao[findState(eLinhaRes)][findState(eColunaRes)][n].find(estados[l]) != -1){
                                            eColunaResRes = estados[l];
                                        }
                                    }

                                    res1 = findState(eLinhaResRes);
                                    res2 = findState(eColunaResRes);
                                    cout << "findState(eLinhaResRes): " << res1 << endl;
                                    cout << "findState(eColunaResRes): " << res2 << endl;


                                    if(tabelaMinimizacao[res1][res2][n] == "X"){
                                        cout << "CHUTEI UM MENDIGO PESSOAL ;]" << endl;
                                        tabelaMinimizacao[i][j].clear();
                                        tabelaMinimizacao[i][j].push_back("X");
                                    }
                                    else /*if(tabelaMinimizacao[findState(eLinhaRes)][findState(eColunaRes)][n] == (estados[i]+estados[j]))*/{
                                        cout << "ACEITEI PESSOAL ;]" << endl;
                                        cout << tabelaMinimizacao[findState(eLinhaRes)][findState(eColunaRes)][n] << "   " << tabelaMinimizacao[i][j][n] << endl;
                                        tabelaMinimizacao[findState(eLinhaRes)][findState(eColunaRes)][n] = tabelaMinimizacao[i][j][n];
                                        //tabelaMinimizacao[findState(eLinhaRes)][findState(eColunaRes)].erase(tabelaMinimizacao[i][j].begin()+n); // <-----------
                                    }
                                }


                            }



                            if(tabelaMinimizacao[i][j][k] == (estados[i]+estados[j])){
                                cout << " ==" << endl;
                                tabelaMinimizacao[i][j].erase(tabelaMinimizacao[i][j].begin()+k);
                                tabelaMinimizacao[i][j].push_back("O");
                            }

                            //cout << "-----" << endl;




                            if(tabelaMinimizacao[i][j][k] == "O" && (int)tabelaMinimizacao[i][j].size() > 0){
                                tabelaMinimizacao[i][j].erase(tabelaMinimizacao[i][j].begin() + k);
                            }

                            if(tabelaMinimizacao[i][j].size() == 0){
                                tabelaMinimizacao[i][j].push_back("O");
                            }




                        }
                    }
                }
            }
        }
        for(i=0;i< (int) estados.size(); i++){
            for(j=0;j< (int) estados.size() && i> j; j++){
                if(tabelaMinimizacao[i][j][0] != "X" && tabelaMinimizacao[i][j][0] != "O"){
                   flagMinimizado = 0;
                }
            }
        }
    }


    printf("\n\nTabela Minima Final:\n");
    printf("\n");
    for(i = 0; i< (int) estados.size(); i++){
        cout << estados[i] << "\t";
        for(j = 0; j< (int) estados.size() && i >= j; j++){
            for(k=0; k< (int) tabelaMinimizacao[i][j].size(); k++){
                if(k ==  (int) tabelaMinimizacao[i][j].size()-1)   cout << tabelaMinimizacao[i][j][k];
                else cout << tabelaMinimizacao[i][j][k] << ",";

            }
            printf("\t");
        }
        cout << endl;
    }
    printf("\t");
    for(i = 0; i< (int) estados.size(); i++)  cout << estados[i] << "\t";



    /* ADICIONANDO ELEMENTOS NO VETOR DE MINIMIZACAO AUXILIAR */

    for(i=0; i < (int) estados.size(); i++){
        for(j = 0; j< (int) estados.size() && i >= j; j++){
            if(estados[i] == estados[j]){
                //cout << estados[i] << ": " << tabelaMinimizacao[i][j][0] << endl;
                vetorMinimizacao.push_back(estados[i]);
            }
            else if(tabelaMinimizacao[i][j][0] == "O"){
                //cout << estados[i] << estados[j] << ": " << tabelaMinimizacao[i][j][0] << endl;
                if( (int) estados[j].find(estados[i]) != -1){
                    vetorMinimizacao.push_back(estados[j]);
                }
                else if( (int) estados[i].find(estados[j]) != -1){
                    vetorMinimizacao.push_back(estados[i]);
                }
                else vetorMinimizacao.push_back(estados[j]+estados[i]);
            }
        }
    }

    //cout << endl << "Passei pelo pushback!" << endl;

    cout << endl;
    for(i = 0; i < (int) vetorMinimizacao.size(); i++) cout << "(" << i << ") " << vetorMinimizacao[i] << endl;


    for(i=0;i< (int) vetorMinimizacao.size(); i++){
        for(j=0; j< (int) vetorMinimizacao.size();j++){

            //cout << ">" << vetorMinimizacao[i] << "< | | >" << vetorMinimizacao[j] << "<: ";

            if(vetorMinimizacao[j] == vetorMinimizacao[i]){
               //cout << "continuei" << endl;
               continue;
            }
            else if(( (int) vetorMinimizacao[j].find(vetorMinimizacao[i]) != -1)){
                //cout << "retirei o >" << vetorMinimizacao[i] << "<" << endl;
                vetorMinimizacao.erase(vetorMinimizacao.begin() + i);
                i=0;
            }
            //else cout << "fiz nada" << endl;
        }
    }

    //cout <<  "Passei pela retirada dos estados!" << endl;

    /* INICIALIZANDO A MATRIZ DE TRANSICOES DO AUTOMATO MINIMO */

    //sort(vetorMinimizacao.begin(), vetorMinimizacao.end(),compare);
    for(i=0; i< (int) vetorMinimizacao.size(); i++){
        for(j=0; j< (int) alfabeto.size(); j++){
            vetorAux.push_back("-");
        }
        automatoMinimo.push_back(vetorAux);
        vetorAux.clear();
    }

    /* ADICIONANDO AS TRANSICOES NA MATRIZ DO AUTOMATO MINIMO */

    for(i=0; i< (int) vetorMinimizacao.size(); i++){
        for(j=0; j< (int) alfabeto.size(); j++){
            for(k=0; k < (int) estados.size(); k++){
                if(automatoMinimo[i][j] == "-" &&  (int) vetorMinimizacao[i].find(estados[k]) != -1){
                    automatoMinimo[i][j] = transicoesAFD[k][j];
                }
            }
        }
    }

    /* ARRUMANDO AS TRANSICOES NA MATRIZ DO AUTOMATO MINIMO */

    for(i=0; i< (int) vetorMinimizacao.size(); i++){
        for(j=0; j< (int) alfabeto.size(); j++){
            for(k=0; k < (int) vetorMinimizacao.size() ; k++) {
                if( (int) vetorMinimizacao[k].find(automatoMinimo[i][j])!= -1){
                    automatoMinimo[i][j] = vetorMinimizacao[k];
                    break;
                }
            }
        }
    }


    /* IMPRIMINDO O RESULTADO DA MINIMIZACAO */
    cout << "\n-----" << endl;
    printf("\nAutomato Minimo:\n");
    printf("\t");
    for(i = 0; i< (int) alfabeto.size(); i++)  printf("%c\t\t", alfabeto[i]);
    printf("\n");

    //int skip=0;

    for(i = 0; i< (int) vetorMinimizacao.size(); i++){

        /*
        skip = 0;
        for(k=0; k<i; k++){
            if(vetorMinimizacao[k] == vetorMinimizacao[i]) skip = 1;
        }
        if(skip == 1) continue;
        */

        cout << vetorMinimizacao[i] << "\t";
        for(j = 0; j< (int) alfabeto.size(); j++){
            cout << automatoMinimo[i][j];
            printf("\t\t");
        }
        cout << endl;
    }
    /*
    cout << "\nEstados Minimizacao:" << endl;
    for(i=0; i< vetorMinimizacao.size(); i++) cout << vetorMinimizacao[i] << "   ";

    cout << "\nEstados:" << endl;
    for(i=0; i< estados.size(); i++) cout << estados[i] << "   ";
    */


    /* CONSTRUINDO O ARQUIVO DE SAIDA */

    cout << endl;
    for(i=0; i< (int) vetorMinimizacao.size(); i++){
        aux = vetorMinimizacao[i];
        for(j=0;j< (int) estadosFinais.size();j++){
            if(aux.find(estadosFinais[j])==0){
                vetorFinais.push_back(aux);
            }
        }
    }

    for(k=0; k< (int) vetorMinimizacao.size(); k++){
        aux = vetorMinimizacao[k];

        for(i=0; i< (int) vetorMinimizacao.size(); i++){
            for(j=0; j< (int) alfabeto.size(); j++){
                if(automatoMinimo[i][j] == aux) automatoMinimo[i][j] = alfa[k];
            }
        }
        for(i=0; i< (int) vetorFinais.size(); i++){
            if(aux == vetorFinais[i]) vetorFinais[i] = alfa[k];
        }
        cout << "De: >" << vetorMinimizacao[k] << "< para: >" << alfa[k] << "<" << endl;
        vetorMinimizacao[k] = alfa[k];
    }

    for(i=0; i< (int) alfabeto.size(); i++){
        alfabeto[i] = i + '0';
        cout << alfabeto[i] << "  ";
    }
    cout << endl;


    ofstream saida;

    nome = nome.substr(0, nome.size()-4);
    nome = nome + "-MIN.afd";
    cout << endl << nome << endl;

    saida.open(nome.c_str());
    saida << vetorMinimizacao[0] << endl;

    saida << vetorMinimizacao.size();
    for(i=0; i< (int) vetorMinimizacao.size(); i++){
        saida << " " << vetorMinimizacao[i];
    }

    saida << endl << vetorFinais.size();
    for(i=0; i< (int) vetorFinais.size(); i++){
        saida << " " << vetorFinais[i];
    }

    saida << endl << alfabeto.size();
    for(i=0; i< (int) alfabeto.size(); i++){
        saida << " " << alfabeto[i];
    }

    k = alfabeto.size() * vetorMinimizacao.size();
    saida << endl << k << endl;
    for(i=0; i< (int) vetorMinimizacao.size(); i++){
        for(j=0; j< (int) alfabeto.size(); j++){
            saida << vetorMinimizacao[i] << " " << alfabeto[j] << " " << automatoMinimo[i][j] << endl;
        }
    }
    saida.close();


    cout << "\n-----" << endl;
    printf("\nAutomato Minimo apos normalizacao:\n");
    printf("\t");
    for(i = 0; i< (int) alfabeto.size(); i++)  printf("%c\t\t", alfabeto[i]);
    printf("\n");
    for(i = 0; i< (int) vetorMinimizacao.size(); i++){

        cout << vetorMinimizacao[i] << "\t";
        for(j = 0; j< (int) alfabeto.size(); j++){
            cout << automatoMinimo[i][j];
            printf("\t\t");
        }
        cout << endl;
    }



}

int main(void){

    string nomeArquivo, formatoArquivo;
    ifstream read;


    cout << "Digite o nome do arquivo: ";
    getline(cin, nomeArquivo);
    cout << "Digite o formato do arquivo: ";
    getline(cin, formatoArquivo);

    nomeArquivo = nomeArquivo + '.' + formatoArquivo;
    read.open(nomeArquivo.c_str());

    while(!read){
        printf("Nome de arquivo invalido!\n");
        read.close();

        cout << endl << "Digite o nome do arquivo: ";
        getline(cin, nomeArquivo);
        cout << "Digite o formato do arquivo: ";
        getline(cin, formatoArquivo);

        nomeArquivo = nomeArquivo + '.' + formatoArquivo;
        read.open(nomeArquivo.c_str());

    }
    read.close();
    cout << "Arquivo aceito!"<< endl;
    inicializaAutomato(nomeArquivo);
    minimizaAutomato(nomeArquivo);
    //trans();

    //verificaPalavra();

    return 0;
}
