#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>


AB::AB() : abc() {}

AB::AB(const AB& ab) : abc(ab.abc) {}

AB::AB(TElem e) : abc(e) {}

AB::AB(const AB& st, TElem e, const AB& dr) : abc(e) {
	abc.adaugaSubSt(st.abc);
	abc.adaugaSubDr(dr.abc);

}

void AB::adaugaSubSt(const AB& st){
	abc.adaugaSubSt(st.abc);
}

void AB::adaugaSubDr(const AB& dr){
	abc.adaugaSubDr(dr.abc);
}

TElem AB::element() const{
	return abc.element();
}

AB AB::stang() const{
	AB a;
	a.abc = abc.stang();
	return a;
}

AB AB::drept() const{
	AB a;
	a.abc = abc.drept();
	return a;
}

AB::~AB() {
	/* de adaugat */
}

bool AB::vid() const{
	return abc.vid();
}


IteratorAB* AB::iterator(string s) const {
	if (s=="preordine")
		return new IteratorPreordine(*this);
	if (s=="inordine")
		return new IteratorInordine(*this);
	if (s=="postordine")
		return new IteratorPostordine(*this);
	if (s=="latime")
		return new IteratorLatime(*this);
	return nullptr;
};
