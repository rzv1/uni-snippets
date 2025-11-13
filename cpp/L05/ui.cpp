#include "ui.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>

using std::string;
using std::getline;
using std::cin;
using std::stringstream;

void UI::print_menu() {
	printf("\nMeniu carti\n");
	printf("-------------------\n");
	printf("1. Adauga\n");
	printf("2. Sterge\n");
	printf("3. Actualizeaza\n");
	printf("4. Filtreaza\n");
	printf("5. Sorteaza\n");
	printf("6. Afiseaza\n");
	printf("7. Exit\n");
}

void UI::print_menu_filter_option() {
	printf("\n");
	printf("1. Titlu\n");
	printf("2. Anul aparitiei\n");
}

void UI::print_menu_sort_option() {
	printf("\n");
	printf("1. Titlu\n");
	printf("2. Autor\n");
	printf("3. An + gen\n");
}

void UI::print_menu_update_option() {
	printf("\n");
	printf("1. Titlu\n");
	printf("2. Autor\n");
	printf("3. Gen\n");
	printf("4. An\n");
}

bool UI::print_all(const vector<Carte>& carti) {
	if (carti.empty()) {
		printf("Nu exista carti in lista!\n");
		return false;
	}
	for (const auto& carte : carti)
		printf("%s\n", carte.to_string().c_str());
	return true;
}

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

void UI::add() {
	string title = read_string("Titlu: ");
	string author = read_string("Autor: ");
	string genre = read_string("Gen (drama, comedie, istorie, fictiune): ");
	int year = read_int("An: ");
	service.add(title, author, genre, year);
}

void UI::remove() {
	bool exista = print_all(service.get_all());
	if (!exista)
		return;
	int id = read_int("Id: ");
	service.remove(id);
	printf("Cartea cu id-ul %d a fost stearsa!\n", id);
}

void UI::update_title() {
	bool exista = print_all(service.get_all());
	if (!exista)
		return;
	int id = read_int("ID: ");
	string title = read_string("Titlu nou: ");
	service.update_title(id, title);
	printf("Cartea cu id-ul %d a fost actualizata!\n", id);
}

void UI::update_author() {
	bool exista = print_all(service.get_all());
	if (!exista)
		return;
	int id = read_int("ID: ");
	string author = read_string("Autor nou: ");
	service.update_author(id, author);
	printf("Cartea cu id-ul %d a fost actualizata!\n", id);
}

void UI::update_genre() {
	bool exista = print_all(service.get_all());
	if (!exista)
		return;
	int id = read_int("ID: ");
	string genre = read_string("Gen nou (drama, comedie, istorie, fictiune): ");
	service.update_genre(id, genre);
	printf("Cartea cu id-ul %d a fost actualizata!\n", id);
}

void UI::update_year() {
	bool exista = print_all(service.get_all());
	if (!exista)
		return;
	int id = read_int("ID: ");
	int year = read_int("An nou: ");
	service.update_year(id, year);
	printf("Cartea cu id-ul %d a fost actualizata!\n", id);
}

void UI::filter_title() {
	string title = read_string("Titlu: ");
	print_all(service.filter_title(title));
}

void UI::filter_year() {
	int year = read_int("An: ");
	print_all(service.filter_year(year));
}

void UI::sort_title() {
	print_all(service.sort_title());
}

void UI::sort_author() {
	print_all(service.sort_author());
}

void UI::sort_year_and_genre() {
	print_all(service.sort_year_and_genre());
}

void UI::invalid() {
	printf("Optiune invalida!");
}

void UI::improved_visuals() {
	printf("\n");
}

void UI::run() {
	while (true) {
		try {
			print_menu();
			int opt, opt_update, opt_filter, opt_sort;
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
			case 6: (void)print_all(service.get_all()); break;
			case 7: return;
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