//g++ -Wall -o decrescente decrescente.cpp && ./decrescente  > decrescente-.txt 
#include <iostream>
using namespace std;

int main(void){
    int n = 1000000;
    for(int i = n; i > 0 ; i--){
        cout << i << endl;
    }
    cout << -1 << endl;
    return 0;
}