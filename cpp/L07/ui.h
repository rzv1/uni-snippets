#pragma once
#include "service.h"
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cin;
using std::cout;

class UI {
private:
	Service service;
public:
	UI(Service service) : service{ service } {};

	void print_menu();
	void print_menu_update_option();
	void print_menu_filter_option();
	void print_menu_sort_option();
	void print_menu_rental_cart();
	bool print_all(const vector<Carte>& carti);

	string read_string(const string& prompt);
	int read_int(const string& prompt);

	void run();

	void add();
	void remove();
	void update_title();
	void update_author();
	void update_genre();
	void update_year();
	void filter_title();
	void filter_year();
	void sort_title();
	void sort_author();
	void sort_year_and_genre();
	void clear_cart();
	void add_cart();
	void generate_cart();
	void export_cart();

	void invalid();
	void improved_visuals();
};