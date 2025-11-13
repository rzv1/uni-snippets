#include "ui.h"
#include "repo.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


void show_menu() {
	/*
	Functie care afiseaza meniul principal
	*/
	printf("\n1. Adauga masina\n");
	printf("2. Actualizeaza masina\n");
	printf("3. Inchiriaza masina\n");
	printf("4. Returneaza masina\n");
	printf("5. Afiseaza masini\n");
	printf("6. Filtrare masini\n");
	printf("7. Sortare masini\n");
	printf("8. Exit\n");
}

void show_update_menu() {
	/*
	Functie care afiseaza meniul de actualizare
	*/
	printf("\n1. Actualizeaza numar de inmatriculare\n");
	printf("2. Actualizeaza model\n");
	printf("3. Actualizeaza categorie\n");
	printf("4. Inapoi\n");
}

void show_filter_menu() {
	/*
	Functie care afiseaza meniul de filtrare
	*/
	printf("\n1. Filtrare dupa model\n");
	printf("2. Filtrare dupa categorie\n");
	printf("3. Inapoi\n");
}

void show_sort_menu() {
	/*
	Functie care afiseaza meniul de sortare
	*/
	printf("\n1. Sortare dupa model\n");
	printf("2. Sortare dupa categorie\n");
	printf("3. Inapoi\n");
}

void show_sort_type_menu() {
	/*
	Functie care afiseaza meniul de sortare
	*/
	printf("\n1. Sortare crescatoare\n");
	printf("2. Sortare descrescatoare\n");
}

void show_cars(Repo* repo) {
	/*
	Functie care afiseaza masinile
	*/
	if (get_size(repo) == 0) {
		printf("Nu exista masini!\n");
		return;
	}
	else for (int i = 0; i < get_size(repo); i++) {
		Car* car = &repo->car[i];
		printf("ID: %d. License: %s Model: %s Type: %s %s", 
			get_id(car), 
			get_license(car), 
			get_model(car), 
			get_category(car),
			get_is_rented(car) ? "| Inchiriata\n" : "\n");
	}
}

int verify_buffer() {
	/*
	Functie care curata bufferul
	*/
	int chars = 0;
	while (getchar() != '\n')
		chars++;
	return chars;
}

bool verify_lenght(){
	/*
	Functie care verifica daca sirul introdus depaseste limita maxima de 8 caractere
	*/
	int c = getchar();
	if (c != '\n') {
		printf("Sirul introdus depaseste limita maxima de 8 caractere.\n");
		// Clear buffer
		while (getchar() != '\n');
		return false;
	}
	return true;
}

bool input_int(int* number) {
	/*
	Functie care citeste un numar
	*/
	(void)scanf("%d", number);
	if (verify_buffer() > 0) {
		printf("Format input incorect!\n");
		return false;
	}
	return true;
}

void ui_add_car(Repo* repo){
	/*
	Functie care afiseaza meniul de adaugare a unei masini
	*/
	char license[9], model[9], category[9];
	printf("Numar de inmatriculare: ");
	//fgets(license, 9, stdin);
	(void)scanf("%8s", license);
	if(verify_lenght() == false)
		return;

	printf("Model: ");
	//fgets(model, 9, stdin);
	(void)scanf("%8s", model);
	if(verify_lenght() == false)
		return;

	printf("Categorie (mini, suv, sport): ");
	//fgets(category, 9, stdin);
	(void)scanf("%8s", category);
	if(verify_lenght() == false)
		return;

	bool success = service_add_car(repo, license, model, category);
	if (success) {
		printf("Masina adaugata cu succes!\n");
	}
	else {
		printf("Eroare la adaugare! (categorie nevalida)\n");
	}
}

void ui_update_license(Repo* repo) {
	/*
	Functie care afiseaza meniul de actualizare a numarului de inmatriculare
	*/
	show_cars(repo);
	printf("\nID: ");
	int id = 0;
	if (input_int(&id) == false)
		return;

	char license[9];
	printf("Numar de inmatriculare: ");
	(void)scanf("%8s", license);
	if(verify_lenght() == false)
		return;

	bool success = service_update_license(repo, id, license);
	if (success) {
		printf("Numar de inmatriculare actualizat cu succes!\n");
	}
	else {
		printf("Eroare la actualizare! (id inexistent)\n");
	}
}

void ui_update_model(Repo* repo) {
	/*
	Functie care afiseaza meniul de actualizare a modelului
	*/
	show_cars(repo);
	printf("\nID: ");
	int id = 0;
	if (input_int(&id) == false)
		return;

	char model[9];
	printf("Model: ");
	(void)scanf("%8s", model);
	if(verify_lenght() == false)
		return;

	bool success = service_update_model(repo, id, model);
	if (success) {
		printf("Model actualizat cu succes!\n");
	}
	else {
		printf("Eroare la actualizare! (id inexistent)\n");
	}
}

void ui_update_category(Repo* repo) {
	/*
	Functie care afiseaza meniul de actualizare a categoriei
	*/
	show_cars(repo);
	printf("\nID: ");
	int id = 0;
	if (input_int(&id) == false)
		return;

	char category[9];
	printf("Categorie: ");
	(void)scanf("%8s", category);
	verify_lenght();
	service_update_category(repo, id, category);

	bool success = service_update_category(repo, id, category);
	if (success) {
		printf("Categorie actualizata cu succes!\n");
	}
	else {
		printf("Eroare la actualizare! (id inexistent / categorie nevalida)\n");
	}
}

void ui_rent_car(Repo* repo) {
	/*
	Functie care afiseaza meniul de inchiriere a unei masini
	*/
	show_cars(repo);
	printf("\nID: ");
	int id = 0;
	if (input_int(&id) == false)
		return;
	bool success = service_update_is_rented(repo, id, true);
	if (success) {
		printf("Masina inchiriata cu succes!\n");
	}
	else {
		printf("Eroare la inchiriere! (id inexistent)\n");
	}
}

void ui_return_car(Repo* repo) {
	/*
	Functie care afiseaza meniul de returnare a unei masini
	*/
	show_cars(repo);
	printf("\nID: ");
	int id = 0;
	if (input_int(&id) == false)
		return;
	bool success = service_update_is_rented(repo, id, false);
	if (success) {
		printf("Masina returnata cu succes!\n");
	}
	else {
		printf("Eroare la returnare! (id inexistent)\n");
	}
}

void ui_filter_by_model(Repo* repo) {
	/*
	Functie care afiseaza meniul de filtrare a masinilor dupa model
	*/
	char model[9];
	printf("Model: ");
	(void)scanf("%8s", model);
	verify_lenght();
	Repo* filtered = service_filter_by_model(repo, model);
	show_cars(filtered);
	free(filtered);
}

void ui_filter_by_category(Repo* repo) {
	/*
	Functie care afiseaza meniul de filtrare a masinilor dupa categorie
	*/
	char category[9];
	printf("Categorie: ");
	(void)scanf("%8s", category);
	verify_lenght();
	Repo* filtered = service_filter_by_category(repo, category);
	show_cars(filtered);
	free(filtered);
}

void ui_sort_asc_by_model(Repo* repo) {
	/*
	Functie care afiseaza meniul de sortare a masinilor crescator dupa model
	*/
	Repo* sorted = service_sort(repo, sort_asc_by_model);
	show_cars(sorted);
	free(sorted);
}

void ui_sort_desc_by_model(Repo* repo) {
	/*
	Functie care afiseaza meniul de sortare a masinilor descrescator dupa model
	*/
	Repo* sorted = service_sort(repo, sort_desc_by_model);
	show_cars(sorted);
	free(sorted);
}

void ui_sort_asc_by_category(Repo* repo) {
	/*
	Functie care afiseaza meniul de sortare a masinilor crescator dupa categorie
	*/
	Repo* sorted = service_sort(repo, sort_asc_by_category);
	show_cars(sorted);
	free(sorted);
}

void ui_sort_desc_by_category(Repo* repo) {
	/*
	Functie care afiseaza meniul de sortare a masinilor descrescator dupa categorie
	*/
	Repo* sorted = service_sort(repo, sort_desc_by_category);
	show_cars(sorted);
	free(sorted);
}

void run() {
	/*
	Functie care ruleaza aplicatia
	*/
	Repo* repo = create_repo();
	int option;
	while (1) {
		show_menu();
		printf("Optiune: ");
		if (input_int(&option) == false)
			continue;

		switch (option) {
		//Adauga masina
		case 1:
			ui_add_car(repo);
			break;
		//Actualizeaza masina
		case 2: 
			while (1) {
				show_update_menu();
				printf("Optiune: ");
				if (input_int(&option) == false)
					continue;

				if (option == 4) {
					break;
				}
				switch (option) {
				case 1:
					ui_update_license(repo);
					break;
				case 2:
					ui_update_model(repo);
					break;
				case 3:
					ui_update_category(repo);
					break;
				}
			}
			break;
		//Inchiriaza masina
		case 3: 
			ui_rent_car(repo);
			break;
		//Returneaza masina
		case 4: 
			ui_return_car(repo);
			break;
		//Afiseaza masini
		case 5: 
			show_cars(repo);
			break;
		//Filtrare masini
		case 6: 
			while (1) {
				show_filter_menu();
				printf("Optiune: ");
				if (input_int(&option) == false)
					continue;

				if (option == 3)
					break;
				switch (option) {
				case 1:
					ui_filter_by_model(repo);
					break;
				case 2:
					ui_filter_by_category(repo);
					break;
				default:
					printf("Optiune invalida!\n");
				}
			}
			break;
		//Sortare masini
		case 7: 
			while (1) {
				show_sort_menu();
				printf("Optiune: ");
				if (input_int(&option) == false)
					continue;
				if (option == 3)
					break;

				switch (option) {
				//Sortare masini dupa model
				case 1: 
					while (1) {
						show_sort_type_menu();
						printf("Optiune: ");
						if (input_int(&option) == false)
							continue;

						switch (option) {
						case 1:
							ui_sort_asc_by_model(repo);
							break;
						case 2:
							ui_sort_desc_by_model(repo);
							break;
						default:
							printf("Optiune invalida!\n");
						}
						break;
					}
					break;
				//Sortare masini dupa categorie
				case 2: 
					while (1) {
						show_sort_type_menu();
						printf("Optiune: ");
						if (input_int(&option) == false)
							continue;

						switch (option) {
						case 1: {
							ui_sort_asc_by_category(repo);
							break;
						}
						case 2: {
							ui_sort_desc_by_category(repo);
							break;
						}
						default:
							printf("Optiune invalida!\n");
						}
						break;
					}
					break;
				default:
					printf("Optiune invalida!\n");
			}
			break;
		//Exit
		case 8: {
			destroy_repo(repo);
			return;
		}
		default:
			printf("Optiune invalida!\n");
			break;
		}
		}
	}
}