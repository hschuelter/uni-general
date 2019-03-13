#include "utils.hpp"

extern vector<double> fitness, temp;
extern pair<vb, int> best;

/* --- SIMULATED ANNEALING FUNCTIONS --- */

int solve(vb& var, vv_ib& clau, double temp, int current, int it){
    vb old_variables = vb();

    random_device rd;
    mt19937 generator (rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    int next = 0;
    int delta;
    double chance;
    bool a1, a2, a3;

    old_variables = var;
    randomize(var, 0.01);

    for(int i = 0; i < (int) clau.size(); i++){
            a1 = not XOR( var[clau[i][0].first], clau[i][0].second );
            a2 = not XOR( var[clau[i][1].first], clau[i][1].second );
            a3 = not XOR( var[clau[i][2].first], clau[i][2].second );

            if (a1 or a2 or a3)
                next++;
    }

    if (next < current){
        double num = dis(generator);

        delta = current - next;
        chance = exp(-delta / temp);

        // Chance de não trocar as variaveis
        if(num > chance){
            var = old_variables;
            next =  current;
        }
    }

    if(next > best.second){
        best = make_pair(var, next);
    }

    if(it % 100 == 1)
        fitness.push_back(next);

    return next;
}

void randomize(vb& var, double value){
    random_device rd;
    mt19937 generator (rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    double num;

    for(int i = 0; i < (int) var.size(); i++){
        num = dis(generator);
        if(num < value)
            var[i] = not var[i];
    }

}

void cooldown(double temp_i, double temp_f, double& temperature, int schedule, int it, int num_it){
    double new_temp = 0.0;

    if(it % 100 == 1)
        temp.push_back(temperature);

    // Schedule 0
    if( schedule == 0 )
        new_temp = temperature - ( (float) temp_i / num_it );

    // Schedule 1
    else if(schedule == 1)
        new_temp = (double) temp_i * pow(( 1.0 / temp_i), ( (double) it / num_it));

    // Schedule 2
    else if(schedule == 2){
        double a, b;

        a = ((temp_i - temp_f) * (num_it + 1.0))/ (1.0 * num_it);
        b = temp_i - a;

        new_temp = (1.0 * a / (it + 1.0)) + b;
    }

    // Schedule 3
    else if(schedule == 3){
        double a;

        a = log(temp_i - temp_f) / log(num_it);
        new_temp = temp_i - pow(it, a);
    }

    // Schedule 4
    else if(schedule == 4)
        new_temp = ( (temp_i - temp_f) / (1.0 + exp(0.3 * (it - (float) num_it * 0.5))) ) + temp_f;
    

    // Schedule 5
    else if(schedule == 5)
        new_temp = (0.5) * (temp_i - temp_f) * (1 + cos( (PI * it)/num_it ) ) + temp_f;


    // Schedule 6
    else if(schedule == 6){
        new_temp = (0.5) * (temp_i - temp_f * (1.0 - tanh( - 5.0 + (10.0 * it)/num_it ) )) + temp_f;
    }

    // Schedule 7
    else if(schedule == 7){
        new_temp = ((temp_i - temp_f) / cosh(10.0 *it / (num_it * 1.0) ) ) + temp_f;
    }

    // Schedule 8
    else if(schedule == 8){
        double a;
        a = (1.0 / num_it ) * log( temp_i / temp_f);

        new_temp = (float) temp_i * exp( -a * it);
    }

    // Schedule 9
    else if(schedule == 9){
        double a;
        a = (1.0 / (num_it * num_it)) * (log(temp_i) - log(temp_f));
        new_temp = temp_i * exp(-a * it * it);
    }

    temperature = new_temp;
}

/* --- RANDOM SEARCH FUNCTIONS --- */

int  r_solve(vb& var, vv_ib& clau, int previous, int it){
    vb old_variables = vb();
    int next = 0;
    bool a1, a2, a3;

    old_variables = var;
    randomize(var, 0.01);

    for(int i = 0; i < (int) clau.size(); i++){
            a1 = not XOR( var[clau[i][0].first], clau[i][0].second );
            a2 = not XOR( var[clau[i][1].first], clau[i][1].second );
            a3 = not XOR( var[clau[i][2].first], clau[i][2].second );

            if (a1 or a2 or a3)
                next++;
    }

    if(next > best.second){
        best = make_pair(var, next);
    }

    // if (next < previous){
    //     var = old_variables;
    //     next = previous;
    // }

    if(it % 100 == 1)
        fitness.push_back(next);

    return next;
}


bool XOR(bool a, bool b){
    return a ^ b;
}
