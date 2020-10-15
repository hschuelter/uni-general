#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <iostream>
#include <vector>

#include "genotype.hpp"
#include "input_parser.hpp"

using namespace std;

class Population{

    public:
        vector<Genotype> genes;

        int gene_size;
        int pop_size;
        int codification;
        int generations;
		int current_generation;
        double lower_bound, upper_bound;
        int k;
        double kp;
        int d;
        double crossover_chance;
        double mutation_chance;
        bool elitism;
        double c_begin, c_end;

        mt19937 generator;
        function<double()> real_rand;
        function<vector<Genotype>(vector<double>&, vector<Genotype>&)> selection;
        function<void(Genotype&, Genotype&)> crossover;
        function<void(Genotype&)> mutation;
        function<double(vector<Genotype>&)> diversity;

        Population();
        Population(Input_Parser parser);

        /* SELEÇÃO */
        vector<Genotype> roulette_selection(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num);
        vector<Genotype> uniform_ranking(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num);
        vector<Genotype> stochastic_tournament(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num);
        vector<Genotype> linear_neighbourhood_best(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num);
        vector<Genotype> linear_neighbourhood_random(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num);
        vector<Genotype> linear_neighbourhood_proporcional(vector<double> fitness, vector<Genotype>& genes, function<double()>& random_num);

        /* CROSSOVER */
        void one_point_crossover(Genotype& g1, Genotype& g2, function<double()>& random_num);
        void two_point_crossover(Genotype& g1, Genotype& g2, function<double()>& random_num);
        void any_point_crossover(Genotype& g1, Genotype& g2, function<double()>& random_num);
        void partially_matched_crossover(Genotype& g1, Genotype& g2, function<double()>& random_num);
        void blend_alpha_crossover(Genotype& g1, Genotype& g2, function<double()>& random_num);

        /* MUTAÇÃO */
        void binary_mutation(Genotype& g, function<double()>& random_num);
        void integer_mutation(Genotype& g, function<double()>& random_num);
        void swap_mutation(Genotype& g, function<double()>& random_num);
		void delta_mutation(Genotype& g, function<double()>& random_num);
        void michalewicz_mutation(Genotype& g, function<double()>& random_num);

        /* DIVERSIDADE */
        double inertia_diversity(vector<Genotype>& genes);
        double manhattan_diversity(vector<Genotype>& genes);

        /* EXTRAS */
		void info(Input_Parser parser);
        void info(Input_Parser parser, string file_path);
		double michalewicz_delta(double t, double y, function<double()>& random_num);
};

int mod(int a, int b);
void swap(int& a, int& b);

void merge_sort(vector<pair<int, double> > &v, int left, int right);
void merge(vector<pair<int, double> > &v, int left, int mid, int right);

int distance(Genotype& g1, Genotype& g2);

#endif
