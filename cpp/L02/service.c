#include "service.h"
#include "masina.h"
#include "repo.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool service_add_car(Repo* repo, const char* license, const char* model, const char* category) {
	/*
	Functie care adauga o masina in repo

	repo: repo ul in care se adauga masina
	license: numarul de inmatriculare al masinii
	model: modelul masinii
	category: categoria masinii

	return: true, daca masina a fost adaugata, false in caz contrar
	*/
	if (validate_category(category) == false) {
		return false;
	}
	Car car = create_car(license, model, category);
	repo_add_car(repo, &car);
	return true;
}

bool service_update_license(Repo* repo, int id, const char* license) {
	/*
	Functie care actualizeaza numarul de inmatriculare al unei masini

	repo: repo ul in care se afla masina
	id: id ul masinii
	license: noul numar de inmatriculare

	return: true, daca numarul de inmatriculare a fost actualizat, false in caz contrar
	*/
	return update_license(repo, id, license);
}

bool service_update_model(Repo* repo, int id, const char* model) {
	/*
	Functie care actualizeaza modelul unei masini

	repo: repo ul in care se afla masina
	id: id ul masinii
	model: noul model

	return: true, daca modelul a fost actualizat, false in caz contrar
	*/
	return update_model(repo, id, model);
}

bool service_update_category(Repo* repo, int id, const char* category) {
	/*
	Functie care actualizeaza categoria unei masini

	repo: repo ul in care se afla masina
	id: id ul masinii
	category: noua categorie

	return: true, daca categoria a fost actualizata, false in caz contrar
	*/
	if (validate_category(category) == false) {
		return false;
	}
	return update_category(repo, id, category);
}

bool service_update_is_rented(Repo* repo, int id, bool is_rented) {
	/*
	Functie care actualizeaza starea de inchiriere a unei masini

	repo: repo ul in care se afla masina
	id: id ul masinii
	is_rented: noua stare de inchiriere

	return: true, daca starea de inchiriere a fost actualizata, false in caz contrar
	*/
	return update_is_rented(repo, id, is_rented);
}

Repo* service_filter_by_model(Repo* repo, const char* model) {
	/*
	Functie care filtreaza masinile dupa model

	repo: repo ul in care se afla masinile
	model: modelul dupa care se filtreaza

	return: repo ul cu masinile filtrate
	*/
	Repo* filtered = create_repo();
	for (int i = 0; i < get_size(repo); i++) {
		if (strcmp(get_model(find_by_index(repo, i)), model) == 0) {
			repo_add_car(filtered, find_by_index(repo, i));
		}
	}
	return filtered;
}

Repo* service_filter_by_category(Repo* repo, const char* category) {
	/*
	Functie care filtreaza masinile dupa categorie

	repo: repo ul in care se afla masinile
	category: categoria dupa care se filtreaza

	return: repo ul cu masinile filtrate
	*/
	Repo *filtered = create_repo();
	for (int i = 0; i < get_size(repo); i++) {
		if (strcmp(get_category(find_by_index(repo, i)), category) == 0) {
			repo_add_car(filtered, find_by_index(repo, i));
		}
	}
	return filtered;
}

bool sort_asc_by_category(Car* car1, Car* car2) {
	/*
	Functie care compara doua masini dupa categorie

	car1: prima masina
	car2: a doua masina

	return: true, daca prima masina este mai mica decat a doua, false in caz contrar
	*/
	return strcmp(get_category(car1), get_category(car2)) < 0;
}

bool sort_desc_by_category(Car* car1, Car* car2) {
	/*
	Functie care compara doua masini dupa categorie

	car1: prima masina
	car2: a doua masina

	return: true, daca prima masina este mai mare decat a doua, false in caz contrar
	*/
	return strcmp(get_category(car1), get_category(car2)) > 0;
}

bool sort_asc_by_model(Car* car1, Car* car2) {
	/*
	Functie care compara doua masini dupa model

	car1: prima masina
	car2: a doua masina

	return: true, daca prima masina este mai mica decat a doua, false in caz contrar
	*/
	return strcmp(get_model(car1), get_model(car2)) < 0;
}

bool sort_desc_by_model(Car* car1, Car* car2) {
	/*
	Functie care compara doua masini dupa model

	car1: prima masina
	car2: a doua masina

	return: true, daca prima masina este mai mare decat a doua, false in caz contrar
	*/
	return strcmp(get_model(car1), get_model(car2)) > 0;
}

Repo* service_sort(Repo* repo, bool(*cmp_sort)(Car* car1, Car* car2)) {
	/*
	Functie care sorteaza masinile din repo

	repo: repo ul cu masinile
	cmp_sort: functie de comparare

	return: repo ul sortat
	*/
	Repo* sorted = create_repo();
	for (int i = 0; i < get_size(repo); i++) {
		repo_add_car(sorted, find_by_index(repo, i));
	}
	for (int i = 0; i < get_size(sorted) - 1; i++) {
		for (int j = i + 1; j < get_size(sorted); j++) {
			Car* car1 = find_by_index(sorted, i);
			Car* car2 = find_by_index(sorted, j);
			if (cmp_sort(car1, car2) == false) {
				Car aux = *car1;
				*car1 = *car2;
				*car2 = aux;
			}
		}
	}
	return sorted;
}