#include "repo.c"
#include "entities.c"
#include <string.h>

/*Controller pentru entitatea masina care permite vizualizarea masinilor dupa criteriu: categorie, model.*/
struct Controller {
	struct Repository* repo;
};

/*Functie care creeaza un controller pentru masini*/
struct Controller create_controller(struct Repository* repo);

struct Controller create_controller(struct Repository* repo)
{
	struct Controller ctrl;
	ctrl.repo = repo;
	return ctrl;
}

/*Functie care afiseaza masinile dupa criteriul categorie*/
void show_cars_by_category(struct Controller* ctrl, char* category);

void show_cars_by_category(struct Controller* ctrl, char* category)
{
	struct Car* cars = get_all_cars(ctrl->repo);
	int size = get_size(ctrl->repo);
	for (int i = 0; i < size; i++) {
		if (strcmp(cars[i].type, category) == 0) {
			printf("Brand: %s, Type: %d, License: %.2f\n", cars[i].brand, cars[i].type, cars[i].license);
		}
	}
}

/*Functie care afiseaza masinile dupa criteriul model*/
void show_cars_by_model(struct Controller* ctrl, char* model);

void show_cars_by_model(struct Controller* ctrl, char* model)
{
	struct Car* cars = get_all_cars(ctrl->repo);
	int size = get_size(ctrl->repo);
	for (int i = 0; i < size; i++) {
		if (strcmp(cars[i].brand, model) == 0) {
			printf("Brand: %s, Type: %d, License: %.2f\n", cars[i].brand, cars[i].type, cars[i].license);
		}
	}
}

