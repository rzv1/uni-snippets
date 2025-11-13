#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "domain.h"

int get_id(Participant* participant) {
	/*
	getter pentru id-ul unui participant

	participant: participantul pentru care se returneaza id ul

	preconditii: participant - sa existe

	return: id-ul (valoare intreaga) participantului
	*/

	return participant->id;
}

char* get_nume(Participant* participant) {
	/*
	getter pentru numele unui participant

	participant: participantul pentru care se returneaza numele

	preconditii: participant - sa existe

	return: numele (pointer catre inceputul sirului de caractere) participantului

	*/
	return participant->nume;
}

char* get_prenume(Participant* participant) {
	/*
	getter pentru prenumele unui participant

	participant: participantul pentru care se returneaza prenumele

	preconditii: participant - sa existe

	return: prenumele (pointer catre inceputul sirului de caractere) participantului

	*/
	return participant->prenume;
}

int get_scor(Participant* participant) {
	/*
	getter pentru scorul unui participant

	participant: participantul pentru care se returneaza scorul

	preconditii: participant - sa existe

	return: scorul (valoare intreaga) participantului
	*/
	return participant->scor;
}

void set_id(Participant* participant, int id) {
	/*
	setter pentru id ul unui participant

	participant: participantul pentru care se seteaza id ul
	id: valoarea id ului ce urmeaza a fi setata

	preconditii: participant - sa existe
				 id >= 1

	postconditii: participant -> id ' = id
	*/
	participant->id = id;
}

void set_nume(Participant* participant, char* nume) {
	/*
	setter pentru numele unui participant

	participant: participantul pentru care se seteaza numele
	nume: valoarea ce urmeaza a fi setata pentru nume

	preconditii: participant - sa existe
				 0 < strlen(nume) <= 64

	postconditii: participant -> nume ' = nume
	*/
	strcpy(participant->nume, nume);
}

void set_prenume(Participant* participant, char* prenume) {
	/*
	setter pentru prenumele unui participant

	participant: participantul pentru care se seteaza prenumele
	prenume: valoarea ce urmeaza a fi setata pentru prenume

	preconditiii: participant - sa existe
				  0 < strlen(prenume) <= 64

	postconditii: participant -> prenume ' = prenume
	*/
	strcpy(participant->prenume, prenume);
}

void set_scor(Participant* participant, int scor) {
	/*
	setter pentru scorul unui participant

	participant: participantul pentru care se seteaza scorul
	scor: valoarea ce urmeaza a fi setata pentru scor

	preconditii: participant - sa existe
				 0 <= scor <= 100

	postconditii: participant -> scor = scor
	*/
	participant->scor = scor;
}

Participant* creeaza_participant(int id, char* nume, char* prenume, int scor) {
	/*
	functie care creeaza un participant

	id: identificatorul unic al participantului (int)
	nume: numele participantului (sir de caractere)
	prenume: prenumele participantului (sir de caractere)
	scor: scorul obtinut de participant (0 <= scor <= 100)

	return: un participant
	*/

	Participant* participant = (Participant*)malloc(sizeof(Participant));

	if (participant != NULL) {
		participant->id = id;

		participant->nume = (char*)malloc(64 * sizeof(char));
		if (participant->nume) {
			memset(participant->nume, 0, 64 * sizeof(char));
			strcpy(participant->nume, nume);
		}


		participant->prenume = (char*)malloc(64 * sizeof(char));
		if (participant->prenume) {
			memset(participant->prenume, 0, 64 * sizeof(char));
			strcpy(participant->prenume, prenume);
		}

		participant->scor = scor;
	}

	return participant;
}

bool valideaza_participant(char* nume, char* prenume, int scor) {
	/*
	functie care valideaza datele unui participant (introduse de catre utilizator)
	id - ul userului nu trebuie validat deoarece el este unic si valid datorita modalitatii
	de atribuire folosita

	nume: numele introdus pentru participant
	prenume: prenumele introdus de catre utilizator
	scor: scorul participantului care este egal cu suma punctelor obtinute pe cele 10 probleme

	return: true, daca datele participantului sunt valide, false in caz contrar
	*/
	if (nume[0] == '\n' || !isalpha(nume[0]) || strlen(nume) == 0)
		return false;

	if (prenume[0] == '\n' || !isalpha(prenume[0]) || strlen(prenume) == 0)
		return false;

	if (scor < 0)
		return false;

	return true;
}

void distruge_participant(Participant* participant) {
	/*
	functie care dealoca memoria alocata pentru campurile unui participant

	participantul: participantul pentru care se dealoca memoria

	preconditii: participant - sa existe
	*/

	free(participant->nume);
	free(participant->prenume);
	free(participant);
}