#include "VectorDinamic.h"
#include "IteratorVectorDinamic.h"
#include <exception>

using namespace std;

void VectorDinamic::redim() {
	/* de adaugat */
	int capacitate_noua = capacitate * 2;
	TElem* elems_nou = new TElem[capacitate_noua];

	for (int i = 0; i < lungime; i++)
		elems_nou[i] = elems[i];

	delete[] elems;

	elems = elems_nou;
	capacitate = capacitate_noua;
}


VectorDinamic::VectorDinamic(int cp) {
	/* de adaugat */
	capacitate = cp;
	lungime = 0;

	elems = new TElem[capacitate];
}



VectorDinamic::~VectorDinamic() {
	/* de adaugat */
	delete[] elems;
}



int VectorDinamic::dim() const {
	/* de adaugat */
	return lungime;
}



TElem VectorDinamic::element(int i) const {
	/* de adaugat */
	if (i < 0 || i >= lungime)
		throw exception();
	return elems[i];
}



void VectorDinamic::adaugaSfarsit(TElem e) {
	/* de adaugat */
	if (lungime == capacitate)
		redim();
	elems[lungime++] = e;
}


void VectorDinamic::adauga(int i, TElem e) {
	/* de adaugat */
	if (i < 0 || i > lungime)
		throw exception();
	if (lungime == capacitate)
		redim();

	for (int j = lungime - 1; j >= i; j--)
		elems[j + 1] = elems[j];
	elems[i] = e;
	lungime++;
}


TElem VectorDinamic::modifica(int i, TElem e) {
	/* de adaugat */
	if (i < 0 || i >= lungime)
		throw exception();

	TElem veche = elems[i];
	elems[i] = e;
	return veche;
}


TElem VectorDinamic::sterge(int i) {
	/* de adaugat */
	if (i < 0 || i >= lungime)
		throw exception();
	TElem sters = elems[i];

	for (int j = i; j < lungime - 1; j++)
		elems[j] = elems[j + 1];
	lungime--;
	return sters;
}

IteratorVectorDinamic VectorDinamic::iterator() {
	return IteratorVectorDinamic(*this);
}



