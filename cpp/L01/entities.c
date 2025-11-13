/*Structura masina cu atributele license, brand, type si metodele get_license(), get_brand(), get_type()*/
struct Car {
	char license[10];
	char brand[20];
	char type[20];
};

char get_license(struct Car car) {
	return car.license;
}

char get_brand(struct Car car) {
	return car.brand;
}

char get_type(struct Car car) {
	return car.type;
}

/*Trebuie verificat daca exista memory leaks folosind if (_CRTmemoryLeaks)*/