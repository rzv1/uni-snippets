#include "test.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "ui.h"
#include <iostream>

int main() {
	Tests tests;
	tests.run();
	printf("All tests passed!\n");
	Repo repo;
	Service service{ repo };
	UI ui{ service };
	ui.run();
	return 0;
}