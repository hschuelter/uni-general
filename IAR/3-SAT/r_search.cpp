#include "utils.hpp"

pair<int, int> setup(string arq, vb& var, vv_ib& clau, int iterations);

void printHeader(string arq, int it, int nvar, int nclau);
void saveOutput(int total, string arq, int schedule, int current_x);


vector<double> fitness;
vector<double> temp;

pair<vb, int> best;

int main(int args, char** argv){
    string arquivo;
    int iterations, schedule, current_x;
    vb variables;
    vv_ib clauses;
    pair<int, int> info;

    int current = 0;

    arquivo = argv[1];
    iterations = atoi(argv[2]);
    schedule = atoi(argv[3]);
    current_x = atoi(argv[4]);

    info = setup(arquivo, variables, clauses, iterations);

    // printHeader(arquivo, iterations, info.first, info.second);
    
    for(int i=1; i <= iterations; i++ ){
        current = r_solve(variables, clauses, current, i);

        // if(i % 100 == 0){
        //     printf("\r [%d/%d]: %d", i, iterations, current);
        // }
    }
    
    saveOutput(clauses.size(), arquivo, schedule, current_x);
    // cout << "RS: " << best.second << " (" << (100.0 * best.second / info.second) << "%)\n";
    return 0;
}

pair<int, int> setup(string arq, vb& var, vv_ib& clau, int iterations){
    int nvar, nclau;
    int a;
    bool b = false;

    ifstream read("input/" + arq + ".in");
    read >> nvar >> nclau;

    var = vb(nvar, false);
    clau= vv_ib( nclau, vector<pair<int, bool> > (3, {0, false} ) );

    for(int i = 0; i < nclau; i++){
        for(int j = 0; j < 3; j++){
            read >> a;
            b = true;
            if(a < 0){
                b = false;
            }
            a = abs(a) - 1;
            clau[i][j] = make_pair(a, b);
        }
    }

    fitness = vector<double>();
    temp = vector<double>();
    best = pair<vb, int>(vb(nvar, false), 0);

    return {nvar, nclau};
}

void printHeader(string arq, int it, int nvar, int nclau){
    system(CLEAR);
    cout << " === Random Search ===" << endl;
    cout << " > Arquivo:\t\"" << arq << "\"" << endl;
    cout << " > Iteracoes:\t" << it << endl;

    cout << " > Variaveis:\t" << nvar << endl;
    cout << " > Clausulas:\t" << nclau << endl;
    cout << " =====================\n\n";
}

void saveOutput(int total, string arq, int schedule, int current_x){

    string file_path = "./output/RS/" + arq;

    ofstream fit(file_path + "/random-" + to_string(schedule) + "-" + to_string(current_x) + ".data", ofstream::out | ofstream::app);
    ofstream bestFile(file_path + "/random-best-" + to_string(schedule) + ".data", ofstream::out | ofstream::app);

    fitness[fitness.size() - 1 ] = best.second;

    fit << total << endl;

    for(int i=0; i< (int) fitness.size(); i++){
        fit << fitness[i] << endl;
    }

    // cout << file_path << endl;
    bestFile << best.second << endl;
}
