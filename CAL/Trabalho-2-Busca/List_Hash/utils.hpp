#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <iostream>
#include <iterator> 
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using namespace std::chrono;

#define INFINITE 0x3f3f3f3f

typedef pair<string, string> full_name;
typedef pair<int, full_name > data;

typedef vector<data> v1d;
typedef vector<v1d> v2d;

int hashing(string str);

void swap(int* a, int* b);
int randomNumber(int upper);

#endif
