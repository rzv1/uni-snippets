#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "repo.h"
#include "domain.h"

Lista* creeaza_lista() {
	/*
	functie care creeaza o lista cu atribute default
	(un vector dinamic cu 50 de pozitii pentru stocarea participantilor, lungimea initiala 0, lungimea maxima 50)

	preconditii: nu exista o lista
	postconditii: exista o lista cu atribute default

	return: o lista cu atributele mentionate
	*/
	Lista* lista = malloc(sizeof(Lista));
	if (lista != NULL) {
		lista->lungime = 0;
		lista->max_lungime = 50;
		lista->elements = malloc(sizeof(void*) * lista->max_lungime);
	}
	return lista;
}

int get_lungime(Lista* lista) {
	/*
	getter pentru lungimea unei liste

	lista: lista pentru care trebuie returnata lungimea

	preconditii: lista - sa existe

	return: lungimea listei (valoare intreaga >= 0)
	*/
	return lista->lungime;
}

int get_max_lungime(Lista* lista) {
	/*
	getter pentru lungimea maxima a unei liste

	lista: lista pentru care trebuie returnata lungimea maxima

	preconditii: lista - sa existe

	return: lungimea maxima a listei (valoarea intreaga > 0)
	*/
	return lista->max_lungime;
}


Participant* get_participant(Lista* lista, int id) {
	/*
	getter pentru un participant din storage cu un id dat

	lista: lista in care se cauta participantul cu id ul data
	id: identificatorul unic dupa care se cauta participantul

	preconditii: lista - sa existe
				 id >= 0

	return: participantul cu id dat, daca exista
			un participat cu campuri nule / default, in caz contrar
	*/

	for (int i = 0; i < get_lungime(lista); i++)
		if (get_id(lista->elements[i]) == id)
			return lista->elements[i];

	return NULL;
}

void* get_element_by_index(Lista* lista, int index) {
	/*
	getter pentru un participant dupa un index dat

	lista: structura de stocare in care se cauta participantul cu indexul dat
	index: pozitia din vector a participantului cautat

	preconditii: lista - sa existe
				 0 <= index < get_lungime(lista)

	return: participantul de pe pozitia index din vectorul in care sunt stocati participantii
	*/
	if (index >= 0 && index < get_lungime(lista))
		return lista->elements[index];
	return NULL;
}

void set_element_on_index(Lista* lista, void* elem, int index) {
	/*
	setter pentru un participant dat pe un anumit index intr-o lista cu participanti

	lista: strucuta de stocare in care se afla participantii
	participant: participantul care trebuie adaugat
	index: pozitia pe care trebuie adaugat participantul

	preconditii: lista - sa existe
				 participant - sa fie valid
				 0 <= index < get_lungime(lista)
	*/

	set_id(lista->elements[index], get_id(elem));
	set_nume(lista->elements[index], get_nume(elem));
	set_prenume(lista->elements[index], get_prenume(elem));
	set_scor(lista->elements[index], get_scor(elem));

}

void set_lungime(Lista* lista, int lungime) {
	/*
	setter pentru lungimea listei

	lista: lista pentru care trebuie actualizata lungimea

	preconditii: lista - sa existe
				 lungime >= 0

	postconditii: lista -> lungime ' = lungime
	*/
	lista->lungime = lungime;
}

void set_max_lungime(Lista* lista, int max_lungime) {
	/*
	setter pentru lungimea listei

	lista: lista pentru care trebuie actualizata lungimea

	preconditii: lista - sa existe
				 lungime >= 0

	postconditii: lista -> lungime ' = lungime
	*/
	lista->max_lungime = max_lungime;
}

void realocare_memorie(Lista* lista) {
	/*
	functie care aloca spatiu suplimentar pentru lista de stocare a participantilor

	lista: lista pentru care trebuie alocat spatiu suplimentar

	preconditii: lista - sa existe
	postconditii: lista.max_lungime' = lista.max_lungime * 2
	*/

	int new_max_lungime = get_max_lungime(lista) * 2;
	
	set_max_lungime(lista, new_max_lungime);
	lista->elements = realloc(lista->elements, sizeof(void*) * lista->max_lungime);
}

void adauga_participant(Lista* lista, int* user_id, Participant* participant) {
	/*
	functie care adauga un participant in lista de stocare

	lista: structura in care se stocheaza participantii
	user_id: identificatorul unic al participantului care urmeaza sa se adauge
	participant: o structura de participant cu toate atributele corespunzatoare

	preconditii: lista - sa existe
				 user_id -  valid
				 participant - valid
	postconditii: lista' = lista + participant
				  user_id' = user_id + 1s
	*/
	if (get_lungime(lista) + 1 > get_max_lungime(lista))
		realocare_memorie(lista);

	lista->elements[lista->lungime] = participant;
	set_lungime(lista, get_lungime(lista) + 1);
	(*user_id)++;
}

void adauga_element(Lista* lista, void* elem) {
	/*
	functie care adauga un element in lista de stocare

	lista: structura in care se stocheaza participantii
	user_id: identificatorul unic al participantului care urmeaza sa se adauge
	participant: o structura de participant cu toate atributele corespunzatoare

	preconditii: lista - sa existe
				 user_id -  valid
				 participant - valid
	postconditii: lista' = lista + participant
				  user_id' = user_id + 1s
	*/
	if (get_lungime(lista) + 1 > get_max_lungime(lista))
		realocare_memorie(lista);

	lista->elements[lista->lungime] = elem;
	set_lungime(lista, get_lungime(lista) + 1);
}

void actualizeaza_nume_participant(Lista* lista, int user_id, char* nume) {
	/*
	functie care actualizeaza numele unui participant

	lista: structura de stocare in care se afla participantul pentru care se actualizeaza numele
	id: identificatorul unic al participantului pentru care se actualizeaza numele
	nume: noul nume al participantului

	preconditii: lista - sa existe
				 id >= 1, id valid
				 0 < strlen(nume) <= 64
	*/

	for (int i = 0; i < get_lungime(lista); i++)
		if (get_id((Participant*)lista->elements[i]) == user_id) {
			set_nume((Participant*)lista->elements[i], nume);
			return;
		}

}

void actualizeaza_prenume_participant(Lista* lista, int user_id, char* prenume) {
	/*
	functie care actualizeaza prenumele unui paticipant

	lista: structura de stocare in care se afla participantul pentru care se actualizeaza prenumele
	id: identificatorul unic al participantului pentru care se actualizeaza prenumele
	prenume: noul prenume al participantului

	preconditii: lista - sa existe
				 id >= 1, id valid
				 0 < strlen(prenume) <= 64
	*/

	for (int i = 0; i < get_lungime(lista); i++)
		if (get_id((Participant*)lista->elements[i]) == user_id) {
			set_prenume((Participant*)lista->elements[i], prenume);
			return;
		}
}

void actualizeaza_scor_participant(Lista* lista, int user_id, int scor) {
	/*
	functie care actualizeaza scorul unui participant

	lista: structura de stocare in care se afla participantul pentru care se actualizeaza scorul
	id: identificatorul unic al participantului pentru care se actualizeaza scorul
	scor: noul scor al participantului

	preconditii: lista - sa existe
				 id >= 1, id valid
				 0 <= scor <= 100
	*/

	for (int i = 0; i < get_lungime(lista); i++)
		if (get_id((Participant*)lista->elements[i]) == user_id) {
			set_scor((Participant*)lista->elements[i], scor);
			return;
		}
}

void sterge_participant(Lista* lista, int user_id) {
	/*
	functie care apeleaza stergerea directa a unui participant cu un id dat

	lista: structura de stocare in care se afla participantul care trebuie sters
	id: identificatorul unic al participantului care trebuie sters

	preconditii: lista - sa existe
				 id >= 1, id valid
	postconditii: lista' = lista - participant
	*/
	bool deleted = false;
	for (int i = 0; i < get_lungime(lista) && !deleted; i++)
		if (get_id((Participant*)lista->elements[i]) == user_id) {
			for (int j = i + 1; j < get_lungime(lista); j++) {
				// participant[i] = participant[i + 1]
				//lista->participanti[j - 1] = lista->participanti[j];
				set_id(lista->elements[j - 1], get_id(lista->elements[j]));
				set_nume(lista->elements[j - 1], get_nume(lista->elements[j]));
				set_prenume(lista->elements[j - 1], get_prenume(lista->elements[j]));
				set_scor(lista->elements[j - 1], get_scor(lista->elements[j]));
			}

			distruge_participant(lista->elements[get_lungime(lista) - 1]);

			set_lungime(lista, get_lungime(lista) - 1);
			deleted = true;
		}
}

void distruge_lista(Lista* lista, void(*free_elem)(void*)) {
	/*
	functie care dealoca toate memoria alocata pentru stocarea participantilor in lista

	lista: lista pentru care se dealoca memoria

	preconditii: lista -  sa existe
	*/
	if (free_elem != NULL) {
		for (int i = 0; i < lista->lungime; i++)
			if(lista->elements[i])
				free_elem(lista->elements[i]);
	}
	lista->lungime = 0;
	free(lista->elements);
	free(lista);
}

void goleste_lista(Lista* lista, void(*free_elem)(void*)) {
	if (free_elem != NULL) {
		for (int i = 0; i < lista->lungime; i++) {
			if (lista->elements[i]) {
				free_elem(lista->elements[i]);
			}
		}
	}
	lista->lungime = 0;
}

void distruge_elem_participant(Participant* participant) {
	/*
	functie care dealoca memoria alocata pentru un participant
	*/
	distruge_participant(participant);
}

void distruge_elem_lista(Lista* lista) {
	/*
functie care dealoca memoria alocata pentru o lista
*/
	distruge_lista(lista, distruge_elem_participant);
}

Participant* copiaza_participant(Participant* participant) {
	/*
	functie care copiaza un participant
	*/
	return creeaza_participant(get_id(participant), get_nume(participant), get_prenume(participant), get_scor(participant));
}

Lista* copiaza_lista(Lista* lista, void* (*copy_elem)(void*)) {
	/*
	functie care copiaza toate elementele unei liste intr-o alta lista
	*/
	Lista* lista_noua = creeaza_lista();
	for (int i = 0; i < get_lungime(lista); i++) {
		void* copie_element = copy_elem(lista->elements[i]);
		adauga_element(lista_noua, copie_element);
	}
	return lista_noua;
}