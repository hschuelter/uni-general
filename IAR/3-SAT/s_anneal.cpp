#include "utils.hpp"

pair<int, int> setup(string arq, vb& var, vv_ib& clau, int iterations);

void printHeader(string arq, double t0, double tn, int it, int sch, int nvar, int nclau);
void saveOutput(int total, float temp_i, string arq, int schedule, int cur_x);


vector<double> fitness;
vector<double> temp;

pair<vb, int> best;

int main(int args, char** argv){
    string arquivo, aux;
    double temp_i, temp_f;
    int iterations, schedule, current_x;
    vb variables;
    vv_ib clauses;
    pair<int, int> info;

    double temperature;
    int current = 0;

    arquivo = argv[1];
    temp_f = atof(argv[2]);
    temp_i = atof(argv[3]);
    iterations = atoi(argv[4]);
    schedule = atoi(argv[5]);

    current_x = atoi(argv[6]);

    info = setup(arquivo, variables, clauses, iterations);

    // printHeader(arquivo, temp_i, temp_f, iterations, schedule, info.first, info.second);

    temperature = temp_i;
    for(int i=1; i <= iterations; i++ ){
        cooldown(temp_i, temp_f, temperature, schedule, i, iterations);
        current = solve(variables, clauses, temperature, current, i);

        // if(i % 100 == 0){
        //     printf("\r [%d/%d]: %d | %f", i, iterations, current, temperature);
        // }
    }
    
    saveOutput(clauses.size(), temp_i, arquivo, schedule, current_x);
    // cout << "SA: " << best.second << " (" << (100.0 * best.second / info.second) << "%)" << endl;
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

void printHeader(string arq, double t0, double tn, int it, int sch, int nvar, int nclau){
    system(CLEAR);
    cout << " === Simulated Annealing ===" << endl;
    cout << " > Arquivo:\t\"" << arq << "\"" << endl;
    cout << " > T. inicial:\t" << t0 << endl;
    cout << " > T. final:\t" << tn << endl;
    cout << " > Iteracoes:\t" << it << endl;
    cout << " > Schedule:\t" << sch << endl << endl;

    cout << " > Variaveis:\t" << nvar << endl;
    cout << " > Clausulas:\t" << nclau << endl;
    cout << " ===========================\n\n";
}

void saveOutput(int total, float temp_i, string arq, int schedule, int cur_x){
    string file_path = "./output/SA/" + arq;

    ofstream fit(file_path + "/fit/fitness-" + to_string(schedule) + "-" + to_string(cur_x) + ".data", ofstream::out | ofstream::app);
    ofstream tem(file_path + "/tem/temperatura-" + to_string(schedule) + "-" + to_string(cur_x) + ".data", ofstream::out | ofstream::app);
    ofstream bestFile(file_path + "/sa-best-" + to_string(schedule) + ".data", ofstream::out | ofstream::app);

    fitness[fitness.size() - 1 ] = best.second;

    fit << total << endl;
    tem << temp_i << endl;

    for(int i=0; i< (int) fitness.size(); i++){
        fit << fitness[i] << endl;
    }

    for(int i=0; i< (int) temp.size(); i++){
        tem << temp[i] << endl;
    }

    // cout << file_path << endl;
    bestFile << best.second << endl;
}
