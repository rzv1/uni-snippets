#include "domain.h"
#include <vector>
#include <string>
#include <cctype>

using std::vector;
using std::string;

void Carte::to_lower_genre() {
	for (auto& c : genre)
		c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
}

bool Carte::validate_author(const string& new_author) const {
  for (auto c : new_author)
   if (isdigit(c))
    throw ValidationException("Autor invalid!");
  return true;
	}

bool Carte::validate_genre(const string& new_genre) const {
	vector<string> list = { "drama", "comedie", "istorie", "fictiune" };
	bool gasit = false;
	for (auto& word : list)
		if (word == new_genre)
			gasit = true;
	if(!gasit)
		throw ValidationException("Gen invalid!");
	return true;
}

bool Carte::validate_book() const {
	return validate_author(author) && validate_genre(genre);
}

string Carte::to_string() const {
	return "ID: " + std::to_string(id) +
		" Titlu: " + title +
		" Autor: " + author +
		" Gen: " + genre +
		" An aparitie: " + std::to_string(year);
}