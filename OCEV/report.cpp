#include "report.hpp"

Report::Report(){
    this -> the_bests = vector<pair<Genotype, double>>(0);
    this -> runs   = -1;
    this -> average_fitness  = -1;
    this -> average_value = -1;
    this -> desvio_fitness = -1;
    this -> desvio_value = -1;
}

Report::Report(Input_Parser parser){
    this -> runs = parser.runs;
    this -> generations = parser.generations;
    this -> average_fitness  = 0.0;
    this -> average_value = 0.0;

    this -> desvio_fitness = 0.0;
    this -> desvio_value = 0.0;
    this -> file = parser.file;


    this -> the_bests = vector<pair<Genotype, double>>(this -> runs);
    for(int i = 0; i < this -> runs; i++)
        this -> the_bests[i] = {Genotype(), 0.0};

    this -> best_fit  = vector< vector<double> >(this -> runs, vector<double>(this -> generations,  0.0) );
    this -> average   = vector< vector<double> >(this -> runs, vector<double>(this -> generations,  0.0) );
    this -> worst_fit = vector< vector<double> >(this -> runs, vector<double>(this -> generations, -1.0) );

    this -> diversity = vector< vector<double> >(this -> generations, vector<double>(this -> runs,  0.0) );

    this -> best_fit_final  = vector<double>(this -> generations, 0.0);
    this -> average_final   = vector<double>(this -> generations, 0.0);
    this -> worst_fit_final = vector<double>(this -> generations, 0.0);

    this -> my_parser = parser;
    switch (parser.fit_function){
        case 0:
            this -> decoder = std::bind(&Report::n_queens_decoder, this,
										std::placeholders::_1, std::placeholders::_2);
            break;

        case 1:
            this -> decoder = std::bind(&Report::weight_n_queens_decoder, this,
										std::placeholders::_1, std::placeholders::_2);
            break;

        case 2:
            this -> decoder = std::bind(&Report::radio_factory_decoder, this,
										std::placeholders::_1, std::placeholders::_2);
            break;


        case 3:
            this -> decoder = std::bind(&Report::maze_decoder, this,
										std::placeholders::_1, std::placeholders::_2);
            break;

        case 4:
            this -> decoder = std::bind(&Report::keane_bump_decoder, this,
										std::placeholders::_1, std::placeholders::_2);
            break;

        case 5:
            this -> decoder = std::bind(&Report::michalewicz_decoder, this,
										std::placeholders::_1, std::placeholders::_2);
            break;

        default:
            break;
    }
}

void Report::basic(){
    int best = 0;
    double average_value = 0.0, desvio_value = 0.0;
	string extra_info = "";

    // Calculando média dos valores de função
    for(int run = 0; run < this -> runs; run++){
        double value = this -> decoder(this -> the_bests[run].first, extra_info);

        cerr << "\n• RUN (" << run << "):" << endl;
        cerr << "    -> Configuracao: ";
        this -> the_bests[run].first.show(); cerr << endl;
        // print_board(this -> the_bests[run].first);
        cerr << "    -> Value: " << value << endl;


        if(this -> the_bests[run].second > this -> the_bests[best].second)
            best = run;
        average_value += (value / this -> runs);
    }

    // Calculando desvio padrão
    for(int run = 0; run < this->runs; run++){
        double value = this -> decoder(this -> the_bests[run].first, extra_info);

        desvio_value   += pow((value - average_value), 2) / this -> runs;
    }
    desvio_value = sqrt(desvio_value);


    // Report
    cerr << "\n------------------\n";
    cerr << "• Media: " << average_value << "\n\n";
    cerr << "• Desvio: " << desvio_value << "\n\n";

    cerr << "• THE BEST:\n";
    cerr << "    -> Run: " << best << endl;
    cerr << "    -> Configuracao: ";
    this -> the_bests[best].first.show(); cerr << endl;
    cerr << "    -> " << this -> decoder(this -> the_bests[best].first, extra_info) << endl;
    // print_board(this -> the_bests[best].first);
    cerr << "    -> Fitness: ";
    cerr << this -> the_bests[best].second << endl;
}

void Report::advanced(){
    int best = 0;
    double average_value = 0.0, desvio_value = 0.0;
	string extra_info = "";

    // Calculando média dos valores de função
    for(int run = 0; run < this -> runs; run++){
        double value = this -> decoder(this -> the_bests[run].first, extra_info);

        cerr << "\n• RUN (" << run << "):" << endl;
        cerr << "    -> Configuracao: ";
            this -> the_bests[run].first.show(); cerr << endl;

        fprintf(stderr, "    -> Valor: %.2f\n", value);

        if(this -> the_bests[run].second > this -> the_bests[best].second)
            best = run;
        average_value += (value / this -> runs);
    }

    // Calculando desvio padrão
    for(int run = 0; run < this->runs; run++){
        double value = this -> decoder(this -> the_bests[run].first, extra_info);
        desvio_value += pow((value - average_value), 2) / this -> runs;
    }
    desvio_value = sqrt(desvio_value);


    // Report
    cerr << "\n------------------\n";
    fprintf(stderr, "• Media:  %.3f\n\n", average_value);
    fprintf(stderr, "• Desvio: %.3f\n\n", desvio_value);

    cerr << "• THE BEST:\n";
    cerr << "    -> Run: " << best << endl;
    cerr << "    -> Configuracao: ";
    this -> the_bests[best].first.show(); cerr << endl;
	double valor_final = this -> decoder(this -> the_bests[best].first, extra_info);
    fprintf(stderr, "    -> Valor: %.3f\n", valor_final);
    fprintf(stderr, "    -> Fitness: %.4f\n", this -> the_bests[best].second);
	cerr << extra_info;

	// Report in file
	printf("• Media:  %.3f\n\n", average_value);
	printf("• Desvio: %.3f\n\n", desvio_value);

	cout << "• THE BEST:\n";
	cout << "    -> Run: " << best << endl;
	cout << "    -> Configuracao: ";
	this -> the_bests[best].first.show(2);

	if(this -> my_parser.fit_function == 3){
		maze_print(this -> the_bests[best].first);
	}

	printf("    -> Valor: %.3f\n", valor_final);
	printf("    -> Fitness: %.4f\n", this -> the_bests[best].second);
	cout << extra_info;

    // print_board(this -> the_bests[best].first);

    this -> print_file(this -> my_parser);
}

void Report::diversity_report(){
    vector<double> div_avg = vector<double>(this -> generations, 0);
    ofstream div_file;
    double max = 0;;
    div_file.open(this -> file + "-div.data");

    div_file << this -> generations << endl;


    for(int g = 0; g < this -> generations; g++){
        div_avg[g] = 0;
        for(int r = 0; r < this -> runs; r++){
            div_avg[g] += this -> diversity[g][r];
        }
        div_avg[g] = div_avg[g] / this -> runs;
        if(div_avg[g] > max) max = div_avg[g];
    }

    for(int g = 0; g < this -> generations; g++)
        div_file << div_avg[g] / max << endl;

    div_file.close();
}

void Report::print_file(Input_Parser parser){
    FILE* file;
    string output_file = this->file + ".txt";

    file = fopen(output_file.c_str(), "w");

    switch (parser.fit_function){
        case 0:
            fprintf(file, "N-Queens %d\n", parser.gene_size);
            break;

        case 1:
            fprintf(file, "Weighted N-Queens %d\n", parser.gene_size);
            break;

        case 2:
            fprintf(file, "Radio Factory\n");
            break;

        case 3:
            fprintf(file, "Maze\n");
            break;

        case 4:
            fprintf(file, "Keane's Bump Test\n");
            break;

        case 5:
            fprintf(file, "Michalewicz\n");
            break;

        default:
            break;
    }

    switch (parser.selection){
        case 0:
            fprintf(file, "Roleta\n");
            break;

        case 1:
            fprintf(file, "Ranking Uniforme\n");
            break;

        case 2:
            fprintf(file, "Torneio Estocastico\n");
            break;

        case 3:
            fprintf(file, "Vizinhanca Linear - BEST\n");
            break;

        case 4:
            fprintf(file, "Vizinhanca Linear - RANDOM\n");
            break;

        case 5:
            fprintf(file, "Vizinhanca Linear - PROPORCIONAL\n");
            break;

        default:
            break;
    }

    switch (parser.crossover){
        case 0:
            fprintf(file, "One Point\n");
            break;

        case 1:
            fprintf(file, "Two Point\n");
            break;

        case 2:
            fprintf(file, "Any Points\n");
            break;

        case 3:
            fprintf(file, "Partially Matched\n");
            break;

        case 4:
            fprintf(file, "Blend Alpha\n");
            break;

        default:
            break;
    }

    switch (parser.mutation){
        case 0:
            fprintf(file, "Binary Mutation\n");
            break;

        case 1:
            fprintf(file, "Integer Mutation\n");
            break;

        case 2:
            fprintf(file, "Swap Mutation\n");
            break;

        case 3:
            fprintf(file, "Delta Mutation\n");
            break;

		case 4:
            fprintf(file, "Michalewicz Mutation\n");
            break;

        default:
            break;
    }

    fprintf(file, "%.0f %%\n", parser.crossover_chance * 100);
    fprintf(file, "%.0f %%\n", parser.mutation_chance * 100);

    if(parser.elitism) fprintf(file, "Com Elitismo\n");
    else fprintf(file, "Sem Elitismo\n");

    fprintf(file, "%d\n", parser.generations);


    for (int g = 0; g < this->generations; g++){
        for(int run = 0; run < this -> runs; run++){
            this -> best_fit_final[g]  += this -> best_fit[run][g];
            this -> average_final[g]   += this -> average[run][g];
            this -> worst_fit_final[g] += this -> worst_fit[run][g];
        }
        this -> best_fit_final[g]  /= this -> runs;
        this -> average_final[g]   /= this -> runs;
        this -> worst_fit_final[g] /= this -> runs;
    }


    for (int g = 0; g < this->generations; g++){
        fprintf(file, "%.2f\n%.2f\n%.2f\n\n", best_fit_final[g], average_final[g], worst_fit_final[g]);
    }


    fclose(file);
}

void Report::show_fitness(){
    for(int run = 0; run < this->runs; run++){
        for(int g = 0; g < this->generations; g++)
            fprintf(stderr, "%.2f\n%.2f\n%.2f\n\n", best_fit[run][g], average[run][g], worst_fit[run][g]);
        cout << "============\n";
    }
}

double Report::n_queens_decoder(Genotype g, string& extra_info){
    double value = 0;
    vector<int> queen_check = vector<int>(g.v_int.size(), 1);

    for(int i = 0; i < (int) g.v_int.size(); i++){
        for(int j = i+1; j < (int) g.v_int.size(); j++){
            int xi, xj;
            int yi, yj;

            xi = g.v_int[i];
            yi = i;

            xj = g.v_int[j];
            yj = j;

            if(abs(xi - xj) == abs(yi - yj)){
                queen_check[yi] = max(0, queen_check[yi]-1);
                queen_check[yj] = max(0, queen_check[yj]-1);
            }
        }
    }
    for(int i = 0; i < (int) queen_check.size(); i++) value += queen_check[i];

	extra_info = "";
    return value;
}

double Report::weight_n_queens_decoder(Genotype g, string& extra_info){
    vector< vf > weight_table;
    vector<int> queen_check = vector<int>(g.v_int.size(), 1);
    double weight_max, value = 0;
    int g_size = g.v_int.size();

    weight_table = vector<vf>(g_size, vf(g_size, 0.0));
    weight_max = 0.0;
    double count = 0;
    for (int i = 0; i < g_size; i++){
        for (int j = 0; j < g_size; j++){
            if(i % 2 == 0)
                weight_table[i][j] = sqrt(++count);
            else
                weight_table[i][j] = log10(++count);

            if(i == g_size - 2) weight_max += weight_table[i][j];
        }
    }


    for(int i = 0; i < (int) g_size; i++){
        for(int j = i+1; j < (int) g_size; j++){
            int xi, xj;
            int yi, yj;

            xi = g.v_int[i];
            yi = i;

            xj = g.v_int[j];
            yj = j;

            if(abs(xi - xj) == abs(yi - yj)){
                queen_check[yi] = max(0, queen_check[yi]-1);
                queen_check[yj] = max(0, queen_check[yj]-1);
            }
        }
    }
    for(int i = 0; i < (int) queen_check.size(); i++){
        int x, y;
        x = i;
        y = g.v_int[i];
        value += queen_check[i] * weight_table[x][y];
    }
	extra_info = "";
    return value;
}

double Report::radio_factory_decoder(Genotype g, string& extra_info){
    int luxury = 0, standard = 0;
    double value = 0;

    for(int j = 0; j < 5; j++){
        luxury  += pow(2, j) * g.v_int[j];
        standard += pow(2, j) * g.v_int[j+5];
    }

    luxury = (1.0 * luxury / 31.0) * 16.0;
    standard = (1.0 * standard / 31.0) * 24.0;

    value = (30.0 * standard + 40.0 * luxury);

	extra_info= "    -> Luxury: " + to_string(luxury) +
				" | Standard: " + to_string(standard) + "\n";

	return value;
}

double Report::maze_decoder(Genotype g, string& extra_info){
    int x, y;
    int dist;
    string s = "";

    pair<int, int> start_point = {1, 10};
    pair<int, int> end_point   = {20, 1};
    vector<vector <int> > maze = vector<vector <int> >(30, vector <int> (25, 0.0));
    maze = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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

    x = start_point.first;
    y = start_point.second;
    vector<vector<int> > maze_copy = vector<vector<int> >(maze);
    int it, hit_count = 0;
    int visitado = 0;
    for(it = 0; it < (int) g.v_int.size(); it++){
        if(maze_copy[y][x] == 3) break;
        if(maze_copy[y][x] == 4) visitado++;
        maze_copy[y][x] = 4;

        switch(g.v_int[it]){
            case RIGHT:
                if( maze_copy[y][x+1] != 0 and (maze_copy[y][x+1] != 4 ) ){
                    x++;
                }
                else hit_count++;
            break;

            case UP:
                if( maze_copy[y-1][x] != 0 and (maze_copy[y-1][x] != 4 ) ){
                    y--;
                }
                else hit_count++;
            break;

            case LEFT:
                if( maze_copy[y][x-1] != 0 and (maze_copy[y][x-1] != 4 ) ){
                    x--;
                }
                else hit_count++;
            break;

            case DOWN:
                if( maze_copy[y+1][x] != 0 and (maze_copy[y+1][x] != 4 ) ){
                    y++;
                }
                else hit_count++;
            break;
        }
    }

    cerr << "Maze: \n";
    for(int i = 0; i < (int) maze.size(); i++){
        for(int j = 0; j < (int) maze[i].size(); j++){
            if(i == y and j == x) cerr << "X ";
            else{
                if(maze_copy[i][j] == 0) cerr << "\u25A0 ";
                else if(maze_copy[i][j] == 1) cerr << "  ";
                else if(maze_copy[i][j] == 2) cerr << "E ";
                else if(maze_copy[i][j] == 3) cerr << "S ";
                else if(maze_copy[i][j] == 4) cerr << "o ";
            }
        }
        cerr << "\n";
    }


    pair<int, int> point = {x, y};
    dist = abs(point.first - end_point.first) + abs(point.second - end_point.second);

	extra_info= "    -> Distancia: " + to_string(dist) +
				" (x: " + to_string(x) + ", y: " + to_string(y) + ") -> " +
				to_string(it) + " passos e " +  to_string(hit_count) + " colisoes!\n";

    return dist;
}

double Report::keane_bump_decoder(Genotype g, string& extra_info){
    double value = 0.0;
    double sum1 = 0.0, sum2 = 0.0, mul = 1.0;
    int n = (int) g.v_double.size();

    for(int i = 0; i < n; i++){
        double xi = g.v_double[i];
        sum1 += cos(xi) * cos(xi) * cos(xi) * cos(xi);
        mul  *= cos(xi) * cos(xi);
        sum2 += xi * xi * (i+1);
    }
	sum2 = sqrt(sum2);

    value = abs(sum1 - 2 * mul) / sum2;

	extra_info = "";
	// extra_info= "    -> Value: " + to_string(value) +
	//			   " / " + to_string(g.v_int.size()) + "\n";

    return value;
}

double Report::michalewicz_decoder(Genotype g, string& extra_info){
    double value = 0.0;
    double pi = 3.14159265358979323846;
    int n = (int) g.v_double.size();

    for(int i = 0; i < n; i++){
        double xi = g.v_double[i];

        value += std::sin( xi ) * pow( std::sin( (i + 1) * xi * xi / pi ), 2*n);
    }
	extra_info = "";
	// extra_info= "    -> Value: " + to_string(value) +
	//  			" / " + to_string(g.v_int.size()) + "\n";

    return value;
}

void maze_print(Genotype g){
	int x, y;

    pair<int, int> start_point = {1, 10};
    vector<vector <int> > maze = vector<vector <int> >(30, vector <int> (25, 0.0));
    maze = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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

    x = start_point.first;
    y = start_point.second;
    vector<vector<int> > maze_copy = vector<vector<int> >(maze);
    int it, hit_count = 0;
    int visitado = 0;
    for(it = 0; it < (int) g.v_int.size(); it++){
        if(maze_copy[y][x] == 3) break;
        if(maze_copy[y][x] == 4) visitado++;
        maze_copy[y][x] = 4;

        switch(g.v_int[it]){
            case RIGHT:
                if( maze_copy[y][x+1] != 0 and (maze_copy[y][x+1] != 4 ) ){
                    x++;
                }
                else hit_count++;
            break;

            case UP:
                if( maze_copy[y-1][x] != 0 and (maze_copy[y-1][x] != 4 ) ){
                    y--;
                }
                else hit_count++;
            break;

            case LEFT:
                if( maze_copy[y][x-1] != 0 and (maze_copy[y][x-1] != 4 ) ){
                    x--;
                }
                else hit_count++;
            break;

            case DOWN:
                if( maze_copy[y+1][x] != 0 and (maze_copy[y+1][x] != 4 ) ){
                    y++;
                }
                else hit_count++;
            break;
        }
    }

    cerr << "Maze: \n";
    for(int i = 0; i < (int) maze.size(); i++){
        for(int j = 0; j < (int) maze[i].size(); j++){
            if(i == y and j == x) cout << "X ";
            else{
                if(maze_copy[i][j] == 0) cout << "\u25A0 ";
                else if(maze_copy[i][j] == 1) cout << "  ";
                else if(maze_copy[i][j] == 2) cout << "E ";
                else if(maze_copy[i][j] == 3) cout << "S ";
                else if(maze_copy[i][j] == 4) cout << "o ";
            }
        }
        cout << "\n";
    }
}
