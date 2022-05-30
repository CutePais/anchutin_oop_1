#pragma once
#include <iostream>
#include <exception>
#include <cstdint>
#include <cstdlib>

template <typename T> class Container {
private:
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
	Node* head;
	Node* tail;
	uint16_t cont_size;

public:
	Container() {
		cont_size = 0;
		head = nullptr;
		tail = nullptr;
	}

	~Container() {
		clear();
	}

	Container(const Container& other) {
		cont_size = 0;
		head = nullptr;
		tail = nullptr;

		Node* k = other.head;

		while (k != nullptr) {
			push_back(k->data);
			k = k->next;
		}
	}

	void push_front(const T& data) {
		Node* k = new Node;
		k->data = data;
		k->prev = nullptr;
		k->next = head;

		if (!is_empty()) {
			head->prev = k;
		}
		else {
			tail = k;
		}
		head = k;

		++cont_size;
	}

	void push_back(const T& data) {
		Node* k = new Node;
		k->data = data;
		k->prev = tail;
		k->next = nullptr;

		if (!is_empty()) {
			tail->next = k;
		}
		else {
			head = k;
		}
		tail = k;

		++cont_size;
	}

	void pop_first() {
		if (cont_size == 0) {
			throw std::exception("Ща бы с пустого контейнера удолять в 2к22...");
		}
		if (cont_size == 1) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			Node* k = head->next;
			k->prev = nullptr;
			head = k;
		}
		--cont_size;
	}

	void pop_last() {
		if (cont_size == 0) {
			throw std::exception("Ща бы с пустого контейнера удолять в 2к22...");
		}
		if (cont_size == 1) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			Node* k = tail->prev;
			k->next = nullptr;
			tail = k;
		}
		--cont_size;
	}

	T& show_first() const {
		if (cont_size == 0) {
			throw std::exception("Не покажусь. Я пустой:(");
		}
		else return head->data;
	}

	T& show_last() const {
		if (cont_size == 0) {
			throw std::exception("Не покажусь. Я пустой:(");
		}
		else return tail->data;
	}

	class Enumerator {
	private:
		Node* list;
	public:
		Enumerator(Node* k) : list(k) {
		};

		Node* get_list() {
			return list;
		}

		Enumerator operator++(int) {
			if (list != nullptr) {
				list = list->next;
				return *this;
			}
		}

		Enumerator operator--(int) {
			if (list != nullptr) {
				list = list->prev;
				return *this;
			}
		}

		bool operator==(const Enumerator& other) {
			return list == other.list;
		}

		bool operator!=(const Enumerator& other) {
			return list != other.list;
		}
	};

	Enumerator begin() {
		return Enumerator(head);
	}
	Enumerator end() {
		return Enumerator(tail);
	}

	int16_t size() const {
		return cont_size;
	}

	bool is_empty() const {
		return cont_size == 0;
	}

	void swap(Container& other) {
		uint16_t cont2size = other.cont_size;
		other.cont_size = cont_size;
		cont_size = cont2size;
		Node* k = other.head;
		other.head = head;
		head = k;
		k = other.tail;
		other.tail = tail;
		tail = k;
	}

	void reverse() {
		Node* k = head;
		Node* prev = nullptr;
		Node* next = nullptr;
		while (k != NULL) {
			next = k->next;
			k->prev = prev;
			prev = k;
			k = next;
		}
		head = prev;
	}

	void clear() {
		while (head != NULL) {
			Node* k = head;
			head = head->next;
			delete k;
		}
		cont_size = 0;
		head = nullptr;
		tail = nullptr;
	}

};
