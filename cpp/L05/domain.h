#pragma once
#include <string>
#include <iostream>
using std::string;

// Clasa ValidationException este folosita pentru a arunca exceptii in cazul in care datele introduse nu sunt valide
class ValidationException {
private:
	string message;
public:
	ValidationException(string message) : message{ message } {}
	const string get_message() const {
		return this->message;
	}
	bool operator==(const string& ot) const {
		return message == ot;
	}
};
// Clasa Carte reprezinta o carte cu titlu, autor, gen, an de publicare si id
class Carte {
private:
	string title;
	string author;
	string genre;
	int year;
	int id;
public:
	//Constructor cu parametrii
	Carte(const string& title, const string& author, const string& genre, int year) : title{ title }, author{ author }, genre{ genre }, year{ year }, id{ 0 } {
		to_lower_genre();
	}
	//Copiator
	Carte(const Carte& other) : title{ other.title }, author{ other.author }, genre{ other.genre }, year{ other.year }, id{ other.id } {
		std::cout << "Carte " << other.get_title() << " copiata!\n";
	}
	//Constructor default
	~Carte() = default;

	// Getters si Setters pentru a accesa si modifica datele private ale cartii
	string get_title() const {
		return title;
	}
	string get_author() const {
		return author;
	}
	string get_genre() const {
		return genre;
	}
	int get_year() const {
		return year;
	}
	int get_id() const {
		return id;
	}

	void set_title(const string& new_title) {
		title = new_title;
	}
	void set_author(const string& new_author) {
		author = new_author;
	}
	void set_genre(const string& new_genre) {
		genre = new_genre;
	}
	void set_year(int new_year) {
		year = new_year;
	}
	void set_id(int new_id) {
		id = new_id;
	}

	// Functii de validare a datelor introduse
	bool validate_author(const string& author) const;
	bool validate_genre(const string& genre) const;
	bool validate_book() const;
	void to_lower_genre();

	// Functie de printare a datelor
	string to_string() const;
};