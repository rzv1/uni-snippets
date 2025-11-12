#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>


bool Multime::adauga(TElem elem) {
	return elems.adauga(elem);
}


bool Multime::sterge(TElem elem) {
	return elems.sterge(elem);
}


bool Multime::cauta(TElem elem) const {
	return elems.cauta(elem);
}


int Multime::dim() const {
	return elems.dim();
}

bool Multime::vida() const {
	return elems.vida();
}


Multime::~Multime() {
	/* de adaugat */
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

int Multime::diferentaMaxMin() const {
    if (this->vida())
        return -1;
    IteratorMultime it = this->iterator();
    it.prim();
    int min = it.element();
    int max = it.element();
    while (it.valid()) {
        int elem = it.element();
        if (elem < min)
            min = elem;
        if (elem > max)
            max = elem;
        it.urmator();
    }
    return max - min;
}
