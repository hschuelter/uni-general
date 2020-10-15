#ifndef REPORT_HPP
#define REPORT_HPP

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#include <iostream>
#include <vector>
#include <fstream>

#include "genotype.hpp"
#include "input_parser.hpp"


#define RIGHT 0
#define UP    1
#define LEFT  2
#define DOWN  3

typedef vector<double> vf;

using namespace std;

class Report{

    public:
        vector< pair<Genotype, double> > the_bests;
        std::function<double(Genotype g, string& extra_info)> decoder;

        int runs, generations;
        double average_fitness, average_value, desvio_fitness, desvio_value;
        string file;

        vector< vector<double> > best_fit;
        vector< vector<double> > average;
        vector< vector<double> > worst_fit;


        vector<double> best_fit_final;
        vector<double> average_final;
        vector<double> worst_fit_final;

        vector< vector<double> > diversity;
        Input_Parser my_parser;

        Report();
        Report(Input_Parser parser);

        void basic();
        void advanced();

        void diversity_report();

        void print_file(Input_Parser parser);
        void show_fitness();
        double n_queens_decoder(Genotype g, string& extra_info);
        double weight_n_queens_decoder(Genotype g, string& extra_info);
        double radio_factory_decoder(Genotype g, string& extra_info);
        double maze_decoder(Genotype g, string& extra_info);
        double keane_bump_decoder(Genotype g, string& extra_info);
        double michalewicz_decoder(Genotype g, string& extra_info);

};
void maze_print(Genotype g);

#endif
