#include "test.h"
#include "ui.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

int main() {
	run_tests();
	run();

	if (_CrtDumpMemoryLeaks() == 1)
		printf("Memory leak");
	else
		printf("ok");

	return 0;
}