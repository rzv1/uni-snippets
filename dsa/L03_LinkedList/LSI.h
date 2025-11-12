#pragma once

#include <iostream>
#include <vector>

using std::vector;

typedef int TElem;

struct Nod {
    TElem valoare;
    int next;
};

class LinkedListArray {
private:
	vector<Nod> elems;
    int cap;
    int coada;
    int primulLiber;
	int dim;

    void grow(int new_dim) {
		int old_dim = (int)elems.size();
		elems.resize(new_dim);
		for (int i = old_dim; i < new_dim - 1; i++) 
			elems[i].next = i + 1;
		elems[new_dim - 1].next = -1;
		primulLiber = old_dim;
    }

    int alocare(int valoare) {
        if (primulLiber == -1) {
            grow(elems.size() * 2);
        }
        int poz = primulLiber;
        primulLiber = elems[poz].next;
        elems[poz].valoare = valoare;
        ++dim;
        return poz;
    }

	void eliberare(int poz) {
		elems[poz].next = primulLiber;
		primulLiber = poz;
        if(dim > 0)
            dim--;
	}
public:
    LinkedListArray(int initdim = 8)
        : elems(initdim), cap(-1), coada(-1), primulLiber(0), dim(0) {
		for (int i = 0; i < initdim - 1; i++) {
			elems[i].next = i + 1;
		}
		elems[initdim - 1].next = -1;
    }

    bool eVida() const {
        return (dim == 0);
    }

    int dimensiune() const {
        return dim;
    }

    void inserareInceput(int valoare) {
		int poz = alocare(valoare);
		elems[poz].next = cap;
        cap = poz;
		if (coada == -1) {
			coada = poz;
		}
    }

    void inserareSfarsit(int valoare) {
        if (coada == -1) {
			inserareInceput(valoare);
            return;
        }
		int poz = alocare(valoare);
		elems[coada].next = poz;
        coada = poz;
    }

    int cauta(int valoare) const {
		for (int c = cap; c != -1; c = elems[c].next) {
			if (elems[c].valoare == valoare) {
				return c;
			}
		}
        return -1;
    }

    void stergeIndex(int poz) {
        if (poz == -1 || cap == -1)
            return;

        if (poz == cap) {
			cap = elems[cap].next;
            if (poz == coada)
                coada = cap;
			eliberare(poz);
            return;
        }
		int prev = cap;
		while (prev != -1 && elems[prev].next != poz) 
			prev = elems[prev].next;
        if(prev == -1)
			return;

		elems[prev].next = elems[poz].next;
		if (poz == coada) {
			coada = prev;
		}
		eliberare(poz);
    }


    bool stergeValoare(int valoare) {
        if (cap == -1) return false;
        if (elems[cap].valoare == valoare) { stergeIndex(cap); return true; }

        int prev = cap;
        while (prev != -1 && elems[prev].next != -1 && elems[elems[prev].next].valoare != valoare)
            prev = elems[prev].next;

        if (prev == -1)
            return false;

        if (prev == -1 || elems[prev].next == -1)
            return false;

        int target = elems[prev].next;

        stergeIndex(target);
        return true;
    }

	int inceput() const {
		return cap;
	}
};
