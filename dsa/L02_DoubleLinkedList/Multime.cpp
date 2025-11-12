#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>
#include <list>

// Complexitate O(n) - in cel mai rau caz, trebuie sa parcurgem toata lista pentru a verifica daca elementul exista deja
bool Multime::adauga(TElem elem) {
	if (cauta(elem)) {
		return false;
	}
	elemente.inserareSfarsit(elem);
	return true;
}

// Complexitate O(n) - in cel mai rau caz, trebuie sa parcurgem toata lista pentru a gasi elementul
bool Multime::sterge(TElem elem) {
	if (cauta(elem)) {
		elemente.stergeValoare(elem);
		return true;
	}
	return false;
}


// Complexitate O(n) - in cel mai rau caz, trebuie sa parcurgem toata lista pentru a verifica daca elementul exista
bool Multime::cauta(TElem elem) const {
	if (elemente.cauta(elem)) {
		return true;
	}
	return false;
}

// Complexitate O(1) - returneaza dimensiunea multimii
int Multime::dim() const {
	return elemente.dimensiune();
}

// Complexitate O(1) - verifica daca lista e vida
bool Multime::vida() const {
	return elemente.eVida();
}

// Complexitate O(1) - destructorul multimii
Multime::~Multime() {}


// Complexitate O(1) - returnam iterator
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}