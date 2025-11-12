#include "AB.h"
#include "IteratorAB.h"

IteratorInordine::IteratorInordine(const AB& _ab):ab(_ab) {
	prim();
}

void IteratorInordine::prim(){
	while (!s.empty()) s.pop();

	AB curent = ab;
	while (!curent.vid()) {
		s.push(curent);
		curent = curent.stang();
	}
}

bool IteratorInordine::valid(){
	return !s.empty();
}

TElem IteratorInordine::element() {
	if (!valid()) throw std::runtime_error("Iterator invalid");
	return s.top().element();
}

void IteratorInordine::urmator(){
	if (!valid()) throw std::runtime_error("Iterator invalid");

	AB top = s.top();
	s.pop();

	AB drept = top.drept();
	while (!drept.vid()) {
		s.push(drept);
		drept = drept.stang();
	}
}

IteratorPreordine::IteratorPreordine(const AB& _ab):ab(_ab){
	prim();
}

void IteratorPreordine::prim(){
	while (!s.empty()) s.pop();
	if (!ab.vid()) {
		s.push(ab);
	}
}


bool IteratorPreordine::valid(){
	return !s.empty();
}

TElem IteratorPreordine::element(){
	if (!valid()) throw std::runtime_error("Iterator invalid");
	return s.top().element();
}

void IteratorPreordine::urmator(){
	if (!valid()) throw std::runtime_error("Iterator invalid");

	AB curent = s.top();
	s.pop();

	if (!curent.drept().vid()) {
		s.push(curent.drept());
	}
	if (!curent.stang().vid()) {
		s.push(curent.stang());
	}
}

IteratorPostordine::IteratorPostordine(const AB& _ab):ab(_ab){
	prim();
}

void IteratorPostordine::prim(){
	while (!st.empty()) st.pop();

	AB curent = ab;
	while (!curent.vid()) {
		st.push(make_pair(curent, false));
		curent = curent.stang();
	}

	while (!st.empty()) {
		auto top = st.top();
		if (top.second) return; // gata, nod pregătit de acces

		st.pop(); // scoatem și îl punem înapoi ca vizitat
		st.push({ top.first, true });

		AB drept = top.first.drept();
		while (!drept.vid()) {
			st.push({ drept, false });
			drept = drept.stang();
		}
	}
}


bool IteratorPostordine::valid(){
	return !st.empty();
}

TElem IteratorPostordine::element(){
	if (!valid()) throw std::runtime_error("Iterator invalid");

	return st.top().first.element();
}

void IteratorPostordine::urmator(){
	if (!valid()) throw std::runtime_error("Iterator invalid");

	while (!st.empty()) {
		auto top = st.top();
		st.pop();

		AB nod = top.first;

		if (!top.second) {
			st.push(make_pair(nod, true));

			AB drept = nod.drept();
			while (!drept.vid()) {
				st.push(make_pair(drept, false));
				drept = drept.stang();
			}
		}
	}
}

IteratorLatime::IteratorLatime(const AB& _ab):ab(_ab){
	prim();
}

void IteratorLatime::prim(){
	while (!q.empty()) q.pop();
	if (!ab.vid())
		q.push(ab);
}


bool IteratorLatime::valid(){
	return !q.empty();
}

TElem IteratorLatime::element(){
	if (!valid()) throw std::runtime_error("Iterator invalid");
	return q.front().element();
}

void IteratorLatime::urmator(){
	if (!valid()) throw std::runtime_error("Iterator invalid");

	AB current = q.front();
	q.pop();

	if (!current.stang().vid()) {
		q.push(current.stang());
	}
	if (!current.drept().vid()) {
		q.push(current.drept());
	}
}
