/* The geeks for geeks algorithm was used as a base for this implementation */
// To run: g++ -o graham.out -Wall graham-scan.cpp && ./graham.out

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

#include <stdlib.h>

using namespace std;

class Point{
	public:
		int x;
		int y;
		char nome;

		Point(){
			this->x = 0;
			this->y = 0;
			this->nome = ' ';
		}

		Point(int x, int y, char nome){
			this->x = x;
			this->y = y;
			this->nome = nome;
		}

		void print(){
			cout << this->nome << ": (" << this->x << ", " << this->y << ")" << endl;
		}
};

/* ==== TYPEDEF ==== */

typedef vector<Point> v1d;

/* ==== TYPEDEF ==== */


/* ==== FUNCTIONS ==== */

void ConvexHull(v1d& v);
int dist(Point p, Point q);
int orientation(Point p, Point q, Point r);
int compare(const void *vp1, const void *vp2);
Point nextToTop(stack<Point>& S);

void printPoints(v1d& v, int size);
void printStack(stack<Point>& S);
void swap(Point& p, Point& q);

/* ==== FUNCTIONS ==== */


/* ==== GLOBAL VARIABLES <3 ==== */

Point p0;
char alfabeto[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

/* ==== GLOBAL VARIABLES <3 ==== */

int main(void){
	ifstream read;
	v1d v;
	int num;
	int x, y;


	read.open("input.in");
	read >> num;

	for(int i = 0; i < num; i++){
		read >> x >> y;
		Point p = Point(x,y, alfabeto[i]);

		v.push_back(p);
	}
	cout << "Conjunto de pontos:" << endl;
	printPoints(v, v.size() );
	cout << "====" << endl;

	ConvexHull(v);

	return 0;
}

/* ==== FUNCTIONS ==== */

void ConvexHull(v1d& v){
	int n = v.size();

	int min = 0;
	int ymin = v[0].y;

	/* 1 Etapa: Encontrar o ponto com o menor y */
	for(int i = 0; i < (int) v.size(); i++){
		if( (v[i].y < ymin) || (v[i].y == ymin && v[i].x < v[min].x ) ){
			min = i;
			ymin = v[i].y;
		}
	}
	swap(v[0], v[min]);
	p0 = v[0];

	cout << "p0:" << endl << "\t";
	p0.print();
	cout << "====" << endl;


	/* 2 Etapa: Ordenar o vetor e retirar os pontos colineares */
	qsort(&v[1], n - 1, sizeof(Point), compare);

	if (v.size() < 3) return;

	int m = 1;
	for (int i = 1; i < n; i++){
		while (i < n-1 && orientation(p0, v[i], v[i+1]) == 0)
			i++;

		v[m] = v[i];
		m++;
	}

	cout << "Conjunto de pontos ordenados:" << endl;
	printPoints(v, m);
	cout << "====" << endl;


	/* 3 Etapa: Aceitar e Rejeitar Pontos */

	stack<Point> S;
	S.push(v[0]);
	S.push(v[1]);
	S.push(v[2]);


	for (int i = 3; i < m; i++){
		while (orientation(nextToTop(S), S.top(), v[i]) != 2)
			S.pop();
			S.push(v[i]);
	}
	cout << "Convex Hull:" << endl;
	printStack(S);
}

int dist(Point p, Point q){
	return (p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y);
}

int orientation(Point p, Point q, Point r){
	int val=(q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;	// colineares
	return (val > 0)? 1: 2; // horario or anti-horario
}
/* Para o qsort */
int compare(const void *vp1, const void *vp2){
	Point *p1 = (Point *)vp1;
	Point *p2 = (Point *)vp2;

	int o = orientation(p0, *p1, *p2);
	if (o == 0)
		return (dist(p0, *p2) >= dist(p0, *p1))? -1 : 1;

	return (o == 2)? -1: 1;
}

Point nextToTop(stack<Point> &S){
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

/* ==== FUNCTIONS ==== */

/* ==== UTILS ==== */

void printPoints(v1d& v, int size ){
	for (int i = 0; i < size; i++){
		cout << "\t";
		v[i].print();
	}
}

void printStack(stack<Point>& S){
   	while (!S.empty())   {
       Point p = S.top();
       cout << "\t";
       cout << p.nome << ": (" << p.x << ", " << p.y <<")" << endl;
       S.pop();
   	}
}

void swap(Point& p, Point& q){
	Point temp = p;
	p = q;
	q = temp;
}
/* ==== UTILS ==== */
