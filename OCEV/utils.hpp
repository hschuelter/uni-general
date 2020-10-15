#ifndef UTILS_HPP
#define UTILS_HPP

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

/* --- INCLUDES --- */
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <functional>
#include <fstream>
#include <set>

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#include "population.hpp"
#include "report.hpp"

/* --- NAMESPACE --- */
using namespace std;

/* --- DEFINES --- */
#define INFINITE 0x3f3f3f3f
#define BINARY 0
#define INTEGER 1
#define PERMUTATION 2
#define REAL 3

#define RIGHT 0
#define UP    1
#define LEFT  2
#define DOWN  3

#define PI 3.14159265358979323846

/* --- TYPEDEFS --- */
typedef vector<int> vi;
typedef vector<double> vf;

/* --- FUNCTIONS --- */
void set_fit_function(function<vector<double>(Population&, vector<Genotype>&)>& f, Input_Parser parser);

/*  --- FITNESS --- */
vf n_queens(Population& p, vector<Genotype>& individuos);
vf weight_n_queens(Population& p, vector<Genotype>& individuos);
vf arithmetic_function(Population& p, double (*f)(double));
vf radio_factory(Population& p, vector<Genotype>& individuos);
vf maze_solver(Population& p, vector<Genotype>& individuos);
vf keane_bump(Population& p, vector<Genotype>& individuos);

vf michalewicz(Population& p, vector<Genotype>& individuos);

/* --- SCALING --- */
vf linear_scaling(vf& old_fitness, double c);

double foo(double x);
double normalize(double value, double max, double min);
double bin_2_real(vi& bin, double lower, double upper, double precision);

/* --- GA STUFF --- */
Genotype cleaning(Genotype& g, function<double()>& random_num);
vector<Genotype> generation_gap(vector<Genotype>& old_pop, vector<Genotype>& new_pop, double g, function<double()>& random_num);
vector<Genotype> standard_crowding(Population& pop, vector<Genotype>& old_pop);
vector<Genotype> deterministic_crowding(Population& pop, function<vector<double>(Population&, vector<Genotype>&)>& fit_function);
vector<double> fitness_sharing(vf& old_fitness, vector<Genotype>& individuos, double alpha, double rho);

double geno_distance(Genotype& g1, Genotype& g2);

double distance(pair<int, int>& p1, pair<int, int>& p2);
vi slice(vi v, int b, int e);
void print_vector(vf& v);
void print_vector(vi& v);
void print_board(Genotype& g);

#endif
