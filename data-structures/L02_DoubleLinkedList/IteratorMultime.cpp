#include "IteratorMultime.h"
#include "Multime.h"


IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
	curent = multime.elemente.inceput();
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
	if (curent->prec == nullptr) {
		curent = nullptr;
	}
	else {
		curent = curent->prec;
	}
}

// Complexitate O(1) - muta cursorul pe elementul urmator
void IteratorMultime::urmator() {
	if (!valid()) {
		throw std::exception();
	}
	curent = curent->urm;
}

// Complexitate O(1) - returneaza elementul curent
TElem IteratorMultime::element() const {
	if (!valid()) {
		throw std::exception();
	}
	return curent->valoare;
}

// Complexitate O(1) - verifica daca iteratorul e valid
bool IteratorMultime::valid() const {
	return (curent != nullptr);
}
