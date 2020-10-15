

#include "utils.hpp"

vector< vector<double> > weight_table;
double weight_max;
vector< vector<double> > maze;
pair<int, int> start_point, end_point;

void set_fit_function(function<vector<double>(Population&, vector<Genotype>&)>& f, Input_Parser parser){
    double count;

    switch (parser.fit_function){
        case 0:
            f = std::bind(n_queens, std::placeholders::_1, std::placeholders::_2);
        break;

        case 1:
            f = std::bind(weight_n_queens, std::placeholders::_1, std::placeholders::_2);
            weight_table = vector<vf>(parser.gene_size, vf(parser.gene_size, 0.0));
            weight_max = 0.0;
            count = 0;
            for (int i = 0; i < parser.gene_size; i++){
                for (int j = 0; j < parser.gene_size; j++){
                    if(i % 2 == 0)
                        weight_table[i][j] = sqrt(++count);
                    else
                        weight_table[i][j] = log10(++count);

                    if(i == parser.gene_size - 2) weight_max += weight_table[i][j];
                }
            }
        break;

        case 2:
            f = std::bind(radio_factory, std::placeholders::_1, std::placeholders::_2);
        break;

        case 3:
            f = std::bind(maze_solver, std::placeholders::_1, std::placeholders::_2);
            start_point = {1, 10};
            end_point   = {20, 1};

            maze = vector<vf>(30, vf(25, 0.0));
            maze =
                {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,3,1,1,0,0},
                {0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,1,0},
                {0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0},
                {0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,0},
                {0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0},
                {0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0},
                {0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0},
                {0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,0},
                {0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,0,1,0},
                {0,2,1,1,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,0,1,1,0},
                {0,1,0,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0},
                {0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0},
                {0,1,0,0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0},
                {0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0},
                {0,1,1,0,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,1,0,0,1,0},
                {0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0},
                {0,0,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,0,0},
                {0,1,1,0,0,0,1,1,0,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,0},
                {0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0},
                {0,0,0,0,1,0,0,0,0,1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,0},
                {0,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0},
                {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0},
                {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0},
                {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0},
                {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0},
                {0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,0},
                {0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0},
                {0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
        break;

        case 4:
            f = std::bind(keane_bump, std::placeholders::_1, std::placeholders::_2);
        break;

        case 5:
            f = std::bind(michalewicz, std::placeholders::_1, std::placeholders::_2);
        break;

        default:
            break;
    }
}

vf n_queens(Population& p, vector<Genotype>& individuos){
    vf fitness = vf(p.pop_size, 0);
    int max_value = p.gene_size;
    int i, j;

    #pragma omp parallel for private(i, j)
    for(int ind = 0; ind < (int) p.genes.size(); ind++){
        vi queen_check = vi(p.gene_size, 1);

        for(i = 0; i < (int) individuos[ind].v_int.size(); i++){
            for(j = i+1; j < (int) individuos[ind].v_int.size(); j++){
                int xi, xj;
                int yi, yj;

                xi = individuos[ind].v_int[i];
                yi = i;

                xj = individuos[ind].v_int[j];
                yj = j;

                if(abs(xi - xj) == abs(yi - yj)){
                    queen_check[yi] = max(0, queen_check[yi]-1);
                    queen_check[yj] = max(0, queen_check[yi]-1);
                }
            }
        }

        for(i = 0; i < (int) queen_check.size(); i++) fitness[ind] += queen_check[i];
    }

    for(int i = 0; i < (int) fitness.size(); i++){
        fitness[i] = fitness[i] / max_value;
    }

    return fitness;
}

vf weight_n_queens(Population& p, vector<Genotype>& individuos){
    vf fitness = vf(p.pop_size, 0);
    int max_value = weight_max;
    int i, j;

    #pragma omp parallel for private(i, j)
    for(int ind = 0; ind < (int) individuos.size(); ind++){
        vi queen_check = vi(p.gene_size, 1);

        for(i = 0; i < (int) individuos[ind].v_int.size(); i++){
            for(j = i+1; j < (int) individuos[ind].v_int.size(); j++){
                int xi, xj;
                int yi, yj;

                yi = individuos[ind].v_int[i];
                xi = i;

                yj = individuos[ind].v_int[j];
                xj = j;

                if(abs(xi - xj) == abs(yi - yj)){
                    queen_check[xi] = max(0, queen_check[xi]-1);
                    queen_check[xj] = max(0, queen_check[xi]-1);
                }
            }
        }

        for(i = 0; i < (int) queen_check.size(); i++){
            int x, y;
            x = i;
            y = individuos[ind].v_int[i];
            fitness[ind] += queen_check[i] * weight_table[x][y];
        }
    }

    for(int i = 0; i < (int) fitness.size(); i++){
        fitness[i] = fitness[i] / max_value;
    }

    return fitness;
}

vf arithmetic_function(Population& p, double (*f)(double)){
    vf fitness = vf(p.pop_size, 0);
    double max, min;
    max = 0;
    min = INFINITE;


    for(int ind = 0; ind < (int) p.genes.size(); ind++){
        double x = bin_2_real(p.genes[ind].v_int, p.lower_bound, p.upper_bound, 0.0001);

        fitness[ind] = (*f)(x);

        max = MAX(max, fitness[ind]);
        min = MIN(min, fitness[ind]);
    }

    for(int i = 0; i < (int) fitness.size(); i++){
        fitness[i] = normalize(fitness[i], max, min);
    }

    return fitness;

}

vf radio_factory(Population& p, vector<Genotype>& individuos){
    vf fitness = vf(p.pop_size, 0);

    #pragma omp parallel for
    for(int i = 0; i < (int) individuos.size(); i++){
        int luxo = 0, stand = 0;
        float h = 0, f0 = 0;

        for(int j = 0; j < 5; j++){
            luxo  += pow(2, j) * individuos[i].v_int[j];
            stand += pow(2, j) * individuos[i].v_int[j+5];
        }
        luxo = (1.0 * luxo / 31.0) * 16.0;
        stand = (1.0 * stand / 31.0) * 24.0;

        h = MAX(0, (1.0 * stand + 2.0 * luxo - 40.0) / 16.0 );
        f0 = (30.0 * stand + 40.0 * luxo) / 1360.0;

        fitness[i] = MAX(f0 - h, 0);
        // cout << "L: " << luxo << "\t| S: " << stand << endl;
    }

    return fitness;
}

vf maze_solver(Population& p, vector<Genotype>& individuos){
    vf fitness = vf(p.pop_size, 1);
    double max_dist = 48.0;
    int i, j;


	// Limpando os genes dos individuos
	for(int ind = 0; ind < p.pop_size; ind++){
		individuos[ind] = cleaning(individuos[ind], p.real_rand);
	}

    #pragma omp parallel for // shared(i)
    for(i = 0; i < p.pop_size; i++){
        int x, y;
        double h, h_dist, h_steps, h_repeat, h_vis;
        int num_steps = 0, repeat = 0;
        int visitado = 0;
        int last_move = INFINITE;

        vector<vf> maze_copy = vector<vf>(maze);
        x = start_point.first;
        y = start_point.second;

        for(j = 0; j < (int) individuos[i].v_int.size(); j++){
            if(maze_copy[y][x] == 3) break;
            if(maze_copy[y][x] == 4) visitado++;
            maze_copy[y][x] = 4;
            num_steps++;

            switch(individuos[i].v_int[j]){
                case RIGHT:
                    if(last_move == LEFT) repeat++;

                    if( maze_copy[y][x+1] != 0 and (maze_copy[y][x+1] != 4) ){
                        x++;
                    }
                break;

                case UP:
                    if(last_move == DOWN) repeat++;

                    if( maze_copy[y-1][x] != 0 and (maze_copy[y-1][x] != 4) ){
                        y--;
                    }
                break;

                case LEFT:
                    if(last_move == RIGHT) repeat++;

                    if( maze_copy[y][x-1] != 0 and (maze_copy[y][x-1] != 4) ){
                        x--;
                    }
                break;

                case DOWN:
                    if(last_move == UP) repeat++;

                    if( maze_copy[y+1][x] != 0 and (maze_copy[y+1][x] != 4) ){
                        y++;
                    }
                break;
            }
            last_move = individuos[i].v_int[j];
        }
        pair<int, int> point = {x, y};

        h_dist   = 1.0 * distance(point, end_point) / max_dist;
        h_steps  = 1.0 * num_steps / p.gene_size;
        h_repeat = 1.0 * repeat / p.gene_size;
        h_vis    = 1.0 * visitado / p.gene_size;

        h = (1.00 * h_dist) + (0.00 * h_steps) + (0.00 * h_repeat) + (0.00 * h_vis);
        // cerr << "visitado: " << visitado << " | h: " << h << endl;

        fitness[i] = MAX(fitness[i] - h, 0);
    }


    return fitness;
}

vf keane_bump(Population& p, vector<Genotype>& individuos){
    vf fitness = vf(p.pop_size, 0.0);
    int n = (int) individuos[0].v_double.size();
    int ind;

    #pragma omp parallel for shared(ind)
    for(ind = 0; ind < p.pop_size; ind++){
        double sum1 = 0.0, sum2 = 0.0, mul = 1.0;
        double h_sum = 0.0, h_mul = 1.0;

        for(int i = 0; i < n; i++){
            double xi = individuos[ind].v_double[i];
            sum1 += cos(xi) * cos(xi) * cos(xi) * cos(xi);
            mul  *= cos(xi) * cos(xi);
            sum2 += xi * xi * (i+1);

            h_sum += xi;
            h_mul *= xi;
        }
		sum2 = sqrt(sum2);

		// cerr << "SUM1: " << sum1 << endl;
		// cerr << "MUL:  " << mul  << endl;
		// cerr << "SUM2: " << sum2 << "\n***************\n";

		fitness[ind]  = abs(sum1 - 2 * mul) / sum2;
        fitness[ind] /= 0.90;

		// Restrições ----------
        if(sum2 == 0)		fitness[ind] = 0;
        if(h_mul <= 0.75)   fitness[ind] = 0;
        if(h_sum >= (15.0 * n) / 2.0)   fitness[ind] = 0;
    }

    return fitness;
}

vf michalewicz(Population& p, vector<Genotype>& individuos){
    vf fitness = vf(p.pop_size, 0.0);
    int n = (int) p.genes[0].v_double.size();
    int ind, i;

    #pragma omp parallel for shared(ind)
    for(ind = 0; ind < p.pop_size; ind++){
        for(i = 0; i < n; i++){
            double xi = p.genes[ind].v_double[i];
            fitness[ind] += std::sin( xi ) * pow( std::sin( (i + 1) * xi * xi / PI ), 2*n);
        }
    }

    for(ind = 0; ind < p.pop_size; ind++){
        fitness[ind] /= 50.0;
    }

    return fitness;
}

/* --- SCALING --- */
vf linear_scaling(vf& old_fitness, double c){
    vf new_fitness = vf(old_fitness.size(), 0.0);
    double f_min = 1.0, f_max = 0.0, f_avg = 0.0;
    double alpha, beta;

    for(int i = 0; i < (int) old_fitness.size(); i++){
        if( old_fitness[i] < f_min ) f_min = old_fitness[i];
        if( old_fitness[i] > f_max ) f_max = old_fitness[i];

        f_avg += old_fitness[i];
    }
    f_avg = f_avg / old_fitness.size();

    if( f_min > ((c * f_avg - f_max) / (c - 1))){
        alpha = f_avg * (c - 1) / (f_max - f_avg);
        beta  = f_avg * (f_max - c * f_avg) / (f_max - f_avg);
    }
    else{
        alpha = f_avg / (f_avg - f_min);
        beta  = (-1.0) * f_min * f_avg / (f_avg - f_min);
    }

    for(int i = 0; i < (int) old_fitness.size(); i++)
        new_fitness[i] = alpha * old_fitness[i] + beta;

    return new_fitness;
}

double foo(double x){
    return cos(20 * x) - (abs(x)/2.0) + (pow(x,3)/4.0);
}

double normalize(double value, double max, double min){
    return (value - min) / (max - min);
}

double bin_2_real(vi& bin, double lower, double upper, double precision){
    double value = 0;
    double max = 0;
    for(int i = 0; i < (int) bin.size(); i++){
        value += bin[i] * pow(2, i);
        max += pow(2,i);
    }
    value = (value + lower) / max;

    value = value * (upper - lower) + lower;
    return value;
}

/* --- GA STUFF --- */
Genotype cleaning(Genotype& g, function<double()>& random_num){
    vector<bool> collisions((int)g.v_int.size(), false);
    Genotype clean_geno(g);
    vector<vector <int> > maze_copy = vector<vector <int> >(30, vector <int> (25, 0.0));
    maze_copy = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,3,1,1,0,0},
            {0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,1,0},
            {0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0},
            {0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,0},
            {0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0},
            {0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0},
            {0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0},
            {0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,0},
            {0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,0,1,0},
            {0,2,1,1,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,0,1,1,0},
            {0,1,0,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0},
            {0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0},
            {0,1,0,0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0},
            {0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0},
            {0,1,1,0,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,1,0,0,1,0},
            {0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0},
            {0,0,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,0,0},
            {0,1,1,0,0,0,1,1,0,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,0},
            {0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0},
            {0,0,0,0,1,0,0,0,0,1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,0},
            {0,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0},
            {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0},
            {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0},
            {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0},
            {0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0},
            {0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,0},
            {0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0},
            {0,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

    int x = start_point.first;
    int y = start_point.second;
    int it = 0;
    int rem = 0;

    for(it = 0; it < (int) g.v_int.size(); it++){
        if(maze_copy[y][x] == 3) break;
        maze_copy[y][x] = 4;

        switch(g.v_int[it]){
            case RIGHT:
                if( maze_copy[y][x+1] != 0 and (maze_copy[y][x+1] != 4 ) ){
                    x++;
                }
                else{
                    collisions[it] = true;
                    rem++;
                }
            break;

            case UP:
                if( maze_copy[y-1][x] != 0 and (maze_copy[y-1][x] != 4 ) ){
                    y--;
                }
                else{
                    collisions[it] = true;
                    rem++;
                }
            break;

            case LEFT:
                if( maze_copy[y][x-1] != 0 and (maze_copy[y][x-1] != 4 ) ){
                    x--;
                }
                else{
                    collisions[it] = true;
                    rem++;
                }
            break;

            case DOWN:
                if( maze_copy[y+1][x] != 0 and (maze_copy[y+1][x] != 4 ) ){
                    y++;
                }
                else{
                    collisions[it] = true;
                    rem++;
                }
            break;
        }
    }
    int size = (int) g.v_int.size();


    for(int i = size - 1; i >= 0; i-- ){
        if(collisions[i])
            clean_geno.v_int.erase(clean_geno.v_int.begin() + i);
    }

    for(int i = 0; i < rem; i++){
        int new_move = (int) (4 * random_num());
        clean_geno.v_int.push_back(new_move);
    }

    return clean_geno;

}

vector<Genotype> generation_gap(vector<Genotype>& old_pop, vector<Genotype>& new_pop, double gap, function<double()>& random_num){
    set<int> old_set, new_set;
    set<int> :: iterator old_it, new_it;

    int n = gap * ((int) old_pop.size());
    for(int i = 1; i <= n; i++){
        while((int)old_set.size() < i)
            old_set.insert(old_pop.size() * random_num() );

        while((int)new_set.size() < i)
            new_set.insert(old_pop.size() * random_num() );
    }

    old_it = old_set.begin();
    new_it = new_set.begin();
    for(int i = 0; i < n ; i++){
        old_pop[*old_it] = Genotype(new_pop[*new_it]);
        old_it++; new_it++;
    }

    // cerr << "Old Set (" << old_set.size() << "): {";
    // for (old_it = old_set.begin(); old_it != old_set.end(); ++old_it) {
    //     cerr << *old_it << ", ";
    // }
    // cerr << "}\n";
    //
    // cerr << "New Set (" << new_set.size() << "): {";
    // for (new_it = new_set.begin(); new_it != new_set.end(); ++new_it) {
    //     cerr << *new_it << ", ";
    // }
    // cerr << "}\n";

    return old_pop;
}

vector<Genotype> standard_crowding(Population& pop, vector<Genotype>& old_pop){
	vector<Genotype> new_pop(pop.genes);
	vector<Genotype> pop_copy(old_pop);
	auto rng = std::default_random_engine {};
	shuffle(begin(new_pop), end(new_pop), rng);

	int size = (int) new_pop.size();

	for(int i = 0; i < size; i++){
		double minimum = INFINITE;
		int pos = 0;

		for(int j = 0; j < size; j++){
			double value = geno_distance(new_pop[i], pop_copy[j]);
			if(value < minimum){
				minimum = value;
				pos = j;
			}
		}

		pop_copy[pos] = Genotype(new_pop[i]);
	}

	return pop_copy;
}

vector<Genotype> deterministic_crowding(Population& pop, function<vector<double>(Population&, vector<Genotype>&)>& fit_function){
	vector<Genotype> parent_pop(pop.genes);
	vector<Genotype> new_pop(pop.genes.size(), Genotype());
	auto rng = std::default_random_engine {};
	shuffle(begin(parent_pop), end(parent_pop), rng);

	int size = (int) parent_pop.size();

	// Criando filhos do população ----------
	vector<Genotype> child_pop(parent_pop);
	#pragma omp parallel for
	for(int ind = 0; ind < size; ind += 2)
		pop.crossover(child_pop[ind], child_pop[ind+1]);

	// Avaliação dos pais e filhos ----------
	vf parent_fitness, child_fitness;
	parent_fitness = fit_function(pop, parent_pop);
	child_fitness  = fit_function(pop, child_pop);

	// Torneio entre pais e filhos ----------
	for(int ind = 0; ind < size; ind += 2){
		vf dists(4, 0.0);
		dists[0] = abs(parent_fitness[ind] - child_fitness[ind]);
		dists[1] = abs(parent_fitness[ind+1] - child_fitness[ind]);
		dists[2] = abs(parent_fitness[ind] - child_fitness[ind+1]);
		dists[3] = abs(parent_fitness[ind+1] - child_fitness[ind+1]);

		int farthest = 0;
		for(int i = 0; i < 4; i++){
			if(dists[i] >= dists[farthest]) farthest = i;
		}

		if(farthest == 1){
			swap(parent_fitness[ind], parent_fitness[ind+1]);
			swap(parent_pop[ind], parent_pop[ind+1]);
		}
		if(farthest == 2){
			iter_swap(child_fitness.begin() + ind, child_fitness.begin() + ind + 1);
			iter_swap(child_pop.begin() + ind, child_pop.begin() + ind + 1);
		}

		new_pop[ind] =  (parent_fitness[ind] > child_fitness[ind]) ?
						(parent_pop[ind]) : (child_pop[ind]);

		new_pop[ind+1]= (parent_fitness[ind+1] > child_fitness[ind+1]) ?
						(parent_pop[ind+1]) : (child_pop[ind+1]);
	}

	return new_pop;
}

vector<double> fitness_sharing(vf& old_fitness, vector<Genotype>& individuos, double alpha, double rho){
	vf new_fitness(old_fitness);
	double minimum = INFINITE, maximum = -1;
	int size = MAX(individuos[0].v_double.size(), individuos[0].v_int.size());

	// Criando a tabela de distancias
	vector<vf> distance_table = vector<vf>(size, vf(size, 0.0));
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			distance_table[i][j] = geno_distance(individuos[i], individuos[j]);
			if(distance_table[i][j] < minimum) minimum = distance_table[i][j];
			if(distance_table[i][j] > maximum) maximum = distance_table[i][j];
		}
	}

	// Normalizando e arrumando as distâncias
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			double d = (distance_table[i][j] - minimum) / (maximum - minimum);
			distance_table[i][j] = 1 - pow(d / rho, alpha);
		}
	}

	// Criando o vetor de Fitness compartilhado
	for(int i = 0; i < size; i++){
		double dists = 0.0;
		for(int j = 0; j < size; j++){
			dists += distance_table[i][j];
		}

		new_fitness[i] = old_fitness[i] / dists;
	}

	return new_fitness;
}

double geno_distance(Genotype& g1, Genotype& g2){
	int size = MAX(g1.v_double.size(), g1.v_int.size());
	double distance = 0.0;
	for(int k = 0; k < size; k++){
		if(g1.v_double.size() > g1.v_int.size())
			distance += abs(g1.v_double[k] - g2.v_double[k]);
		else
			distance += abs(g1.v_int[k] - g2.v_int[k]);
	}

	return distance;
}

/* ====== OTHERS ====== */
double distance(pair<int, int>& p1, pair<int, int>& p2){
    return (abs(p1.first - p2.first) + abs(p1.second - p2.second));
}

vi slice(vi v, int b, int e){
    vi::iterator first, last;
    vi new_vec;

    first = v.begin() + b;
    last = v.begin() + e;

    new_vec = vi(first, last);
    return new_vec;
}

void print_vector(vf& v){
    cerr << "| ";
    for (int i = 0; i < (int) v.size(); i++)
        fprintf(stderr, "%.2f | ", v[i]);
    cerr << "\n";
}

void print_vector(vi& v){
    cerr << "| ";
    for (int i = 0; i < (int) v.size(); i++)
        cerr << v[i] << " | ";
    cerr << "\n";
}

void print_board(Genotype& g){
    for(int i = 0; i < (int) g.v_int.size(); i++){
        cerr << "|";
        for(int j = 0; j < (int) g.v_int.size(); j++){
            if(i == g.v_int[j])
                cerr << "Q|";
            else
                cerr << " |";
        }
        cerr << "\n";
    }
}
