#pragma once
#include "repo.h"

/*
* Service pentru adaugare masina
*/
bool service_add_car(Repo* repo, const char* license, const char* model, const char* category);

/*
* Service pentru actualizare numar de inmatriculare
*/
bool service_update_license(Repo* repo, int id, const char* license);

/*
* Service pentru actualizare model
*/
bool service_update_model(Repo* repo, int id, const char* model);

/*
* Service pentru actualizare categorie
*/
bool service_update_category(Repo* repo, int id, const char* category);

/*
* Service pentru actualizare starea de inchiriere
*/
bool service_update_is_rented(Repo* repo, int id, bool is_rented);

/*
* Service pentru filtrare dupa model
*/
Repo* service_filter_by_model(Repo* repo, const char* model);

/*
* Service pentru filtrare dupa categorie
*/
Repo* service_filter_by_category(Repo* repo, const char* category);

/*
* Service pentru sortare crescatoare dupa model
*/
bool sort_asc_by_category(Car* car1, Car* car2);

/*
* Service pentru sortare descrescatoare dupa model
*/
bool sort_desc_by_category(Car* car1, Car* car2);

/*
* Service pentru sortare crescatoare dupa model
*/
bool sort_asc_by_model(Car* car1, Car* car2);

/*
* Service pentru sortare descrescatoare dupa model
*/
bool sort_desc_by_model(Car* car1, Car* car2);

/*
* Service pentru sortare dupa categorie
*/
Repo* service_sort(Repo* repo, bool(*sort)(Car* car1, Car* car2));