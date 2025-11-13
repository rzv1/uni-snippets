#ifndef STORAGE_H_

#define STORAGE_H_

#include "domain.h"

typedef struct {
	void** elements;
	int lungime;
	int max_lungime;
} Lista;

// getter pentru lungimea unei liste
int get_lungime(Lista* lista);

// getter pentru lungimea maxima a unei liste
int get_max_lungime(Lista* lista);

// getter pentru un participant din storage cu un id dat
Participant* get_participant(Lista* lista, int id);

// getter pentru un participant dupa indexul din vectorul in care este stocat
void* get_element_by_index(Lista* lista, int index);

// setter pentru un participant pe un anumit index in vectorul in care sunt stocati participantii
void set_element_on_index(Lista* lista, void* elem, int index);

//setter pentru lungimea listei
void set_lungime(Lista* lista, int lugime);

// functie care creeaza o lista cu valori default (lungimea initiala 0, lungimea maxima 50 si un vector static de 50 de pozitii)
Lista* creeaza_lista();

// functie care dealoca toata memoria alocata pentru stocarea participantilor
void distruge_lista(Lista* lista, void (*free_elem)(void*));

// functie care copiaza lista
Lista* copiaza_lista(Lista* lista, void* (*copy_elem)(void*));

// functie care aloca spatiu suplimentar pentru lista de stocare
void realocare_memorie(Lista* lista);

// functie care adauga un element in lista
void adauga_element(Lista* lista, void* elem);

// functie care adauga un participant in lista de stocare
void adauga_participant(Lista* lista, int* user_id, Participant* participant);

// functie care actualizeaza numele unui participant
void actualizeaza_nume_participant(Lista* lista, int user_id, char* nume);

// functie care actualizeaza prenumele unui participant
void actualizeaza_prenume_participant(Lista* lista, int user_id, char* prenume);

// functie care actualizeaza scorul unui participant
void actualizeaza_scor_participant(Lista* lista, int user_id, int scor);

// functie care sterge un participant
void sterge_participant(Lista* lista, int user_id);

void distruge_elem_participant(Participant* participant);

void distruge_elem_lista(Lista* lista);

void goleste_lista(Lista* lista, void(*free_elem)(void*));

Participant* copiaza_participant(Participant* participant);

#endif STORAGE_H_