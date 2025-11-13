#include "domain.h"
#include <vector>
#include <string>
#include <cctype>

using std::string;
using std::vector;
using std::find_if;

/*
Functie utilitara care transforma un string in lowercase
pre: genre - sa existe
post: genre - complet lowercase
*/
void Carte::to_lower_genre() {
	for (auto& c : genre)
		c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
}

/*
Functie care valideaza autorul
pre: new_author - sa existe
post: true - stringul nu contine cifre
	  throw - stringul contine cifre
*/
bool Carte::validate_author(const string& new_author) const {
	for (auto c : new_author)
		if (isdigit(c))
			throw ValidationException("Autor invalid!");
	return true;
}

/*
Functie care valideaza gen-ul\
pre: new_genre - sa existe
post: true - gen-ul respecta structura data
      throw - altfel
*/
bool Carte::validate_genre(const string& new_genre) const {
	vector<string> list = { "drama", "comedie", "istorie", "fictiune" };
	auto it = find_if(list.begin(), list.end(), [&](const string& word) { return word == new_genre; });
	if (it == list.end())
		throw ValidationException("Gen invalid!");
	return true;
}

/*
Functie care valideaza autorul si gen-ul
post: true - cartea e valida si poate fi adaugata in repo
      throw - carte invalida
*/
bool Carte::validate_book() const {
	return validate_author(author) && validate_genre(genre);
}

//Pregateste obiectul pentru a fi afisat in consola
string Carte::to_string() const {
	return "ID: " + std::to_string(id) +
		" Titlu: " + title +
		" Autor: " + author +
		" Gen: " + genre +
		" An aparitie: " + std::to_string(year);
}