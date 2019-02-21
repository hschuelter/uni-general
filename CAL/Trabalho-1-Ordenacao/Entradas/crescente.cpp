//g++ -Wall -o crescente crescente.cpp && ./crescente  > crescente-.txt 
#include <iostream>
using namespace std;

int main(void){
    int n = 1000000;
    for(int i = 0; i < n ; i++){
        cout << i+1 << endl;
    }
    cout << -1 << endl;
    return 0;
}