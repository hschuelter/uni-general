// g++ -Wall -o puzzle-dfs.out puzzle-dfs.cpp && ./puzzle-dfs.out
#include<bits/stdc++.h>
using namespace std;

typedef vector<int> v1d;
typedef vector<v1d> v2d;

/* ========= FUNCTIONS ======== */
bool search(int n);
bool verifyAnswer(v2d& puzzle);

void solve(v2d puzzle);
void swap(int* a, int* b);

void printPuzzle(v2d puzzle);
void printStack();
/* =========================== */


/* === GLOBAL VARIABLES <3 === */

map<v2d, int> mapa;
stack< v2d > resposta;
int cnt = 0;

bool fim = false;
/* =========================== */

int main(void){
	ifstream read;
	v2d puzzle(3, v1d(3, 0));
	int a;

	read.open("puzzle.txt");

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			read >> a;
			puzzle[i][j] = a;
		}
	}

	solve(puzzle);
	resposta.push(puzzle);

	cout << "Resolucao: " << endl;
	cout << "Numero de movimentos: " << cnt << endl;
	cout << "=========" << endl;
	printStack();

	return 0;
}

void solve(v2d puzzle){
	/* MATA OS RAMOS DA RECURSAO QUANDO ACHA A RESPOSTA */
	if(fim == true){
		return;
	}

	/* TESTA A RESPOSTA */
	if( verifyAnswer(puzzle) == true ){ // Verifica se achou a resposta
		fim = true;
		return;
	}

	/* VERIFICA SE ESSA CONFIGURACAO JA TINHA APARECIDO */
	if(mapa.count(puzzle) > 0){
		return;
	}
	mapa[puzzle] = 1;
	/* ACHAR A POSICAO DO ZERO */
	int y, x;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if( puzzle[i][j] == 0 ){
				y = i;
				x = j;
			}
		}
	}

	// cout << y << " | " << x << endl;
	cnt++;

	if(y != 2){
		swap(puzzle[y][x], puzzle[y+1][x]);
		solve(puzzle);
		if(fim == true){
			resposta.push(puzzle);
			return;
		}
		swap(puzzle[y][x], puzzle[y+1][x]);
	}

	if(y != 0){
		swap(puzzle[y][x], puzzle[y-1][x]);
		solve(puzzle);
		if(fim == true){
			resposta.push(puzzle);
			return;
		}
		swap(puzzle[y][x], puzzle[y-1][x]);
	}

	if(x != 2){
		swap(puzzle[y][x], puzzle[y][x+1]);
		solve(puzzle);
		if(fim == true){
			resposta.push(puzzle);
			return;
		}
		swap(puzzle[y][x], puzzle[y][x+1]);
	}

	if(x != 0){
		swap(puzzle[y][x], puzzle[y][x-1]);
		solve(puzzle);
		if(fim == true){
			resposta.push(puzzle);
			return;
		}
		swap(puzzle[y][x], puzzle[y][x-1]);
	}
	cnt--;
}

bool verifyAnswer(v2d& puzzle){
	int cont = 1;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(cont == 9)
				cont = 0;

			if( puzzle[i][j] != cont++ )
				return false;
		}
	}
	return true;
}

/* ======= UTILS ======= */

void swap(int* a, int* b){
	int* aux;
	aux = a;
	a = b;
	b = aux;
}

void printPuzzle(v2d puzzle){
	for(int i = 0; i < (int) puzzle.size(); i++){
		for(int j = 0; j < (int) puzzle[i].size(); j++){
			cout << " " << puzzle[i][j] << " ";
		}
		cout << endl;
	}
}

void printStack(){
	v2d mat;

	while( !resposta.empty() ){
		mat = resposta.top();
		printPuzzle(mat);
		cout << "=========" << endl;
		resposta.pop();
	}
}
