#include "IteratorVectorDinamic.h"
#include "VectorDinamic.h"


IteratorVectorDinamic::IteratorVectorDinamic(const VectorDinamic& _v) :

	v(_v) {
	/* de adaugat */
	current = 0;
}



void IteratorVectorDinamic::prim() {
	/* de adaugat */
	current = 0;
}



bool IteratorVectorDinamic::valid() const {
	/* de adaugat */
	return (current < v.dim());
}



TElem IteratorVectorDinamic::element() const {
	/* de adaugat */
	if (valid())
		return v.element(current);
}



void IteratorVectorDinamic::urmator() {
	/* de adaugat */
	if (valid())
		current++;
}

