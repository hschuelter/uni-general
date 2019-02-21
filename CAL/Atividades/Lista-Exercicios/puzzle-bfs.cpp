// g++ -Wall -o puzzle-bfs.out puzzle-bfs.cpp && ./puzzle-bfs.out
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> v1d;
typedef vector<v1d> v2d;

class Solver{
	public:
		v2d puzzle;
		int steps;

	Solver(){
		puzzle = v2d(3, v1d(3, 0));
		steps = 0;
	}

	Solver(v2d p, int s){
		puzzle = p;
		steps = s;
	}
};

/* ========= FUNCTIONS ======== */

Solver solve(Solver sol);
bool verifyAnswer(v2d& puzzle);

void swap(int* a, int* b);
void printPuzzle(v2d puzzle);

/* =========================== */


/* === GLOBAL VARIABLES <3 === */

map<v2d, int> mapa;

/* =========================== */

int main(void){
	ifstream read;
	Solver sol;
	int a;

	read.open("puzzle.txt");

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			read >> a;
			sol.puzzle[i][j] = a;
		}
	}

	/* === PRINTS === */
	cout << endl;
	cout << "Inicio:" << endl;
	cout << "=========" << endl;
	printPuzzle(sol.puzzle);
	cout << "=========" << endl;
	/* ============== */

	sol = solve(sol);

	/* RESPOSTA */
	cout << endl;
	cout << "Numero de movimentos: " << sol.steps << endl;
	cout << "Resposta: " << endl;
	cout << "=========" << endl;
	printPuzzle(sol.puzzle);
	cout << "=========" << endl;
	/* ======== */

	return 0;
}

Solver solve(Solver sol){
	queue< Solver > fila;
	Solver s;

	fila.push(sol);
	while( !fila.empty() ){

		s = fila.front();

		/* TESTA A RESPOSTA */
		if( verifyAnswer(s.puzzle) == true )
			break;


		/* VERIFICA SE ESSA CONFIGURACAO JA APARECERA */
		if(mapa.count(s.puzzle) > 0){
			fila.pop();
			continue;
		}

		mapa[s.puzzle] = 1;

		/* ACHAR A POSICAO DO ZERO */
		int y, x;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if( s.puzzle[i][j] == 0 ){
					y = i;
					x = j;
				}
			}
		}
		// cout << y << " | " << x << endl;

		if(y != 2){
			swap(s.puzzle[y][x], s.puzzle[y+1][x]);
			s.steps++;
			fila.push(s);
			s.steps--;
			swap(s.puzzle[y][x], s.puzzle[y+1][x]);
		}

		if(y != 0){
			swap(s.puzzle[y][x], s.puzzle[y-1][x]);
			s.steps++;
			fila.push(s);
			s.steps--;
			swap(s.puzzle[y][x], s.puzzle[y-1][x]);
		}

		if(x != 2){
			swap(s.puzzle[y][x], s.puzzle[y][x+1]);
			s.steps++;
			fila.push(s);
			s.steps--;
			swap(s.puzzle[y][x], s.puzzle[y][x+1]);
		}

		if(x != 0){
			swap(s.puzzle[y][x], s.puzzle[y][x-1]);
			s.steps++;
			fila.push(s);
			s.steps--;
			swap(s.puzzle[y][x], s.puzzle[y][x-1]);
		}

        fila.pop();
	}

	return s;
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
