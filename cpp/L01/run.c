#include "ui.c"
#include "controller.c"
#include "repo.c"
/*Modul care initializeaza repo, controller si ui si ruleaza ui-ul*/
int main()
{
	struct Repository repo = create_repository(10);
	struct Controller ctrl = create_controller(&repo);
	struct UI ui = create_ui(&ctrl);
	show_menu(&ui);
	return 0;
}