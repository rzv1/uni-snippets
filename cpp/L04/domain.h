#ifndef PARTICIPANT_H_

#define PARTICIPANT_H_

#include <stdbool.h>

typedef struct {
	int id;
	char* nume;
	char* prenume;
	int scor;
} Participant;

// getter pentru id
int get_id(Participant* participant);

//getter pentru nume
char* get_nume(Participant* participant);

//getter pentru prenume
char* get_prenume(Participant* participant);

//getter pentru scor
int get_scor(Participant* participant);

//setter pentru id
void set_id(Participant* participant, int id);

//setter pentru nume
void set_nume(Participant* participant, char* nume);

//setter pentru prenume
void set_prenume(Participant* participant, char* prenume);

//setter pentru scor
void set_scor(Participant* participant, int scor);

// creeaza un participant nou
Participant* creeaza_participant(int id, char* nume, char* prenume, int scor);

// valideaza datele unui participant (un participant poate fi creat doar daca toate datele sale sunt valide)
bool valideaza_participant(char* nume, char* prenume, int scor);

// functie care dealoca memoria alocata pentru stocarea unui participant
void distruge_participant(Participant* participant);

#endif
