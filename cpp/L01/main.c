#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>


/*linked list of strings*/
typedef struct Node {
	char* data;
	short index;
	struct Node *next;
}Node;

static Node* create_node(const char* str) {
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	char* new_str = malloc(strlen(str) + 1);
	if (new_str == NULL) {
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	strcpy(new_str, str);
	new_node->data = new_str;
	new_node->next = NULL;
	return new_node;
}

static void append(Node** head, const char* str) {
	Node* new_node = create_node(str);
	if (*head == NULL) {
		new_node->index = 1;
		*head = new_node;
	}
	else {
		Node* current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->index = current->index + 1;
	}
}

static void free_list(Node* head) {
	Node* tmp = head;
	while (head != NULL){
		tmp = head;
		head = head->next;
		free(tmp->data);
		free(tmp);
	}
}

/*Programs implementation*/
int prime(int n) {
	if (n < 2)
		return 0;
	if (n > 2 && n % 2 == 0)
		return 0;
	for (int i = 3; i <= n / 2; i += 2)
		if (n % i == 0)
			return 0;
	return 1;
}

void program1() {
	printf("Programul afiseaza numerele prime mai mici ca N\n");
	int n, x;
	printf("Introduceti N: ");
	(void)scanf("%d", &n);
	#pragma omp parallel for schedule(dynamic)
	for (int i = 3; i < n; i += 2)
		if (prime(i))
			printf("%d ", i);
	printf("\n");
}

void program2() {
	printf("Programul genereaza primele N numere prime\n");
	int n;
	printf("Introduceti N: ");
	(void)scanf("%d", &n);
	for (int i = 3; n > 0; i += 2)
		if (prime(i)) {
			printf("%d ", i);
			n--;
		}
	printf("\n");
}

void program3_slow() {
	/* Programul are complexitate Theta(n^2), varianta 'naiva' */
	printf("Programul determina toate reprezentarile unui numar N ca suma de numere consecutive\n");
	int n;
	printf("Introduceti N: ");
	(void)scanf("%d", &n);
	for (int i = 1; i <= n / 2; i++) {
		int sum = 0;
		for (int j = i; j <= n; j++) {
			sum += j;
			if (sum == n) {
				for (int k = i; k <= j; k++)
					printf("%d ", k);
				printf("\n");
				break;
			}
			if (sum > n)
				break;
		}
	}
	printf("\n");
}

void program3_optimized(){
	/* Programul are complexitate Theta(n) folosind Two Pointers*/
	printf("Programul determina toate reprezentarile unui numar N ca suma de numere consecutive\n");
	int n;
	printf("Introduceti N: ");
	(void)scanf("%d", &n);
	int i = 1, j = 1, sum = 1;
	while (i <= n / 2) {
		if (sum < n) {
			j++;
			sum += j;
		}
		else if (sum > n) {
			sum -= i;
			i++;
		}
		else {
			for (int k = i; k <= j; k++)
				printf("%d ", k);
			printf("\n");
			j++;
			sum += j;
		}
	}
	printf("\n");
}

void program3_fast() {
	/* Programul are complexitate Theta(sqrt(n)) folosind Mathematica
		---
		Formula: m = (n - k * (k + 1) / 2) / k  , unde k este numarul de elemente consecutive si m este primul element
	*/
	printf("Programul determina toate reprezentarile unui numar N ca suma de numere consecutive\n");
	int n;
	printf("Introduceti N: ");
	(void)scanf("%d", &n);
	for (int k = 2; k * (k + 1) / 2 <= n; k++) {
		int numerator = n - k * (k + 1) / 2;
		if (numerator % k == 0) {
			int start = numerator / k;
			for (int i = 0; i < k; i++)
				printf("%d ", start + i);
			printf("\n");
		}
	}
	printf("\n");
}

void program4() {
	printf("Programul determina N cifre zecimale ale impartirii subunitare k/m\n");
	int k, m, n, rest;
	printf("Introduceti k: ");
	(void)scanf("%d", &k);
	printf("Introduceti m: ");
	(void)scanf("%d", &m);
	printf("Introduceti N: ");
	(void)scanf("%d", &n);
	rest = k % m;
	for (int i = 0; i < n; i++) {
		printf("%d", rest * 10 / m);
		rest = rest * 10 % m;
	}
	printf("\n");
}

void program5() {
	printf("Programul tipareste N termeni dintr-un sir generat pe baza divizorilor numerelor naturale\n");
	int n;
	printf("Introduceti N: ");
	(void)scanf("%d", &n);
	for (int i = 1; i <= n; i++) {

	}
}
	
static void populate_menu(Node** lista) {
	append(lista, "Program 1");
	append(lista, "Program 2");
	append(lista, "Program 3");
	append(lista, "Program 4");
}

static void menu() {
	int optiune, run = 1;
	Node* lista = NULL;
	populate_menu(&lista);
	while (run)
	{
		Node* current = lista;
		while (current != NULL) {
			printf("%d. %s\n", current->index, current->data);
			current = current->next;
		}
		printf("Introduceti optiunea: ");
		(void)scanf("%d", &optiune);
		switch (optiune) {
		case 1:
			program1();
			break;
		case 2:
			program2();
			break;
		case 3:
			program3_fast();
			break;
		case 4:
			program4();
			break;
		case 5:
			run = 0;
			free_list(lista);
			break;
		default:
			printf("Optiune invalida\n");
			continue;
		}
	}
}

int main() {
	menu();
	return 0;
}