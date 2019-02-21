
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include <vector>

#define NUMBER 100000 
#define ACCURACY 0.00001

using namespace std;

typedef vector<int> v1d;


void bubbleSort(int *v, int n);
void selectionSort(int *v, int n);
void insertionSort(int *v, int n);

int fib(int n);
int fibVetor(int n, int position, v1d v);
int fibonice(int n, int value, int prev);

int power(int base, int expo);
float sqr_root(float n, float upper, float bottom);

void formatTime(int n);

void random(int n);
void clear();
