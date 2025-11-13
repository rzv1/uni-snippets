#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

// Funcție pentru a crea un nou nod
Node* create_node(const char* str) {
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
		printf("malloc error\n");
        return 1;
    }
	char* new_str = malloc(strlen(str) + 1);
    if (new_str == NULL) {
        printf("malloc error\n");
        return 1;
    }
	strcpy(new_str, str);
    new_node->data = new_str;
    new_node->next = NULL;
    return new_node;
}

// Funcție pentru a adăuga un nod la finalul listei
void append(Node** head, const char* str) {
    Node* new_node = create_node(str);
    if (*head == NULL) {
        *head = new_node;
    }
    else {
        Node* current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

// Funcție pentru a elibera lista
void free_list(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

int main(void) {
    Node* lista = NULL;

    append(&lista, "Primul string");
    append(&lista, "Al doilea string");
    append(&lista, "Al treilea string");

    // Parcurgem și afișăm lista
    Node* current = lista;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }

    // Eliberăm memoria
    free_list(lista);

    return 0;
}
