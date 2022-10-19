#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include <iostream>
#include <omp.h>
#include <ctime>

#include"hashtable.h"
#include "sorting.h"

using namespace std;

//benchmark functions
void benchmark_quicksort();
void benchmark_hybridquicksort();
void benchmark_mergesort();
void benchmark_heapsort();
void benchmark_shellsort_2n();
void benchmark_shellsort_3n();
void benchmark_insertionsort();


int main(int argc, char** argv) {

  Catch::Session().run();

  //std::cout << "\nPress Enter to run measurement" << std::endl;
  //std::cin.get();

  //benchmark_quicksort();
  //benchmark_hybridquicksort();
  //benchmark_mergesort();
  //benchmark_heapsort();
  //benchmark_shellsort_2n();
  //benchmark_shellsort_3n();
  //benchmark_insertionsort();
  
  system("PAUSE");

  
  int collision_Strategie = 0;
  double threshold_for_rehashing = 0.0;
  int size = 0;

  cout << endl << "------------------------------- HASHING -------------------------------" << endl;
  cout << " 1. Lineares Sondieren" << endl;
  cout << " 2. Quadratisches Sondieren" << endl;
  cout << " 3. Doppel Hashing" << endl;
  cout << " Nimm eine Kollisionsstrategie  : ";
  cin >> collision_Strategie;
  cout << " Gib den Belegungsfaktor an : ";
  cin >> threshold_for_rehashing;
  cout << " Gib die Größe der Tabelle an : ";
  cin >> size;

  HashTable hash_table(size, threshold_for_rehashing, collision_Strategie);
  int input = 0;
  int item = 0;
  int index = 0;

  cout << "1. Item einfügen" << endl;
  cout << "2. Tabelle zeigen" << endl;
  cout << "3. beenden" << endl;
  cout << "Was wollen Sie damit machen : " << endl;
  
  do {
	  cout << "Input : ";
	  cin >> input;
	  if (input < 1 || input > 3) {
		  cout << "!!! Wrong input !!!" << endl;
		  input = 4;
	  }

	  switch (input) {
	  case 1:
		  cout << "Gib das Item ein : " << endl;
		  cin >> item;
		  index = hash_table.insert(item);
		  cout << "Index : " << index << endl;
		  break;
	  case 2 :
		  hash_table.print();
		  break;
	  case 3 :
		  return 0;
	  }

  } while (input >= 1 && input <= 4);
  
  /*
  cout << endl << "------------------------------- HASHING 2 -------------------------------" << endl;
  HashTable hash_table_2(1000, 0.6, 3);
  int items = 0;
  
  srand(time(0));
  // 200 Zahlen zwischen 1000 bis 1500
  for (int i = 0; i < 200; i++) {
	  items = (rand() % 501) + 1000;
	  hash_table_2.insert(items);
  }
  cout << "gesamte Kollision : ";
  cout << hash_table_2.getCollisionCount() << endl;
  */
  system("PAUSE");
  return 0;
}


//executes benchmark for quicksort
void benchmark_quicksort() {

  //file stream
  ofstream quicksort_measurement;
  quicksort_measurement.open("quicksort.txt", ios::out | ios::app);

  //benchmark parameters / variables
  double dtime;
  double averageTime = 0;
  int n_start = 1000;
  int n_step = 1000;
  int n_end = 1000000;

  vector<int> V;

  //actual benchmark loop
  for (int n = n_start; n<=n_end; n += n_step) {
	  averageTime = 0;
	//"progress bar"
    std::cout << "Running Quicksort with n: " << n << std::endl;

	for (int i = 0; i < 10; i++) {
		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		sorting::QuickSort(V, 0, V.size() - 1);

		//stop time
		dtime = omp_get_wtime() - dtime;
		averageTime += dtime;
	}

	averageTime = averageTime / 10;

	//write to file
    quicksort_measurement << n << "\t" << setprecision(10) << scientific << averageTime << endl;
  }

  //close file handle
  quicksort_measurement.close();
}

void benchmark_hybridquicksort() {

	//file stream
	ofstream hybridquicksort_measurement;
	hybridquicksort_measurement.open("hybridquicksort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	double averageTime = 0;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {
		averageTime = 0;

		//"progress bar"
		std::cout << "Running Hybrid Quicksort with n: " << n << std::endl;

		for (int i = 0; i < 10; i++) {
			//generate n random integers
			sorting::randomizeVector(V, n);

			//start measurement
			dtime = omp_get_wtime();

			//execzute sorting algorithm
			sorting::HybridQuickSort(V, 0, V.size() - 1);

			//stop time
			dtime = omp_get_wtime() - dtime;
			averageTime += dtime;
		}

		averageTime = averageTime / 10;

		//write to file
		hybridquicksort_measurement << n << "\t" << setprecision(10) << scientific << averageTime << endl;
	}

	//close file handle
	hybridquicksort_measurement.close();
}

void benchmark_mergesort() {

	//file stream
	ofstream mergesort_measurement;
	mergesort_measurement.open("mergesort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	double averageTime = 0;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;
	vector<int> B;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {
		averageTime = 0;

		//"progress bar"
		std::cout << "Running Mergesort with n: " << n << std::endl;

		for (int i = 0; i < 10; i++) {
			//generate n random integers
			sorting::randomizeVector(V, n);
			B.resize(V.size(), 0);

			//start measurement
			dtime = omp_get_wtime();

			//execzute sorting algorithm
			sorting::MergeSort(V, B, 0, V.size() - 1);

			//stop time
			dtime = omp_get_wtime() - dtime;
			averageTime += dtime;
		}

		averageTime = averageTime / 10;

		//write to file
		mergesort_measurement << n << "\t" << setprecision(10) << scientific << averageTime << endl;
	}

	//close file handle
	mergesort_measurement.close();
}

void benchmark_heapsort() {

	//file stream
	ofstream heapsort_measurement;
	heapsort_measurement.open("heapsort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	double averageTime = 0;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {
		averageTime = 0;

		//"progress bar"
		std::cout << "Running Heapsort with n: " << n << std::endl;

		for (int i = 0; i < 10; i++) {
			//generate n random integers
			sorting::randomizeVector(V, n);

			//start measurement
			dtime = omp_get_wtime();

			//execzute sorting algorithm
			sorting::HeapSort(V, V.size());

			//stop time
			dtime = omp_get_wtime() - dtime;
			averageTime += dtime;
		}

		averageTime = averageTime / 10;

		//write to file
		heapsort_measurement << n << "\t" << setprecision(10) << scientific << averageTime << endl;
	}

	//close file handle
	heapsort_measurement.close();
}

void benchmark_shellsort_2n() {

	//file stream
	ofstream shellsort_2n_measurement;
	shellsort_2n_measurement.open("shellsort_2n.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	double averageTime = 0;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {
		averageTime = 0;

		//"progress bar"
		std::cout << "Running shellsort_2n with n: " << n << std::endl;

		for (int i = 0; i < 10; i++) {
			//generate n random integers
			sorting::randomizeVector(V, n);

			//start measurement
			dtime = omp_get_wtime();

			//execzute sorting algorithm
			sorting::ShellSort_2n(V, V.size());

			//stop time
			dtime = omp_get_wtime() - dtime;
			averageTime += dtime;
		}

		averageTime = averageTime / 10;

		//write to file
		shellsort_2n_measurement << n << "\t" << setprecision(10) << scientific << averageTime << endl;
	}

	//close file handle
	shellsort_2n_measurement.close();
}

void benchmark_shellsort_3n() {

	//file stream
	ofstream shellsort_3n_measurement;
	shellsort_3n_measurement.open("shellsort_3n.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	double averageTime = 0;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {
		averageTime = 0;

		//"progress bar"
		std::cout << "Running shellsort_3n with n: " << n << std::endl;

		for (int i = 0; i < 10; i++) {
			//generate n random integers
			sorting::randomizeVector(V, n);

			//start measurement
			dtime = omp_get_wtime();

			//execzute sorting algorithm
			sorting::ShellSort_3n(V, V.size());

			//stop time
			dtime = omp_get_wtime() - dtime;
			averageTime += dtime;
		}

		averageTime = averageTime / 10;

		//write to file
		shellsort_3n_measurement << n << "\t" << setprecision(10) << scientific << averageTime << endl;
	}

	//close file handle
	shellsort_3n_measurement.close();
}

void benchmark_insertionsort() {
	// file stream
	ofstream insertionsort_measurement;
	insertionsort_measurement.open("insertionsort.txt", ios::out | ios::app);

	// benchmark parameters / variables
	double dtime;
	int n_start = 1;
	int n_step = 1;
	int n_end = 1000;
	double averageTime = 0;

	vector<int> V;

	// actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {
		averageTime = 0;

		//"progress bar"
		std::cout << "Running Insertionsort with n: " << n << std::endl;

		for (int i = 0; i < 10; i++) {
			//generate n random integers
			sorting::randomizeVector(V, n);

			//start measurement
			dtime = omp_get_wtime();

			//execzute sorting algorithm
			sorting::InsertionSort(V);

			//stop time
			dtime = omp_get_wtime() - dtime;
			averageTime += dtime;
		}

		averageTime = averageTime / 10;

		//write to file
		insertionsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	// close file handle
	insertionsort_measurement.close();
}











