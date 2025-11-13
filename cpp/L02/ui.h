#pragma once
#include "service.h"

/*
* Afiseaza meniul principal
*/
void show_menu();

/*
* Afiseaza meniul de actualizare
*/
void show_update_menu();

/*
* Afiseaza meniul de filtrare
*/
void show_filter_menu();

/*
* Afiseaza meniul de sortare
*/
void show_sort_menu();

/*
* Afiseaza masinile
*/
void show_cars(Repo* repo);

/*
* Curata bufferul
*/
int verify_buffer();

/*
* Verifica daca sirul introdus depaseste limita maxima de 8 caractere
*/
bool verify_lenght();

/*
* Citeste un numar
*/
bool input_int(int* number);

/*
* UI pentru Adauga o masina
*/
void ui_add_car(Repo* repo);

/*
* UI pentru Actualizeaza numar de inmatriculare
*/
void ui_update_license(Repo* repo);

/*
* UI pentru Actualizeaza model
*/
void ui_update_model(Repo* repo);

/*
* UI pentru Actualizeaza categorie
*/
void ui_update_category(Repo* repo);

/*
* UI pentru Inchiriaza masina
*/
void ui_rent_car(Repo* repo);

/*
* UI pentru Returneaza masina
*/
void ui_return_car(Repo* repo);

/*
* UI pentru Filtrare dupa model
*/
void ui_filter_by_model(Repo* repo);

/*
* UI pentru Filtrare dupa categorie
*/
void ui_filter_by_category(Repo* repo);

/*
* UI pentru Sortare crescator dupa model
*/
void ui_sort_asc_by_model(Repo* repo);

/*
* UI pentru Sortare descrescator dupa model
*/
void ui_sort_desc_by_model(Repo* repo);

/*
* UI pentru Sortare crescator dupa categorie
*/
void ui_sort_asc_by_category(Repo* repo);

/*
* UI pentru Sortare descrescator dupa categorie
*/
void ui_sort_desc_by_category(Repo* repo);

/*
* Functia care ruleaza aplicatia
*/
void run();