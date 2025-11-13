#pragma once
#include "domain.h"
#include "VectorDinamic.h"

class RepoException {
private:
	string message;
public:
	RepoException(const string& message) : message{ message } {}
	~RepoException() = default;
	const string& get_message() const {
		return message;
	}
};

class Repo {
private:
	VectorDinamic<Carte> books;
	int next_id;
public:
	Repo() : next_id{ 1 } {}

	~Repo() = default;

	void add(Carte& book);

	void remove(int id);

	void update_title(int id, const string& title);
	void update_author(int id, const string& author);
	void update_genre(int id, const string& genre);
	void update_year(int id, const int year);

	Carte& get_by_id(int id);

	const VectorDinamic<Carte>& get_all() const {
		return books;
	}

	size_t get_size() const {
		return books.get_size();
	}
};