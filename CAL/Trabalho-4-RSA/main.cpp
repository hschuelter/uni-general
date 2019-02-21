#include "utils.hpp"
#include "bigint.hpp"

int main(void){
	string teste;
	BigInt bi;

	cin >> teste;
	bi = BigInt(teste);
	bi.print();

	return 0;
}
