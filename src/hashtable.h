#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <vector>

using namespace std;

class HashTable {
public:
	//HashTable(int size, double threshold=0.6);		// Konstruktor
	HashTable(int size, double threshold = 0.6, int collision_Strategie = 2);		// Konstruktor
	~HashTable();								// Destruktor
	int insert(int item);						// fügt ein Element der Hashtabelle hinzu
	int at(int i);								// Liefert das i-te Element der Hashtabelle zurück
	int getCollisionCount();    			// Liefert die Anzahl der Kollisionen zurück
	int getSize();					// Liefert die Größe der Hashtabelle zurück
	int getElements();				// Liefert die Anzahl der Elemente der Hashtabelle zurück
	void print();					// Ausgabe der Hashtable ind er Form:
								// [0] -> 1
								//  .....
private:	
	int size;						// Größe der HashTable
	int elements;					// Anz. d. Elemente in HashTable
	int collisionCount;				// Anz. d. Kollisionen beim Einfügen
	double threshold_rehashing;			// Schwellwert fürs rehashing (size/elements)
	vector<int>* hashTable;				// HashTable
	bool linSondieren;
	bool qSondieren;
	bool dHashing;
	int hashValue(int item);			// calculate hash value
	void rehashing();					// rehashing
};

// Helper Funktion:
int get_next_prime(int a);				// Gibt zu einer natuerlichen Zahl a, die nächstgrößere Primzahl zurück

#endif 