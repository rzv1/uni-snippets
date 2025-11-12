#pragma once
#include <stdexcept>

typedef int TElem;

struct Nod {
    TElem e;
    Nod* st;
    Nod* dr;
    Nod(TElem val) : e(val), st(nullptr), dr(nullptr) {}
};

class ABC {
private:
    struct Nod {
        TElem e;
        Nod* st;
        Nod* dr;
        Nod(TElem val) : e(val), st(nullptr), dr(nullptr) {}
    };

    Nod* rad;

	// Complexitate O(n), unde n este numarul de noduri in arborele p
    Nod* copiaza(Nod* p) const {
        if (p == nullptr) return nullptr;
        Nod* q = new Nod(p->e);
        q->st = copiaza(p->st);
        q->dr = copiaza(p->dr);
        return q;
    }

	// Complexitate O(n), unde n este numarul de noduri in arborele p
    void distruge(Nod* p) {
        if (p == nullptr) return;
        distruge(p->st);
        distruge(p->dr);
        delete p;
    }

public:
    ABC() : rad(nullptr) {}

    ABC(TElem val) {
        rad = new Nod(val);
    }

    ABC(const ABC& other) : rad(nullptr) {
        rad = copiaza(other.rad);
    }

    ABC& operator=(const ABC& other) {
        if (this != &other) {
            distruge(rad);
            rad = copiaza(other.rad);
        }
        return *this;
    }

    ~ABC() {
        distruge(rad);
    }

	// Complexitate O(1)
    bool vid() const {
        return rad == nullptr;
    }

	// Complexitate O(1)
    TElem element() const {
        if (vid()) throw std::runtime_error("Arbore vid");
        return rad->e;
    }

    // Complexitate O(n), unde n este numarul de noduri in arborele drept
    ABC stang() const {
        if (vid()) throw std::runtime_error("Arbore vid");
        ABC a;
        a.rad = copiaza(rad->st);
        return a;
    }

	// Complexitate O(n), unde n este numarul de noduri in arborele drept
    ABC drept() const {
        if (vid()) throw std::runtime_error("Arbore vid");
        ABC a;
        a.rad = copiaza(rad->dr);
        return a;
    }

	// Complexitate O(n), unde n este numarul de noduri in arborele stang
    void adaugaSubSt(const ABC& st) {
        if (vid()) throw std::runtime_error("Arbore vid");
        if (rad->st != nullptr) throw std::runtime_error("Subarbore stâng deja existent");
        rad->st = copiaza(st.rad);
    }

	// CComplexitate O(n), unde n este numarul de noduri in arborele drept
    void adaugaSubDr(const ABC& dr) {
        if (vid()) throw std::runtime_error("Arbore vid");
        if (rad->dr != nullptr) throw std::runtime_error("Subarbore drept deja existent");
        rad->dr = copiaza(dr.rad);
    }

    // Functie prietena pentru AB – acces intern la radacina
    friend class AB;
};
