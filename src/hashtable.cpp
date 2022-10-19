#include "hashtable.h"
#include <iostream>
#include <cmath>

using namespace std;

HashTable::HashTable(int size, double threshold, int collision_Strategie)
{
	this->size = size;
	this->threshold_rehashing = threshold;
	elements = 0;
	collisionCount = 0;
	hashTable = new vector<int>(size, -1);

	if (collision_Strategie == 1) {
		linSondieren = true;
		qSondieren = false;
		dHashing = false;
	}
	else if (collision_Strategie == 3) {
		linSondieren = false;
		qSondieren = false;
		dHashing = true;
	}
	else {
		linSondieren = false;
		qSondieren = true;
		dHashing = false;
	}
}

HashTable::~HashTable()
{
	delete hashTable;
}

// Berechnung des Hashwertes mit quadr. Sondieren
int HashTable::hashValue(int item)
{	
	// Lineares Sondieren
	if (linSondieren) {
		int hashIndex = item % size;

		while (hashTable->at(hashIndex) != -1) {
			collisionCount++;
			hashIndex++;
			hashIndex %= size;
		}
		return hashIndex;
	}
	// Quadratisches Sondieren (standardm‰ﬂig)
	if (qSondieren) {
		int hashIndex = item;

		// Sondieren
		for (int i = 0; i < size; i++) {
			// i aus {0,....,m-1}
			hashIndex = item + std::pow(i, 2);
			hashIndex %= size;
			if (hashTable->at(hashIndex) != -1) {
				collisionCount++;
				continue;
			}
			else {
				break;
			}
		}
		return hashIndex;
	}

	// Doppeltes Hashing
	if (dHashing) {
		int last_prime;
		int r; // n‰chst kleinere Primzahl zu size(M)

		// Finde hier die n‰chst kleinere Primzahl zu size(M)
		for (int i = 1; i <= size; i++) {
			last_prime = get_next_prime(i);

			if (last_prime >= size) {
				break;
			}
			r = last_prime;
		}

		// 2. Hashfunktion
		int hash_2_k = r - (item % r);
		int hashIndex = 0;

		// i aus {0,....,m-1}
		for (int i = 0; i < size; i++) {
			hashIndex = (item + (i * hash_2_k)) % size;
			if (hashTable->at(hashIndex) == -1) {
				break;
			}
			collisionCount++;
		}
		return hashIndex;
	}

}


void HashTable::rehashing()
{
	//this->print();
	int max_size = 1000;
	vector<int>* newHashTable;

	// neue Size berechnen und Speicherplatz anlegen
	int new_size = 2 * size;
	new_size = get_next_prime(new_size);
	if (new_size <= max_size) {
		size = new_size;
	}
	newHashTable = new vector<int>(size, -1);

	vector<int>* oldTable = hashTable;
	hashTable = newHashTable;
	collisionCount = 0;
	// den alten Speicherplatz durchiterieren
	for (int i = 0; i < oldTable->size(); i++) {
		if (oldTable->at(i) == -1) continue;
		int hash_value = hashValue(oldTable->at(i));
		hashTable->at(hash_value) = oldTable->at(i);
	}
	delete oldTable;
}

int HashTable::insert(int item)
{	
	// Index finden und speichern
	int hashIndex = hashValue(item);
	hashTable->at(hashIndex) = item;
	elements++;
	//this->print();
	// Pr¸fe ob den Belegungsfaktor ¸berschritten ist
	if ((elements / double(size)) >= threshold_rehashing) {
		this->print();
		rehashing();
	}
	return hashIndex;
}


int HashTable::at(int i)
{
	return hashTable->at(i);
}

int HashTable::getCollisionCount()
{
	return this->collisionCount;
}

int HashTable::getSize()
{
	return this->size;
}

int HashTable::getElements()
{
	return this->elements;
}

void HashTable::print() {
	cout << "======= Hash Table =======" << endl;
	for (int i = 0; i < size; i++) {
		cout << "\t" << "[" << i << "]" << " -> " << hashTable->at(i) << endl;
	}
	cout << "==========================" << endl;
}

int get_next_prime(int x)
{
	x = x + 1;
	bool found = true;
	while (true)
	{
		found = true;
		for (int i = 2; i <= sqrt(x); i++)
		{
			if (x % i == 0)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return x;
		}
		x += 1;
	}
}

