//g++ -o turi.out -Wall little-turing.cpp && ./turi.out < entrada.in
#include<bits/stdc++.h>
using namespace std;

#define MAX(a,b) ((a) > (b) ? (a):(b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef vector< pair<int, int> > v1d_pair;

typedef vector< int > v1d;
typedef vector<v1d> v2d;

int main(void){
    v1d_pair disc;
    v2d tabela;
    string nomes[8] = {"ALP", "CAL", "REC", "TEC", "PAP", "BAN", "PPR", "SOP"};
    vector<string> resposta = vector<string>();

    int horas, materias;
    int tempo, is;
    int halt = 1;

    cin >> horas;
    cin >> materias;

    disc = v1d_pair(materias, make_pair(0, 0) );
    tabela = v2d(materias+1, v1d(horas, 0));

    for(int i = 0; i < materias; i++){
        cin >> tempo;
        cin >> is;

        disc[i].first = tempo;
        disc[i].second = is;
    }

    /* PRINT DISCIPLINAS */
    for( int i = 0; i < (int) disc.size(); i++ ){
        cout << i+1 << ") " << nomes[i] << ": (" << disc[i].first << " | " << disc[i].second << ")" << endl;
    }
    cout << endl;



    for(int y = 1; y <= (int) tabela.size(); y++){
        for(int x = 0; x <= (int) tabela[y].size(); x++){
            if(disc[y - 1].first <= x)
                tabela[y][x] = MAX( disc[y-1].second + tabela[y-1][x - disc[y-1].first], tabela[y-1][x] );
            else
                tabela[y][x] = tabela[y-1][x];
        }
    }

    int x = tabela[0].size();
    int y = tabela.size()-1 ;
    while(halt != 0){
        halt = tabela[y][x];
        if(tabela[y-1][x] == halt)      y--;
        else if(tabela[y][x-1] == halt) x--;

        else{
            resposta.push_back(nomes[y-1]);
            y--;
        }

        if (tabela[y][x] == 0)
            break;

    }




    /* PRINT DA TABELA */
    for(int i = 0; i <= horas; i++)
        cout << "\t" << i;
    cout << endl;

    for(int i = 0; i < (int) tabela.size(); i++){
        cout << i << ":\t";
        for(int j = 0; j <= (int) tabela[i].size(); j++){
            cout << tabela[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Resposta - " << endl;
    cout << "  Creditos: " << endl;
    cout << "\t" << tabela[tabela.size()-1][tabela[0].size()] << " creditos" << endl;

    cout << "  Materias: " << endl;
    for(int i = resposta.size()-1; i >= 0; i--)
        cout << "\t" << resposta[i] << endl;


    return 0;
}
