#include "service.h"

/*
Functia valideaza o carte apoi o adauga in repo
throw: gen / autor invalid
*/
void Service::add(const string& title, const string& author, const string& genre, const int year) {
	Carte c{ title, author, genre, year };
	c.validate_book();
	repo.add(c);
}

/*
Functia sterge cartea cu id-ul dat
throw: Cartea cu ID nu exista
*/
void Service::remove(int id) {
	repo.remove(id);
}

/*
Functia actualizeaza titlul unei carti
throw: Cartea cu ID nu exista
*/
void Service::update_title(int id, const string& title) {
	repo.update_title(id, title);
}

/*
Functia actualizeaeza autorul unei carti
throw: Cartea cu ID nu exista sau autor invalid
*/
void Service::update_author(int id, const string& author) {
	repo.update_author(id, author);
}

/*
Functia actualizeaeza gen-ul unei carti
throw: Cartea cu ID nu exista sau gen invalid
*/
void Service::update_genre(int id, const string& genre) {
	repo.update_genre(id, genre);
}

/*
Functia actualizeaeza anul unei carti
throw: Cartea cu ID nu exista
*/
void Service::update_year(int id, const int year) {
	repo.update_year(id, year);
}

/*
Functia filtreaza cartile dupa un titlu dat
*/
VectorDinamic<Carte> Service::filter_title(const string& title) const {
	VectorDinamic<Carte> filtered;
	for (auto& carte : get_all())
		if (carte.get_title() == title)
			filtered.push_back(carte);
	return filtered;
}

/*
Functia filtreaza cartile dupa un an dat
*/
VectorDinamic<Carte> Service::filter_year(const int year) const {
	VectorDinamic<Carte> filtered;
	for (auto& carte : get_all())
		if (carte.get_year() == year)
			filtered.push_back(carte);
	return filtered;
}

/*
Functia sorteaza cartile dupa un titlu dat
*/
VectorDinamic<Carte> Service::sort_title() const {
	VectorDinamic<Carte> sorted = get_all();
	for (size_t i = 0; i < sorted.get_size() - 1; i++)
		for (size_t j = i + 1; j < sorted.get_size(); j++)
			if (sorted[i].get_title() > sorted[j].get_title()) {
				Carte temp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = temp;
			}
	return sorted;
}

/*
Functia filtreaza cartile dupa un autor dat
*/
VectorDinamic<Carte> Service::sort_author() const {
	VectorDinamic<Carte> sorted = get_all();
	for (size_t i = 0; i < sorted.get_size() - 1; i++)
		for (size_t j = i + 1; j < sorted.get_size(); j++)
			if (sorted[i].get_author() > sorted[j].get_author()) {
				Carte temp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = temp;
			}
	return sorted;
}

/*
Functia filtreaza cartile dupa un an si gen date
*/
VectorDinamic<Carte> Service::sort_year_and_genre() const {
	VectorDinamic<Carte> sorted = get_all();
	for (size_t i = 0; i < sorted.get_size() - 1; i++)
		for (size_t j = i + 1; j < sorted.get_size(); j++)
			if (sorted[i].get_year() > sorted[j].get_year() ||
				(sorted[i].get_year() == sorted[j].get_year() &&
					sorted[i].get_genre() > sorted[j].get_genre())) {
				Carte temp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = temp;
			}
	return sorted;
}