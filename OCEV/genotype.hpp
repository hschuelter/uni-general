#ifndef GENOTYPE_HPP
#define GENOTYPE_HPP

#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <chrono>
#include <algorithm>

using namespace std;

#define MIN(a,b) ((a < b) ? (a):(b))
#define MAX(a,b) ((a > b) ? (a):(b))

class Genotype{

    public:
        vector<int>    v_int;
        vector<double> v_double;

        int codification;

    Genotype(){
        this -> v_int = vector<int>(0);
        this -> v_double = vector<double>(0);

        this -> codification = -1;
    }

    Genotype(int nvars, int cod, double lower_bound, double upper_bound){
        random_device rd;
        mt19937 generator (rd());
        uniform_real_distribution<double> bin_dist(0.0, 1.0);
        uniform_real_distribution<double> dist(lower_bound, upper_bound);

        unsigned my_seed = chrono::system_clock::now().time_since_epoch().count();

        this-> codification = cod;
        switch(cod){
            case 0:
                /* --- BINARY --- */
                this -> v_int = vector<int>(nvars, 0);
                for(int i = 0; i < (int) this -> v_int.size(); i++)
                    this -> v_int[i] = (bin_dist(generator) > 0.5) ? 1 : 0;

                break;

            case 1:
                /* --- INTEGER --- */
                this -> v_int = vector<int>(nvars, 0);
                for(int i = 0; i < (int) this -> v_int.size(); i++)
                    this -> v_int[i] = round(dist(generator));
                break;

            case 2:
                /* --- PERMUTATION --- */
                this -> v_int = vector<int>(nvars, 0);
                for(int i = 0; i < (int) this -> v_int.size(); i++)
                    this -> v_int[i] = i;

                shuffle(this -> v_int.begin(), this -> v_int.end(), default_random_engine(my_seed));
                break;

            case 3:
                /* --- REAL --- */
                this -> v_double = vector<double>(nvars, 0);
                for(int i = 0; i < (int) this -> v_double.size(); i++)
                    this -> v_double[i] = dist(generator);
                break;
        }


    }

    Genotype(vector<int> v){
        this -> v_double = vector<double>(0);
        this -> v_int = vector<int>(v.size(), 0);

        for(int i = 0; i < (int) v.size(); i++){
            this->v_int[i] = v[i];
        }
    }

    void show(){
        if(this -> codification == 3){
            for(int i=0; i < (int) this -> v_double.size(); i++)
				fprintf(stderr, "%.2f ", this -> v_double[i]);
        }
        else{
            for(int i=0; i < (int) this -> v_int.size(); i++)
				cerr << this -> v_int[i] << " ";
        }
    }

	void show(int num){
        if(this -> codification == 3){
            for(int i=0; i < (int) this -> v_double.size(); i++)
				printf("%.2f ", this -> v_double[i]);
			printf("\n");
        }
		else{
            for(int i=0; i < (int) this -> v_int.size(); i++)
				cout << this -> v_int[i] << " ";
			printf("\n");
        }

    }

};

#endif
