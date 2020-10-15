#include "utils.hpp"

int main(int argc, char** argv){
    if(argc != 47){
        Input_Parser parser = Input_Parser();
        parser.error_message();
        return 0;
    }
    Input_Parser parser(argc, argv);
    Population p;
    Report rp;
    int run_count = 0;

    function<vector<double>(Population&, vector<Genotype>&)> fit_function;
    set_fit_function(fit_function, parser);

    rp = Report(parser);
    p = Population(parser);
	p.info(parser);
    p.info(parser, "./Results/all-final.txt");

    #pragma omp parallel for shared(run_count, rp) num_threads(8) schedule(dynamic)
    for(int run = 0; run < parser.runs; run++){
        Population pop = Population(parser);
        double linear_c, linear_step;
        linear_c = pop.c_begin;
        linear_step = (pop.c_end - pop.c_begin) / pop.generations;


        for(int g = 0; g < pop.generations; g++){
            pair<int, double> best  = pair<int, double>(0, 0.0);
            pair<int, double> worst = pair<int, double>(0, 1.0);
            Genotype best_gen;
            double average = 0.0;
            vf fitness;

            vector<Genotype> old_pop(pop.pop_size, Genotype(pop.gene_size, pop.codification, pop.lower_bound, pop.upper_bound));


			pop.current_generation = g;
            // Fitness Evaluation ----------
            fitness = fit_function(pop, pop.genes);

            // cerr << "-------------------------------------\n";
            for(int i = 0; i < pop.pop_size; i++){
                // fprintf(stderr, "%2d -> ", i);
                // pop.genes[i].show(); cerr << " | ";
                // cerr << fitness[i] << endl;

                old_pop[i] = Genotype(pop.genes[i]);

                average += fitness[i];
                if(fitness[i] > best.second)  best  = {i,fitness[i]};
                if(fitness[i] < worst.second) worst = {i,fitness[i]};

                if(fitness[i] > rp.the_bests[run].second)
                    rp.the_bests[run] = {Genotype(pop.genes[i]), fitness[i]};
            }
            best_gen = Genotype(pop.genes[ best.first ]);

            rp.best_fit[run][g]  = best.second;
            rp.average[run][g]   = average / pop.pop_size;
            rp.worst_fit[run][g] = worst.second;

			// Fitness Sharing ----------
			fitness = fitness_sharing(fitness, pop.genes, parser.alpha, parser.rho);

            // Linear Scaling ----------
            // fitness = linear_scaling(fitness, linear_c);

            // Selection ----------
			pop.genes = pop.selection(fitness, pop.genes);

            // Genetic Operations ----------
            #pragma omp parallel for
            for(int ind = 0; ind < pop.pop_size; ind += 2){
                if(pop.real_rand() <= pop.crossover_chance){
					pop.crossover(pop.genes[ind], pop.genes[ind+1]);
                }

                pop.mutation(pop.genes[ind]);
                pop.mutation(pop.genes[ind+1]);
            }

            // Generation Gap ----------
            pop.genes = generation_gap(old_pop, pop.genes, parser.gap, pop.real_rand);

            // Elitism ----------
            if(pop.elitism){
                int worst = 0;
                fitness = fit_function(pop, pop.genes);

                for(int i = 0 ; i < (int) fitness.size(); i++){
                    if(fitness[i] < fitness[worst]) worst = i;
                }

                pop.genes[worst] = Genotype(best_gen);
                fitness[worst] = best.second;
            }

			// Crowding ----------
			// pop.genes = standard_crowding(pop, old_pop);
			// pop.genes = deterministic_crowding(pop, fit_function);

            rp.diversity[g][run] = pop.diversity(pop.genes);

            // fprintf(stderr, "    [%d / %d]\r", g+1, pop.generations);
            linear_c += linear_step;
        }
        run_count++;
        fprintf(stderr, "    -> Run: %4d / %d\n", run_count, parser.runs);
    }


    rp.advanced();
    // rp.basic();
    rp.diversity_report();

    // delete &rp;
    // delete &pop;

    return 0;
}
