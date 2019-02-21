//g++ cal-prova.cpp -o cal && ./cal
#include <bits/stdc++.h>
using namespace std;


void mediasMatriz(vector<vector<int> > m, int p);
void mediasLista( vector< vector< pair<int, int> > > m, int p);
void mergeSort(vector< pair<int, double> > &v, int begin, int end);
void merge(vector< pair<int, double> > &v, int begin, int middle, int end);

int main(void){
    vector<vector<int> > m;
    vector<vector< pair<int, int> > > l;

    ifstream read;
    read.open("entrada.txt");

    int n;
    int origem, destino, peso;

    read >> n;

    m = vector<vector<int> >(n, vector<int>(n, 0));
    l = vector<vector<pair<int, int> > >(n, vector< pair<int, int> >() );
    read >> n;

    for (int i = 0; i < n; i++){
        read >> origem;
        read >> destino;
        read >> peso;

        m[origem][destino] = peso;
        m[destino][origem] = peso;

        l[origem].push_back(make_pair(destino, peso));
        l[destino].push_back(make_pair(origem, peso));

    }

    for(int i=0; i < m.size(); i++)
        cout << "\t " << i;
    cout << endl;

    for(int i = 0; i < m.size(); i++){
        cout << i << "\t";
        for(int j = 0; j < m[i].size(); j++){
            cout << "[" << m[i][j] << "]" << "\t";
        }
        cout << endl;
    }

    cout << endl << "-------------------------" << endl << endl;

    for(int i = 0; i < l.size(); i++){
        cout << i << " -> ";
        for(int j = 0; j < l[i].size(); j++){
            cout << "[" << l[i][j].first << "|" << l[i][j].second << "]" << " -> ";
        }
        cout << endl;
    }

    cout << endl << "-------------------------" << endl << endl;

    mediasMatriz(m, 3);
    mediasLista(l, 3);

    return 0;
}


void mediasMatriz(vector<vector<int> > m, int p){ //O(V² + log V)
    vector< pair<int, double> > medias = vector< pair<int, double> >(m.size());
    int tam = m.size();
    int cont;
    for(int i = 0 ; i < tam; i++ ){
        cont = 0;
        medias[i] = make_pair(i, 0);

        for(int j = 0; j < tam; j++){
            medias[i].second += m[i][j];
            if(m[i][j] != 0)
                cont++;
        }
        if(cont > 0)
            medias[i].second /= cont;
    }


    mergeSort(medias, 0, medias.size() - 1 );
    cout << "Matriz:" << endl;
    for(int i=medias.size()-1; i >= medias.size() - p ; i--)
        cout << "\tVertice: " << medias[i].first << "\tMedia:" << medias[i].second << "\n";
    cout << endl;
}

void mediasLista( vector< vector< pair<int, int> > > m, int p){ // O(V + E + log V)
    vector< pair<int, double> > medias = vector< pair<int, double> >(m.size());

    int tam = m.size();
    int e;
    for(int i = 0 ; i < tam; i++ ){
        e = m[i].size();
        medias[i] = make_pair(i, 0);

        for(int j = 0; j < e; j++){
            medias[i].second += m[i][j].second;
        }
        if(e)
            medias[i].second /= e;
    }


    mergeSort(medias, 0, medias.size() - 1 );
    cout << "Lista:" << endl;
    for(int i=medias.size()-1; i >= medias.size() - p ; i--)
        cout << "\tVertice: " << medias[i].first << "\tMedia:" << medias[i].second << "\n";
    cout << endl;
}

void mergeSort(vector< pair<int, double> > &v, int begin, int end){

    if(begin < end){
        int middle = begin + (end - begin)/2;

        mergeSort(v, begin, middle);
        mergeSort(v, middle + 1 , end);

        merge(v, begin, middle, end);
    }

}

void merge(vector< pair<int, double> > &v, int begin, int middle, int end){

    int tam1 = (middle - begin) +1 ;
    int tam2 = (end - middle);

    int i,j,k;

    vector< pair<int, double> > left;
    vector< pair<int, double> > right;

    for(i = 0; i < tam1; i++){
        left.push_back(v[i + begin]);
    }   
    
    for(i = 0; i < tam2; i++){
        right.push_back(v[i + middle + 1]);
    }

    i = 0;
    j = 0;
    k = begin;

    while( i < tam1 && j < tam2){

        if( left[i].second <= right[j].second){
            v[k] = left[i];
            i++;
        }
        else{
            v[k] = right[j];
            j++;
        }
        k++;
    }
    
    while(i < tam1){
        v[k] = left[i];
        i++;
        k++;
    }


    while(j < tam2){
        v[k] = right[j];
        j++;
        k++;
    }
    
}