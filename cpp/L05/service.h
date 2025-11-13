#pragma once
#include "repo.h"
#include "domain.h"
#include <string>
using std::string;

class Service {
private:
	Repo repo;
public:
	Service(Repo repo) : repo{ repo } {}

	void add(const string& title, const string& author, const string& genre, const int year);
	void remove(int id);
	void update_title(int id, const string& title);
	void update_author(int id, const string& author);
	void update_genre(int id, const string& genre);
	void update_year(int id, const int year);
	vector<Carte> filter_title(const string& title);
	vector<Carte> filter_year(const int year);
	vector<Carte> sort_title();
	vector<Carte> sort_author();
	vector<Carte> sort_year_and_genre();

	const vector<Carte>& get_all() const {
		return repo.get_all();
	}
};