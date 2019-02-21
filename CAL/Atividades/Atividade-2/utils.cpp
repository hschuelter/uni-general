#include "utils.hpp"

void bubbleSort(int *v, int n){
    int i, j, aux;
    for(i = n - 1; i > 0; i--){
        for(j = 0; j < i; j++){
            if(v[j] > v[j+1]){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}

void selectionSort(int *v, int n){
    int i, j, x, aux;
    for (i = 0; i < n; i++){
        x = i;
        for (j = i+1; j < n; j++){
            if ( v[j] < v[x] )
                x = j;
            }
        aux = v[i];
        v[i] = v[x];
        v[x] = aux;
    }
}


void insertionSort(int *v, int n){
    int i, j, x;
    for (i = 1; i < n; i++){
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = x;
    }
}


int power(int base, int expo){
    int ret = 1;

    for(int i=0; i < expo; i++)
        ret *= base;

    return ret;
}


float sqr_root(float n, float upper, float bottom = 1){

    float sqr = (upper + bottom)/2.0;


    if( fabs(sqr - bottom) < ACCURACY )
        return sqr;


    if( n > 1 ){
        if(sqr*sqr > n)
            return sqr_root(n, sqr, bottom);    

        else if(sqr*sqr < n)
            return sqr_root(n, upper, sqr);
    }

    else if( n > 0){

        if(sqr*sqr < n)
            return sqr_root(n, sqr, bottom);    

        else if(sqr*sqr > n)
            return sqr_root(n, upper, sqr);

    }

    return sqr;
}


int fib(int n){

    if( n == 0 || n == 1 )
        return 1;

    return fib( n -1 ) + fib( n -2 );
}

int fibVetor(int n, int position, v1d v){

    if (v.size() == 0)
        v = v1d(n,-1);

    
    if(n == position)
        return v[position-1];


    if(position == 0 || position == 1)
        v[position] = position;
    else
        v[position] = v[position-1] + v[position-2];


    return fibVetor(n, position+1, v);

}

int fibonice(int n, int value = 1, int prev = 0){
    
    if (n == 0) return prev;
    if (n == 1) return value;

    return fibonice(n-1, value+prev, value);
}



void formatTime(int n){
    double time;
    string ret;

    time = double(n);

    if(time >= 1000)
        time /= 1000;
    else        
        printf("Time elapsed = %.0f ms", time);
        return;

    if(time < 60){
        printf("Time elapsed = %.2f s", time);
        return;
    }

    else
        time /= 60;

    printf("Time elapsed = %.2f min", time);
}

void random(int n){

    srand(time(NULL));

    for(int i=0; i < n; i++){
        cout << rand()%n << endl; 
    }

}

void clear(){
    system(CLEAR);
}
