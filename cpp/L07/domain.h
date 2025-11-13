#pragma once
#include <string>
#include <iostream>
using std::string;

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

class Carte {
private:
	string title;
	string author;
	string genre;
	int year = 0;
	int id = 0;
public:
	Carte(const string& title, const string& author, const string& genre, int year) : title{ title }, author{ author }, genre{ genre }, year{ year }, id{ 0 } {
		to_lower_genre();
	}
	Carte() = default;

	Carte(const Carte& other) : title{ other.title }, author{ other.author }, genre{ other.genre }, year{ other.year }, id{ other.id } {
		//std::cout << "Carte " << other.get_title() << " copiata!\n";
	}

	~Carte() = default;

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

	bool validate_author(const string& author) const;
	bool validate_genre(const string& genre) const;
	bool validate_book() const;
	void to_lower_genre();

	string to_string() const;
};