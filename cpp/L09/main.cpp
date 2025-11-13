#include "tests.h"
#include "domain.h"
#include "repo.h"
#include "rentalcart.h"
#include "service.h"
#include "ui.h"
#include "gui.h"
#include <iostream>

using std::cout;

int main(int argc, char* argv[])
{
	Tests().run();
	cout << "Teste rulate";

	RepoNormal repo{ "carti.txt" };
	Rentalcart cart;
	Service service{ repo, cart };

	QApplication app(argc, argv);
	ShopGUI gui{ service };
	gui.show();

	return app.exec();
}