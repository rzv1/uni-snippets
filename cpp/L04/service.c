#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "service.h"
#include "domain.h"
#include "repo.h"
#include "ui.h"

#define UNDO_MAX 100
static Lista* undoStack[UNDO_MAX];
static int undoTop = -1;

static void push_undo(Lista* lista) {
	undoStack[++undoTop] = copiaza_lista(lista, copiaza_participant);
}

Lista* pop_undo() {
	if (undoTop < 0) {
		return NULL;
	}
	Lista* lista = undoStack[undoTop];
	undoTop--;
	return lista;
}

void free_undo_stack() {
	while (undoTop >= 0) {
		Lista* lista = undoStack[undoTop];
		undoTop--;
		distruge_lista(lista, distruge_elem_participant);
	}
}

bool undo_service(Lista* lista) {
	Lista* ultima_lista = pop_undo();
	if (ultima_lista == NULL) {
		return false;
	}
	goleste_lista(lista, distruge_elem_participant);
	for (int i = 0; i < get_lungime(ultima_lista); i++) {
		Participant* participant = (Participant*)get_element_by_index(ultima_lista, i);
		Participant* copie = copiaza_participant(participant);
		adauga_element(lista, copie);
	}
	set_lungime(lista, get_lungime(ultima_lista));

	distruge_lista(ultima_lista, distruge_elem_participant);
	return true;
}

bool adauga(Lista* lista, int* user_id, char* nume, char* prenume, int scor) {
	/*
	functie care se ocupa cu trimiterea unui participant spre adaugare (daca este valid)

	lista: structura care se ocupa cu stocarea participantilor
	user_id: identificatorul userului care urmeaza sa fie introdus
	nume: numele participantului
	prenume: prenumele participantului
	scor: scorul participantului

	preconditii: lista - sa existe
	postconditii: lista' = lista + noul participant (daca datele sale sunt valide)
				  user_id' = user_id + 1 (daca participantul a fost adaugat)

	return: true daca datele userului sunt valide si s-a putut crea si trimite participantul spre adaugare
			false in caz contrar
	*/
	if (!valideaza_participant(nume, prenume, scor))
		return false;

	push_undo(lista);
	Participant* participant = creeaza_participant(*user_id, nume, prenume, scor);
	adauga_participant(lista, user_id, participant);

	return true;
}

Participant* cauta_participant_dupa_id(Lista* lista, int id) {
	/*
	functie care catua un participant in storage dupa id

	lista: lista in care se cauta participantul cu id ul data
	id: identificatorul unic dupa care se cauta participantul

	preconditii: lista - sa existe
				 id >= 0

	return: participantul cu id dat, daca exista
			un participat cu campuri nule / default, in caz contrar
	*/

	Participant* participant_cautat = get_participant(lista, id);
	return participant_cautat;
}

void actualizeaza_nume(Lista* lista, int id, char* nume) {
	/*
	functie care apeleaza actualizarea directa a numelui unui participant

	lista: structura de stocare in care se afla participantul pentru care se actualizeaza numele
	id: identificatorul unic al participantului pentru care se actualizeaza numele
	nume: noul nume al participantului

	preconditii: lista - sa existe
				 id >= 1, id valid
				 0 < strlen(nume) <= 64
	*/
	push_undo(lista);
	actualizeaza_nume_participant(lista, id, nume);
}

void actualizeaza_prenume(Lista* lista, int id, char* prenume) {
	/*
	functie care apeleaza actualizarea directa a prenumelui unui participant

	lista: structura de stocare in care se afla participantul pentru care se actualizeaza prenumele
	id: identificatorul unic al participantului pentru care se actualizeaza numele
	prenume: noul prenume al participantului

	preconditii: lista - sa existe
				 id >= 1, id valid
				 0 < strlen(prenume) <= 64
	*/
	push_undo(lista);
	actualizeaza_prenume_participant(lista, id, prenume);
}

void actualizeaza_scor(Lista* lista, int id, int scor) {
	/*
	functie care apeleaza actualizarea directa a scorului unui participant

	lista: structura de stocare in care se afla participantul pentru care se actualizeaza scorul
	id: identificatorul unic al participantului pentru care se actualizeaza scorul
	scor: noul scor al participantului

	preconditii: lista - sa existe
				 id >= 1, id valid
				 0 <= scor <= 100;
	*/
	push_undo(lista);
	actualizeaza_scor_participant(lista, id, scor);
}

void sterge(Lista* lista, int id) {
	/*
	functie care apeleaza stergerea directa a unui participant cu un id dat

	lista: structura de stocare in care se afla participantul care trebuie sters
	id: identificatorul unic al participantului care trebuie sters

	preconditii: lista - sa existe
				 id >= 1, id valid
	postconditii: lista' = lista - participant
	*/  
	push_undo(lista);
	sterge_participant(lista, id);
}

Lista* filtrare_participanti_dupa_scor(Lista* lista, int scor) {
	/*
	functie care filtreaza partcipantii dupa un scor dat, returnandu-i doar pe cei care au scorul mai mic decat cel dat

	lista: structura de stocare in care se afla participantii
	scor: pragul de filtrare al participantilor

	preconditii: lista - sa existe

	return: o lista cu toti participantii care indeplinesc filtrul aplicat
	*/

	Lista* lista_participanti_filtrati = creeaza_lista();
	int user_id_filtrat = 1;

	for (int i = 0; i < get_lungime(lista); i++) {
		Participant* participant = get_element_by_index(lista, i);
		if (get_scor(participant) < scor)
			adauga_participant(lista_participanti_filtrati, &user_id_filtrat, participant);
	}

	return lista_participanti_filtrati;
}

Lista* filtrare_participanti_dupa_litera(Lista* lista, char litera) {
	/*
	functie care filtreaza participantii dupa prima litera a numelui, returnandu-i doar pe cei al caror nume incepe cu litera data

	lista: structura de stocare in care se afla participantii
	litera: un caractere reprezentand criteriul filtrului

	preconditii: lista - sa existe
				 litera -  un caracter reprezentand o litera a alfabetului englez

	return: o lista cu toti participantii care indeplinesc filtrul aplicat
	*/

	Lista* lista_participanti_filtrati = creeaza_lista();
	int user_id_filtrat = 1;

	for (int i = 0; i < get_lungime(lista); i++) {
		char* nume = (char*)malloc(64 * sizeof(char));
		Participant* participant = get_element_by_index(lista, i);
		if (nume) {
			memset(nume, 0, 64 * sizeof(char));
			strcpy(nume, get_nume(participant));
		}

		if (nume != NULL && nume[0] == litera)
			adauga_participant(lista_participanti_filtrati, &user_id_filtrat, participant);

		free(nume);
	}

	return lista_participanti_filtrati;
}

int cmp_func_nume_crescator(Participant* a, Participant* b) {
	/*
	functie de comparare a doi participanti dupa nume si la nume egale, dupa prenume

	a: primul participant de comparat
	b: al doilea participant de comparat

	return: 1, daca cei doi participanti sunt in ordine crescatorare conform criteriilor
			0, in caz contrar
	*/

	return (strcmp(get_nume(a), get_nume(b)) < 0) || (strcmp(get_nume(a), get_nume(b)) == 0 && strcmp(get_prenume(a), get_prenume(b)) < 0);
}

int cmp_func_nume_descrescator(Participant* a, Participant* b) {
	/*
	functie de comparare a doi participanti dupa nume si la nume egale, dupa prenume

	a: primul participant de comparat
	b: al doilea participant de comparat

	return: 1, daca cei doi participanti sunt in ordine descrescatoare conform criteriilor
			0, in caz contrar
	*/

	return (strcmp(get_nume(a), get_nume(b)) > 0) || (strcmp(get_nume(a), get_nume(b)) == 0 && strcmp(get_prenume(a), get_prenume(b)) > 0);
}

int cmp_func_scor_crescator(Participant* a, Participant* b) {
	/*
	functie de comparare a doi participanti dupa scor

	a: primul participant de comparat
	b: al doilea participant de comparat

	return: 1, daca cei doi participanti sunt in ordine crescatoare conform criteriului
			0, in caz contrar
	*/

	return get_scor(a) < get_scor(b);
}

int cmp_func_scor_descrescator(Participant* a, Participant* b) {
	/*
	functie de comparare a doi participanti dupa scor

	a: primul participant de comparat
	b: al doilea participant de comparat

	return: 1, daca cei doi participanti sunt in ordine descrescatoare conform criteriului
			0, in caz contrar
	*/

	return get_scor(a) > get_scor(b);
}

Lista* sortare_participanti(Lista* lista, int(*cmp_func)(Participant* a, Participant* b)) {
	/*
	functie care sorteaza participantii dupa un criteriu dat

	lista: structura de stocare in care se afla participantii
	cmp_func: functie de comparare care reprezinta criteriul sortarii

	preconditii: lista - sa existe

	return: o lista cu toti participantii sortati dupa criteriul dat
	*/
	Lista* participanti_sortati = creeaza_lista();
	int user_id = 1;
	for (int i = 0; i < get_lungime(lista); i++)
		adauga_participant(participanti_sortati, &user_id, get_element_by_index(lista, i));
	//print_all_participants(participanti_sortati);

	for (int i = 0; i < get_lungime(participanti_sortati) - 1; i++)
		for (int j = i + 1; j < get_lungime(participanti_sortati); j++) {
			Participant* participant_i = get_element_by_index(participanti_sortati, i);
			Participant* participant_j = get_element_by_index(participanti_sortati, j);
			if (!cmp_func(participant_i, participant_j)) {
				Participant* temp = copiaza_participant(participant_i);
				set_element_on_index(participanti_sortati, participant_j, i);
				set_element_on_index(participanti_sortati, temp, j);
				distruge_participant(temp);
			}
			//distruge_participant(participant_i);
			//distruge_participant(participant_j);
		}
	return participanti_sortati;
}