#include "domain.h"
#include "service.h"
#include "repo.h"
#include "tests.h"
#include <cassert>
#include <stdio.h>
#include <iostream>
#include <fstream>


static void test_get_title() {
	Carte c{ "A", "B", "istorie", 2000 };
	assert(c.get_title() == "A");

	Carte c2{ "D", "E", "drama", 2000 };
	assert(c2.get_title() == "D");

	Carte c3{ "G", "H", "comedie", 2000 };
	assert(c3.get_title() == "G");
}

static void test_get_author() {
	Carte c{ "A", "B", "istorie", 2000 };
	assert(c.get_author() == "B");
	Carte c2{ "D", "E", "drama", 2000 };
	assert(c2.get_author() == "E");
	Carte c3{ "G", "H", "comedie", 2000 };
	assert(c3.get_author() == "H");
}

static void test_get_genre() {
	Carte c{ "A", "B", "istorie", 2000 };
	assert(c.get_genre() == "istorie");
	Carte c2{ "D", "E", "drama", 2000 };
	assert(c2.get_genre() == "drama");
	Carte c3{ "G", "H", "comedie", 2000 };
	assert(c3.get_genre() == "comedie");
}

static void test_get_year() {
	Carte c{ "A", "B", "istorie", 2000 };
	assert(c.get_year() == 2000);
	Carte c2{ "D", "E", "drama", 2001 };
	assert(c2.get_year() == 2001);
	Carte c3{ "G", "H", "comedie", 2002 };
	assert(c3.get_year() == 2002);
}

static void test_get_id() {
	Carte c{ "A", "B", "istorie", 2000 };
	assert(c.get_id() == 0);
}

static void test_set_title() {
	Carte c{ "A", "B", "istorie", 2000 };
	c.set_title("D");
	assert(c.get_title() == "D");
	Carte c1{ "E", "F", "drama", 2000 };
	c1.set_title("H");
	assert(c1.get_title() == "H");
}

static void test_set_author() {
	Carte c{ "A", "B", "istorie", 2000 };
	c.set_author("D");
	assert(c.get_author() == "D");
	Carte c1{ "E", "F", "drama", 2000 };
	c1.set_author("H");
	assert(c1.get_author() == "H");
}

static void test_set_genre() {
	Carte c{ "A", "B", "istorie", 2000 };
	c.set_genre("drama");
	assert(c.get_genre() == "drama");
	Carte c1{ "E", "F", "comedie", 2000 };
	c1.set_genre("istorie");
	assert(c1.get_genre() == "istorie");
}

static void test_set_year() {
	Carte c{ "A", "B", "istorie", 2000 };
	c.set_year(2001);
	assert(c.get_year() == 2001);
	Carte c1{ "E", "F", "drama", 2000 };
	c1.set_year(2001);
	assert(c1.get_year() == 2001);
}

static void test_set_id() {
	Carte c{ "A", "B", "istorie", 2000 };
	c.set_id(1);
	assert(c.get_id() == 1);
	Carte c1{ "E", "F", "drama", 2000 };
	c1.set_id(2);
	assert(c1.get_id() == 2);
}

static void test_to_string() {
	Carte c{ "A", "B", "istorie", 2000 };
	assert(c.to_string() == "ID: 0 Titlu: A Autor: B Gen: istorie An aparitie: 2000");
	Carte c1{ "E", "F", "drama", 2000 };
	assert(c1.to_string() == "ID: 0 Titlu: E Autor: F Gen: drama An aparitie: 2000");
}

void Tests::run_test_domain() {
	test_get_title();
	test_get_author();
	test_get_genre();
	test_get_year();
	test_get_id();
	test_set_title();
	test_set_author();
	test_set_genre();
	test_set_year();
	test_set_id();
	test_to_string();
}

static void test_add() {
	RepoNormal r("test_carti.txt");
	Carte c{ "A", "B", "istorie", 2000 };
	r.add(c);
	assert(r.get_size() == 1);
	Carte c2{ "D", "E", "drama", 2000 };
	r.add(c2);
	assert(r.get_size() == 2);
	Carte c3{ "G", "H", "comedie", 2000 };
	r.add(c3);
	assert(r.get_size() == 3);
	r.remove(1);
	r.remove(2);
	r.remove(3);
}

static void test_remove() {
	RepoNormal r("test_carti.txt");
	Carte c{ "A", "B", "istorie", 2000 };
	r.add(c);
	assert(r.get_size() == 1);
	Carte c1{ "E", "F", "drama", 2000 };
	r.add(c1);
	assert(r.get_size() == 2);
	r.remove(1);
	assert(r.get_size() == 1);
	Carte c2{ "D", "E", "drama", 2000 };
	r.add(c2);
	assert(r.get_size() == 2);
	r.remove(2);
	assert(r.get_size() == 1);
	try {
		r.remove(4);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.get_message() == "Cartea cu id-ul dat nu exista!");
	}
	r.remove(3);
}

static void test_update_title() {
	RepoNormal r("test_carti.txt");
	Carte c{ "A", "B", "istorie", 2000 };
	r.add(c);
	assert(r.get_by_id(1).get_title() == "A");
	r.update_title(1, "D");
	assert(r.get_by_id(1).get_title() == "D");
	r.remove(1);
}

static void test_update_author() {
	RepoNormal r("test_carti.txt");
	Carte c{ "A", "B", "istorie", 2000 };
	r.add(c);
	assert(r.get_by_id(1).get_author() == "B");
	r.update_author(1, "D");
	assert(r.get_by_id(1).get_author() == "D");
	r.remove(1);
}

static void test_update_genre() {
	RepoNormal r("test_carti.txt");
	Carte c{ "A", "B", "istorie", 2000 };
	r.add(c);
	assert(r.get_by_id(1).get_genre() == "istorie");
	r.update_genre(1, "drama");
	assert(r.get_by_id(1).get_genre() == "drama");
	r.remove(1);
}

static void test_update_year() {
	RepoNormal r("test_carti.txt");
	Carte c{ "A", "B", "istorie", 2000 };
	r.add(c);
	assert(r.get_by_id(1).get_year() == 2000);
	r.update_year(1, 2001);
	assert(r.get_by_id(1).get_year() == 2001);
	r.remove(1);
}

static void test_get_by_id() {
	RepoNormal r("test_carti.txt");
	Carte c{ "A", "B", "istorie", 2000 };
	r.add(c);
	assert(r.get_by_id(1).get_title() == "A");
	assert(r.get_by_id(1).get_author() == "B");
	assert(r.get_by_id(1).get_genre() == "istorie");
	assert(r.get_by_id(1).get_year() == 2000);
	r.remove(1);
	try {
		r.get_by_id(2);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.get_message() == "Id-ul nu exista!");
	}
}

void Tests::run_test_repo() {
	test_add();
	test_remove();
	test_update_title();
	test_update_author();
	test_update_genre();
	test_update_year();
	test_get_by_id();
}

static void test_add_service() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	s.add("A", "B", "istorie", 2000);
	assert(s.get_all().size() == 1);
	s.add("D", "E", "drama", 2000);
	assert(s.get_all().size() == 2);
	try {
		s.add("G", "H", "comed", 2000);
		assert(false);
	}
	catch (ValidationException& e) {
		assert(e.get_message() == "Gen invalid!");
		try {
			s.add("J", "1321", "istorie", 2000);
			assert(false);
		}
		catch (ValidationException& e) {
			assert(e.get_message() == "Autor invalid!");
		}
	}
	r.remove(1);
	r.remove(2);
}

static void test_remove_service() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	s.add("A", "B", "istorie", 2000);
	assert(s.get_all().size() == 1);
	s.remove(1);
	assert(s.get_all().size() == 0);
	//try {
	//	s.remove(20);
	//	assert(false);
	//}
	//catch (RepoException& e) {
	//	string expected = "Cartea cu id-ul dat nu exista!";
	//	assert(e.get_message() == expected);
	//}
}

static void test_update_service() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	s.add("A", "B", "istorie", 2000);
	assert(s.get_all().size() == 1);
	s.update_title(1, "D");
	assert(s.get_all()[0].get_title() == "D");
	s.update_author(1, "E");
	assert(s.get_all()[0].get_author() == "E");
	s.update_genre(1, "drama");
	assert(s.get_all()[0].get_genre() == "drama");
	s.update_year(1, 2001);
	assert(s.get_all()[0].get_year() == 2001);
	r.remove(1);
}

static void test_filter_title() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	s.add("A", "B", "istorie", 2000);
	s.add("D", "E", "drama", 2001);
	s.add("G", "H", "comedie", 2002);
	assert(s.filter_title("A").size() == 1);
	assert(s.filter_title("D").size() == 1);
	assert(s.filter_title("O").size() == 0);
	r.remove(1);
	r.remove(2);
	r.remove(3);
}

static void test_filter_year() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	s.add("A", "B", "istorie", 2000);
	s.add("D", "E", "drama", 2001);
	s.add("G", "H", "comedie", 2002);
	assert(s.filter_year(2000).size() == 1);
	assert(s.filter_year(2001).size() == 1);
	assert(s.filter_year(2003).size() == 0);
	r.remove(1);
	r.remove(2);
	r.remove(3);
}

static void test_sort_title() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	s.add("C", "B", "istorie", 2000);
	s.add("A", "E", "drama", 2001);
	s.add("B", "H", "comedie", 2002);
	auto sorted = s.sort_title();
	assert(sorted[0].get_title() == "A");
	assert(sorted[1].get_title() == "B");
	assert(sorted[2].get_title() == "C");
	r.remove(1);
	r.remove(2);
	r.remove(3);
}

static void test_sort_author() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	s.add("A", "C", "istorie", 2000);
	s.add("D", "A", "drama", 2001);
	s.add("G", "B", "comedie", 2002);
	auto sorted = s.sort_author();
	assert(sorted[0].get_author() == "A");
	assert(sorted[1].get_author() == "B");
	assert(sorted[2].get_author() == "C");
	r.remove(1);
	r.remove(2);
	r.remove(3);
}

static void test_sort_year_and_genre() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	s.add("A", "B", "istorie", 2005);
	s.add("D", "E", "drama", 2001);
	s.add("G", "H", "comedie", 2002);
	auto sorted = s.sort_year_and_genre();
	assert(sorted[0].get_year() == 2001);
	assert(sorted[1].get_year() == 2002);
	assert(sorted[2].get_year() == 2005);
	r.remove(1);
	r.remove(2);
	r.remove(3);
}

static void test_add_cart() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	s.add("A", "B", "istorie", 2005);
	s.add("D", "E", "drama", 2001);
	s.add("E", "H", "comedie", 2002);
	string title = "A";
	assert(s.add_cart(title) == true);
	assert(c.get_size() == 1);
	assert(c.get_all()[0].get_genre() == "istorie");
	s.add("A", "C", "drama", 2010);
	s.add_cart(title);
	assert(c.get_all().size() == 3);
	assert(c.get_all()[1].get_genre() == "istorie");
	assert(c.get_all()[2].get_genre() == "drama");
	(void)s.cart_get_all();
	r.remove(1);
	r.remove(2);
	r.remove(3);
	r.remove(4);
}

static void test_clear_cart() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	s.add("A", "B", "istorie", 2005);
	s.add("D", "E", "drama", 2001);
	s.add("A", "H", "comedie", 2002);
	string title = "A";
	s.add_cart(title);
	assert(c.get_all().size() == 2);
	assert(s.clear_cart() == true);
	assert(c.get_all().size() == 0);
}

static void test_generate_cart() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	assert(s.generate_cart(5) == true);
	assert(c.get_all().size() == 5);
}

static void test_export_cart() {
	RepoNormal r("test_carti.txt");
	Rentalcart c;
	Service s{ r, c };
	s.add("A", "B", "istorie", 2005);
	s.add("D", "E", "drama", 2001);
	s.add("A", "H", "comedie", 2002);
	string title = "A";
	s.add_cart(title);
	string filename = "test.csv";
	assert(s.export_cart(filename) == true);
}

void Tests::run_test_service() {
	test_add_service();
	test_remove_service();
	test_update_service();
	test_filter_title();
	test_filter_year();
	test_sort_title();
	test_sort_author();
	test_sort_year_and_genre();
	test_add_cart();
	test_clear_cart();
	test_generate_cart();
	test_export_cart();
}

static void test_validate_book() {
	try {
		Carte c{ "A", "B", "invalid_genre", 2000 };
		c.validate_book();
		assert(false);
	}
	catch (ValidationException& e) {
		assert(e.get_message() == "Gen invalid!");
	}
	try {
		Carte c{ "A", "invalid_312author", "istorie", 2000 };
		c.validate_book();
		assert(false);
	}
	catch (ValidationException& e) {
		assert(e.get_message() == "Autor invalid!");
	}
}

static void test_validate_author() {
	Carte c{ "A", "B", "istorie", 2000 };
	assert(c.validate_author("B") == true);
	try {
		c.validate_author("invalid_au312thor");
		assert(false);
	}
	catch (ValidationException& e) {
		assert(e.get_message() == "Autor invalid!");
	}
}

static void test_validate_genre() {
	Carte c{ "A", "B", "istorie", 2000 };
	assert(c.validate_genre("istorie") == true);
	try {
		c.validate_genre("invalid_genre");
		assert(false);
	}
	catch (ValidationException& e) {
		assert(e.get_message() == "Gen invalid!");
	}
}

void Tests::run_test_validation() {
	test_validate_book();
	test_validate_author();
	test_validate_genre();
}

void Tests::run() {
	run_test_domain();
	run_test_repo();
	run_test_service();
	run_test_validation();
	remove("test_carti.txt");
}
