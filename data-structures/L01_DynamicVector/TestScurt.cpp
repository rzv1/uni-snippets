#include "TestScurt.h"
#include <assert.h>
#include "VectorDinamic.h"
#include "Multime.h"
#include "IteratorVectorDinamic.h"
#include <iostream>

using namespace std;

void testMultime() {
    Multime m;
    assert(m.dim() == 0);
    assert(m.vida() == true);

    // Adaugam elemente
    assert(m.adauga(5) == true);   
    assert(m.adauga(1) == true);   
    assert(m.adauga(10) == true);  
    assert(m.dim() == 3);
    assert(m.vida() == false);
    // M = {1, 5, 10}

    // Incercam sa adaugam un element existent
    assert(m.adauga(5) == false);  // 5 exista deja; nu se adauga
    assert(m.dim() == 3);          // dimensiunea ramane 3

    // Cautam elemente
    assert(m.cauta(5) == true);
    assert(m.cauta(2) == false);

    assert(m.sterge(1) == true);
    assert(m.dim() == 2);         
    assert(m.cauta(1) == false);

    assert(m.sterge(7) == false);
    assert(m.dim() == 2);

    assert(m.adauga(3) == true);  
    assert(m.dim() == 3);         


    assert(m.sterge(3) == true);
    assert(m.sterge(5) == true);
    assert(m.sterge(10) == true);
    assert(m.vida() == true);

}

void testVectorDinamic() {
    VectorDinamic v(4);
    assert(v.dim() == 0); //adaug niste elemente
    v.adaugaSfarsit(5);
    v.adauga(1, 1);
    v.adauga(0, 10);
    v.adauga(1, 7);
    v.adauga(1, 1);
    v.adauga(1, 11);
    v.adauga(1, -3);
    assert(v.dim() == 7);
    assert(v.sterge(1) == -3);
    assert(v.sterge(4) == 5);
    assert(v.dim() == 5);
    assert(v.modifica(0, 7) == 10);
    assert(v.dim() == 5);
    IteratorVectorDinamic iv = v.iterator();
    int vals[] = { 7,11,1,7,1 };
    iv.prim();
    int k = 0;
    while (iv.valid()) {
        TElem e = iv.element();
        assert(e == vals[k++]);
        iv.urmator();
    }
}

void testAll() { //apelam fiecare functie sa vedem daca exista
	testMultime();
	testVectorDinamic();
}
