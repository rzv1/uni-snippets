#include "masina.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

Car create_car(const char* license, const char* model, const char* category) {
	/*
	Functie care creeaza si returneaza o masina

	license: numarul de inmatriculare al masinii
	model: modelul masinii
	category: categoria masinii

	return: o masina
	*/
	Car car;
	car.ID = 0;
	car.is_rented = false;
	car.license = malloc(strlen(license) + (size_t)1);
	if (car.license != NULL) {
		strcpy(car.license, license);
	}
	car.model = malloc(strlen(model) + (size_t)1);
	if (car.model != NULL) {
		strcpy(car.model, model);
	}
	car.category = malloc(strlen(category) + (size_t)1);
	if (car.category != NULL) {
		strcpy(car.category, category);
	}
	return car;
}

bool validate_category(const char* category) {
	/*
	Functie care valideaza categoria unei masini

	category: categoria masinii

	return: true, daca categoria este valida, false in caz contrar
	*/
	char* copy = malloc(strlen(category) + (size_t)1);
	if (copy != NULL) {
		strcpy(copy, category);
		for (int i = 0; copy[i]; i++) {
			copy[i] = (char)tolower(copy[i]);
		}
		if (strcmp(copy, "mini") == 0 || strcmp(copy, "suv") == 0 || strcmp(copy, "sport") == 0) {
			free(copy);
			return true;
		}
	}
	free(copy);
	return false;
}

void destroy_car(Car* car) {
	/*
	Functie care distruge o masina

	car: masina care va fi distrusa
	*/
	free(car->license);
	free(car->model);
	free(car->category);
}

int get_id(Car* car) {
	/*
	Functie care returneaza ID ul unei masini

	car: masina pentru care se returneaza ID ul

	return: ID ul masinii
	*/
	return car->ID;
}

const char* get_license(Car* car) {
	/*
	Functie care returneaza numarul de inmatriculare al unei masini

	car: masina pentru care se returneaza numarul de inmatriculare

	return: numarul de inmatriculare al masinii
	*/
	return car->license;
}

const char* get_model(Car* car) {
	/*
	Functie care returneaza modelul unei masini

	car: masina pentru care se returneaza modelul

	return: modelul masinii
	*/
	return car->model;
}

const char* get_category(Car* car) {
	/*
	Functie care returneaza categoria unei masini

	car: masina pentru care se returneaza categoria

	return: categoria masinii
	*/
	return car->category;
}

bool get_is_rented(Car* car) {
	/*
	Functie care returneaza starea de inchiriere a unei masini

	car: masina pentru care se returneaza starea de inchiriere

	return: true, daca masina este inchiriata, false in caz contrar
	*/
	return car->is_rented;
}

void set_license(Car* car, const char* license) {
	/*
	Functie care seteaza numarul de inmatriculare al unei masini

	car: masina pentru care se seteaza numarul de inmatriculare
	license: numarul de inmatriculare
	*/
	free(car->license);
	car->license = malloc(strlen(license) + (size_t)1);
	if (car->license != NULL) {
		strcpy(car->license, license);
	}
}

void set_model(Car* car, const char* model) {
	/*
	Functie care seteaza modelul unei masini

	car: masina pentru care se seteaza modelul
	model: modelul masinii
	*/
	free(car->model);
	car->model = malloc(strlen(model) + (size_t)1);
	if (car->model != NULL) {
		strcpy(car->model, model);
	}
}

void set_category(Car* car, const char* category) {
	/*
	Functie care seteaza categoria unei masini

	car: masina pentru care se seteaza categoria
	category: categoria masinii
	*/
	free(car->category);
	car->category = malloc(strlen(category) + (size_t)1);
	if (car->category != NULL) {
		strcpy(car->category, category);
	}
}

void set_is_rented(Car* car, bool is_rented) {
	/*
	Functie care seteaza starea de inchiriere a unei masini

	car: masina pentru care se seteaza starea de inchiriere
	is_rented: starea de inchiriere
	*/
	car->is_rented = is_rented;
}