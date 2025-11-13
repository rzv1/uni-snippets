#include "test.h"
#include "repo.h"
#include "service.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/*
* Testeaza masina.h
*/
static void test_create_car() {
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	assert(strcmp(get_license(&car1), "AB-12-CD") == 0);
	assert(strcmp(get_model(&car1), "Audi") == 0);
	assert(strcmp(get_category(&car1), "Mini") == 0);
	assert(get_id(&car1) == 0);
	destroy_car(&car1);

	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	assert(strcmp(get_license(&car2), "BC-34-DE") == 0);
	assert(strcmp(get_model(&car2), "BMW") == 0);
	assert(strcmp(get_category(&car2), "Suv") == 0);
	assert(get_id(&car2) == 0);
	destroy_car(&car2);

	Car car3 = create_car("CD-56-EF", "Mercedes", "Sport");
	assert(strcmp(get_license(&car3), "CD-56-EF") == 0);
	assert(strcmp(get_model(&car3), "Mercedes") == 0);
	assert(strcmp(get_category(&car3), "Sport") == 0);
	assert(get_id(&car3) == 0);
	destroy_car(&car3);
}

static void test_find_by_id() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	Car* car = find_by_id(repo, 1);
	assert(strcmp(get_license(car), "AB-12-CD") == 0);
	assert(strcmp(get_model(car), "Audi") == 0);
	assert(strcmp(get_category(car), "Mini") == 0);
	assert(get_id(car) == 1);

	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	repo_add_car(repo, &car2);
	Car* car3 = find_by_id(repo, 2);
	assert(strcmp(get_license(car3), "BC-34-DE") == 0);
	assert(strcmp(get_model(car3), "BMW") == 0);
	assert(strcmp(get_category(car3), "Suv") == 0);
	assert(get_id(car3) == 2);
	destroy_repo(repo);
}

static void test_find_by_index() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	Car* car = find_by_index(repo, 0);
	assert(strcmp(get_license(car), "AB-12-CD") == 0);
	assert(strcmp(get_model(car), "Audi") == 0);
	assert(strcmp(get_category(car), "Mini") == 0);
	assert(get_id(car) == 1);
	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	repo_add_car(repo, &car2);
	Car* car3 = find_by_index(repo, 1);
	assert(strcmp(get_license(car3), "BC-34-DE") == 0);
	assert(strcmp(get_model(car3), "BMW") == 0);
	assert(strcmp(get_category(car3), "Suv") == 0);
	assert(get_id(car3) == 2);
	assert(find_by_index(repo, 2) == NULL);
	destroy_repo(repo);
}

static void test_validate_category() {
	assert(validate_category("mini") == true);
	assert(validate_category("suv") == true);
	assert(validate_category("sport") == true);
	assert(validate_category("Mini") == true);
	assert(validate_category("Suv") == true);
	assert(validate_category("Sport") == true);
	assert(validate_category("mini ") == false);
	assert(validate_category(" suv") == false);
	assert(validate_category("sport ") == false);
	assert(validate_category("mini1") == false);
	assert(validate_category("suv1") == false);
	assert(validate_category("sport1") == false);
	assert(validate_category("mini1") == false);
	assert(validate_category("suv1") == false);
	assert(validate_category("sport1") == false);
}

static void test_get_id() {
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	assert(get_id(&car1) == 0);
	destroy_car(&car1);
	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	assert(get_id(&car2) == 0);
	destroy_car(&car2);
	Car car3 = create_car("CD-56-EF", "Mercedes", "Sport");
	assert(get_id(&car3) == 0);
	destroy_car(&car3);
}

static void test_destroy_car() {
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	destroy_car(&car1);
	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	destroy_car(&car2);
	Car car3 = create_car("CD-56-EF", "Mercedes", "Sport");
	destroy_car(&car3);
}

static void test_get_license() {
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	assert(strcmp(get_license(&car1), "AB-12-CD") == 0);
	destroy_car(&car1);
	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	assert(strcmp(get_license(&car2), "BC-34-DE") == 0);
	destroy_car(&car2);
	Car car3 = create_car("CD-56-EF", "Mercedes", "Sport");
	assert(strcmp(get_license(&car3), "CD-56-EF") == 0);
	destroy_car(&car3);
}

static void test_get_model() {
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	assert(strcmp(get_model(&car1), "Audi") == 0);
	destroy_car(&car1);
	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	assert(strcmp(get_model(&car2), "BMW") == 0);
	destroy_car(&car2);
	Car car3 = create_car("CD-56-EF", "Mercedes", "Sport");
	assert(strcmp(get_model(&car3), "Mercedes") == 0);
	destroy_car(&car3);
}

static void test_get_category() {
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	assert(strcmp(get_category(&car1), "Mini") == 0);
	destroy_car(&car1);
	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	assert(strcmp(get_category(&car2), "Suv") == 0);
	destroy_car(&car2);
	Car car3 = create_car("CD-56-EF", "Mercedes", "Sport");
	assert(strcmp(get_category(&car3), "Sport") == 0);
	destroy_car(&car3);
}

static void test_set_license() {
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	set_license(&car1, "BC-34-DE");
	assert(strcmp(get_license(&car1), "BC-34-DE") == 0);
	destroy_car(&car1);

	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	set_license(&car2, "CD-56-EF");
	assert(strcmp(get_license(&car2), "CD-56-EF") == 0);
	destroy_car(&car2);

	Car car3 = create_car("CD-56-EF", "Mercedes", "Sport");
	set_license(&car3, "DE-78-FG");
	assert(strcmp(get_license(&car3), "DE-78-FG") == 0);
	destroy_car(&car3);
}

static void test_set_model() {
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	set_model(&car1, "BMW");
	assert(strcmp(get_model(&car1), "BMW") == 0);
	destroy_car(&car1);

	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	set_model(&car2, "Mercedes");
	assert(strcmp(get_model(&car2), "Mercedes") == 0);
	destroy_car(&car2);

	Car car3 = create_car("CD-56-EF", "Mercedes", "Sport");
	set_model(&car3, "Audi");
	assert(strcmp(get_model(&car3), "Audi") == 0);
	destroy_car(&car3);
}

static void test_set_category() {
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	set_category(&car1, "Suv");
	assert(strcmp(get_category(&car1), "Suv") == 0);
	destroy_car(&car1);

	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	set_category(&car2, "Sport");
	assert(strcmp(get_category(&car2), "Sport") == 0);
	destroy_car(&car2);

	Car car3 = create_car("CD-56-EF", "Mercedes", "Sport");
	set_category(&car3, "Mini");
	assert(strcmp(get_category(&car3), "Mini") == 0);
	destroy_car(&car3);
}

static void test_set_is_rented() {
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	set_is_rented(&car1, true);
	assert(car1.is_rented == true);
	destroy_car(&car1);

	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	set_is_rented(&car2, false);
	assert(car2.is_rented == false);
	destroy_car(&car2);
}

static void test_get_is_rented() {
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	assert(get_is_rented(&car1) == false);
	destroy_car(&car1);

	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	set_is_rented(&car2, true);
	assert(get_is_rented(&car2) == true);
	destroy_car(&car2);
}

/*
* Testeaza repo.h
*/
static void test_create_repo() {
	Repo* repo = create_repo();
	assert(get_size(repo) == 0);
	assert(repo->next_id == 1);
	destroy_repo(repo);
}

static void test_repo_add_car() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	assert(get_size(repo) == 1);
	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	repo_add_car(repo, &car2);
	assert(get_size(repo) == 2);
	destroy_repo(repo);
	Repo* repo3 = create_repo();
	Car car3 = create_car("CD-56-EF", "Mercedes", "Sport");
	repo_add_car(repo3, &car3);
	assert(get_size(repo3) == 1);
	destroy_repo(repo3);
}

static void test_destroy_repo() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	repo_add_car(repo, &car2);
	destroy_repo(repo);
}

static void test_get_size() {
	Repo* repo = create_repo();
	assert(get_size(repo) == 0);
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	assert(get_size(repo) == 1);
	Car car2 = create_car("BC-34-DE", "BMW", "Suv");
	repo_add_car(repo, &car2);
	assert(get_size(repo) == 2);
	destroy_repo(repo);
}

static void test_update_license() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	assert(update_license(repo, 1, "BC-34-DE") == true);
	assert(strcmp(get_license(find_by_index(repo, 0)), "BC-34-DE") == 0);
	assert(update_license(repo, 0, "CD-56-EF") == false);
	destroy_repo(repo);
}

static void test_update_model() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	assert(update_model(repo, 1, "BMW") == true);
	assert(strcmp(get_model(find_by_index(repo, 0)), "BMW") == 0);
	assert(update_model(repo, 0, "Mercedes") == false);
	destroy_repo(repo);
}

static void test_update_category() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	assert(update_category(repo, 1, "Suv") == true);
	assert(strcmp(get_category(find_by_index(repo, 0)), "Suv") == 0);
	assert(update_category(repo, 0, "Sport") == false);
	destroy_repo(repo);
}

static void test_update_is_rented() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	assert(update_is_rented(repo, 1, true) == true);
	assert(get_is_rented(find_by_index(repo, 0)) == true);
	assert(update_is_rented(repo, 1, false) == true);
	assert(get_is_rented(find_by_index(repo, 0)) == false);
	assert(update_is_rented(repo, 0, false) == false);
	destroy_repo(repo);
}


/*
* Testeaza service.h
*/
static void test_service_add_car() {
	Repo* repo = create_repo();
	assert(service_add_car(repo, "AB-12-CD", "Audi", "Mini") == true);
	assert(get_size(repo) == 1);
	assert(strcmp(get_license(find_by_index(repo, 0)), "AB-12-CD") == 0);
	assert(strcmp(get_model(find_by_index(repo, 0)), "Audi") == 0);
	assert(strcmp(get_category(find_by_index(repo, 0)), "Mini") == 0);
	assert(service_add_car(repo, "BC-34-DE", "BMW", "Suvito") == false);
	destroy_repo(repo);
}

static void test_service_update_license() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	assert(service_update_license(repo, 1, "BC-34-DE") == true);
	assert(strcmp(get_license(find_by_index(repo, 0)), "BC-34-DE") == 0);
	assert(service_update_license(repo, 0, "CD-56-EF") == false);
	destroy_repo(repo);
}

static void test_service_update_model() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	assert(service_update_model(repo, 1, "BMW") == true);
	assert(strcmp(get_model(find_by_index(repo, 0)), "BMW") == 0);
	assert(service_update_model(repo, 0, "Mercedes") == false);
	destroy_repo(repo);
}

static void test_service_update_category() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	assert(service_update_category(repo, 1, "Suv") == true);
	assert(strcmp(get_category(find_by_index(repo, 0)), "Suv") == 0);
	assert(service_update_category(repo, 0, "Sport") == false);
	assert(service_update_category(repo, 1, "Spu") == false);
	destroy_repo(repo);
}

static void test_service_update_is_rented() {
	Repo* repo = create_repo();
	Car car1 = create_car("AB-12-CD", "Audi", "Mini");
	repo_add_car(repo, &car1);
	assert(service_update_is_rented(repo, 1, true) == true);
	assert(get_is_rented(find_by_index(repo, 0)) == true);
	assert(service_update_is_rented(repo, 1, false) == true);
	assert(get_is_rented(find_by_index(repo, 0)) == false);
	assert(service_update_is_rented(repo, 0, false) == false);
	destroy_repo(repo);
}

static void test_service_filter_by_model() {
	Repo* repo = create_repo();
	service_add_car(repo, "AB-12-CD", "Audi", "Mini");
	service_add_car(repo, "BC-34-DE", "Audi", "Suv");
	service_add_car(repo, "CD-56-EF", "Mercedes", "Sport");
	service_add_car(repo, "DE-78-FG", "BMW", "Suv");
	Repo* filtered = service_filter_by_model(repo, "Audi");
	assert(get_size(filtered) == 2);
	for (int i = 0; i < get_size(filtered); i++) {
		assert(strcmp(get_model(find_by_index(filtered, i)), "Audi") == 0);
	}
	destroy_repo(repo);
	free(filtered);
}

static void test_service_filter_by_category() {
	Repo* repo = create_repo();
	service_add_car(repo, "AB-12-CD", "Audi", "Mini");
	service_add_car(repo, "BC-34-DE", "Audi", "Suv");
	service_add_car(repo, "CD-56-EF", "Mercedes", "Sport");
	service_add_car(repo, "DE-78-FG", "BMW", "Suv");
	Repo *filtered = service_filter_by_category(repo, "Suv");
	assert(get_size(filtered) == 2);
	for (int i = 0; i < get_size(filtered); i++) {
		assert(strcmp(get_category(find_by_index(filtered, i)), "Suv") == 0);
	}
	destroy_repo(repo);
	free(filtered);
		
}

static void test_service_sort_asc_by_category() {
	Repo* repo = create_repo();
	service_add_car(repo, "AB-12-CD", "Audi", "Mini");
	service_add_car(repo, "BC-34-DE", "Audi", "Suv");
	service_add_car(repo, "CD-56-EF", "Mercedes", "Sport");
	service_add_car(repo, "DE-78-FG", "BMW", "Suv");
	Repo* sorted = service_sort(repo, sort_asc_by_category);
	assert(strcmp(get_category(find_by_index(sorted, 0)), "Mini") == 0);
	assert(strcmp(get_category(find_by_index(sorted, 1)), "Sport") == 0);
	assert(strcmp(get_category(find_by_index(sorted, 2)), "Suv") == 0);
	assert(strcmp(get_category(find_by_index(sorted, 3)), "Suv") == 0);
	destroy_repo(repo);
	free(sorted);
}

static void test_service_sort_desc_by_category() {
	Repo* repo = create_repo();
	service_add_car(repo, "AB-12-CD", "Audi", "Mini");
	service_add_car(repo, "BC-34-DE", "Audi", "Suv");
	service_add_car(repo, "CD-56-EF", "Mercedes", "Sport");
	service_add_car(repo, "DE-78-FG", "BMW", "Suv");
	Repo* sorted = service_sort(repo, sort_desc_by_category);
	assert(strcmp(get_category(find_by_index(sorted, 0)), "Suv") == 0);
	assert(strcmp(get_category(find_by_index(sorted, 1)), "Suv") == 0);
	assert(strcmp(get_category(find_by_index(sorted, 2)), "Sport") == 0);
	assert(strcmp(get_category(find_by_index(sorted, 3)), "Mini") == 0);
	destroy_repo(repo);
	free(sorted);
}

static void test_service_sort_asc_by_model() {
	Repo* repo = create_repo();
	service_add_car(repo, "AB-12-CD", "Audi", "Mini");
	service_add_car(repo, "BC-34-DE", "Audi", "Suv");
	service_add_car(repo, "CD-56-EF", "Mercedes", "Sport");
	service_add_car(repo, "DE-78-FG", "BMW", "Suv");
	Repo* sorted = service_sort(repo, sort_asc_by_model);
	assert(strcmp(get_model(find_by_index(sorted, 0)), "Audi") == 0);
	assert(strcmp(get_model(find_by_index(sorted, 1)), "Audi") == 0);
	assert(strcmp(get_model(find_by_index(sorted, 2)), "BMW") == 0);
	assert(strcmp(get_model(find_by_index(sorted, 3)), "Mercedes") == 0);
	destroy_repo(repo);
	free(sorted);
}

static void test_service_sort_desc_by_model() {
	Repo* repo = create_repo();
	service_add_car(repo, "AB-12-CD", "Audi", "Mini");
	service_add_car(repo, "BC-34-DE", "Audi", "Suv");
	service_add_car(repo, "CD-56-EF", "Mercedes", "Sport");
	service_add_car(repo, "DE-78-FG", "BMW", "Suv");
	Repo* sorted = service_sort(repo, sort_desc_by_model);
	assert(strcmp(get_model(find_by_index(sorted, 0)), "Mercedes") == 0);
	assert(strcmp(get_model(find_by_index(sorted, 1)), "BMW") == 0);
	assert(strcmp(get_model(find_by_index(sorted, 2)), "Audi") == 0);
	assert(strcmp(get_model(find_by_index(sorted, 3)), "Audi") == 0);
	destroy_repo(repo);
	free(sorted);
}


void run_tests() {
	test_create_car();
	test_find_by_id();
	test_find_by_index();
	test_validate_category();
	test_destroy_car();
	test_get_id();
	test_get_license();
	test_get_model();
	test_get_category();
	test_set_license();
	test_set_model();
	test_set_category();
	test_set_is_rented();
	test_get_is_rented();
	test_create_repo();
	test_repo_add_car();
	test_destroy_repo();
	test_get_size();
	test_update_license();
	test_update_model();
	test_update_category();
	test_update_is_rented();
	test_service_add_car();
	test_service_update_license();
	test_service_update_model();
	test_service_update_category();
	test_service_update_is_rented();
	test_service_filter_by_model();
	test_service_filter_by_category();
	test_service_sort_asc_by_category();
	test_service_sort_desc_by_category();
	test_service_sort_asc_by_model();
	test_service_sort_desc_by_model();
	printf("Teste au rulat cu succes!\n");
}