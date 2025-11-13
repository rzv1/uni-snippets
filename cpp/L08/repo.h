#pragma once
#include "domain.h"
#include <vector>
#include <random>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class RepoException {
private:
	string message;
public:
	RepoException(const string& message) : message{ message } {}
	~RepoException() = default;
	const string& get_message() const {
		return message;
	}
	bool operator==(const string& ot) const {
		return message == ot;
	}
};

class Repo {
public:
	virtual void add(Carte& c) = 0;
	virtual void remove(int id) = 0;
	virtual void update_title(int id, const string& title) = 0;
	virtual void update_author(int id, const string& author) = 0;
	virtual void update_genre(int id, const string& genre) = 0;
	virtual void update_year(int id, const int year) = 0;
	virtual Carte& get_by_id(int id) = 0;
	virtual const vector<Carte>& get_all() = 0;
};

class RepoProbabilitate : public Repo {
private:
	unordered_map<int, Carte> carti;
	float probabilitate;
	float random;
	int next_id;
	string filepath;
	vector<Carte> books;
	void gen_random() {
		std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		std::random_device rd;
		std::mt19937 gen(rd());
		random = dist(gen);
	}
	void verify() {
		gen_random();
		if (random < probabilitate)
			throw RepoException("Eroare!\n");
	}
public:
	RepoProbabilitate(float prob, const string& filepath) : probabilitate{ prob }, filepath{ filepath }, random{ 0 }, next_id{ 1 } {
		read_file();
	};
	
	inline void add(Carte& c) override {
		verify();
		c.set_id(next_id);
		carti[next_id++] = c;
		write_file();
	}

	inline Carte& get_by_id(int id){
		auto it = carti.find(id);
		if (it == carti.end())
			throw RepoException("Cartea cu id-ul dat nu exista!");
		return it->second;
	}

	inline void remove(int id) override {
		verify();
		Carte c = get_by_id(id);
		carti.erase(id);
		write_file();
	}

	inline const vector<Carte>& get_all() override {
		verify();
		books.clear();
		for (const auto& pair : carti)
			books.push_back(pair.second);
		return books;
	}

	inline void update_title(int id, const string& title) override {
		verify();
		Carte& c = get_by_id(id);
		c.set_title(title);
		write_file();
	}
	inline void update_author(int id, const string& author) override {
		verify();
		Carte& c = get_by_id(id);
		c.validate_author(author);
		c.set_author(author);
		write_file();
	}
	inline void update_genre(int id, const string& genre) override {
		verify();
		Carte& c = get_by_id(id);
		c.validate_genre(genre);
		c.set_genre(genre);
		write_file();
	}
	inline void update_year(int id, const int year) override {
		verify();
		Carte& c = get_by_id(id);
		c.set_year(year);
		write_file();
	}

	void write_file();
	void read_file();
};

class RepoNormal : public Repo {
private:
	vector<Carte> books;
	int next_id;
	string filepath;
public:
	RepoNormal(string filepath) : next_id{ 1 }, filepath{ filepath } {
		read_file();
	}

	~RepoNormal() = default;

	void add(Carte& book) override;

	void remove(int id) override;

	void update_title(int id, const string& title) override;
	void update_author(int id, const string& author) override;
	void update_genre(int id, const string& genre) override;
	void update_year(int id, const int year) override;

	void read_file();
	void write_file();

	Carte& get_by_id(int id) override;

	const vector<Carte>& get_all() override {
		return books;
	}

	size_t get_size() const {
		return books.size();
	}
};