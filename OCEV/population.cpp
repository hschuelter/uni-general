#include "population.hpp"

Population::Population(){
    this -> genes = vector<Genotype>();
    this -> gene_size = -1;
    this -> pop_size = -1;
    this -> codification = -1;

    random_device rd;
    this -> real_rand = std::bind( std::uniform_real_distribution<double>(0,1), mt19937(rd()) );
    this -> selection = std::bind(&Population::stochastic_tournament, this,  std::placeholders::_1, std::placeholders::_2, this -> real_rand);
    this -> mutation  = std::bind(&Population::binary_mutation, this,  std::placeholders::_1, this -> real_rand);
}

Population::Population (Input_Parser parser){

    this -> gene_size = parser.gene_size;
    this -> pop_size = parser.pop_size;
    this -> codification = parser.codification;
    this -> lower_bound = parser.lower_bound;
    this -> upper_bound = parser.upper_bound;
	this -> generations = parser.generations;
    this -> current_generation = 0;

    this -> k  = parser.k;
    this -> kp = parser.kp;
    this -> d  = parser.d;

    this -> crossover_chance = parser.crossover_chance;
    this -> mutation_chance  = parser.mutation_chance;

    this -> elitism = parser.elitism;
    this -> c_begin = parser.c_begin;
    this -> c_end = parser.c_end;

    this -> genes = vector<Genotype>(this -> pop_size);
    for(int i=0; i < (int) this -> genes.size(); i++){
        this -> genes[i] = Genotype(this -> gene_size, this -> codification, this -> lower_bound, this -> upper_bound);
    }

    random_device rd;
    this -> real_rand = std::bind(std::uniform_real_distribution<double>(0,1), mt19937(rd()) );

    // Defining the selection method
    switch(parser.selection){
        case 0:
            this->selection = bind(&Population::roulette_selection, this, std::placeholders::_1,
                                        std::placeholders::_2, this -> real_rand);
        break;

        case 1:
            this->selection = bind(&Population::uniform_ranking, this, std::placeholders::_1,
                                        std::placeholders::_2, this -> real_rand);
        break;

        case 2:
            this->selection = bind(&Population::stochastic_tournament, this, std::placeholders::_1,
                                        std::placeholders::_2, this -> real_rand);
        break;

        case 3:
            this->selection = bind(&Population::linear_neighbourhood_best, this, std::placeholders::_1,
                                        std::placeholders::_2, this -> real_rand);
        break;

        case 4:
            this->selection = bind(&Population::linear_neighbourhood_random, this, std::placeholders::_1,
                                        std::placeholders::_2, this -> real_rand);
        break;

        case 5:
            this->selection = bind(&Population::linear_neighbourhood_proporcional, this, std::placeholders::_1,
                                        std::placeholders::_2, this -> real_rand);
        break;
    }

    // Defining the crossover method
    switch(parser.crossover){
        case 0:
            this->crossover = std::bind(&Population::one_point_crossover, this, std::placeholders::_1,
                                        std::placeholders::_2, this -> real_rand);
        break;

        case 1:
            this->crossover = std::bind(&Population::two_point_crossover, this, std::placeholders::_1,
                                        std::placeholders::_2, this -> real_rand);
        break;

        case 2:
            this->crossover = std::bind(&Population::any_point_crossover, this, std::placeholders::_1,
                                        std::placeholders::_2, this -> real_rand);
        break;

        case 3:
            this->crossover = std::bind(&Population::partially_matched_crossover, this, std::placeholders::_1,
                                        std::placeholders::_2, this -> real_rand);

        case 4:
            this->crossover = std::bind(&Population::blend_alpha_crossover, this, std::placeholders::_1,
                                                                        std::placeholders::_2, this -> real_rand);
        break;
    }

    // Defining the mutation method
    switch(parser.mutation){
        case 0:
            this->mutation  = std::bind(&Population::binary_mutation, this,
                                        std::placeholders::_1, this -> real_rand);
        break;

        case 1:
            this->mutation  = std::bind(&Population::integer_mutation, this,
                                        std::placeholders::_1, this -> real_rand);
        break;

        case 2:
            this->mutation  = std::bind(&Population::swap_mutation, this,
                                        std::placeholders::_1, this -> real_rand);
		break;

		case 3:
            this->mutation  = std::bind(&Population::delta_mutation, this,
                                        std::placeholders::_1, this -> real_rand);
        break;

		case 4:
			this->mutation  = std::bind(&Population::michalewicz_mutation, this,
										std::placeholders::_1, this -> real_rand);
		break;
    }

	// Defining the Diversity method
    switch(parser.codification){
        case 0:
            this -> diversity = std::bind(&Population::inertia_diversity,
                                          this, std::placeholders::_1);
        break;

        case 1:
            this -> diversity = std::bind(&Population::inertia_diversity,
                                          this, std::placeholders::_1);
        break;

        case 2:
            this -> diversity = std::bind(&Population::manhattan_diversity,
                                          this, std::placeholders::_1);
        break;

		case 3:
			this -> diversity = std::bind(&Population::manhattan_diversity,
										  this, std::placeholders::_1);
		break;

        default:
            this -> diversity = std::bind(&Population::inertia_diversity,
                                          this, std::placeholders::_1);
        break;
    }
}

/* SELEÇÃO */
vector<Genotype> Population::roulette_selection(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num){
    // cout << "Roulette\n";
    vector<Genotype> new_genes = vector<Genotype>(this -> pop_size);
    vector<double> fit_related = vector<double>(this -> pop_size);
    double fit_sum = 0;

    for(int i=0; i < this -> pop_size; i++) fit_sum += fitness[i];

    fit_related[0] = fitness[0] / fit_sum;
    for(int i = 1; i < this -> pop_size; i++){
        fit_related[i] = fit_related[i-1] + fitness[i] / fit_sum;
    }

    for(int ind = 0; ind < (int) new_genes.size(); ind++){
        int i, j;

        double num_1 = random_num();
        for(i = 0; i < (int) genes.size(); i++){
            if(num_1 <= fit_related[i]){
                new_genes[ind] = Genotype(genes[i]);
                break;
            }
        }

        ind++;
        double num_2 = random_num();
        for(j = 0; j < (int) genes.size(); j++){
            if(num_2 <= fit_related[j]){
                if(j == i) j = (j+1) % genes.size();
                new_genes[ind] = Genotype(genes[j]);
                break;
            }
        }
    }

    return new_genes;
}

vector<Genotype> Population::uniform_ranking(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num){
    // cout << "Ranking\n";
    vector<Genotype> new_genes = vector<Genotype>(this -> pop_size);
    vector<pair<int, double> > ranking = vector<pair<int, double> >(this -> pop_size);
    vector<double> fit_related = vector<double>(this -> pop_size);
    int fit_sum = 0;

    for(int i = 0; i < (int) ranking.size(); i++){
        ranking[i] = {i, fitness[i]};
        // cout << ranking[i].first << " -> " << ranking[i].second << endl;
    }
    // cout << "--------\n";
    merge_sort(ranking, 0, ranking.size()-1);

    for(int i = 0; i < (int) ranking.size(); i++){
        // cout << ranking[i].first << " -> " << ranking[i].second << endl;
        ranking[i].second = i+1;
        fit_sum += i+1;
    }

    fit_related[0] = ranking[0].second / fit_sum;
    for(int i = 1; i < (int) fit_related.size(); i++){
        fit_related[i] = fit_related[i-1] + ranking[i].second / fit_sum;
    }

    for(int ind = 0; ind < this->pop_size; ind++){
        int i, j;
        double n1 = random_num();
        for(i = 0; i < this->pop_size; i++){
            if(n1 < fit_related[i]) break;
        }

        double n2 = random_num();
        for(j = 0; j < this->pop_size; j++){
            if(n2 < fit_related[j]) break;
        }

        new_genes[ind++] = Genotype(genes[i]);
        new_genes[ind]   = Genotype(genes[j]);
    }

    return new_genes;
}

vector<Genotype> Population::stochastic_tournament(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num){
    // cout << "Torneio\n";
    vector<Genotype> new_genes = vector<Genotype>(this -> pop_size);
    int k  = this->k;
    int kp = this->kp;

    for(int ind = 0; ind < this->pop_size; ind++){
        vector<pair<int, double> > match = vector<pair<int, double> >( k, {-1, -1});

        // Choosing the k participants
        for(int i = 0; i < k; i++){
            int n = (int) (this->pop_size * random_num());
            for(int j = i - 1; j >= 0; j--){
                if(n == match[j].first){
                    n = (int) (this->pop_size * random_num());
                    j = i;
                }
            }
            match[i] = {n, fitness[n]};
        }
        merge_sort(match, 0, k - 1);

        // Defining the winner
        double match_result = random_num();
        int pos;
        if(match_result <= kp){
            pos = match[k-1].first;
            new_genes[ind] = Genotype(genes[pos]);
        }
        else{
            int win_pos = (int) (k * random_num());

            pos = match[win_pos].first;
            new_genes[ind] = Genotype(genes[pos]);
        }
    }

    return new_genes;
}

vector<Genotype> Population::linear_neighbourhood_best(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num){
    // cout << "Linear BEST\n";
    vector<Genotype> new_genes = vector<Genotype>(this -> pop_size);
    int d = this->d;

    for(int ind = 0; ind < this->pop_size; ind++){
        pair<int, double> best_fit = {-1, -1};
        int first, second;
        first = (int) (this->pop_size * random_num());

        for(int i = -d; i <= d; i++){
            if(i == 0) continue;
            second = mod(first + i, this->pop_size);
            if(fitness[second] > best_fit.second)
                best_fit = {second, fitness[second]};
        }
        new_genes[ind++] = Genotype(genes[first]);
        new_genes[ind]   = Genotype(genes[best_fit.first]);
    }

    return new_genes;
}

vector<Genotype> Population::linear_neighbourhood_random(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num){
    // cout << "Linear RANDOM\n";
    vector<Genotype> new_genes = vector<Genotype>(this -> pop_size);
    vector< pair<int, double> > vizinhos = vector< pair<int, double> >(2 * this->d, {0, 0});
    int d = this->d;

    for(int ind = 0; ind < this->pop_size; ind++){
        int first, second, pos;
        first = (int) (this->pop_size * random_num());

        int j = 0;
        for(int i = -d; i <= d; i++){
            if(i == 0) continue;
            pos = mod(first + i, this->pop_size);
            vizinhos[j++] = {pos, fitness[pos]};
        }
        second = (int) (2 * d * random_num());
        new_genes[ind++] = Genotype(genes[ first ]);
        new_genes[ind]   = Genotype(genes[ vizinhos[second].first ]);
    }

    return new_genes;
}

vector<Genotype> Population::linear_neighbourhood_proporcional(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num){
    // cout << "Linear PROPOR\n";
    vector<Genotype> new_genes = vector<Genotype>(this -> pop_size);
    vector< pair<int, double> > vizinhos = vector< pair<int, double> >(2 * this->d, {0, 0});
    int d = this->d;

    for(int ind = 0; ind < this->pop_size; ind++){
        int first_pos = 0, second_pos = 0, pos;
        double roulette, fit_sum;
        fit_sum = 0.0;

        first_pos = (int) (this->pop_size * random_num());
        int j = 0;
        for(int i = -d; i <= d; i++){
            if(i == 0) continue;
            pos = mod(first_pos + i, this->pop_size);
            vizinhos[j++] = {pos, fitness[pos]};

            fit_sum += fitness[pos];
        }
        // vizinhos has the cumulative percentage
        vizinhos[0] = {vizinhos[0].first, fitness[vizinhos[0].first] / fit_sum};
        for(int i = 1; i < (int) vizinhos.size(); i++){
            vizinhos[i] = {vizinhos[i].first, vizinhos[i-1].second + (fitness[vizinhos[i].first] / fit_sum)};
        }

        // Choice similar to the roulette selection
        roulette = random_num();
        for(int i = 0; i < (int) vizinhos.size(); i++){
            second_pos = i;
            if (roulette <= vizinhos[i].second){
                second_pos = i;
                break;
            }
        }
        new_genes[ind++] = Genotype(genes[ first_pos ]);
        new_genes[ind]   = Genotype(genes[ vizinhos[second_pos].first ]);
    }
    return new_genes;
}


/* CROSSOVER */
void Population::one_point_crossover(Genotype& g1, Genotype& g2, function<double()>& random_num){
    // cout << "ONE POINT\n";
    int cross_point = (int) 1 + (random_num() * (this->gene_size -1));

    for(int i = 0; i < this->gene_size; i++){
        if(i >= cross_point) swap(g1.v_int[i],  g2.v_int[i]);
    }
}

void Population::two_point_crossover(Genotype& g1, Genotype& g2, function<double()>& random_num){
    // cout << "TWO POINT\n";
    int point_1, point_2;
    point_1 = (int) 1 + (random_num() * (this->gene_size -1));
    point_2 = (int) 1 + (random_num() * (this->gene_size -1));

    while(point_2 == point_1) point_2 = (int) 1 + (random_num() * (this->gene_size -1));
    if(point_1 > point_2) swap(point_1, point_2);

    for(int i = point_1; i < point_2; i++){
        swap(g1.v_int[i],  g2.v_int[i]);
    }
}

void Population::any_point_crossover(Genotype& g1, Genotype& g2, function<double()>& random_num){
    int size = max(g1.v_int.size(), g1.v_double.size());
    vector<int> mask = vector<int>(size, 0);

    for(int i = 0; i < size; i++){
        mask[i] = (random_num() > 0.5);
    }

    for(int i = 0; i < size; i++){
        if(mask[i]) swap(g1.v_int[i],  g2.v_int[i]);
    }
}

void Population::partially_matched_crossover(Genotype& g1, Genotype& g2, function<double()>& random_num){
    // cout << "PMX\n";
    int point_1, point_2;
    point_1 = (int) 1 + (random_num() * (this->gene_size -1));
    point_2 = (int) 1 + (random_num() * (this->gene_size -1));

    Genotype g1_copy = Genotype(g1);
    Genotype g2_copy = Genotype(g2);

    while(point_2 == point_1) point_2 = (int) 1 + (random_num() * (this->gene_size -1));
    if(point_1 > point_2) swap(point_1, point_2);

    for(int i = point_1; i < point_2; i++){
        swap(g1.v_int[i],  g2.v_int[i]);
    }

    for(int i = 0; i < (int) g1.v_int.size(); i++){
        if(i >= point_1 and i < point_2) continue;
        bool flag = true;
        while(flag){
            flag = false;
            for(int j = point_1; j < point_2; j++){
                if (g1.v_int[i] == g1.v_int[j]){
                    g1.v_int[i] = g1_copy.v_int[j];
                    flag = true;
                    break;
                }
            }
        }

        flag = true;
        while(flag){
            flag = false;
            for(int j = point_1; j < point_2; j++){
                if (g2.v_int[i] == g2.v_int[j]){
                    g2.v_int[i] = g2_copy.v_int[j];
                    flag = true;
                    break;
                }
            }
        }
    }
}

void Population::blend_alpha_crossover(Genotype& g1, Genotype& g2, function<double()>& random_num){
    int size = (int) g1.v_double.size();
    double alpha = 0.5;

    for(int i = 0; i < size; i++){
        double min_i, max_i, d_i;
        min_i = MIN(g1.v_double[i],  g2.v_double[i]);
        max_i = MAX(g1.v_double[i],  g2.v_double[i]);

        d_i = max_i - min_i;

        g1.v_double[i] = ( (max_i - d_i*alpha) - (min_i - d_i*alpha) ) * random_num() + (min_i - d_i*alpha);
        g2.v_double[i] = ( (max_i - d_i*alpha) - (min_i - d_i*alpha) ) * random_num() + (min_i - d_i*alpha);

        if(g1.v_double[i] < this -> lower_bound) g1.v_double[i] = this -> lower_bound;
        if(g1.v_double[i] > this -> upper_bound) g1.v_double[i] = this -> upper_bound;
        if(g2.v_double[i] < this -> lower_bound) g2.v_double[i] = this -> lower_bound;
        if(g2.v_double[i] > this -> upper_bound) g2.v_double[i] = this -> upper_bound;

    }
}

/* MUTAÇÃO */
void Population::binary_mutation(Genotype& g, function<double()>& random_num){
    // cout << "Binary MUTATION\n";
    double chance = this -> mutation_chance;

    for(int i = 0; i < (int) g.v_int.size(); i++){
        if( chance > random_num() )g.v_int[i] = !g.v_int[i];
    }
}

void Population::integer_mutation(Genotype& g, function<double()>& random_num){
    // cout << "Integer MUTATION\n";
    double chance = this -> mutation_chance;
    int size = this -> upper_bound - this -> lower_bound;

    for(int i = 0; i < (int) g.v_int.size(); i++){
        if( chance > random_num()){
            int num = (int) (random_num() * (size+1));
            num = num + this->lower_bound;
            g.v_int[i] = num;
        }
    }
}

void Population::swap_mutation(Genotype& g, function<double()>& random_num){
    // cout << "Swap MUTATION\n";
    double chance = this -> mutation_chance;

    for(int i=0; i < (int) g.v_int.size(); i++){
        int point_1, point_2;
        point_1 = i;
        point_2 = (int) (random_num() * this->gene_size);
        if(chance > random_num()){
            while(point_2 == point_1) point_2 = (int) (random_num() * this->gene_size);
            swap(g.v_int[point_1],  g.v_int[point_2]);
        }
    }
}

void Population::delta_mutation(Genotype& g, function<double()>& random_num){
    // cout << "Swap MUTATION\n";
    double chance = this -> mutation_chance;
    int size = (int) g.v_double.size();

    for(int i=0; i < size; i++){
        if(chance > random_num()){
            double num = (this -> upper_bound - this -> lower_bound) * random_num() + this -> lower_bound;
            int mult = (random_num() > 0.5) ? (1) : (-1);

            g.v_double[i] += num * mult;

            if(g.v_double[i] > this -> upper_bound) g.v_double[i] = this -> upper_bound;
            if(g.v_double[i] < this -> lower_bound) g.v_double[i] = this -> lower_bound;
        }
    }
}

void Population::michalewicz_mutation(Genotype& g, function<double()>& random_num){
    // cout << "Swap MUTATION\n";
    double chance = this -> mutation_chance;
    int size = (int) g.v_double.size();

    for(int i=0; i < size; i++){
        if(chance > random_num()){
			double xi = g.v_double[i];
			if(random_num() > 0.5){
				xi += michalewicz_delta(this -> current_generation,
					 					this -> upper_bound - xi, random_num);
			}
			else{
				xi -= michalewicz_delta(this -> current_generation,
					 					xi - this -> lower_bound, random_num);
			}

            if(xi > this -> upper_bound) xi = this -> upper_bound;
            if(xi < this -> lower_bound) xi = this -> lower_bound;
			g.v_double[i] = xi;
		}
    }
}

/* DIVERSIDADE */
double Population::inertia_diversity(vector<Genotype>& genes){
    double value = 0.0;
    vector<double> centroid = vector<double>(this -> gene_size, 0.0);

    for(int i = 0; i < this -> gene_size; i++){
        for(int j = 0; j < this -> pop_size; j++){
            centroid[i] += genes[j].v_int[i];
        }
        centroid[i] = centroid[i] / this -> pop_size;
    }

    for(int i = 0; i < this -> gene_size; i++){
        for(int j = 0; j < this -> pop_size; j++){
            value += pow(genes[j].v_int[i] - centroid[i], 2);
        }
    }

    // print_vector(centroid);
    // fprintf(stderr, "Diversity: %2f", value);
    return value;
}

double Population::manhattan_diversity(vector<Genotype>& genes){
    double value = 0.0;

    for(int i = 0; i < this -> pop_size; i++){
        for(int j = i + 1; j < this -> pop_size; j++){
            value += distance(genes[i], genes[j]);
        }
    }

    return value;
}

double Population::michalewicz_delta(double t, double y, function<double()>& random_num){
	double value;
	double a = random_num();
	double b = 5;
	double T = this -> generations;
	double exponent = pow( (1 - t/T) , b);

	value = y * ( 1 - pow(a, exponent) );

	return value;
}

void Population::info(Input_Parser parser){
    cerr << endl;
    cerr << "Population size: " << this -> pop_size << endl;
    cerr << "Genotype size: "   << this -> gene_size << endl;
    cerr << "Codification: "    << this -> codification << endl;
    cerr << "Lower bound: "    << this -> lower_bound << endl;
    cerr << "Upper bound: "    << this -> upper_bound << endl;
    cerr << "K: "  << this -> k  << endl;
    cerr << "Kp: " << this -> kp << endl;
    cerr << "d: "  << this -> d  << endl;
    cerr << "Crossover: " << this -> crossover_chance << endl;
    cerr << "Mutacao: "   << this -> mutation_chance  << endl;
    cerr << "Elitismo: " << this -> elitism << endl;

    cerr << "Generations: " << this -> generations << endl;
    cerr << "Runs: " << parser.runs << "\n\n";
}

void Population::info(Input_Parser parser, string file_path){
	FILE* file;
    file = fopen(file_path.c_str(), "a");

    fprintf(file, "Population size: %d\n", this -> pop_size);
    fprintf(file, "Genotype size: %d\n", this -> gene_size);
    fprintf(file, "Codification: %d\n", this -> codification);
    fprintf(file, "Lower bound: %.2f\n", this -> lower_bound);
    fprintf(file, "Upper bound: %.2f\n", this -> upper_bound);
    fprintf(file, "K: %d\n", this -> k);
    fprintf(file, "Kp: %.2f\n", this -> kp);
    fprintf(file, "d: %d\n", this -> d );
    fprintf(file, "Crossover: %.2f\n", this -> crossover_chance);
    fprintf(file, "Mutacao: %.2f\n", this -> mutation_chance);
    fprintf(file, "Elitismo: %d\n", this -> elitism);

    fprintf(file, "Generations: %d\n", this -> generations);
    fprintf(file, "Runs: %d\n\n", parser.runs);

	fclose(file);
}

void swap(int& a, int& b){
    int aux = a;
    a = b;
    b = aux;
}

int mod(int a, int b){
    return ((a % b) + b) % b;
}

void merge_sort(vector<pair<int, double> > &v, int left, int right){
    if (left < right){
        int mid = left + (right - left) / 2;
        merge_sort(v, left, mid);
        merge_sort(v, mid+1, right);

        merge(v, left, mid, right);
    }
}

void merge(vector<pair<int, double> > &v, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int i, j, k;

    vector<pair<int, double> > L = vector<pair<int, double> >(n1);
    vector<pair<int, double> > R = vector<pair<int, double> >(n2);

    for(i = 0; i < n1; i++)
        L[i] = v[left + i];
    for(j = 0; j < n2; j++)
        R[j] = v[mid + j + 1];

    i = 0; j = 0; k = left;
    while (i < n1 && j < n2){
        if (L[i].second <= R[j].second) v[k] = L[i++];
        else v[k] = R[j++];
        k++;
    }

    while (i < n1) v[k++] = L[i++];
    while (j < n2) v[k++] = R[j++];

}

int distance(Genotype& g1, Genotype& g2){
    int value = 0;
	int size = MAX(g1.v_int.size(), g1.v_double.size());

    for(int i=0; i < size; i++){
		if(g1.v_int.size() >= g1.v_double.size())
        	value += abs(g1.v_int[i] - g2.v_int[i]);
		else
			value += abs(g1.v_double[i] - g2.v_double[i]);
    }
    return value;
}
