// g++ -Wall -std=c++11 -O2 -o cal main.cpp utils.cpp && ./cal && rm cal
#include "utils.hpp"

int main(void){

	v1d v;
	vector<string> files;
	string path = "Entradas/2-Decrescente/";

	//files.push_back("Entradas/teste.txt");

	
	files.push_back(path + "decrescente-25k.txt");
	files.push_back(path + "decrescente-50k.txt");
	files.push_back(path + "decrescente-75k.txt");
	files.push_back(path + "decrescente-100k.txt");
	files.push_back(path + "decrescente-1M.txt");



	system(CLEAR);
	cout << "Algorithm: Merge Sort" << endl;
	for(int i = 0; i < (int) files.size(); i++){
		cout << endl;
		v = readVector(files[i]);

		//cout << "Antes:" << endl;
		//printVetor(v);

		auto start = high_resolution_clock::now();

		//bubbleSort(v); 					//cout << " Bubble Sort" << endl;
		//selectionSort(v); 				//cout << " Selection Sort" << endl;
		//insertSort(v); 					//cout << " Insert Sort" << endl;
		mergeSort(v, 0, (v.size()-1) );	//cout << " Merge Sort" << endl;
		//quickSort1(v, 0, v.size() - 1); 	//cout << " Quick Sort (w/ fixed Pivot)" << endl;
		//quickSort2(v, 0, v.size() - 1); 	//cout << " Quick Sort (w/ random Pivot)" << endl;
		//heapSort(v, v.size());			//cout << " Heap Sort" << endl;

		//countingSort(v);					//cout << " Counting Sort" << endl;
		//bucketSort(v);						//cout << " Bucket Sort" << endl;

		auto stop = high_resolution_clock::now();

		//cout << "\nDepois:" << endl;
		//printVetor(v);

		auto duration = duration_cast<microseconds>(stop - start);
		cout << i+1 << ") Size: " << v.size() << " elements" << endl;
		cout << "Time elapsed: " << duration.count() << " microseconds" << endl;
		cout << "=============" << endl;
		v.clear();
	}





	return 0;
}