#include "IteratorMultime.h"
#include "Multime.h"
#define NULL_TCheie 9999


IteratorMultime::IteratorMultime(const Multime& m) : multime(m), cur(0){
	while (cur < multime.elems.c() && multime.elems.getChei()[cur] == NULL_TCheie)
		cur++;
}


void IteratorMultime::prim() {
	cur = 0;
	while (cur < multime.elems.c() && multime.elems.getChei()[cur] == NULL_TCheie)
		cur++;
}


void IteratorMultime::urmator() {
	cur++;
	while (cur < multime.elems.c() && multime.elems.getChei()[cur] == NULL_TCheie)
		cur++;
}


TElem IteratorMultime::element() const {
	/* de adaugat */
	if (!valid())
		return NULL_TELEM;
	return multime.elems.getChei()[cur];
}

bool IteratorMultime::valid() const {
	/* de adaugat */
	return cur < multime.elems.c();
}
