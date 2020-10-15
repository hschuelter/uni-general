#ifndef INPUT_PARSER_HPP
#define INPUT_PARSER_HPP

#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <chrono>
#include <algorithm>
#include <unistd.h>

using namespace std;

class Input_Parser{
    public:
        int gene_size, pop_size, codification, selection, crossover, mutation, fit_function;
        int generations, runs;
        double lower_bound, upper_bound;
        int k; double kp;
        int d;
        double crossover_chance, mutation_chance;
        bool elitism;
        double c_begin, c_end; // escalonamento linear
        double gap;
		double alpha, rho;
        string file;

        Input_Parser(){
            this -> gene_size = -1;
        }

        Input_Parser(int argc, char** argv){
            int c;
            while ((c = getopt (argc, argv, "v:p:c:S:X:M:l:u:g:r:k:K:d:x:m:E:F:b:e:a:f:A:R:")) != -1)
                switch (c) {
                    case 'v':
                        this -> gene_size = stoi(optarg);
                        break;

                    case 'p':
                        this -> pop_size = stoi(optarg);
                        break;

                    case 'c':
                        this -> codification = stoi(optarg);
                        break;

                    case 'S':
                        this -> selection = stoi(optarg);
                        break;

                    case 'X':
                        this -> crossover = stoi(optarg);
                        break;

                    case 'M':
                        this -> mutation = stoi(optarg);
                        break;

                    case 'l':
                        this -> lower_bound = stod(optarg);
                        break;

                    case 'u':
                        this -> upper_bound = stod(optarg);
                        break;

                    case 'g':
                        this -> generations = stoi(optarg);
                        break;

                    case 'r':
                        this -> runs = stoi(optarg);
                        break;

                    case 'k':
                        this -> k = stoi(optarg);
                        break;

                    case 'K':
                        this -> kp = stod(optarg);
                        break;

                    case 'd':
                        this -> d = stoi(optarg);
                        break;

                    case 'x':
                        this -> crossover_chance = stod(optarg);
                        break;

                    case 'm':
                        this -> mutation_chance = stod(optarg);
                        break;

                    case 'E':
                        this -> elitism = (bool) stoi(optarg);
                        break;

                    case 'F':
                        this -> fit_function = stoi(optarg);
                        break;

                    case 'b':
                        this -> c_begin = stoi(optarg);
                        break;

                    case 'e':
                        this -> c_end = stoi(optarg);
                        break;

                    case 'a':
                        this -> gap = stod(optarg);
                        break;

                    case 'f':
                        this -> file = optarg;
                        break;

					case 'A':
						this -> alpha = stod(optarg);
						break;

					case 'R':
                        this -> rho = stod(optarg);
                        break;

                    case '?':
                        if (optopt == 'c')
                            fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                        else if (isprint (optopt))
                            fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                        else
                            fprintf (stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                    default:
                        abort ();
                }
        }

        void error_message(){
            cout << "[-v: num variables]\n[-p: pop size]\n[-c: codification]\n";
            cout << "[-l: lower bound] \n[-u: upper bound]\n";
            cout << "[-g: num generations]\n[-r: num runs]\n";
            cout << "[-k: k] \n[-K: kp] \n[-d: distance]\n";
            cout << "[-S: selection]\n[-X: crossover]\n[-x: crossover chance]\n";
            cout << "[-M: mutation]\n[-m: mutation chance]\n";
            cout << "[-E: elitism]\n";
        }

};

#endif
