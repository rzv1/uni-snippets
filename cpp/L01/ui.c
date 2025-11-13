/*Structura pentru ui care se foloseste pentru afisarea unui meniu*/
struct UI {
	struct Controller* ctrl;
};

/*Functie care creeaza un ui pentru masini*/
struct UI create_ui(struct Controller* ctrl);

struct UI create_ui(struct Controller* ctrl)
{
	struct UI ui;
	ui.ctrl = ctrl;
	return ui;
}

/*Functie care afiseaza meniul principal*/
void show_menu(struct UI* ui);

void show_menu(struct UI* ui)
{
	while (1) {
		printf("1. Show cars by category\n");
		printf("2. Show cars by model\n");
		printf("3. Exit\n");
		int option = 0;
		printf("Choose an option: ");
		scanf("%d", &option);
		if (option == 1) {
			char category[20];
			printf("Enter category: ");
			scanf("%s", category);
			show_cars_by_category(ui->ctrl, category);
		}
		else if (option == 2) {
			char model[20];
			printf("Enter model: ");
			scanf("%s", model);
			show_cars_by_model(ui->ctrl, model);
		}
		else if (option == 3) {
			break;
		}
		else {
			printf("Invalid option!\n");
		}
	}
}

/*Functie de sortare care primeste ca parametru o alta functie pentru lab 4*/