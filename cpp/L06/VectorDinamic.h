#pragma once
#include <initializer_list>
using std::initializer_list;
template <typename T>

class IteratorVectorDinamic;

template <typename T>
class VectorDinamic {
private:
	size_t size;
	size_t capacity;
	T* elements;
	void resize() {
		capacity *= 2;
		T* new_elements = new T[capacity];
		for (size_t i = 0; i < size; i++) {
			new_elements[i] = elements[i];
		}
		delete[] elements;
		elements = new_elements;
	}
public:
	VectorDinamic() : size(0), capacity(2) {
		elements = new T[capacity];
	}
	//Constructor care initializiaza vectorul cu o lista de elemente
	VectorDinamic(initializer_list<T> initList) {
		size = initList.size();
		capacity = size * 2;
		elements = new T[capacity];
		int i = 0;
		for (const auto& element : initList) {
			elements[i++] = element;
		}
	}
	VectorDinamic(const VectorDinamic& other) : size(other.size), capacity(other.capacity) {
		elements = new T[capacity];
		if (other.size <= capacity)
			for (size_t i = 0; i < other.size; i++) {
				elements[i] = other.elements[i];
			}
	}
	VectorDinamic& operator=(const VectorDinamic& other) {
		if (this != &other) {
			delete[] elements;
			size = other.size;
			capacity = other.capacity;
			elements = new T[capacity];
			for (int i = 0; i < size; i++) {
				elements[i] = other.elements[i];
			}
		}
		return *this;
	}
	~VectorDinamic() {
		delete[] elements;
	}
	void push_back(const T& element) {
		if (size == capacity) {
			resize();
		}
		elements[size++] = element;
	}
	T& operator[](size_t index) noexcept {
		return elements[index];
	}
	T& operator[](size_t index) const noexcept {
		return elements[index];
	}
	size_t get_size() const noexcept {
		return size;
	}
	bool empty() const noexcept {
		return size == 0;
	}
	void remove(size_t index) {
		for (size_t i = index; i < size - 1; i++) {
			elements[i] = elements[i + 1];
		}
		size--;
	}
	friend class IteratorVectorDinamic<T>;
	IteratorVectorDinamic<T> begin() {
		return IteratorVectorDinamic<T>(*this);
	}
	IteratorVectorDinamic<T> end() {
		return IteratorVectorDinamic<T>(*this, size);
	}
	IteratorVectorDinamic<T> begin() const{
		return IteratorVectorDinamic<T>(*this);
	}
	IteratorVectorDinamic<T> end() const{
		return IteratorVectorDinamic<T>(*this, size);
	}
};

template <typename T>

class IteratorVectorDinamic {
private:
	const VectorDinamic<T>& v;
	size_t pos;
public:
	IteratorVectorDinamic(const VectorDinamic<T>& v) : v{ v }, pos{ 0 } {}
	IteratorVectorDinamic(const VectorDinamic<T>& v, size_t pos) : v{ v }, pos{ pos } {}
	bool valid() const {
		return pos < v.get_size();
	}
	T& element() const {
		return v[pos];
	}
	void urmator() {
		pos++;
	}
	IteratorVectorDinamic<T>& operator++() {
		urmator();
		return *this;
	}
	T& operator*() const{
		return element();
	}
	bool operator==(const IteratorVectorDinamic<T>& ot) const{
		return pos == ot.pos;
	}
	bool operator!=(const IteratorVectorDinamic<T>& ot) const{
		return !(*this == ot);
	}
};