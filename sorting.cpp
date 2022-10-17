#include "sorting.h"



namespace sorting {

	//************
	// QuickSort *
	//************   

	int partition(vector<int>& arr, int left, int right) {
		int x = arr[right];
		int i = left - 1;
		// Alle Elemente, die kleiner als Pivot nach links swappen
		for (int j = left; j < right; j++) {
			if (arr[j] <= x) {
				++i;
				std::swap(arr[i], arr[j]);
			}
		}
		// Pivot auf die Mitte setzen
		// links <= Pivot
		// rechts > Pivot
		std::swap(arr[i + 1], arr[right]);
		return i + 1;
	}

	void QuickSort(vector<int>& arr, int left, int right)
	{
		if (left < right) {
			int q = partition(arr, left, right);
			QuickSort(arr, left, q - 1);
			QuickSort(arr, q + 1, right);
		}
	}

	void InsertionSort(vector<int>& arr)
	{
		// N - 1 Durchläufe, da erstes Element sortiert ist
		for (int i = 1; i < arr.size(); i++) {
			// einzufuegendes Element merken
			int tmp = arr[i];
			// Einfuegestelle suchen
			int j = i - 1;
			while (j >= 0 && arr[j] > tmp) {
				arr[j + 1] = arr[j];
				j--;
			}

			// neues Element an der Position j+1 einfuegen
			arr[j + 1] = tmp;
		}
	}

	void InsertionSort2(vector<int>& arr, int size) {

		// N - 1 Durchläufe, da erstes Element sortiert ist
		for (int i = 1; i < size; i++) {
			// einzufuegendes Element merken
			int tmp = arr[i];
			// Einfuegestelle suchen
			int j = i - 1;
			while (j >= 0 && arr[j] > tmp) {
				arr[j + 1] = arr[j];
				j--;
			}

			// neues Element an der Position j+1 einfuegen
			arr[j + 1] = tmp;
		}
	}

	int median3(vector<int>& arr, int left, int right) {
		int center = (left + right) / 2;

		if (arr[center] < arr[left]) {
			std::swap(arr[center], arr[left]);
		}
		if (arr[right] < arr[left]) {
			std::swap(arr[right], arr[left]);
		}
		if (arr[right] < arr[center]) {
			std::swap(arr[right], arr[center]);
		}
		std::swap(arr[center], arr[right]);
		return center;
	}

	void HybridQuickSort(vector<int>& arr, int left, int right)
	{
		int size = right - left + 1;
		if (left < right) {
			
			if (size < 80) {
				InsertionSort2(arr, size);
			}
			else {
				int median = median3(arr, left, right);
				std::swap(arr[median], arr[right]);
				int q = partition(arr, left, right);
				HybridQuickSort(arr, left, q - 1);
				HybridQuickSort(arr, q + 1, right);
			}
		}

	}

	//************
	// MergeSort *
	//************
	void Merge(vector<int>& a, vector<int>& b, int low, int pivot, int high)
	{
		int i = low;
		int j = pivot;
		int lowEnd = pivot - 1;
		int hightEnd = high;
		// Schreibindex für b
		int tmpPos = low;
		// Anzahl Elemente
		int n = high - low + 1;

		while (i <= lowEnd && j <= hightEnd) {
			if (a[i] <= a[j]) {
				b[tmpPos] = a[i];
				i++;
			}
			else {
				b[tmpPos] = a[j];
				j++;
			}
			tmpPos++;
		}

		while (i <= lowEnd) {
			b[tmpPos++] = a[i++];
		}
		while (j <= hightEnd) {
			b[tmpPos++] = a[j++];
		}

		int k = 0;
		while (k < n) {
			a[hightEnd] = b[hightEnd];
			hightEnd--;
			k++;
		}
	}


	void MergeSort(vector<int>& a, vector<int>& b, int low, int high)
	{
		if (low < high) {
			int middle = (low + high) / 2;
			MergeSort(a, b, low, middle);
			MergeSort(a, b, middle + 1, high);
			Merge(a, b, low, middle + 1, high);
		}
	}

	/*
	void natMerge(vector<int> &a, vector<int> &b, int left, int middle, int right)
	{

	}
	*/

	// b löschen
	void natMergeSort(vector<int>& a, vector<int>& b)
	{
		int n = a.size();

		vector<int> tmp;
		tmp.resize(n, 0);
		vector<int> starts;
		starts.resize(n + 1, 0);

		// Schritt 1 : Starts von Runs identifizieren
		int runCount = 0;
		starts[0] = 0;
		for (int i = 1; i <= n; i++) {
			if ((i == n) || a[i] < a[i - 1]) {
				starts[++runCount] = i;
			}
		}

		// Schritt 2 : Runs mergen
		vector<int> from = a;
		vector<int> to = tmp;

		while (runCount > 1) {
			int newRunCount = 0;

			// Merge jeweils 2 Runs
			for (int i = 0; i < runCount - 1; i += 2) {
				Merge(from, to, starts[i], starts[i + 1], starts[i + 2] - 1);
				starts[newRunCount++] = starts[i];
			}

			// Bei ungerade Runs, letzte Run wird kopiert
			if (runCount % 2 == 1) {
				int lastStart = starts[runCount - 1];
				for (int i = lastStart; i < n; i++) {
					to[i] = from[i];
				}
				starts[newRunCount++] = lastStart;
			}

			// nächster Runde
			starts[newRunCount] = n;
			runCount = newRunCount;

			// Array wechseln
			vector<int> help = from;
			from = to;
			to = help;
		}

		// from array ist jetzt sortiert
		for (int i = 0; i < n; i++) {
			a[i] = to[i];
		}
	}


	//************
	// Heapsort (Max Heap)  *
	//************


	int leftChildIdx(int idx) {
		return 2 * idx + 1;
	}

	// percdown
	void heapify(vector<int>& a, int i, int n)
	{
		int child = i;
		int tmp = a[i];
		int j = i;

		// child muss < n
		while (leftChildIdx(j) < n) {
			child = leftChildIdx(j);
			if (child != (n - 1) && a[child] < a[child + 1]) {
				child = child + 1;
			}
			if (tmp < a[child]) {
				a[j] = a[child];
			}
			else {
				break;
			}
			j = child;
		}
		a[j] = tmp;
	}

	void HeapSort(vector<int>& a, int n)
	{
		int size = n;
		int i = size / 2;

		// Max Heap erzeugen
		while (i >= 0) {
			heapify(a, i, size);
			i--;
		}

		int j = size - 1;

		// Sortieren
		while (j > 0) {
			// Wurzel und letzten Knoten tauschen
			std::swap(a[0], a[j]);
			// neues Max Heap erzeugen
			heapify(a, 0, j);
			j--;
		}
	}

	//************
	// Shellsort *
	//************

	// Hibbardfolge : {1, 3, 7, 15, .....}
	void ShellSort_2n(vector<int>& a, int n)
	{
		int size = n;
		int gap = 0;
		// Max gap finden.
		for (int i = 1; i < n; i = (2 * i) + 1) {
			gap = i;
		}

		for (gap; gap > 0; gap = (gap - 1) / 2) {
			// Insertionsort von Elementen mit Abstand gap
			for (int i = gap; i < size; i++) {
				int tmp = a[i];
				int j = i;
				for (; j >= gap && tmp < a[j - gap]; j -= gap) {
					a[j] = a[j - gap];
				}
				a[j] = tmp;
			}
			// Elemente sind im Abstand gap sortiert
		}
	}


	void ShellSort_3n(vector<int>& a, int n)
	{
		int size = n;
		int gap = 0;
		// Max gap finden.
		for (int i = 1; i < n; i = (3 * i) + 1) {
			gap = i;
		}

		for (gap; gap > 0; gap = (gap - 1) / 3) {
			// Insertionsort von Elementen mit Abstand gap
			for (int i = gap; i < size; i++) {
				int tmp = a[i];
				int j = i;
				for (; j >= gap && tmp < a[j - gap]; j -= gap) {
					a[j] = a[j - gap];
				}
				a[j] = tmp;
			}
			// Elemente sind im Abstand gap sortiert
		}
	}


	void randomizeVector(vector<int>& array, int n) {
		array.resize(n);

		for (unsigned int i = 0; i < array.size(); i++)
			array[i] = rand() % 1000000;
	}

}





