#pragma once

#include <iostream>

class Nod {
public:
    int valoare;
    Nod* urm;
    Nod* prec;

    Nod(int v, Nod* u = nullptr, Nod* p = nullptr)
        : valoare(v), urm(u), prec(p) {
    }
};

class DoubleLinkedList {
private:
    Nod* cap;  
    Nod* coada; 
    int dim; 

public:
    DoubleLinkedList()
        : cap(nullptr), coada(nullptr), dim(0) {
    }

    ~DoubleLinkedList() {
        Nod* curent = cap;
        while (curent) {
            Nod* temp = curent;
            curent = curent->urm;
            delete temp;
        }
    }

    bool eVida() const {
        return (dim == 0);
    }

    int dimensiune() const {
        return dim;
    }

    void inserareInceput(int valoare) {
        Nod* nou = new Nod(valoare, cap, nullptr);
        if (cap == nullptr) {
            cap = nou;
            coada = nou;
        }
        else {
            cap->prec = nou;
            cap = nou;
        }
        dim++;
    }

    void inserareSfarsit(int valoare) {
        if (coada == nullptr) {
            inserareInceput(valoare);
            return;
        }
        Nod* nou = new Nod(valoare, nullptr, coada);
        coada->urm = nou;
        coada = nou;
        dim++;
    }

    Nod* cauta(int valoare) const {
        Nod* curent = cap;
        while (curent != nullptr) {
            if (curent->valoare == valoare)
                return curent;
            curent = curent->urm;
        }
        return nullptr;
    }

    void stergeNod(Nod* deSters) {
        if (deSters == nullptr)
            return;
        if (deSters == cap && deSters == coada) {
            cap = nullptr;
            coada = nullptr;
        }
        else if (deSters == cap) {
            cap = cap->urm;
            cap->prec = nullptr;
        }
        else if (deSters == coada) {
            coada = coada->prec;
            coada->urm = nullptr;
        }
        else {
            deSters->prec->urm = deSters->urm;
            deSters->urm->prec = deSters->prec;
        }
        delete deSters;
        dim--;
    }


    bool stergeValoare(int valoare) {
        Nod* gasit = cauta(valoare);
        if (gasit) {
            stergeNod(gasit);
            return true;
        }
        return false;
    }


    Nod* inceput() const {
        return cap;
    }
};
