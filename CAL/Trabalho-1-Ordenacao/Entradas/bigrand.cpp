//g++ -Wall -o bigrand bigrand.cpp && ./bigrand  > entrada.txt 
#include <bits/stdc++.h>
using namespace std;

int main(void){
    srand(time(NULL));

    int n = 1000000;
    int pos = rand()%n;
    
    for(int i = 0; i < n ; i++){
    	if(i == pos)
    		cout << 100000000000 << endl;
        else        	
        	cout << rand()%n << endl;
    }
    cout << -1 << endl;
    return 0;
}
