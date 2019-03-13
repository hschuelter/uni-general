#ifndef UTILS_HPP
#define UTILS_HPP

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

/* --- INCLUDES --- */
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

/* --- NAMESPACE --- */
using namespace std;
using namespace std::chrono;

/* --- DEFINES --- */
#define INFINITE 0x3f3f3f3f
#define PI 3.14159265358979

/* --- TYPEDEFS --- */
typedef vector<int> vi;
typedef vector<vi> v2i;

typedef vector<bool> vb;

typedef vector< pair<int, bool> > v_ib;
typedef vector<v_ib> vv_ib;


/* --- FUNCTIONS --- */
int  solve(vb& var, vv_ib& clau, double temp, int previous, int it);
void randomize(vb& var, double value);
void cooldown(double temp_i, double temp_f, double& temperature, int schedule, int it, int num_it);

int  r_solve(vb& var, vv_ib& clau, int previous, int it);

bool XOR(bool a, bool b);

#endif
