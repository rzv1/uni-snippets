#pragma once
#include <stdbool.h>

typedef struct Car {
	int ID;
	char* license;
	char* model;
	char* category;
	bool is_rented;
}Car;

/*
* Constructor pentru entitatea masina
*/
Car create_car(const char* license, const char* model, const char* category);

/*
* Valideaza categoria masinii
*/
bool validate_category(const char* category);

/*
* Destructor pentru entitatea masina
*/
void destroy_car(Car* car);

/*
* Getter pentru ID
*/
int get_id(Car* car);

/*
* Getter pentru numarul de inmatriculare
*/
const char* get_license(Car* car);

/*
* Getter pentru model
*/
const char* get_model(Car* car);

/*
* Getter pentru categorie
*/
const char* get_category(Car* car);

/*
* Getter pentru is_rented
*/
bool get_is_rented(Car* car);

/*
* Setter pentru numarul de inmatriculare
*/
void set_license(Car* car, const char* license);

/*
* Setter pentru model
*/
void set_model(Car* car, const char* model);

/*
* Setter pentru categorie
*/
void set_category(Car* car, const char* category);

/*
* Setter pentru is_rented
*/
void set_is_rented(Car* car, bool is_rented);