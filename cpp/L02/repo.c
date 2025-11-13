#include "repo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Repo* create_repo() {
	/*
	Functie care creeaza un repository

	return: un repository
	*/
	Repo* repo = malloc(sizeof(Repo));
	if (repo != NULL) {
		repo->size = 0;
		repo->next_id = 1;
	}
	return repo;
}

void repo_add_car(Repo* repo, Car* car) {
	/*
	Functie care adauga o masina in repository

	repo: repository ul in care se adauga masina
	car: masina care se adauga
	*/
	car->ID = repo->next_id++;
	repo->car[repo->size++] = *car;
}

void destroy_repo(Repo* repo) {
	/*
	Functie care distruge un repository

	repo: repository ul care se distruge
	*/
	for (int i = 0; i < get_size(repo); i++) {
		destroy_car(&repo->car[i]);
	}
	free(repo);
}

int get_size(Repo* repo) {
	/*
	Functie care returneaza size ul repository-ului

	repo: repository ul pentru care se returneaza size ul

	return: size ul repository-ului
	*/
	return repo->size;
}

Car* find_by_id(Repo* repo, int id) {
	/*
	Functie care gaseste o masina dupa id

	repo: repository ul in care se cauta masina
	id: id ul masinii

	return: masina gasita sau NULL
	*/
	for (int i = 0; i < get_size(repo); i++) {
		if (repo->car[i].ID == id) {
			return &repo->car[i];
		}
	}
	return NULL;
}

Car* find_by_index(Repo* repo, int index) {
	/*
	Functie care gaseste o masina dupa index

	repo: repository ul in care se cauta masina
	index: index ul masinii

	return: masina gasita sau NULL
	*/
	if (index < 0 || index >= get_size(repo)) {
		return NULL;
	}
	return &repo->car[index];
}

bool update_license(Repo* repo, int id, const char* license) {
	/*
	Functie care actualizeaza numarul de inmatriculare al unei masini

	repo: repository ul in care se afla masina
	id: id ul masinii
	license: noul numar de inmatriculare

	return: true, daca numarul de inmatriculare a fost actualizat, false in caz contrar
	*/
	Car* car = find_by_id(repo, id);
	if (car == NULL) {
		return false;
	}
	set_license(car, license);
	return true;
}

bool update_model(Repo* repo, int id, const char* model) {
	/*
	Functie care actualizeaza modelul unei masini

	repo: repository ul in care se afla masina
	id: id ul masinii
	model: noul model

	return: true, daca modelul a fost actualizat, false in caz contrar
	*/
	Car* car = find_by_id(repo, id);
	if (car == NULL) {
		return false;
	}
	set_model(car, model);
	return true;
}

bool update_category(Repo* repo, int id, const char* category) {
	/*
	Functie care actualizeaza categoria unei masini

	repo: repository ul in care se afla masina
	id: id ul masinii
	category: noua categorie

	return: true, daca categoria a fost actualizata, false in caz contrar
	*/
	Car* car = find_by_id(repo, id);
	if (car == NULL) {
		return false;
	}
	set_category(car, category);
	return true;
}

bool update_is_rented(Repo* repo, int id, bool is_rented) {
	/*
	Functie care actualizeaza starea de inchiriere a unei masini

	repo: repository ul in care se afla masina
	id: id ul masinii
	is_rented: noua stare de inchiriere

	return: true, daca starea de inchiriere a fost actualizata, false in caz contrar
	*/
	Car* car = find_by_id(repo, id);
	if (car == NULL) {
		return false;
	}
	set_is_rented(car, is_rented);
	return true;
}