#ifndef UTILS_HPP
#define UTILS_HPP

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Ant.hpp"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace std::chrono;

#define INFINITE 0x3f3f3f3f

#define WINDOW_X 600
#define WINDOW_Y WINDOW_X + 20


typedef vector<int> v1d;
typedef vector<v1d> v2d;

void setup(v2d& mat, vector< vector<bool> >& ant_position, vector<Ant>& ants, int tam, int items, int num, int raio);

void terminalPrint(v2d& mat, vector<Ant>& ants, int op, int current, int total);
void printAnts(v2d& mat, vector<Ant>& ants);
void printRadius(v2d& mat, vector<Ant>& ants);
void printMat(v2d& mat);

void draw_map(v2d& mat, vector<Ant>& ants, sf::RenderWindow& win);
void draw(v2d& mat, vector<Ant>& ants, sf::RenderWindow& win, int current, int total);

#endif
