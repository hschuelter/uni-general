#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

#define INFINITE 0x3f3f3f3f

typedef vector<int> v1d;
typedef vector<v1d> v2d;

void find(map<pair<string, string>, int > mapping, string nome, string snome);
void printMap(map<pair<string, string>, int > mapping);

void swap(int* a, int* b);
int randomNumber(int upper);

int hashStr(string str);

#endif
