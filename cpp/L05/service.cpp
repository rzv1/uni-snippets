#include "service.h"

void Service::add(const string& title, const string& author, const string& genre, const int year) {
	Carte c{ title, author, genre, year };
	c.validate_book();
	repo.add(c);
}

void Service::remove(int id) {
	repo.remove(id);
}

void Service::update_title(int id, const string& title) {
	repo.update_title(id, title);
}

void Service::update_author(int id, const string& author) {
	repo.update_author(id, author);
}

void Service::update_genre(int id, const string& genre) {
	repo.update_genre(id, genre);
}

void Service::update_year(int id, const int year) {
	repo.update_year(id, year);
}

vector<Carte> Service::filter_title(const string& title) {
	vector<Carte> filtered;
	for (auto& carte : get_all())
		if (carte.get_title() == title)
			filtered.push_back(carte);
	return filtered;
}

vector<Carte> Service::filter_year(const int year) {
	vector<Carte> filtered;
	for (auto& carte : get_all())
		if (carte.get_year() == year)
			filtered.push_back(carte);
	return filtered;
}

vector<Carte> Service::sort_title() {
	vector<Carte> sorted = get_all();
	for (size_t i = 0; i < sorted.size() - 1; i++)
		for (size_t j = i + 1; j < sorted.size(); j++)
			if (sorted[i].get_title() > sorted[j].get_title()) {
				Carte temp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = temp;
			}
	return sorted;
}

vector<Carte> Service::sort_author() {
	vector<Carte> sorted = get_all();
	for (size_t i = 0; i < sorted.size() - 1; i++)
		for (size_t j = i + 1; j < sorted.size(); j++)
			if (sorted[i].get_author() > sorted[j].get_author()) {
				Carte temp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = temp;
			}
	return sorted;
}

vector<Carte> Service::sort_year_and_genre() {
	vector<Carte> sorted = get_all();
	for (size_t i = 0; i < sorted.size() - 1; i++)
		for (size_t j = i + 1; j < sorted.size(); j++)
			if (sorted[i].get_year() > sorted[j].get_year() ||
				(sorted[i].get_year() == sorted[j].get_year() &&
					sorted[i].get_genre() > sorted[j].get_genre())) {
				Carte temp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = temp;
			}
	return sorted;
}