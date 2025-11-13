#include "repo.h"
#include "domain.h"
#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::find_if;

/*
Functie care adauga o carte validata in repo
*/
void Repo::add(Carte& book) {
	book.set_id(next_id++);
	books.push_back(book);
}

/*
Functia care sterge cartea cu id-ul dat din repo
throw: Cartea cu ID nu exista in repo
*/
void Repo::remove(int id) {
	auto it = find_if(books.begin(), books.end(), [id](const Carte& carte) { return carte.get_id() == id; });
	if (it != books.end())
		books.erase(it);
	else
	throw RepoException("Cartea cu id-ul dat nu exista!");
}

/*
Functia actualizeaza titlul unei carti
*/
void Repo::update_title(int id, const string& title) {
	Carte& c = get_by_id(id);
	c.set_title(title);
}

/*
Functia actualizeaza autorul unei carti\
*/
void Repo::update_author(int id, const string& author) {
	Carte& c = get_by_id(id);
	c.validate_author(author);
	c.set_author(author);
}

/*
Functia actualizeaza gen-ul unei carti
*/
void Repo::update_genre(int id, const string& genre) {
	Carte& c = get_by_id(id);
	c.validate_genre(genre);
	c.set_genre(genre);
}

/*
Functia actualizeaza anul unei carti
*/
void Repo::update_year(int id, const int year) {
	Carte& c = get_by_id(id);
	c.set_year(year);
}

/*
Functia returneaza cartea cu id-ul dat
throw: Cartea cu ID nu se afla in repo
*/
Carte& Repo::get_by_id(int id) {
	auto it = find_if(books.begin(), books.end(), [&](const Carte& carte) { return carte.get_id() == id; });
	if (it != books.end())
		return *it;
	else
		throw RepoException("Id-ul nu exista!");
}