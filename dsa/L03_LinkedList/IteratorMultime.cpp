#include "IteratorMultime.h"
#include "Multime.h"


IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
	prim();
}

// Complexitate O(1) - muta cursorul pe primul element
void IteratorMultime::prim() {
	curent = multime.elemente.inceput();
}

// Complexitate O(1) - muta cursorul pe elementul anterior
void IteratorMultime::anterior() {
	if (!valid()) {
		throw std::exception();
	}
	for(int ind = multime.elemente.inceput(); ind != -1; ind = multime.elemente[ind].next)
		if (curent == multime.elemente[ind].next) {
			curent = ind;
			break;
		}
}

// Complexitate O(1) - muta cursorul pe elementul urmator
void IteratorMultime::urmator() {
	if (!valid()) {
		throw std::exception();
	}
	curent = multime.elemente[curent].next;
}

// Complexitate O(1) - returneaza elementul curent
TElem IteratorMultime::element() const {
	if (!valid()) {
		throw std::exception();
	}
	return multime.elemente[curent].valoare;
}

// Complexitate O(1) - verifica daca iteratorul e valid
bool IteratorMultime::valid() const {
	return (curent != -1);
}
