#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include "tests.h"
#include "domain.h"
#include "repo.h"
#include "rentalcart.h"
#include "service.h"
#include "ui.h"
#include <iostream>

using std::cout;

void run() {
	Tests tests;
	tests.run();
	cout << "Teste trecute!";
	Repo repo;
	Rentalcart cart;
	Service service{ repo, cart };
	UI ui{ service };
	ui.run();
}

int main() {
	run();
	if (_CrtDumpMemoryLeaks())
		cout << "Leaks";
	else
		cout << "No memory leaks";
	return 0;
}