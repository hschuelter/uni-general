#ifndef UTILS_HPP
#define UTILS_HPP

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <cmath>

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Ant.hpp"
#include "Item.hpp"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace std::chrono;

#define INFINITE 0x3f3f3f3f

#define WINDOW_X 600
#define WINDOW_Y WINDOW_X + 20


typedef vector<int> v1d;
typedef vector<v1d> v2d;

typedef vector<Item> v1I;
typedef vector<v1I> v2I;

void setup(v2I& grid, vector<Ant>& ants, int tam, int items, int num, int raio, double alpha, double sigma);

void draw(v2I& grid, vector<Ant>& ants, sf::RenderWindow& win, int current, int total);
void draw(v2I& grid, vector<Ant>& ants, sf::RenderWindow& win);
void draw_map(v2I& grid, vector<Ant>& ants, sf::RenderWindow& win);

void printColor(v2I& grid);
void waitKey();
#endif
