#pragma once  
#include <vector>  
using std::vector;  

typedef int TCheie;
#define NULL_TCheie 9999

class TD {  
private:  
	int cap;
	int primLiber;
	vector<TCheie> e;
	vector<int> urmator;
	void actualizeazaPrimLiber() {
		primLiber++;
		while (primLiber < cap && e[primLiber] != NULL_TCheie)
			primLiber++;
	}
	int d(TCheie c) const{
		return ((c % cap) + cap) % cap;
	}
	void redimensionare() {
		int old_cap = cap;
		cap = 2 * cap;
		vector<TCheie> old_e = e;
		//vector<int> old_urmator = urmator;

		e.assign(cap, NULL_TCheie);
		urmator.assign(cap, NULL_TCheie);
		primLiber = 0;
		
		for (int i = 0; i < old_cap; i++)
			if (old_e[i] != NULL_TCheie)
				adauga(old_e[i]);
	}
public:
	TD(int c = 20) : cap(c), e(cap, NULL_TCheie), urmator(cap, NULL_TCheie), primLiber(0) {}
	// Complexitate Average case: Theta(1) ; Worst case: Theta(m), m - dimensiune TD
	bool adauga(TCheie c) {
		int i = d(c);
		int j = i;
		//daca locatia e libera, adaugam acolo
		if (e[i] == NULL_TCheie) {
			e[i] = c;
			if (i == primLiber)
				actualizeazaPrimLiber();
		}
		else {
			//mergem pe vectorul de urmator pana dam de  si memoram locatia precedenta pentru a-i modifica urm la noua valoarea adaugata
			while (i != NULL_TCheie && e[i] != c) {
				j = i;
				i = urmator[i];
			}
			//redimensionam vectorul daca este cazul
			if (primLiber == cap) {
				redimensionare();
				return adauga(c);
			}
			//adaugam cheia in lista verificand ca aceasta nu exista deja
			else if (i == NULL_TCheie) {
				e[primLiber] = c;
				urmator[j] = primLiber;
				actualizeazaPrimLiber();
			}
			else
				return false;
		}
		return true;
	}
	// Complexitate Average case: Theta(1) ; Worst case: Theta(m), m - dimensiune TD
	bool cauta(TCheie c) const{
		int i = d(c);
		while (i != NULL_TCheie && e[i] != c)
			i = urmator[i];
		return i != NULL_TCheie && e[i] == c;
	}
	// Complexitate Average case: Theta(1) ; Worst case: Theta(m), m - dimensiune TD
	bool sterge(TCheie c) {
		//caut cheia
		int i = d(c);
		int j = i;
		while (i != NULL_TCheie && e[i] != c) {
			j = i;
			i = urmator[i];
		}
		//nu am gasit cheia
		if (i == NULL_TCheie)
			return false;
		//caut un nod dupa i care ar putea fi mutat pe i
		int k = urmator[i], prev = i;
		while (k != NULL_TCheie) {
			if (d(e[k]) == d(c)) {
				e[i] = e[k];
				i = k;
				j = prev;
				break;
			}
			prev = k;
			k = urmator[k];
		}
		//sterg nod i
		if (j == NULL_TCheie) {
			if (urmator[i] != NULL_TCheie)
				e[i] = e[urmator[i]];
			else
				e[i] = NULL_TCheie;
		}
		else {
			urmator[j] = urmator[i];
			e[i] = NULL_TCheie;
		}
		urmator[i] = NULL_TCheie;
		if (i < primLiber)
			primLiber = i;
		return true;
	}

	//Complexitate Theta(1)
	int dim() const {
		int cnt = 0;
		for (int i = 0; i < cap; ++i)
			if (e[i] != NULL_TCheie) cnt++;
		return cnt;
	}

	//Complexitate Theta(1)
	bool vida() const {
		for (int i = 0; i < cap; ++i)
			if (e[i] != NULL_TCheie) return false;
		return true;
	}

	//Complexitate Theta(1)
	int c() const {
		return cap;
	}

	//Complexitate Theta(1)
	const vector<TCheie>& getChei() const {
		return e;
	}
};