#pragma once
#include "repo.h"
#include "domain.h"
#include "rentalcart.h"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include "DTO.h"
using std::string;
using std::vector;
using std::map;
using std::copy_if;
using std::unique_ptr;


class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() noexcept = default;
};

class UndoAdauga final : public ActiuneUndo {
	Repo& repo;
	int id;
public:
	UndoAdauga(Repo& r, int idCarteNoua) : repo{ r }, id{ idCarteNoua } {}
	void doUndo() override {
		repo.remove(id);
	}
};

class UndoSterge final : public ActiuneUndo {
	Repo& repo;
	Carte carteStearsa;
public:
	UndoSterge(Repo& r, const Carte& c) : repo{ r }, carteStearsa{ c } {}
	void doUndo() override {
		repo.add(carteStearsa);
	}
};

class UndoModifica final : public ActiuneUndo {
	Repo& repo;
	Carte carteVeche;
public:
	UndoModifica(Repo& r, const Carte& inainte) : repo{ r }, carteVeche{ inainte } {}
	void doUndo() override {
		repo.update_title(carteVeche.get_id(), carteVeche.get_title());
		repo.update_author(carteVeche.get_id(), carteVeche.get_author());
		repo.update_genre(carteVeche.get_id(), carteVeche.get_genre());
		repo.update_year(carteVeche.get_id(), carteVeche.get_year());
	}
};

class Service {
private:
	Repo& repo;
	Rentalcart& cart;
	map<string, DTO> type_pairs;
	vector<unique_ptr<ActiuneUndo>> undoActions;
public:
	Service(Repo& repo, Rentalcart& cart) : repo{ repo }, cart{ cart } {
		add_to_map();
	}
	Service(const Service&) = delete;
	Service& operator=(const Service&) = delete;

	void add(const string& title, const string& author, const string& genre, const int year);
	void remove(int id);
	void update_title(int id, const string& title);
	void update_author(int id, const string& author);
	void update_genre(int id, const string& genre);
	void update_year(int id, const int year);
	vector<Carte> filter_title(const string& title) const;
	vector<Carte> filter_year(const int year) const;
	vector<Carte> sort_title() const;
	vector<Carte> sort_author() const;
	vector<Carte> sort_year_and_genre() const;

	void undo();

	void add_to_map() {
		for (const auto& book : repo.get_all()) {
			string genre = book.get_genre();
			auto it = type_pairs.find(genre);
			if (it == type_pairs.end()) {
				type_pairs.insert({ genre, DTO(genre) });
			}
			else {
				it->second.increment();
			}
		}
	}

	void clear_map() {
		type_pairs.clear();
	}

	map<string, DTO> get_map() const {
		return type_pairs;
	}

	Rentalcart& get_cart() {
		return cart;
	}
	bool clear_cart();
	bool add_cart(string& title);
	bool generate_cart(int n);
	bool export_cart(string& filename);
	vector<Carte>& cart_get_all();

	const vector<Carte>& get_all() const {
		return repo.get_all();
	}
};
