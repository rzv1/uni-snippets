#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "ui.h"
#include "domain.h"
#include "repo.h"
#include "service.h"

void clear_input_buffer(int* extra_chars) {
	/*
	functie care curata bufferul create dupa citire si actualizeaza numarul de caractere citite in plus fata de citirea asteptata

	extra_chars: numarul de caractere din buffer care au fost citite in plus fata de cate se asteptau sa fie citite

	preconditii: extra_chars = 0
	postconditii: extra_chars >= 0
	*/

	int left_char = 0;
	while ((left_char = getchar()) && ((char)left_char != '\n') && (left_char != EOF))
		(*extra_chars)++;
}

void meniu() {
	/*
	functie care afiseaza meniul aplicatiei
	*/
	printf("\nMeniu\n");
	printf("1. Adauga participant\n");
	printf("2. Actualizeaza participant\n");
	printf("3. Sterge participant\n");
	printf("4. Filtrare participanti\n");
	printf("5. Sortare participanti\n");
	printf("6. Afiseaza toti participantii\n");
	printf("7. Undo\n");
	printf("8. Afisare stersi\n");
	printf("9. Inchidere aplicatie\n");
}

void meniu_filtrare() {
	/*
	functie care afiseaza sub meniul optiunii de filtrare
	*/
	printf("\n1. Afisarea participantilor cu un scor mai mic decat o anumita valoare\n");
	printf("2. Afisarea participantilor al caror nume incepe cu o anumita litera\n");
}

void meniu_sortare() {
	/*
	functie care afiseaza sub meniul optiunii de sortare
	*/
	printf("\n1. Sortare dupa nume\n");
	printf("2. Sortare dupa scor\n");
}

void meniu_actualizare() {
	/*
	functie care afiseaza sub meniul optiunii de actualizare
	*/
	printf("\n1. Nume\n");
	printf("2. Prenume\n");
	printf("3. Scor\n");
}

void print_all_participants(Lista* lista) {
	/*
	functie care afiseaza toti participantii stocati

	preconditii: lista - sa existe
	*/
	printf("%d\n", get_lungime(lista));
	if (get_lungime(lista) == 0) {
		printf("Nu exista participanti!\n");
		return;
	}

	for (int i = 0; i < get_lungime(lista); i++) {
		Participant* participant = get_element_by_index(lista, i);
		printf("ID: %d, Nume: %s, Prenume: %s, Scor: %d\n", get_id(participant), get_nume(participant), get_prenume(participant), get_scor(participant));
	}
}

void user_interface_adaugare_participant(Lista* lista, int* user_id) {
	/*
	functie care controleaza interactiunea cu utilizatorul pentru functionalitatea de adaugare a unui participant in aplicatie

	lista: structura care se ocupa cu stocarea participantilor
	user_id: id-ul pentru userul care urmeaza sa fie adaugat

	preconditii: lista - sa existe (sa fie creata)
				 user_id >= 1

	postconditii: lista' = lista + noul participant (daca este valid si exista spatiu in lista)
				  user_id' = user_id + 1 (daca a fost adaugat cu succes participantul)
	*/

	//char nume[64] = "", prenume[64] = "";
	char* nume = (char*)malloc(64 * sizeof(char));
	memset(nume, 0, 64 * sizeof(char));

	char* prenume = (char*)malloc(64 * sizeof(char));
	memset(prenume, 0, 64 * sizeof(char));

	// citirea stringurilor o realizez cu fgets pentru memory safety (evitarea introducerii unui string mai mare decat dimensiunea alocata)

	printf("Nume: ");
	if (fgets(nume, 64, stdin) == NULL) {
		printf("Numele este prea lung!\n");
		return;
	}

	printf("Prenume: ");
	if (fgets(prenume, 64, stdin) == NULL) {
		printf("Prenumele este prea lung!\n");
		return;
	}

	int extra_chars = 0, puncte = 0, scor = 0;
	printf("Introdu numarul de puncte pentru fiecare problema. (max 10 pct per problema)\n");
	for (int i = 1; i <= 10; i++) {
		printf("Problema %d : ", i);

		(void)scanf("%d", &puncte);

		extra_chars = 0;
		clear_input_buffer(&extra_chars);

		if (extra_chars > 0 || puncte < 0 || puncte > 10) {
			printf("Numar de puncte invalid!\n");
			return;
		}

		scor += puncte;
	}

	// fgets citeste si '\n' (sarituta la linie noua)
	// inlocuiesc '\n' cu '\0' (sfarsitul de sir)
	nume[strlen(nume) - 1] = '\0';
	prenume[strlen(prenume) - 1] = '\0';
	bool added = adauga(lista, user_id, nume, prenume, scor);

	if (!added) {
		printf("Date invalide!\n");
	}
	else {
		printf("Participantul a fost adaugat cu succes!\n");
	}
	free(nume);
	free(prenume);
}

void user_interface_actualizare_participant(Lista* lista) {
	/*
	functie care controleaza interactiunea cu utilizatorul pentru functionalitatea de actualizare a datelor despre un participant
	*/
	printf("\nParticipanti\n");
	print_all_participants(lista);

	int id = 0;
	printf("\nIntrodu id-ul participantului: ");
	(void)scanf("%d", &id);

	int extra_chars = 0;
	clear_input_buffer(&extra_chars);

	if (extra_chars > 0 || id <= 0) {
		printf("Id invalid!\n");
		return;
	}

	Participant* participant = cauta_participant_dupa_id(lista, id);

	if (participant == NULL) {
		printf("Nu este inregistrat niciun participant cu id %d!\n", id);
		return;
	}
	meniu_actualizare();
	printf("\nIntrodu campul pe care vrei sa il actualizezi: ");

	char option = '0';
	(void)scanf(" %c", &option);

	extra_chars = 0;
	clear_input_buffer(&extra_chars);

	if (extra_chars > 0 || option < '1' || option > '3') {
		printf("Optiunea introdusa este invalida!\n");
		return;
	}

	switch (option) {

	case '1': {
		char* nume = (char*)malloc(64 * sizeof(char));
		memset(nume, 0, 64 * sizeof(char));

		printf("Introdu noul nume: ");
		if (fgets(nume, 64, stdin) == NULL) {
			printf("Numele este prea lung!\n");
			return;
		}
		else if (nume[0] == '\n') {
			printf("Numele este invalid!\n");
			return;
		}

		nume[strlen(nume) - 1] = '\0';
		actualizeaza_nume(lista, id, nume);
		free(nume);
		break;
	}

	case '2': {
		char* prenume = (char*)malloc(64 * sizeof(char));
		memset(prenume, 0, 64 * sizeof(char));

		printf("Introdu noul prenume: ");
		if (fgets(prenume, 64, stdin) == NULL) {
			printf("Prenumele este prea lung!\n");
			return;
		}
		else if (prenume[0] == '\n') {
			printf("Numele este invalid!\n");
			return;
		}

		prenume[strlen(prenume) - 1] = '\0';

		actualizeaza_prenume(lista, id, prenume);
		free(prenume);

		break;
	}

	case '3': {
		int scor = 0;

		printf("Introdu noul scor: ");
		(void)scanf("%d", &scor);

		extra_chars = 0;
		clear_input_buffer(&extra_chars);

		if (extra_chars > 0 || scor < 0 || scor > 100) {
			printf("Scorul este invalid!\n");
			return;
		}
		actualizeaza_scor(lista, id, scor);
		
		break;
	}

	default: {
		printf("Optiunea introdusa este invalida!\n");
		break;
	}

	}

}

void user_interface_stergere_participant(Lista* lista, Lista* stersi) {
	/*
	functie care controleaza interactiunea cu utilizatorul pentru functionalitatea de stergere a unui participant

	lista: structura care se ocupa cu stocarea participantilor

	preconditii: lista - sa existe (sa fie creata)
	postconditii: lista' = lista - participant (participantul care urmeaza sa fie sters)
	*/
	printf("\nParticipanti\n");
	print_all_participants(lista);

	int id = 0;
	printf("\nIntrodu id-ul participantului: ");
	(void)scanf("%d", &id);

	int extra_chars = 0;
	clear_input_buffer(&extra_chars);

	if (extra_chars > 0 || id <= 0) {
		printf("Id invalid!\n");
		return;
	}

	Participant* participant = cauta_participant_dupa_id(lista, id);

	if (participant == NULL) {
		printf("Nu este inregistrat niciun participant cu id %d!\n", id);
		return;
	}
	Participant* copie_participant = copiaza_participant(participant);
	adauga_element(stersi, copie_participant);
	sterge(lista, id);
	printf("Participantul cu id %d a fost sters cu succes!\n", id);
}

void user_interface_filtrare_participanti(Lista* lista) {
	/*
	functie care controleaza interactiunea cu utilizatorul pentru functionalitatea de filtrare a participantilor

	lista: structura de stocare in care se afla participantii

	preconditii: lista - sa existe
	*/

	meniu_filtrare();
	printf("Introdu optiunea de filtrare: ");

	char option;
	(void)scanf(" %c", &option);

	int extra_chars = 0;
	clear_input_buffer(&extra_chars);

	if (extra_chars > 0) {
		printf("Optiunea introdusa este invalida!\n");
		return;
	}

	switch (option) {

	case '1': {
		int scor = 0;
		printf("Introdu scorul: ");
		(void)scanf("%d", &scor);

		extra_chars = 0;
		clear_input_buffer(&extra_chars);

		if (extra_chars > 0) {
			printf("Scorul introdus este invalid!\n");
			return;
		}

		Lista* lista_filtrata = filtrare_participanti_dupa_scor(lista, scor);
		print_all_participants(lista_filtrata);
		free(lista_filtrata->elements);
		free(lista_filtrata);

		break;
	}

	case '2': {
		char litera = 0;
		printf("Introdu litera: ");
		(void)scanf(" %c", &litera);

		extra_chars = 0;
		clear_input_buffer(&extra_chars);

		if (extra_chars > 0) {
			printf("Litera introdusa este invalida!\n");
			return;
		}

		if (litera >= 'a' && litera <= 'z')
			litera -= (int)('a' - 'A');
		else if (litera < 'A' || litera > 'Z') {
			printf("Caracterul introdus este o litera invalida!\n");
			return;
		}
		Lista* lista_filtrata = filtrare_participanti_dupa_litera(lista, litera);
		print_all_participants(lista_filtrata);
		free(lista_filtrata->elements);
		free(lista_filtrata);

		break;
	}

	default: {
		printf("Optiunea introdusa este invalida!\n");
		break;
	}

	}
}

void user_interface_sortare_participanti(Lista* lista) {
	/*
	functie care controleaza interactiunea cu utilizatorul pentru functionalitatea de sortare a participantilr dupa anumite criterii

	lista: structura de stocare in care se afla participantii

	preconditii: lista - sa existe
	*/

	meniu_sortare();
	printf("Introdu optiunea de sortare: ");

	char option;
	(void)scanf(" %c", &option);

	int extra_chars = 0;
	clear_input_buffer(&extra_chars);

	if (extra_chars > 0) {
		printf("Optiunea introdusa este invalida!\n");
		return;
	}

	switch (option) {

	case '1': {
		printf("\n1. Crescator\n");
		printf("2. Descrescator\n");

		printf("Introdu ordinea de sortare: ");

		option;
		(void)scanf(" %c", &option);

		extra_chars = 0;
		clear_input_buffer(&extra_chars);

		if (extra_chars > 0) {
			printf("Optiunea introdusa este invalida!\n");
			return;
		}

		if (option == '1') {
			Lista* participanti_sortati = sortare_participanti(lista, cmp_func_nume_crescator);
			print_all_participants(participanti_sortati);
			free(participanti_sortati->elements);
			free(participanti_sortati);
		}
		else if (option == '2') {
			Lista* participanti_sortati = sortare_participanti(lista, cmp_func_nume_descrescator);
			print_all_participants(participanti_sortati);
			free(participanti_sortati->elements);
			free(participanti_sortati);
		}
		else {
			printf("Optiunea introdusa este invalida!\n");
			return;
		}

		break;
	}

	case '2': {
		printf("\n1. Crescator\n");
		printf("2. Descrescator\n");

		printf("Introdu ordinea de sortare: ");

		option;
		(void)scanf(" %c", &option);

		extra_chars = 0;
		clear_input_buffer(&extra_chars);

		if (extra_chars > 0) {
			printf("Optiunea introdusa este invalida!\n");
			return;
		}

		if (option == '1') {
			Lista* participanti_sortati = sortare_participanti(lista, cmp_func_scor_crescator);
			print_all_participants(participanti_sortati);
			free(participanti_sortati->elements);
			free(participanti_sortati);
		}
		else if (option == '2') {
			Lista* participanti_sortati = sortare_participanti(lista, cmp_func_scor_descrescator);
			print_all_participants(participanti_sortati);
			free(participanti_sortati->elements);
			free(participanti_sortati);
		}
		else {
			printf("Optiunea introdusa este invalida!\n");
			return;
		}

		break;
	}

	default: {
		printf("Optiunea introdusa este invalida!\n");
		break;
	}

	}


}

void ui_undo(Lista* lista) {
	/*
	functie care revine la starea anterioara a listei de participanti
	*/
	bool gasit = undo_service(lista);
	if (gasit) {
		printf("Operatie de undo efectuata cu succes!\n");
	}
	else
		printf("Nu mai exista operatii de undo!\n");
}

void ui_show_deleted(Lista* stersi) {
	/*
	functie care afiseaza participantii stersi
	*/
	printf("\nParticipanti stersi:\n");
	print_all_participants(stersi);
}

void ruleaza() {
	/*
	functie care ruleaza intreaga aplicatie
	*/
	Lista* lista = creeaza_lista();
	Lista* stersi = creeaza_lista();
	int user_id = 1;

	while (true) {
		meniu();

		char option = 0;
		int extra_chars = 0;

		printf("Introdu o optiune: ");
		(void)scanf(" %c", &option);

		clear_input_buffer(&extra_chars);
		if (extra_chars > 0) {
			printf("Optiunea introdusa este invalida!\n");
			continue;
		}

		switch (option) {

		case '1': {
			user_interface_adaugare_participant(lista, &user_id);
			break;
		}

		case '2': {
			user_interface_actualizare_participant(lista);
			break;
		}

		case '3': {
			user_interface_stergere_participant(lista, stersi);
			break;
		}

		case '4': {
			user_interface_filtrare_participanti(lista);
			break;
		}

		case '5': {
			user_interface_sortare_participanti(lista);
			break;
		}

		case '6': {
			print_all_participants(lista);
			break;
		}

		case '7': {
			ui_undo(lista);
			break;
		}

		case '8': {
			ui_show_deleted(stersi);
			break;
		}

		case '9': {
			distruge_lista(lista, distruge_elem_participant);
			free_undo_stack();
			distruge_lista(stersi, distruge_elem_participant);
			return;
			break;
		}

		default: {
			printf("Optiunea introdusa este invalida!\n");
			break;
		}

		}

	}
}