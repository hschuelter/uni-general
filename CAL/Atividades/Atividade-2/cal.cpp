#include "utils.hpp"


int main(void){

    double time;
    float n2;
	int start, finish;
    int iTime;
    int n;
	int num;

	v1d fibo;

    
    cout << "Fibonacci com Vetor:" << endl;
    n = 25;
    while(n < 61){
        start = clock();
        fibVetor(n, 0, fibo);
        finish = clock();

        time = (finish - start) / double(CLOCKS_PER_SEC)*1000;
        iTime = time;
        if(time > 60000){
            printf("\t[%d] %d min e %d s\n", n, iTime/60000 , iTime % 60);
        }
        else if(time > 1000){
            time /= 1000;
            printf("\t[%d] %.2f s\n", n, time);
        }
        else
            printf("\t[%d] %.2f ms\n", n, time);
        n++;
    }

    cout << endl << "--------------------" << endl << endl;
    cout << "Fibonacci sem Vetor:" << endl;
    n = 25;
    while(n < 61){
        start = clock();
        fib(n);
        finish = clock();

        time = (finish - start) / double(CLOCKS_PER_SEC)*1000;
        iTime = time;
        if(time > 60000){
            printf("\t[%d] %d min e %d s\n", n, iTime/60000 , iTime % 60);
        }
        else if(time > 1000){
            time /= 1000;
            printf("\t[%d] %.2f s\n", n, time);
        }
        else
            printf("\t[%d] %.2f ms\n", n, time);
        n++;
    }

    return 0;
}
