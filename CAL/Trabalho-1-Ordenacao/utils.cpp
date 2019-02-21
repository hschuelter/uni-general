#include "utils.hpp"

void bubbleSort(v1d &v){
	lli tam = v.size();

	for(lli i = tam - 1; i > 0; i-- ){
		for(lli j = 0; j < i; j++){

			if(v[j] > v[j+1]){
				swap(v[j], v[j+1]);
			}
		}
	}
}


void selectionSort(v1d &v){
	lli x;
	lli tam = v.size();
	
	for(lli i = 0; i < tam; i++){
		x = i;

		for(lli j = i+1; j < tam; j++){

			if (v[x] > v[j])
				x = j;
		
		}

		swap(v[i], v[x]);
	}
}

void insertSort(v1d &v){
	lli j, x, tam;
	tam = v.size();

	for (lli i = 1; i < tam; i++ ){
		x = v[i];
		j = i - 1;

		while(j >= 0 && v[j] > x){
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = x;
	}

	//return v;
}

void mergeSort(v1d &v, lli begin, lli end){

	if(begin < end){
		lli middle = begin + (end - begin)/2;

		mergeSort(v, begin, middle);
		mergeSort(v, middle + 1 , end);

		merge(v, begin, middle, end);
	}

}

void merge(v1d &v, lli begin, lli middle, lli end){

	lli tam1 = (middle - begin) +1 ;
	lli tam2 = (end - middle);

	lli i,j,k;

	v1d left;
	v1d right;

	for(i = 0; i < tam1; i++){
		left.push_back(v[i + begin]);
	}	
	
	for(i = 0; i < tam2; i++){
		right.push_back(v[i + middle + 1]);
	}

	i = 0;
	j = 0;
	k = begin;

	while( i < tam1 && j < tam2){

		if( left[i] <= right[j]){
			v[k] = left[i];
			i++;
		}
		else{
			v[k] = right[j];
			j++;
		}
		k++;
	}
	
	while(i < tam1){
		v[k] = left[i];
		i++;
		k++;
	}


	while(j < tam2){
		v[k] = right[j];
		j++;
		k++;
	}
	
}


void quickSort1(v1d &v, lli begin, lli end){
    if (begin < end){
        lli pivot = partition(v, begin, end);


        quickSort1(v, begin, pivot-1);
        quickSort1(v, pivot, end);
    }
}

lli partition(v1d &v, lli begin, lli end){
    lli pivot = v[begin];   // Primeiro elemento
    lli it = begin+1;       // Indice do maior elemento

    for(int i = begin+1 ; i <= end ; i++){
        if(v[i] < pivot){
            swap(v[it], v[i]);
            it++;
        }
    }
    swap(v[begin], v[it-1]);
    return it;
}


void quickSort2(v1d &v, lli begin, lli end){

	if (begin < end){
		lli pos = randomNumber( end - begin );
		swap(v[pos], v[begin]);

		lli pivot = partition(v, begin, end);

		quickSort2(v, begin, pivot-1);
		quickSort2(v, pivot, end);

	}
}

lli randomNumber(lli upper){	
	srand(time(NULL));
	return rand() % upper;
}


/* RIP Sort */
void heapSort(v1d &v, int n){
	letItHeap(v, n);
	for (lli i = n-1; i > 0; i--){
		swap(v[0], v[i]);
		heapify(v,i,0);
	}
}

void letItHeap(v1d &v, int n){
	for (lli i = n/2; i >= 0; i--){
		heapify(v, n, i);
	}
}

void heapify(v1d &v, lli n, lli i){
	lli l = left(i);
	lli r = right(i);

	lli big = i;

	if (l < n && v[l] > v[big])
		big = l;
	if (r < n && v[r] > v[big])
		big = r;

	if( big != i ){
		swap(v[i], v[big]);
		heapify(v, n, big);
	}


}

lli left(lli a){
	return (2*a + 1);
}
lli right(lli a){
	return (2*a + 2);
}


void countingSort(v1d &v){
	lli size = v.size();
	lli maximum = findMaximum(v);

	v1d sorted = v1d(size, -1);
	v1d countArray = v1d(maximum, 0);

	for(lli i = 0; i < size; i++){
		countArray[ v[i] ]++;
	}

	for(lli i = 1; i < size; i++){
		countArray[i] += countArray[i-1];
	}

	for(lli i = 0; i < size; i++){
		sorted[ --countArray[v[i]] ] = v[i];
	}

	v = sorted;
}



lli findMaximum(v1d v){
	lli max = -1;
	for(lli i = 0; i < v.size(); i++){
		if(v[i] > max)
			max = v[i];
	}

	return max;
}


void bucketSort(v1d &v){
	lli size = v.size();

	v2d bucket = v2d(size+1, v1d(0,0));
	v1d sorted = v1d(0,0);

	for(lli i = 0; i < size; i++){
		if (v[i]/size > bucket.size())
			bucket [ bucket.size()-1 ].push_back(v[i]);
		else 
			bucket[ v[i]/size ].push_back(v[i]);
	}

	for(lli i = 0; i < bucket.size(); i++){
		insertSort(bucket[i]);
	}

	for(lli i = 0; i < bucket.size() ; i++ ){
		if(bucket[i].size() > 0){
			for(lli j = 0; j < bucket[i].size(); j++){
				sorted.push_back(bucket[i][j]);
			} 
		}
	}

	v = sorted;

}


/* FUNCOES EXTRAS */

v1d readVector(string str){
	ifstream read;
	read.open(str);

    v1d vetor;
    lli a = 0;
    lli cont = 0;
    read >> a;
    do{
        vetor.push_back(a);
        read >> a;
        cont++;
    }while(a != -1);

    read.close();

    return vetor;
}

void printVetor(v1d v){
	//cout << "----" << endl;
	for (lli i = 0; i < (lli) v.size(); i++){
		cout << v[i] << " | ";
	}
	//cout << "----" << endl;
}

void swap(lli* a, lli* b){
	lli* aux;
	aux  = a;
	a = b;
	b = aux;
}
