#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

// Complexitate O(n), n - nr elemente in multime
bool Multime::adauga(TElem elem) {
	if (cauta(elem)) {
		return false;
	}
	elemente.inserareSfarsit(elem);
	return true;
}

// Complexitate O(n), n - nr elemente in multime
bool Multime::sterge(TElem elem) {
	if (cauta(elem)) {
		elemente.stergeValoare(elem);
		return true;
	}
	return false;
}


// Complexitate O(n), n - nr elemente in multime
bool Multime::cauta(TElem elem) const{
	return elemente.cauta(elem);
}

// Complexitate O(1) - returneaza dimensiunea multimii
int Multime::dim() const {
	return elemente.dimensiune();
}

// Complexitate O(1) - verifica daca lista e vida
bool Multime::vida() const {
	return elemente.eVida();
}

Multime::~Multime() {}


// Complexitate O(1) - returnam iterator
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

int Multime::diferenta(const Multime& b) {
	int nrSterse = 0;
	int curent = elemente.cap;
	while (curent != -1) {
		int urmator = elems[curent].next;
		int val = elems[curent].valoare;

		if (b.cauta(val)) {
			sterge(val);
			nrSterse++;
		}

		curent = urmator;
	}
	return nrSterse;
}
