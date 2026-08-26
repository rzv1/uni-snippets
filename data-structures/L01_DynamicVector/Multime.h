#pragma once
#include "VectorDinamic.h"  

typedef int TElem;

class Multime {
private:
    VectorDinamic elems;

	int cautaPozitie(TElem e, bool& exista) const;

public:
    Multime(int cp = 10);

    bool adauga(TElem e);

    bool sterge(TElem e);

    bool cauta(TElem e) const;

    int dim() const;

    bool vida() const;

    ~Multime();
};
