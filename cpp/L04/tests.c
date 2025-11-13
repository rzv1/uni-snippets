#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h.>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tests.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "ui.h"

void test_get_id() {
	Participant* participant_1 = creeaza_participant(1, "Samoila", "Alexandru", 90);
	assert(get_id(participant_1) == 1);
	distruge_participant(participant_1);

	Participant* participant_2 = creeaza_participant(40, "Ionel", "John", 100);
	assert(get_id(participant_2) == 40);
	distruge_participant(participant_2);

	Participant* participant_3 = creeaza_participant(10, "Andreescu", "Andrei", 78);
	assert(get_id(participant_3) == 10);
	distruge_participant(participant_3);
}

void test_get_nume() {
	Participant* participant_1 = creeaza_participant(1, "Samoila", "Alexandru", 90);
	assert(strcmp(get_nume(participant_1), "Samoila") == 0);
	distruge_participant(participant_1);

	Participant* participant_2 = creeaza_participant(40, "Ionel", "John", 100);
	assert(strcmp(get_nume(participant_2), "Ionel") == 0);
	distruge_participant(participant_2);

	Participant* participant_3 = creeaza_participant(10, "Andreescu", "Andrei", 78);
	assert(strcmp(get_nume(participant_3), "Andreescu") == 0);
	distruge_participant(participant_3);
}

void test_get_prenume() {
	Participant* participant_1 = creeaza_participant(1, "Samoila", "Alexandru", 90);
	assert(strcmp(get_prenume(participant_1), "Alexandru") == 0);
	distruge_participant(participant_1);

	Participant* participant_2 = creeaza_participant(40, "Ionel", "John", 100);
	assert(strcmp(get_prenume(participant_2), "John") == 0);
	distruge_participant(participant_2);

	Participant* participant_3 = creeaza_participant(10, "Andreescu", "Andrei", 78);
	assert(strcmp(get_prenume(participant_3), "Andrei") == 0);
	distruge_participant(participant_3);

}

void test_get_scor() {
	Participant* participant_1 = creeaza_participant(1, "Samoila", "Alexandru", 90);
	assert(get_scor(participant_1) == 90);
	distruge_participant(participant_1);

	Participant* participant_2 = creeaza_participant(40, "Ionel", "John", 100);
	assert(get_scor(participant_2) == 100);
	distruge_participant(participant_2);

	Participant* participant_3 = creeaza_participant(10, "Andreescu", "Andrei", 78);
	assert(get_scor(participant_3) == 78);
	distruge_participant(participant_3);
}

void test_set_id() {
	Participant* participant = creeaza_participant(0, "Samoila", "Alexandru", 10);

	assert(get_id(participant) == 0);

	set_id(participant, 1);
	assert(get_id(participant) == 1);

	set_id(participant, 35);
	assert(get_id(participant) == 35);

	set_id(participant, 20);
	assert(get_id(participant) == 20);

	distruge_participant(participant);
}

void test_set_nume() {
	Participant* participant = creeaza_participant(0, "Alexandrescu", "Alexandru", 10);

	assert(strcmp(get_nume(participant), "Alexandrescu") == 0);

	set_nume(participant, "Stefan");
	assert(strcmp(get_nume(participant), "Stefan") == 0);

	set_nume(participant, "Leoneanu");
	assert(strcmp(get_nume(participant), "Leoneanu") == 0);

	set_nume(participant, "Mihai");
	assert(strcmp(get_nume(participant), "Mihai") == 0);

	distruge_participant(participant);
}

void test_set_prenume() {
	Participant* participant = creeaza_participant(0, "Alexandrescu", "Alexandru", 10);

	assert(strcmp(get_prenume(participant), "Alexandru") == 0);

	set_prenume(participant, "Ionel");
	assert(strcmp(get_prenume(participant), "Ionel") == 0);

	set_prenume(participant, "Andrei");
	assert(strcmp(get_prenume(participant), "Andrei") == 0);

	set_prenume(participant, "Stefan");
	assert(strcmp(get_prenume(participant), "Stefan") == 0);

	distruge_participant(participant);
}

void test_set_scor() {
	Participant* participant = creeaza_participant(0, "Alexandrescu", "Alexandru", 10);

	assert(get_scor(participant) == 10);

	set_scor(participant, 20);
	assert(get_scor(participant) == 20);

	set_scor(participant, 40);
	assert(get_scor(participant) == 40);

	set_scor(participant, 100);
	assert(get_scor(participant) == 100);

	distruge_participant(participant);
}

void test_creeaza_participant() {
	int user_id = 1;

	char* nume = (char*)malloc(64 * sizeof(char));
	if (nume)
		memset(nume, 0, 64 * sizeof(char));
	if (nume)
		strcpy(nume, "Samoila");

	char* prenume = (char*)malloc(64 * sizeof(char));
	if (prenume)
		memset(prenume, 0, 64 * sizeof(char));
	if (prenume)
		strcpy(prenume, "Alexandru");

	int scor = 67;

	Participant* participant = creeaza_participant(user_id, nume, prenume, scor);

	assert(get_id(participant) == 1);
	if (nume)
		assert(strcmp(get_nume(participant), nume) == 0);
	if (prenume)
		assert(strcmp(get_prenume(participant), prenume) == 0);
	assert(get_scor(participant) == 67);

	user_id = 2;
	if (nume)
		strcpy(nume, "New");
	if (prenume)
		strcpy(prenume, "User");
	scor = 90;

	distruge_participant(participant);

	participant = creeaza_participant(user_id, nume, prenume, scor);

	assert(get_id(participant) == 2);
	if (nume)
		assert(strcmp(get_nume(participant), nume) == 0);
	if (prenume)
		assert(strcmp(get_prenume(participant), prenume) == 0);
	assert(get_scor(participant) == 90);

	free(nume);
	free(prenume);
	distruge_participant(participant);
}

void test_valideaza_participant() {
	char* nume = (char*)malloc(64 * sizeof(char));
	if (nume)
		memset(nume, 0, 64 * sizeof(char));

	char* prenume = (char*)malloc(64 * sizeof(char));
	if (prenume)
		memset(prenume, 0, 64 * sizeof(char));

	int scor = -7;

	assert(valideaza_participant(nume, prenume, scor) == false);

	if (nume)
		strcpy(nume, "Ionel");

	assert(valideaza_participant(nume, prenume, scor) == false);

	if (prenume)
		strcpy(prenume, "Alex");

	assert(valideaza_participant(nume, prenume, scor) == false);

	scor = 10;

	assert(valideaza_participant(nume, prenume, scor) == true);

	free(nume);
	free(prenume);
}

void test_creeaza_lista() {
	Lista* lista = creeaza_lista();

	assert(lista->lungime == 0);
	assert(lista->max_lungime == 50);

	distruge_lista(lista, distruge_elem_participant);
}

void test_get_lungime() {
	Lista* lista = creeaza_lista();

	assert(get_lungime(lista) == 0);

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	assert(get_lungime(lista) == 1);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Alexandru", 90);
	adauga_participant(lista, &user_id, participant_1);

	assert(get_lungime(lista) == 2);

	distruge_lista(lista, distruge_elem_participant);
}

void test_get_max_lungime() {
	Lista* lista = creeaza_lista();

	assert(get_max_lungime(lista) == 50);

	distruge_lista(lista, distruge_elem_participant);
}

void test_set_lungime() {
	Lista* lista = creeaza_lista();

	assert(get_lungime(lista) == 0);

	set_lungime(lista, 1);
	assert(get_lungime(lista) == 1);

	set_lungime(lista, get_lungime(lista) + 1);
	assert(get_lungime(lista) == 2);

	set_lungime(lista, 45);
	assert(get_lungime(lista) == 45);

	set_lungime(lista, 0);
	assert(get_lungime(lista) == 0);

	distruge_lista(lista, distruge_elem_participant);

}

void test_get_participant() {
	Lista* lista = creeaza_lista();

	Participant* participant_gasit = get_participant(lista, 10);

	assert(participant_gasit == NULL);

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);


	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Alexandru", 90);
	adauga_participant(lista, &user_id, participant_1);

	participant_gasit = get_participant(lista, 2);

	assert(get_id(participant_gasit) == 2);
	assert(strcmp(get_nume(participant_gasit), "Alexandrescu") == 0);
	assert(strcmp(get_prenume(participant_gasit), "Alexandru") == 0);
	assert(get_scor(participant_gasit) == 90);

	distruge_lista(lista, distruge_elem_participant);
}

void test_adauga_participant() {
	Participant* participant = creeaza_participant(1, "Samoila", "Alexandru", 90);
	Lista* lista = creeaza_lista();

	int user_id = 1;
	adauga_participant(lista, &user_id, participant);

	assert(get_lungime(lista) == 1);
	assert(user_id == 2);
	assert(get_id(lista->elements[0]) == 1);
	assert(strcmp(get_nume(lista->elements[0]), "Samoila") == 0);
	assert(strcmp(get_prenume(lista->elements[0]), "Alexandru") == 0);
	assert(get_scor(lista->elements[0]) == 90);

	// presupun ca am adaugat 50 de elements (capacitate maxima initiala)
	lista->lungime = 50;
	user_id = 51;

	adauga_participant(lista, &user_id, participant);
	assert(get_lungime(lista) == 51);
	assert(get_max_lungime(lista) == 100);
	assert(user_id == 52);

	lista->lungime = 1;
	distruge_lista(lista, distruge_elem_participant);
}

void test_adauga() {
	Lista* lista = creeaza_lista();

	assert(lista->lungime == 0);

	int user_id = 1;
	char* nume = (char*)malloc(64 * sizeof(char));
	if (nume) {
		memset(nume, 0, 64 * sizeof(char));
		strcpy(nume, "Samoila");
	}

	char* prenume = (char*)malloc(64 * sizeof(char));
	if (prenume) {
		memset(prenume, 0, 64 * sizeof(char));
		strcpy(prenume, "Alexandru");
	}

	int scor = 67;

	adauga(lista, &user_id, nume, prenume, scor);

	assert(lista->lungime == 1);
	assert(get_id(lista->elements[0]) == 1);
	assert(strcmp(get_nume(lista->elements[0]), "Samoila") == 0);
	assert(strcmp(get_prenume(lista->elements[0]), "Alexandru") == 0);
	assert(get_scor(lista->elements[0]) == 67);

	strcpy(nume, "");

	bool added = adauga(lista, &user_id, nume, prenume, scor);

	assert(lista->lungime == 1);
	assert(added == false);

	free(nume);
	free(prenume);
	distruge_lista(lista, distruge_elem_participant);

}

void test_actualizeaza_nume() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Alexandru", 90);
	adauga_participant(lista, &user_id, participant_1);

	Participant* participant_cautat = get_participant(lista, 1);
	assert(strcmp(get_nume(participant_cautat), "Samoila") == 0);

	actualizeaza_nume(lista, 1, "Iulian");

	participant_cautat = get_participant(lista, 1);
	assert(strcmp(get_nume(participant_cautat), "Iulian") == 0);


	participant_cautat = get_participant(lista, 2);
	assert(strcmp(get_nume(participant_cautat), "Alexandrescu") == 0);

	actualizeaza_nume(lista, 2, "Stefan");

	participant_cautat = get_participant(lista, 2);
	assert(strcmp(get_nume(participant_cautat), "Stefan") == 0);

	distruge_lista(lista, distruge_elem_participant);

}

void test_actualizeaza_nume_participant() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Alexandru", 90);
	adauga_participant(lista, &user_id, participant_1);

	Participant* participant_cautat = get_participant(lista, 1);
	assert(strcmp(get_nume(participant_cautat), "Samoila") == 0);

	actualizeaza_nume_participant(lista, 1, "Iulian");

	participant_cautat = get_participant(lista, 1);
	assert(strcmp(get_nume(participant_cautat), "Iulian") == 0);


	participant_cautat = get_participant(lista, 2);
	assert(strcmp(get_nume(participant_cautat), "Alexandrescu") == 0);

	actualizeaza_nume_participant(lista, 2, "Stefan");

	participant_cautat = get_participant(lista, 2);
	assert(strcmp(get_nume(participant_cautat), "Stefan") == 0);

	distruge_lista(lista, distruge_elem_participant);
}

void test_actualizeaza_prenume() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);

	Participant* participant_cautat = get_participant(lista, 1);
	assert(strcmp(get_prenume(participant_cautat), "Alexandru") == 0);

	actualizeaza_prenume(lista, 1, "George");

	participant_cautat = get_participant(lista, 1);
	assert(strcmp(get_prenume(participant_cautat), "George") == 0);


	participant_cautat = get_participant(lista, 2);
	assert(strcmp(get_prenume(participant_cautat), "Mihai") == 0);

	actualizeaza_prenume(lista, 2, "John");

	participant_cautat = get_participant(lista, 2);
	assert(strcmp(get_prenume(participant_cautat), "John") == 0);

	distruge_lista(lista, distruge_elem_participant);
}

void test_actualizeaza_prenume_participant() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);

	Participant* participant_cautat = get_participant(lista, 1);
	assert(strcmp(get_prenume(participant_cautat), "Alexandru") == 0);

	actualizeaza_prenume_participant(lista, 1, "George");

	participant_cautat = get_participant(lista, 1);
	assert(strcmp(get_prenume(participant_cautat), "George") == 0);


	participant_cautat = get_participant(lista, 2);
	assert(strcmp(get_prenume(participant_cautat), "Mihai") == 0);

	actualizeaza_prenume_participant(lista, 2, "John");

	participant_cautat = get_participant(lista, 2);
	assert(strcmp(get_prenume(participant_cautat), "John") == 0);

	distruge_lista(lista, distruge_elem_participant);
}

void test_actualizeaza_scor() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);

	Participant* participant_cautat = get_participant(lista, 1);
	assert(get_scor(participant_cautat) == 80);

	actualizeaza_scor(lista, 1, 10);

	participant_cautat = get_participant(lista, 1);
	assert(get_scor(participant_cautat) == 10);


	participant_cautat = get_participant(lista, 2);
	assert(get_scor(participant_cautat) == 90);

	actualizeaza_scor(lista, 2, 100);

	participant_cautat = get_participant(lista, 2);
	assert(get_scor(participant_cautat) == 100);

	distruge_lista(lista, distruge_elem_participant);
}

void test_actualizeaza_scor_participant() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);

	Participant* participant_cautat = get_participant(lista, 1);
	assert(get_scor(participant_cautat) == 80);

	actualizeaza_scor_participant(lista, 1, 10);

	participant_cautat = get_participant(lista, 1);
	assert(get_scor(participant_cautat) == 10);


	participant_cautat = get_participant(lista, 2);
	assert(get_scor(participant_cautat) == 90);

	actualizeaza_scor_participant(lista, 2, 100);

	participant_cautat = get_participant(lista, 2);
	assert(get_scor(participant_cautat) == 100);

	distruge_lista(lista, distruge_elem_participant);
}

void test_get_participant_by_index() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);

	Participant* participant_cautat = get_element_by_index(lista, 0);

	assert(get_id(participant_cautat) == 1);
	assert(strcmp(get_nume(participant_cautat), "Samoila") == 0);
	assert(strcmp(get_prenume(participant_cautat), "Alexandru") == 0);
	assert(get_scor(participant_cautat) == 80);

	participant_cautat = get_element_by_index(lista, 1);

	assert(get_id(participant_cautat) == 2);
	assert(strcmp(get_nume(participant_cautat), "Alexandrescu") == 0);
	assert(strcmp(get_prenume(participant_cautat), "Mihai") == 0);
	assert(get_scor(participant_cautat) == 90);

	distruge_lista(lista, distruge_elem_participant);
}

void test_set_participant_on_index() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);
	
	//Se creeaza un nou participant pentru a nu avea pointeri comuni
	Participant* temp = creeaza_participant(
		get_id(get_element_by_index(lista, 0)),
		get_nume(get_element_by_index(lista, 0)),
		get_prenume(get_element_by_index(lista, 0)),
		get_scor(get_element_by_index(lista, 0))
	);

	set_element_on_index(lista, participant_1, 0);
	set_element_on_index(lista, temp, 1);

	assert(get_lungime(lista) == 2);

	participant = get_element_by_index(lista, 0);
	assert(get_id(participant) == 2);
	assert(strcmp(get_nume(participant), "Alexandrescu") == 0);
	assert(strcmp(get_prenume(participant), "Mihai") == 0);
	assert(get_scor(participant) == 90);


	participant = get_element_by_index(lista, 1);
	assert(get_id(participant) == 1);
	assert(strcmp(get_nume(participant), "Samoila") == 0);
	assert(strcmp(get_prenume(participant), "Alexandru") == 0);
	assert(get_scor(participant) == 80);


	distruge_participant(temp);
	distruge_lista(lista, distruge_elem_participant);

}

void test_sterge() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);

	sterge(lista, 1);

	participant = get_element_by_index(lista, 0);
	assert(get_lungime(lista) == 1);
	assert(get_id(participant) == 2);
	assert(strcmp(get_nume(participant), "Alexandrescu") == 0);
	assert(strcmp(get_prenume(participant), "Mihai") == 0);
	assert(get_scor(participant) == 90);

	sterge(lista, 2);

	assert(get_lungime(lista) == 0);


	distruge_lista(lista, distruge_elem_participant);
}

void test_sterge_participant() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);

	sterge_participant(lista, 1);

	participant = get_element_by_index(lista, 0);
	assert(get_lungime(lista) == 1);
	assert(get_id(participant) == 2);
	assert(strcmp(get_nume(participant), "Alexandrescu") == 0);
	assert(strcmp(get_prenume(participant), "Mihai") == 0);
	assert(get_scor(participant) == 90);

	sterge_participant(lista, 2);

	assert(get_lungime(lista) == 0);

	distruge_lista(lista, distruge_elem_participant);
}

void test_filtrare_participanti_dupa_scor() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);

	Participant* participant_2 = creeaza_participant(user_id, "Gheorghe", "Andrei", 50);
	adauga_participant(lista, &user_id, participant_2);

	Participant* participant_3 = creeaza_participant(user_id, "Ionescu", "George", 45);
	adauga_participant(lista, &user_id, participant_3);

	Lista* participanti_filtrati = filtrare_participanti_dupa_scor(lista, 70);

	distruge_lista(participanti_filtrati, NULL);
	distruge_lista(lista, distruge_elem_participant);
}

void test_filtrare_participanti_dupa_litera() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);

	Participant* participant_2 = creeaza_participant(user_id, "Gheorghe", "Andrei", 50);
	adauga_participant(lista, &user_id, participant_2);

	Participant* participant_3 = creeaza_participant(user_id, "Sibescu", "George", 45);
	adauga_participant(lista, &user_id, participant_3);

	Lista* participanti_filtrati = filtrare_participanti_dupa_litera(lista, 'S');

	assert(get_lungime(participanti_filtrati) == 2);

	distruge_lista(participanti_filtrati, NULL);
	distruge_lista(lista, distruge_elem_participant);
}

void test_cmp_func_nume_crescator() {
	Participant* participant = creeaza_participant(1, "Samoila", "Alexandru", 80);
	Participant* participant_1 = creeaza_participant(2, "Alexandrescu", "Mihai", 90);

	assert(cmp_func_nume_crescator(participant, participant_1) == 0);

	set_nume(participant_1, "Samoila");

	assert(cmp_func_nume_crescator(participant, participant_1) == 1);

	distruge_participant(participant);
	distruge_participant(participant_1);
}

void test_cmp_func_nume_descrescator() {
	Participant* participant = creeaza_participant(1, "Samoila", "Alexandru", 80);
	Participant* participant_1 = creeaza_participant(2, "Alexandrescu", "Mihai", 90);

	assert(cmp_func_nume_descrescator(participant, participant_1) == 1);

	set_nume(participant_1, "Samoila");

	assert(cmp_func_nume_descrescator(participant, participant_1) == 0);

	distruge_participant(participant);
	distruge_participant(participant_1);
}

void test_cmp_func_scor_crescator() {
	Participant* participant = creeaza_participant(1, "Samoila", "Alexandru", 90);
	Participant* participant_1 = creeaza_participant(2, "Alexandrescu", "Mihai", 40);

	assert(cmp_func_scor_crescator(participant, participant_1) == 0);

	set_scor(participant_1, 100);

	assert(cmp_func_scor_crescator(participant, participant_1) == 1);

	distruge_participant(participant);
	distruge_participant(participant_1);
}

void test_cmp_func_scor_descrescator() {
	Participant* participant = creeaza_participant(1, "Samoila", "Alexandru", 90);
	Participant* participant_1 = creeaza_participant(2, "Alexandrescu", "Mihai", 40);

	assert(cmp_func_scor_descrescator(participant, participant_1) == 1);

	set_scor(participant_1, 100);

	assert(cmp_func_scor_descrescator(participant, participant_1) == 0);

	distruge_participant(participant);
	distruge_participant(participant_1);
}

void test_sortare_participanti() {
	Lista* lista = creeaza_lista();

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);

	Participant* participant_2 = creeaza_participant(user_id, "Gheorghe", "Andrei", 50);
	adauga_participant(lista, &user_id, participant_2);

	Participant* participant_3 = creeaza_participant(user_id, "Sibescu", "George", 45);
	adauga_participant(lista, &user_id, participant_3);

	Participant* participant_4 = creeaza_participant(user_id, "Rosu", "Luca", 67);
	adauga_participant(lista, &user_id, participant_4);

	Participant* participant_5 = creeaza_participant(user_id, "Ionescu", "Ion", 50);
	adauga_participant(lista, &user_id, participant_5);

	Participant* participant_6 = creeaza_participant(user_id, "Bibescu", "George", 60);
	adauga_participant(lista, &user_id, participant_6);

	//Sortare crescatoare dupa nume
	Lista* participanti_sortati = sortare_participanti(lista, cmp_func_nume_crescator);

	assert(get_lungime(participanti_sortati) == 7);

	participant = get_element_by_index(participanti_sortati, 0);
	assert(get_id(participant) == 2);
	assert(strcmp(get_nume(participant), "Alexandrescu") == 0);
	assert(strcmp(get_prenume(participant), "Mihai") == 0);
	assert(get_scor(participant) == 90);

	participant = get_element_by_index(participanti_sortati, 1);
	assert(get_id(participant) == 7);
	assert(strcmp(get_nume(participant), "Bibescu") == 0);
	assert(strcmp(get_prenume(participant), "George") == 0);
	assert(get_scor(participant) == 60);

	participant = get_element_by_index(participanti_sortati, 2);
	assert(get_id(participant) == 3);
	assert(strcmp(get_nume(participant), "Gheorghe") == 0);
	assert(strcmp(get_prenume(participant), "Andrei") == 0);
	assert(get_scor(participant) == 50);

	participant = get_element_by_index(participanti_sortati, 3);
	assert(get_id(participant) == 6);
	assert(strcmp(get_nume(participant), "Ionescu") == 0);
	assert(strcmp(get_prenume(participant), "Ion") == 0);
	assert(get_scor(participant) == 50);

	participant = get_element_by_index(participanti_sortati, 4);
	assert(get_id(participant) == 5);
	assert(strcmp(get_nume(participant), "Rosu") == 0);
	assert(strcmp(get_prenume(participant), "Luca") == 0);
	assert(get_scor(participant) == 67);

	participant = get_element_by_index(participanti_sortati, 5);
	assert(get_id(participant) == 1);
	assert(strcmp(get_nume(participant), "Samoila") == 0);
	assert(strcmp(get_prenume(participant), "Alexandru") == 0);
	assert(get_scor(participant) == 80);

	participant = get_element_by_index(participanti_sortati, 6);
	assert(get_id(participant) == 4);
	assert(strcmp(get_nume(participant), "Sibescu") == 0);
	assert(strcmp(get_prenume(participant), "George") == 0);
	assert(get_scor(participant) == 45);

	distruge_lista(participanti_sortati, NULL);

	//Sortare descrescatoare dupa nume
	Lista* participanti_sortati1 = sortare_participanti(lista, cmp_func_nume_descrescator);

	assert(get_lungime(participanti_sortati1) == 7);

	participant = get_element_by_index(participanti_sortati1, 0);
	assert(get_id(participant) == 4);
	assert(strcmp(get_nume(participant), "Sibescu") == 0);
	assert(strcmp(get_prenume(participant), "George") == 0);
	assert(get_scor(participant) == 45);

	participant = get_element_by_index(participanti_sortati1, 1);
	assert(get_id(participant) == 1);
	assert(strcmp(get_nume(participant), "Samoila") == 0);
	assert(strcmp(get_prenume(participant), "Alexandru") == 0);
	assert(get_scor(participant) == 80);

	participant = get_element_by_index(participanti_sortati1, 2);
	assert(get_id(participant) == 5);
	assert(strcmp(get_nume(participant), "Rosu") == 0);
	assert(strcmp(get_prenume(participant), "Luca") == 0);
	assert(get_scor(participant) == 67);

	participant = get_element_by_index(participanti_sortati1, 3);
	assert(get_id(participant) == 6);
	assert(strcmp(get_nume(participant), "Ionescu") == 0);
	assert(strcmp(get_prenume(participant), "Ion") == 0);
	assert(get_scor(participant) == 50);

	participant = get_element_by_index(participanti_sortati1, 4);
	assert(get_id(participant) == 3);
	assert(strcmp(get_nume(participant), "Gheorghe") == 0);
	assert(strcmp(get_prenume(participant), "Andrei") == 0);
	assert(get_scor(participant) == 50);

	participant = get_element_by_index(participanti_sortati1, 5);
	assert(get_id(participant) == 7);
	assert(strcmp(get_nume(participant), "Bibescu") == 0);
	assert(strcmp(get_prenume(participant), "George") == 0);
	assert(get_scor(participant) == 60);

	participant = get_element_by_index(participanti_sortati1, 6);
	assert(get_id(participant) == 2);
	assert(strcmp(get_nume(participant), "Alexandrescu") == 0);
	assert(strcmp(get_prenume(participant), "Mihai") == 0);
	assert(get_scor(participant) == 90);

	distruge_lista(participanti_sortati1, NULL);

	//Sortare crescatoare dupa scor
	Lista* participanti_sortati2 = sortare_participanti(lista, cmp_func_scor_crescator);

	assert(get_lungime(participanti_sortati2) == 7);

	participant = get_element_by_index(participanti_sortati2, 0);
	assert(get_id(participant) == 4);
	assert(strcmp(get_nume(participant), "Sibescu") == 0);
	assert(strcmp(get_prenume(participant), "George") == 0);
	assert(get_scor(participant) == 45);

	participant = get_element_by_index(participanti_sortati2, 1);
	assert(get_id(participant) == 3);
	assert(strcmp(get_nume(participant), "Gheorghe") == 0);
	assert(strcmp(get_prenume(participant), "Andrei") == 0);
	assert(get_scor(participant) == 50);

	participant = get_element_by_index(participanti_sortati2, 2);
	assert(get_id(participant) == 6);
	assert(strcmp(get_nume(participant), "Ionescu") == 0);
	assert(strcmp(get_prenume(participant), "Ion") == 0);
	assert(get_scor(participant) == 50);

	participant = get_element_by_index(participanti_sortati2, 3);
	assert(get_id(participant) == 7);
	assert(strcmp(get_nume(participant), "Bibescu") == 0);
	assert(strcmp(get_prenume(participant), "George") == 0);
	assert(get_scor(participant) == 60);

	participant = get_element_by_index(participanti_sortati2, 4);
	assert(get_id(participant) == 5);
	assert(strcmp(get_nume(participant), "Rosu") == 0);
	assert(strcmp(get_prenume(participant), "Luca") == 0);
	assert(get_scor(participant) == 67);

	participant = get_element_by_index(participanti_sortati2, 5);
	assert(get_id(participant) == 1);
	assert(strcmp(get_nume(participant), "Samoila") == 0);
	assert(strcmp(get_prenume(participant), "Alexandru") == 0);
	assert(get_scor(participant) == 80);

	participant = get_element_by_index(participanti_sortati2, 6);
	assert(get_id(participant) == 2);
	assert(strcmp(get_nume(participant), "Alexandrescu") == 0);
	assert(strcmp(get_prenume(participant), "Mihai") == 0);
	assert(get_scor(participant) == 90);

	distruge_lista(participanti_sortati2, NULL);

	//Sortare descrescatoare dupa scor
	Lista* participanti_sortati3 = sortare_participanti(lista, cmp_func_scor_descrescator);

	assert(get_lungime(participanti_sortati3) == 7);

	participant = get_element_by_index(participanti_sortati3, 0);
	assert(get_id(participant) == 2);
	assert(strcmp(get_nume(participant), "Alexandrescu") == 0);
	assert(strcmp(get_prenume(participant), "Mihai") == 0);
	assert(get_scor(participant) == 90);

	participant = get_element_by_index(participanti_sortati3, 1);
	assert(get_id(participant) == 1);
	assert(strcmp(get_nume(participant), "Samoila") == 0);
	assert(strcmp(get_prenume(participant), "Alexandru") == 0);
	assert(get_scor(participant) == 80);

	participant = get_element_by_index(participanti_sortati3, 2);
	assert(get_id(participant) == 5);
	assert(strcmp(get_nume(participant), "Rosu") == 0);
	assert(strcmp(get_prenume(participant), "Luca") == 0);
	assert(get_scor(participant) == 67);

	participant = get_element_by_index(participanti_sortati3, 3);
	assert(get_id(participant) == 7);
	assert(strcmp(get_nume(participant), "Bibescu") == 0);
	assert(strcmp(get_prenume(participant), "George") == 0);
	assert(get_scor(participant) == 60);

	participant = get_element_by_index(participanti_sortati3, 4);
	assert(get_id(participant) == 6);
	assert(strcmp(get_nume(participant), "Ionescu") == 0);
	assert(strcmp(get_prenume(participant), "Ion") == 0);
	assert(get_scor(participant) == 50);

	participant = get_element_by_index(participanti_sortati3, 5);
	assert(get_id(participant) == 3);
	assert(strcmp(get_nume(participant), "Gheorghe") == 0);
	assert(strcmp(get_prenume(participant), "Andrei") == 0);
	assert(get_scor(participant) == 50);

	participant = get_element_by_index(participanti_sortati3, 6);
	assert(get_id(participant) == 4);
	assert(strcmp(get_nume(participant), "Sibescu") == 0);
	assert(strcmp(get_prenume(participant), "George") == 0);
	assert(get_scor(participant) == 45);

	distruge_lista(participanti_sortati3, NULL);
	distruge_lista(lista, distruge_elem_participant);


}

void test_realocare_memorie() {
	Lista* lista = creeaza_lista();

	assert(get_lungime(lista) == 0);
	assert(get_max_lungime(lista) == 50);

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);

	Participant* participant_2 = creeaza_participant(user_id, "Gheorghe", "Andrei", 50);
	adauga_participant(lista, &user_id, participant_2);

	Participant* participant_3 = creeaza_participant(user_id, "Sibescu", "George", 45);
	adauga_participant(lista, &user_id, participant_3);

	Participant* participant_4 = creeaza_participant(user_id, "Rosu", "Luca", 67);
	adauga_participant(lista, &user_id, participant_4);

	realocare_memorie(lista);

	assert(get_max_lungime(lista) == 100);

	participant = get_element_by_index(lista, 0);
	assert(get_id(participant) == 1);
	assert(strcmp(get_nume(participant), "Samoila") == 0);
	assert(strcmp(get_prenume(participant), "Alexandru") == 0);
	assert(get_scor(participant) == 80);

	//distruge_participant(participant);

	participant = get_element_by_index(lista, 1);
	assert(get_id(participant) == 2);
	assert(strcmp(get_nume(participant), "Alexandrescu") == 0);
	assert(strcmp(get_prenume(participant), "Mihai") == 0);
	assert(get_scor(participant) == 90);

	//distruge_participant(participant);

	participant = get_element_by_index(lista, 2);
	assert(get_id(participant) == 3);
	assert(strcmp(get_nume(participant), "Gheorghe") == 0);
	assert(strcmp(get_prenume(participant), "Andrei") == 0);
	assert(get_scor(participant) == 50);

	//distruge_participant(participant);

	participant = get_element_by_index(lista, 3);
	assert(get_id(participant) == 4);
	assert(strcmp(get_nume(participant), "Sibescu") == 0);
	assert(strcmp(get_prenume(participant), "George") == 0);
	assert(get_scor(participant) == 45);

	//distruge_participant(participant);
	//distruge_lista(participanti_filtrati, distruge_elem_participant);
	//free(participanti_filtrati->elements);
	//free(participanti_filtrati);

	Lista* participanti_filtrati1 = filtrare_participanti_dupa_litera(lista, 'F');

	assert(get_lungime(participanti_filtrati1) == 0);

	distruge_lista(lista, distruge_elem_participant);
	//distruge_lista(participanti_filtrati1, distruge_elem_participant);
	free(participanti_filtrati1->elements);
	free(participanti_filtrati1);
}

void test_distruge_lista() {
	Lista* lista = creeaza_lista();

	assert(get_lungime(lista) == 0);
	assert(get_max_lungime(lista) == 50);

	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);

	assert(get_lungime(lista) == 1);

	distruge_lista(lista, distruge_elem_participant);

}

static void test_set_max_lungime() {
	Lista* lista = creeaza_lista();
	assert(get_lungime(lista) == 0);
	assert(get_max_lungime(lista) == 50);
	set_max_lungime(lista, 100);
	assert(get_max_lungime(lista) == 100);
	distruge_lista(lista, distruge_elem_participant);
}

static void test_get_element_by_index() {
	Lista* lista = creeaza_lista();
	assert(get_lungime(lista) == 0);
	assert(get_max_lungime(lista) == 50);
	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);
	Participant* participant_1 = get_element_by_index(lista, 0);
	assert(get_id(participant_1) == 1);
	assert(strcmp(get_nume(participant_1), "Samoila") == 0);
	assert(strcmp(get_prenume(participant_1), "Alexandru") == 0);
	assert(get_scor(participant_1) == 80);
	Participant* participant_2 = get_element_by_index(lista, 1);
	assert(participant_2 == NULL);
	distruge_lista(lista, distruge_elem_participant);
}

static void test_set_element_on_index() {
	Lista* lista = creeaza_lista();
	assert(get_lungime(lista) == 0);
	assert(get_max_lungime(lista) == 50);
	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);
	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	set_element_on_index(lista, participant_1, 0);
	Participant* participant_2 = get_element_by_index(lista, 0);
	assert(get_id(participant_2) == 2);
	assert(strcmp(get_nume(participant_2), "Alexandrescu") == 0);
	assert(strcmp(get_prenume(participant_2), "Mihai") == 0);
	assert(get_scor(participant_2) == 90);
	distruge_lista(lista, distruge_elem_participant);
	distruge_participant(participant_1);
}

void test_adauga_element() {
	Lista* lista = creeaza_lista();
	assert(get_lungime(lista) == 0);
	assert(get_max_lungime(lista) == 50);
	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	//set_lungime(lista, 50);
	adauga_element(lista, participant);
	Participant* participant_1 = get_element_by_index(lista, 0);
	assert(get_id(participant_1) == 1);
	assert(strcmp(get_nume(participant_1), "Samoila") == 0);
	assert(strcmp(get_prenume(participant_1), "Alexandru") == 0);
	assert(get_scor(participant_1) == 80);
	distruge_lista(lista, distruge_elem_participant);
}

void test_copiaza_lista() {
	Lista* lista = creeaza_lista();
	assert(get_lungime(lista) == 0);
	assert(get_max_lungime(lista) == 50);
	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);
	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);
	Lista* lista_copie = copiaza_lista(lista, copiaza_participant);
	assert(get_lungime(lista_copie) == 2);
	assert(get_max_lungime(lista_copie) == 50);
	distruge_lista(lista, distruge_elem_participant);
	distruge_lista(lista_copie, distruge_elem_participant);
}

static void test_cauta_participant_dupa_id() {
	Lista* lista = creeaza_lista();
	assert(get_lungime(lista) == 0);
	assert(get_max_lungime(lista) == 50);
	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);
	Participant* participant_1 = creeaza_participant(user_id, "Alexandrescu", "Mihai", 90);
	adauga_participant(lista, &user_id, participant_1);
	Participant* participant_cautat = cauta_participant_dupa_id(lista, 1);
	assert(get_id(participant_cautat) == 1);
	assert(strcmp(get_nume(participant_cautat), "Samoila") == 0);
	assert(strcmp(get_prenume(participant_cautat), "Alexandru") == 0);
	assert(get_scor(participant_cautat) == 80);
	distruge_lista(lista, distruge_elem_participant);
}

static void test_undo() {
	Lista* lista = creeaza_lista();
	int user_id = 1;
	adauga(lista, &user_id, "Alex", "Samoila", 90);
	adauga(lista, &user_id, "Alex", "Mihai", 80);
	assert(get_lungime(lista) == 2);
	undo_service(lista);
	assert(get_lungime(lista) == 1);
	undo_service(lista);
	assert(get_lungime(lista) == 0);
	undo_service(lista);
	undo_service(lista);
	pop_undo(lista);
	pop_undo(lista);
	pop_undo(lista);
	pop_undo(lista);
	pop_undo(lista);
	pop_undo(lista);
	free_undo_stack();
	distruge_lista(lista, distruge_elem_participant);
}

static void test_distruge_elem_lista() {
	Lista* lista = creeaza_lista();
	int user_id = 1;
	Participant* participant = creeaza_participant(user_id, "Samoila", "Alexandru", 80);
	adauga_participant(lista, &user_id, participant);
	distruge_elem_lista(lista);
}

void ruleaza_teste() {
	//teste domain
	test_get_id();
	test_get_nume();
	test_get_prenume();
	test_get_scor();
	test_set_id();
	test_set_nume();
	test_set_prenume();
	test_set_scor();
	test_creeaza_participant();
	test_valideaza_participant();
	//teste repo
	test_set_lungime();
	test_get_lungime();
	test_get_max_lungime();
	test_set_max_lungime();
	test_creeaza_lista();
	test_get_participant();
	test_get_element_by_index();
	test_set_element_on_index();
	test_realocare_memorie();
	test_adauga_participant();
	test_adauga_element();
	test_actualizeaza_nume_participant();
	test_actualizeaza_prenume_participant();
	test_actualizeaza_scor_participant();
	test_distruge_lista();
	test_sterge_participant();
	test_copiaza_lista();
	//Service
	test_adauga();
	test_actualizeaza_nume();
	test_actualizeaza_prenume();
	test_actualizeaza_scor();
	test_sterge();
	test_cauta_participant_dupa_id();
	test_filtrare_participanti_dupa_scor();
	test_filtrare_participanti_dupa_litera();
	test_cmp_func_nume_crescator();
	test_cmp_func_nume_descrescator();
	test_cmp_func_scor_crescator();
	test_cmp_func_scor_descrescator();
	test_sortare_participanti();
	test_undo();
	test_distruge_elem_lista();
	printf("Toate testele au fost trecute cu succes!\n");
}