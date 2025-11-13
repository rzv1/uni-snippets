#ifndef SERVICE_H_

#define SERVICE_H_

#include <stdbool.h>

#include "repo.h"


// functie responsabila cu trimiterea unui participant spre adaugare in storage (trimiterea are loc doar daca are datele valide)
bool adauga(Lista* lista, int* user_id, char* nume, char* prenume, int scor);

// functie care cauta un participant dupa un id dat
Participant* cauta_participant_dupa_id(Lista* lista, int id);

// functie care actualizeaza numele unui participant
void actualizeaza_nume(Lista* lista, int user_id, char* nume);

// functie care actualizeaza prenumele unui paticipant
void actualizeaza_prenume(Lista* lista, int user_id, char* prenume);

// functie care actualizeaza scorul unui participant
void actualizeaza_scor(Lista* lista, int user_id, int scor);

// functie care sterge un participant
void sterge(Lista* lista, int user_id);

// filtrarea participantilor dupa scor
Lista* filtrare_participanti_dupa_scor(Lista* lista, int scor);

// filtrarea participantilor dupa prima litera a numelui
Lista* filtrare_participanti_dupa_litera(Lista* lista, char litera);

// functie de comparare a numelui a doi participanti pentru utilizare in sortare crescatoare dupa nume
int cmp_func_nume_crescator(Participant* a, Participant* b);

// functie de comparare a numelui a doi participanti pentru utilizare in sortare descrescatoare dupa numwe
int cmp_func_nume_descrescator(Participant* a, Participant* b);

// functie de comparare a scorului a doi participanti pentru utilizare in sortare crescatoare dupa scor
int cmp_func_scor_crescator(Participant* a, Participant* b);

// functie de comparare a scorului a doi participanti pentru utilizare in sortare descrescatoare dupa scor
int cmp_func_scor_descrescator(Participant* a, Participant* b);

// functie pentru sortarea participantilor dupa un criteriu dat ca parametru
Lista* sortare_participanti(Lista* lista, int(*cmp_func)(Participant* a, Participant* b));

//Lista* undo(Lista* lista, Lista* undoList);

bool undo_service(Lista* lista);

Lista* pop_undo();

#endif SERVICE_H_