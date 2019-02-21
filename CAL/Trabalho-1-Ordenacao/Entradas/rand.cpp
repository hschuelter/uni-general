//g++ -Wall -o rand rand.cpp && ./rand  > entrada.txt 
#include <bits/stdc++.h>
using namespace std;

int main(void){
    srand(time(NULL));
    int n = 1000000;
    for(int i = 0; i < n ; i++){
        cout << rand()%n << endl;
    }
    cout << -1 << endl;
    return 0;
}
