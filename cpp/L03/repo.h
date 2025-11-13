#pragma once
#include "masina.h"
#include <stdbool.h>

#define INITIAL_CAPACITY 1

typedef struct Repo {
	Car* cars;
	int size;
	int capacity;
	int next_id;
}Repo;

/*
* Creeaza un repository
*/
Repo* create_repo();

/*
* Sterge un repository
*/
void destroy_repo(Repo* repo);

/*
* Getter pentru size-ul repository-ului
*/
int get_size(Repo* repo);

/*
* Adauga o masina in repository
*/
void repo_add_car(Repo* repo, Car car);

/*
* Gaseste o masina dupa id
*/
Car* find_by_id(Repo* repo, int id);

/*
* Gaseste o masina dupa index
*/
Car* find_by_index(Repo* repo, int index);

/*
* Actualizeaza numarul de inmatriculare al unei masini
*/
bool update_license(Repo* repo, int id, const char* license);

/*
* Actualizeaza modelul unei masini
*/
bool update_model(Repo* repo, int id, const char* model);

/*
* Actualizeaza categoria unei masini
*/
bool update_category(Repo* repo, int id, const char* category);

/*
* Actualizeaza starea de inchiriere a unei masini
*/
bool update_is_rented(Repo* repo, int id, bool is_rented);