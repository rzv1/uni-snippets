#include "ui.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>

using std::string;
using std::vector;
using std::getline;
using std::cin;
using std::stringstream;

/*
Functia printeaza meniul principal
*/
void UI::print_menu() {
	printf("\nMeniu carti\n");
	printf("-------------------\n");
	printf("1. Adauga\n");
	printf("2. Sterge\n");
	printf("3. Actualizeaza\n");
	printf("4. Filtreaza\n");
	printf("5. Sorteaza\n");
	printf("6. Cos\n");
	printf("7. Raport\n");
	printf("8. Afiseaza\n");
	printf("9. Undo\n");
	printf("10. Exit\n");
}

/*
Functia printeaza meniul optiunii de filtrare
*/
void UI::print_menu_filter_option() {
	printf("\n");
	printf("1. Titlu\n");
	printf("2. Anul aparitiei\n");
}

/*
Functia printeaza meniul optiunii de sortare
*/
void UI::print_menu_sort_option() {
	printf("\n");
	printf("1. Titlu\n");
	printf("2. Autor\n");
	printf("3. An + gen\n");
}

/*
Functia printeaza meniul optiunii de update
*/
void UI::print_menu_update_option() {
	printf("\n");
	printf("1. Titlu\n");
	printf("2. Autor\n");
	printf("3. Gen\n");
	printf("4. An\n");
}

/*
Functia printeaza meniul pentru cos
*/
void UI::print_menu_rental_cart() {
	printf("\n");
	printf("1. Goleste cos\n");
	printf("2. Adauga in cos\n");
	printf("3. Genereaza cos\n");
	printf("4. Export\n");
	printf("5. Afisaza\n");
}

/*
Functia printeaza toate cartile
*/
bool UI::print_all(const vector<Carte>& carti) {
	if (carti.size() == 0) {
		printf("Nu exista carti in lista!\n");
		return false;
	}
	for (const auto& carte : carti)
		printf("%s\n", carte.to_string().c_str());
	return true;
}

void UI::print_report() {
	service.clear_map();
	service.add_to_map();
	map<string, DTO> raport = service.get_map();
	for (const auto& element : raport) {
		printf("%s => %d\n", element.first.c_str(), element.second.get_freq());
	}
}

/*
Functie utilitara care citeste un sir de caractere
*/
string UI::read_string(const string& prompt) {
	string read;
	do {
		printf("%s", prompt.c_str());
		getline(cin, read);
		if (read.empty())
			printf("Inputul nu poate fi gol!");
	} while (read.empty());
	return read;
}

/*
Functie utilitara care citeste un intreg
*/
int UI::read_int(const string& prompt) {
	string read;
	int value;
	while (true) {
		printf("%s", prompt.c_str());
		getline(cin, read);

		stringstream ss(read);
		if (ss >> value && ss.eof())
			return value;
		else
			printf("Optiune/Valoare Invalida!\n");
	}
}

/*
Functia de ui pentru adaugare
*/
void UI::add() {
	string title = read_string("Titlu: ");
	string author = read_string("Autor: ");
	string genre = read_string("Gen (drama, comedie, istorie, fictiune): ");
	int year = read_int("An: ");
	service.add(title, author, genre, year);
}

/*
Functia de ui pentru stergere
*/
void UI::remove() {
	bool exista = print_all(service.get_all());
	if (!exista)
		return;
	int id = read_int("Id: ");
	service.remove(id);
	printf("Cartea cu id-ul %d a fost stearsa!\n", id);
}

/*
Functia de ui pentru actualizare
*/
void UI::update_title() {
	bool exista = print_all(service.get_all());
	if (!exista)
		return;
	int id = read_int("ID: ");
	string title = read_string("Titlu nou: ");
	service.update_title(id, title);
	printf("Cartea cu id-ul %d a fost actualizata!\n", id);
}

/*
Functia de ui pentru actualizare
*/
void UI::update_author() {
	bool exista = print_all(service.get_all());
	if (!exista)
		return;
	int id = read_int("ID: ");
	string author = read_string("Autor nou: ");
	service.update_author(id, author);
	printf("Cartea cu id-ul %d a fost actualizata!\n", id);
}

/*
Functia de ui pentru actualizare
*/
void UI::update_genre() {
	bool exista = print_all(service.get_all());
	if (!exista)
		return;
	int id = read_int("ID: ");
	string genre = read_string("Gen nou (drama, comedie, istorie, fictiune): ");
	service.update_genre(id, genre);
	printf("Cartea cu id-ul %d a fost actualizata!\n", id);
}

/*
Functia de ui pentru actualizare
*/
void UI::update_year() {
	bool exista = print_all(service.get_all());
	if (!exista)
		return;
	int id = read_int("ID: ");
	int year = read_int("An nou: ");
	service.update_year(id, year);
	printf("Cartea cu id-ul %d a fost actualizata!\n", id);
}

/*
Functia de ui pentru filtrare dupa titlu
*/
void UI::filter_title() {
	string title = read_string("Titlu: ");
	print_all(service.filter_title(title));
}

/*
Functia de ui pentru filtrare dupa an
*/
void UI::filter_year() {
	int year = read_int("An: ");
	print_all(service.filter_year(year));
}

/*
Functia de ui pentru sortare dupa titlu
*/
void UI::sort_title() {
	print_all(service.sort_title());
}

/*
Functia de ui pentru sortare dupa autor
*/
void UI::sort_author() {
	print_all(service.sort_author());
}

/*
Functia de ui pentru sortare dupa an si gen
*/
void UI::sort_year_and_genre() {
	print_all(service.sort_year_and_genre());
}

/*
Functie de ui pentru golire cos
*/
void UI::clear_cart() {
	bool ret = service.clear_cart();
	if(ret)
	printf("Cos golit cu succes!");
}

/*
Functie de ui pentru adaugare in cos
*/
void UI::add_cart() {
	string title = read_string("Titlu: ");
	bool ret = service.add_cart(title);
	if(ret)
	printf("Carte adaugata cu succes!\n");
}

/*
Functie de ui pentru generare cos random
*/
void UI::generate_cart() {
	int n = read_int("Numar de generari: ");
	bool ret = service.generate_cart(n);
	if(ret)
	printf("Carte generata cu succes!");
}

/*
Functie de ui care face export la cos
*/
void UI::export_cart() {
	string filename = read_string("Nume fisier: ");
	bool ret = service.export_cart(filename);
	if(ret)
	printf("Cos exportat cu succes!");
}

/*
Functie de ui
*/
void UI::invalid() {
	printf("Optiune invalida!");
}

/*
Functie de ui
*/
void UI::improved_visuals() {
	printf("\n");
}

/*
Functie care porneste interfata
*/
void UI::run() {
	while (true) {
		try {
			print_menu();
			int opt, opt_update, opt_filter, opt_sort, opt_cart;
			opt = read_int("Optiune: ");

			switch (opt) {
			case 1: add(); break;
			case 2: remove(); break;
			case 3:
				print_menu_update_option();
				opt_update = read_int("Optiune: ");
				improved_visuals();
				switch (opt_update) {
				case 1: update_title(); break;
				case 2: update_author(); break;
				case 3: update_genre(); break;
				case 4: update_year(); break;
				default: invalid(); break;
				} break;
			case 4:
				print_menu_filter_option();
				opt_filter = read_int("Optiune: ");
				improved_visuals();
				switch (opt_filter) {
				case 1: filter_title(); break;
				case 2: filter_year(); break;
				default: invalid(); break;
				} break;
			case 5:
				print_menu_sort_option();
				opt_sort = read_int("Optiune: ");
				improved_visuals();
				switch (opt_sort) {
				case 1: sort_title(); break;
				case 2: sort_author(); break;
				case 3: sort_year_and_genre(); break;
				default: invalid(); break;
				} break;
			case 6:
				print_menu_rental_cart();
				opt_cart = read_int("Optiune: ");
				switch (opt_cart) {
				case 1: clear_cart(); break;
				case 2: add_cart(); break;
				case 3: generate_cart(); break;
				case 4: export_cart(); break;
				case 5: (void)print_all(service.cart_get_all()); break;
				} break;
			case 7: print_report(); break;
			case 8: (void)print_all(service.get_all()); break;
			case 9: undo(); break;
			case 10: return;
			}
		}
		catch (RepoException& e) {
			printf("%s\n\n", e.get_message().c_str());
		}
		catch (ValidationException& e) {
			printf("%s\n\n", e.get_message().c_str());
		}
	}
}

void UI::undo() {
	try {
		service.undo();
		printf("Ultima actiune a fost anulata!\n");
	}
	catch (const std::runtime_error& e) {
		printf("%s\n\n", e.what());
	}
}