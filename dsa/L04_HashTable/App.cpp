
#include "TestExtins.h"
#include "TestScurt.h"
#include <iostream>
using namespace std;

int main() {

	testAll();
	testAllExtins();

	cout << "That's all!" << endl;

}


// Complexitata: Theta(n) , n - nr de elemente din multime
// returnează diferența dintre valoarea maximă și minimă
// dacă mulțimea este vidă, se returnează -1
//Subalgoritm diferentaMaxMin(a: Multime) : Intreg
//    Daca a.vida() atunci
//        diferentaMaxMin ← - 1
//    altfel
//        it ← iterator(a)
//        it.prim()
//        min ← it.element()
//        max ← it.element()
//        CatTimp it.valid() executa
//            elem ← it.element()
//            Daca elem < min atunci
//                min ← elem
//            SfDaca
//            Daca elem > max atunci
//                max ← elem
//            SfDaca
//            it.urmator()
//        SfCatTimp
//        diferentaMaxMin ← max - min
//    SfDaca
//SfSubalgoritm


