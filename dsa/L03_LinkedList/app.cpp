
#include "TestScurt.h"
#include "TestExtins.h"
#include "TestLSI.h"
#include <iostream>
using namespace std;

int main() {

	testAllExtins();
	testAllScurt();
	testLSI();

	cout << "That's all!" << endl;

}
