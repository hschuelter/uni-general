//#include <bits/stdc++.h>

#ifdef WINDOWS
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <ctime>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <cstdlib>
//#include <math.h>

using namespace std;
using namespace std::chrono;

typedef long long int lli;
typedef vector<long long int> v1d;
typedef vector<v1d> v2d;

#define INFINITE 0x3f3f3f3f

void bubbleSort(v1d &v);
void selectionSort(v1d &v);
void insertSort(v1d &v);

/* Merge Sort */
void mergeSort(v1d &v, lli begin, lli end);
void merge(v1d &v, lli begin, lli middle, lli end);

/* Quick Sorts */
void quickSort1(v1d &v, lli begin, lli end);
lli partition(v1d &v, lli begin, lli end);

void quickSort2(v1d &v, lli begin, lli end);
lli randomNumber(lli upper);

/*Heap Sort*/
void heapSort(v1d &v, int n);
void letItHeap(v1d &v, int n);
void heapify(v1d &v, lli n, lli i);
lli left(lli a);
lli right(lli a);

/* Counting Sort */
void countingSort(v1d &v);
lli findMaximum(v1d v);

/* Bucket Sort */
void bucketSort(v1d &v);



/* FUNCOES EXTRAS */
v1d readVector(string str);
void printVetor(v1d v);

void swap(lli* a, lli* b);