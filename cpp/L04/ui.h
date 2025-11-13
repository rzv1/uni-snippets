// avem nevoie de directivele de preprocesare pentru a evita includerea multipla a headerelor care ar conduce la 
// declarari multiple ale functiilor
#ifndef USER_INTERFACE_H_
// se verifica daca interfata a mai fost definita 
// doar daca nu a mai fost definita se executa tot codul pana la ednif

#define USER_INTERFACE_H_
// definirea interfetei astfel incat preprocesorul sa stie sa nu o includa de mai multe ori

#include "repo.h"

// functie care curata bufferul de intrare pentru a verifica validitatea anumitor input uri
void clear_input_buffer(int* extra_chars);

// functie care afiseaza toti participantii stocati
void print_all_participants(Lista* lista);

// interfata cu utilizatorul pentru functionalitatea de adaugare a unui participant
void user_interface_adaugare_participant(Lista* lista, int* user_id);

// interfata cu utilizatorul pentru functionalitatea de actualizare a datelor unui participant
void user_interface_actualizare_participant(Lista* lista);

// interfata cu utilizatorul pentru functionalitatea de stergere a unui participant
void user_interface_stergere_participant(Lista* lista, Lista* stersi);

// interfata cu utilizatorul pentru functionalitatea de filtarea a participantilor
void user_interface_filtrare_participanti(Lista* lista);

// interfata cu utiizatorul pentru functionalitatea de undo
void ui_undo(Lista* lista);

// interfata cu utilizatorul pentru functionalitatea de afisare a participantilor stersi
void ui_show_deleted(Lista* stersi);

// functia care ruleaza intreaga aplicatie
void ruleaza();

#endif 