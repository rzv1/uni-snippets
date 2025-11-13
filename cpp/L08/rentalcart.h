#pragma once
#include "domain.h"
#include <vector>
#include <random>

using std::vector;

class Rentalcart {
private:
	vector<Carte> books;
	size_t size;

	std::string chars = "abcdefghijklmnopqrstuvwxyz";
	std::mt19937 gen;

	string random_string(int lenght);
	string random_genre();
	int random_int(int limit);
public:
	Rentalcart() : gen(std::random_device{}()), size{ 0 } {}

	bool clear_cart();
	bool add_cart(vector<Carte>& carti);
	bool generate_cart(int n);
	bool export_cart(string filename);

	vector<Carte>& get_all() {
		return books;
	}

	size_t get_size() const{
		return size;
	}
};