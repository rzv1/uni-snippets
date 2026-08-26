#include "Multime.h"

Multime::~Multime() {}
Multime::Multime(int cp) : elems(cp){}


int Multime::cautaPozitie(TElem e, bool& exista) const {
    int st = 0;
    int dr = elems.dim() - 1;
    exista = false;

    while (st <= dr) {
        int m = (st + dr) / 2;
        TElem val = elems.element(m);
        if (val == e) {
            exista = true;
            return m; 
        }
        else if (val < e) {
            st = m + 1;
        }
        else {
            dr = m - 1;
        }
    }
    return st;
}

bool Multime::adauga(TElem e) {
    bool gasit = false;
    int poz = cautaPozitie(e, gasit);
    if (gasit) {
        return false;
    }

    elems.adauga(poz, e);
    return true;
}

bool Multime::sterge(TElem e) {
    bool gasit = false;
    int poz = cautaPozitie(e, gasit);
    if (!gasit) {
        return false;
    }
    
    elems.sterge(poz);
    return true;
}

bool Multime::cauta(TElem e) const {
    bool gasit = false;
   
    cautaPozitie(e, gasit);
    return gasit;
}

int Multime::dim() const {
    return elems.dim();
}

bool Multime::vida() const {
    return (elems.dim() == 0);
}