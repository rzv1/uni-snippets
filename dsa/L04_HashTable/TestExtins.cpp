#include "Multime.h"
#include <assert.h>
#include "TestExtins.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

void printM(Multime& m){
	IteratorMultime im = m.iterator();
	while (im.valid()){
		std::cout << im.element() << " ";
		im.urmator();
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void testCreeaza() {
	Multime m;
	assert(m.dim() == 0);
	assert(m.vida() == true);

	for (int i = -10; i < 10; i++) { //cautam in multimea vida
		assert(m.cauta(i) == false);
	}
	for (int i = -10; i < 10; i++) { //stergem din multimea vida
		assert(m.sterge(i) == false);
	}

	IteratorMultime im = m.iterator(); //iterator pe multimea vida ar trebui sa fie invalid din start
	assert(im.valid() == false);
}


void testAdauga() {
	Multime m; //adaugam elemente [0, 10)
	for (int i = 0; i < 10; i++) {
		m.adauga(i);
	}
	//printM(m);
	assert(m.vida() == false);
	assert(m.dim() == 10);
	for (int i = -10; i < 20; i++) { //mai adaugam elemente [-10, 20)
		m.adauga(i);
	}
	//printM(m);
	assert(m.vida() == false);
	assert(m.dim() == 30);
	for (int i = -100; i < 100; i++) { //mai adaugam elemente [-100, 100)
		m.adauga(i);
	}
	//printM(m);
	assert(m.vida() == false);
	assert(m.dim() == 200);
	for (int i = -200; i < 200; i++) {
		if (i < -100) {
			assert(m.cauta(i) == false);
		}
		else if (i < 0) {
			assert(m.cauta(i) == true);
		}
		else if (i < 100) {
			assert(m.cauta(i) == true);
		}
		else {
			assert(m.cauta(i) == false);
		}
	}
	for (int i = 10000; i >= -10000; i--) { //adaugam mult, si acum prima data adaugam valori mari, dupa aceea mici
		m.adauga(i);
	}
	assert(m.dim()==20000);
}


void testSterge() {
	Multime m;
	for (int i = -100; i < 100; i++) { //stergem din multimea vida
		assert(m.sterge(i) == false);
	}
	assert(m.dim() == 0);
	//printM(m);
	for (int i = -100; i < 100; i = i + 2) { //adaugam elemente din 2 in 2 (numere pare)
		m.adauga(i);
	}
	for (int i = -100; i < 100; i++) { //stergem tot (inclusiv elemente inexistente)
		if (i % 2 == 0) {
			assert(m.sterge(i) == true);
		}
		else {
			assert(m.sterge(i) == false);
		}
	}
	assert(m.dim() == 0);
	//printM(m);

	for (int i = -100; i <= 100; i = i + 2) { //adaugam elemente din 2 in 2
		m.adauga(i);
	}
	//printM(m);
	for (int i = 100; i > -100; i--) { //stergem descrescator (in ordine inversa fata de ordinea adaugarii)
		if (i % 2 == 0) {
			assert(m.sterge(i) == true);
		}
		else {
			assert(m.sterge(i) == false);
		}
	}

	assert(m.dim() == 1);
	//printM(m);

	m.sterge(-100);
	assert(m.dim() == 0);

	for (int i = -100; i < 100; i++) { //adaugam de 5 ori pe fiecare element
		m.adauga(i);
		m.adauga(i);
		m.adauga(i);
		m.adauga(i);
		m.adauga(i);
	}
	//printM(m);
	assert(m.dim() == 200);
	for (int i = -200; i < 200; i++) { //stergem elemente inexistente si existente
		if (i < -100 || i >= 100) {
			assert(m.sterge(i) == false);
		}
		else {
			assert(m.sterge(i) == true);
			assert(m.sterge(i) == false);
		}
	}
	assert(m.dim() == 0);

 }



void testIterator() {
	Multime m;
	IteratorMultime im = m.iterator(); //iterator pe multime vida
	assert(im.valid() == false);

	for (int i = 0; i < 100; i++) {  //adaug de 100 de ori valoarea 33
		m.adauga(33);
	}
	//printM(m);
	IteratorMultime im2 = m.iterator(); //daca iterez doar 33 poate sa-mi dea iteratorul
	assert(im2.valid() == true);
	TElem elem = im2.element();
	assert(elem == 33);
	im2.urmator();
	assert(im2.valid() == false);

	im2.prim(); //resetam pe primul elemente
	assert(im2.valid() == true);

	Multime m2;
	for (int i = -100; i < 100; i++) { //adaug 200 de elemente, fiecare de 3 ori
		m2.adauga(i);
		m2.adauga(i);
		m2.adauga(i);
	}
	//printM(m2);
	IteratorMultime im3 = m2.iterator();
	assert(im3.valid() == true);
	for (int i = 0; i < 200; i++) {
		//TElem e1 = im3.element();
		im3.urmator();
	}
	assert(im3.valid() == false);
	im3.prim();
	assert(im3.valid() == true);


	Multime m3;
	for (int i = 0; i < 200; i= i + 4) { //adaugam doar multipli de 4
		m3.adauga(i);
	}
	//printM(m3);

	IteratorMultime im4 = m3.iterator();
	assert(im4.valid() == true);
	int count = 0;
	while (im4.valid()) { //fiecare element e multiplu de 4 si sunt in total 50 de elemente
		TElem e = im4.element();
		assert(e % 4 == 0);
		im4.urmator();
		count++;
	}
	assert(count == 50);

}



void testQuantity() {//scopul e sa adaugam multe date
	Multime m;
	for (int i = 10; i >= 1; i--) {
		for (int j = -30000; j <= 30000; j = j + i) {
			m.adauga(j);
		}
	}
	assert(m.dim() == 60000);
	IteratorMultime im = m.iterator();
	assert(im.valid() == true);
	for (int i = 0; i < m.dim(); i++) {
		im.urmator();
	}
	im.prim();
	while (im.valid()) { //fiecare element returnat de iterator trebuie sa fie in multime
		TElem e = im.element();
		assert(m.cauta(e) == true);
		im.urmator();
	}
	assert(im.valid() == false);
	for (int i = 0; i < 10; i++) { //stergem multe elemente existente si inexistente
		for (int j = 40000; j >= -40000; j--) {
			m.sterge(j);
		}
	}
	assert(m.dim() == 0);
}

void testeDiferentaMaxMin() {
	Multime m1;
	assert(m1.diferentaMaxMin() == -1);

	Multime m2;
	m2.adauga(5);
	assert(m2.diferentaMaxMin() == 0);

	Multime m3;
	m3.adauga(10);
	m3.adauga(20);
	assert(m3.diferentaMaxMin() == 10);

	Multime m4;
	m4.adauga(-10);
	m4.adauga(0);
	m4.adauga(10);
	assert(m4.diferentaMaxMin() == 20);

	Multime m5;
	m5.adauga(3);
	m5.adauga(3);
	m5.adauga(3);
	assert(m5.diferentaMaxMin() == 0);

	Multime m6;
	m6.adauga(1000000);
	m6.adauga(-1000000);
	assert(m6.diferentaMaxMin() == 2000000);
}



// nu stim reprezentarea multimii, putem testa doar anumite lucruri generale, nu stim in ce ordine vor fi afisate elementele.
void testAllExtins() {
	testCreeaza();
	testAdauga();
	testSterge();
	testIterator();
	testQuantity();
	testeDiferentaMaxMin();
}
