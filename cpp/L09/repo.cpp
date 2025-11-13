#include "repo.h"
#include "domain.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using std::string;
using std::ofstream;
using std::ifstream;
using std::find_if;

/*
Functie care adauga o carte validata in repo
*/
void RepoNormal::add(Carte& book) {
	book.set_id(next_id++);
	books.push_back(book);
	write_file();
}

/*
Functie care citeste din fisier
*/
void RepoProbabilitate::read_file() {
	ifstream f(filepath);
	int year;
	string title, author, genre;
	while (f >> title >> author >> genre >> year) {
		Carte c(title, author, genre, year);
		add(c);
	}
}

/*
Functie care scrie in fisier
*/
void RepoProbabilitate::write_file() {
	ofstream f(filepath);
	for (const auto& carte : carti) {
		Carte book = carte.second;
		f << book.get_title() << " " << book.get_author() << " " << book.get_genre() << " " << book.get_year() << "\n";
	}
}

/*
Functie care citeste din fisier
*/
void RepoNormal::read_file() {
	ifstream f(filepath);
	int year;
	string title, author, genre;
	while (f >> title >> author >> genre >> year) {
		Carte c(title, author, genre, year);
		add(c);
	}
}

/*
Functie care scrie in fisier
*/
void RepoNormal::write_file() {
	ofstream f(filepath);
	for (const auto& book : books) {
		f << book.get_title() << " " << book.get_author() << " " << book.get_genre() << " " << book.get_year() << "\n";
	}
}

/*
Functia care sterge cartea cu id-ul dat din repo
throw: Cartea cu ID nu exista in repo
*/
void RepoNormal::remove(int id) {
	auto it = find_if(books.begin(), books.end(), [id](const Carte& carte) { return carte.get_id() == id; });
	if (it != books.end()) {
		books.erase(it);
		write_file();
	}
	else
	throw RepoException("Cartea cu id-ul dat nu exista!");
}

/*
Functia actualizeaza titlul unei carti
*/
void RepoNormal::update_title(int id, const string& title) {
	Carte& c = get_by_id(id);
	c.set_title(title);
	write_file();
}

/*
Functia actualizeaza autorul unei carti\
*/
void RepoNormal::update_author(int id, const string& author) {
	Carte& c = get_by_id(id);
	c.validate_author(author);
	c.set_author(author);
	write_file();
}

/*
Functia actualizeaza gen-ul unei carti
*/
void RepoNormal::update_genre(int id, const string& genre) {
	Carte& c = get_by_id(id);
	c.validate_genre(genre);
	c.set_genre(genre);
	write_file();
}

/*
Functia actualizeaza anul unei carti
*/
void RepoNormal::update_year(int id, const int year) {
	Carte& c = get_by_id(id);
	c.set_year(year);
	write_file();
}

/*
Functia returneaza cartea cu id-ul dat
throw: Cartea cu ID nu se afla in repo
*/
Carte& RepoNormal::get_by_id(int id) {
	auto it = find_if(books.begin(), books.end(), [&](const Carte& carte) { return carte.get_id() == id; });
	if (it != books.end())
		return *it;
	else
		throw RepoException("Id-ul nu exista!");
}