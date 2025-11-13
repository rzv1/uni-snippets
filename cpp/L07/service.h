#pragma once
#include "repo.h"
#include "domain.h"
#include "rentalcart.h"
#include <string>
#include <vector>
#include <algorithm>
using std::string;
using std::vector;
using std::copy_if;

class Service {
private:
	Repo repo;
	Rentalcart& cart;
public:
	Service(Repo repo, Rentalcart& cart) : repo{ repo }, cart{ cart } {}

	void add(const string& title, const string& author, const string& genre, const int year);
	void remove(int id);
	void update_title(int id, const string& title);
	void update_author(int id, const string& author);
	void update_genre(int id, const string& genre);
	void update_year(int id, const int year);
	vector<Carte> filter_title(const string& title) const;
	vector<Carte> filter_year(const int year) const;
	vector<Carte> sort_title() const;
	vector<Carte> sort_author() const;
	vector<Carte> sort_year_and_genre() const;

	Rentalcart& get_cart() {
		return cart;
	}
	bool clear_cart();
	bool add_cart(string& title);
	bool generate_cart(int n);
	bool export_cart(string& filename);
	vector<Carte>& cart_get_all();

	const vector<Carte>& get_all() const {
		return repo.get_all();
	}
};