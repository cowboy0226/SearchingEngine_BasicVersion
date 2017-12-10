#pragma once

#include "list.h"
#include "flexibleArr.h"
#include "term.h"

unsigned int Hash(const char* str);

unsigned int Hash(const FlexibleArr<char> wrd);

template<class K,class T>
class HashTable {
private:
	int size;
	int num;
	int MaxColi;
	List<T>* table;
public:
	HashTable(int s) :size(s),num(0),MaxColi(0) { table = new List<T>[size]; }
	~HashTable() { delete[] table; }
	int getNum() { return num; }
	int getMaxColi() { return MaxColi; }
	T& getValue(const K& key,T& val);
	T* getValue(const K& key);
	bool addValue(const K& key,const T& val);
	T* operator[](const K& key);
	const T* operator[](const K& key) const;
};

template<class K, class T>
T& HashTable<K, T>::getValue(const K& key, T& val) {
	unsigned int index = Hash(key) % size;
	Node<T>* temp = table[index].getFirst();
	int cnt = 0;
	while (temp != nullptr) {
		++cnt;
		if (temp->item == key) {
			return temp->item;
		}
		temp = temp->next;
	}
	table[index].add(val);
	++num;
	++cnt;
	MaxColi = cnt > MaxColi ? cnt : MaxColi;
	return table[index].getLast()->item;
}

template<class K,class T>
T* HashTable<K, T>::getValue(const K& key) {
	unsigned int index = Hash(key) % size;
	Node<T>* temp = table[index].getFirst();
	int cnt = 0;
	while (temp != nullptr) {
		++cnt;
		if (temp->item == key) {
			return &(temp->item);
		}
		temp = temp->next;
	}
	return nullptr;
}

template<class K, class T>
bool HashTable<K, T>::addValue(const K& key, const T& val) {
	unsigned int index = Hash(key) % size;
	Node<T>* temp = table[index].getFirst();
	while (temp != nullptr) {
		if (temp->item == key) {
			temp->item = val;
			return true;
		}
		temp = temp->next;
	}
	table[index].add(val);
	++num;
	return true;
}

template<class K, class T>
T* HashTable<K, T>::operator[](const K& key) {
	unsigned int index = Hash(key) % size;
	Node<T>* temp = table[index].getFirst();
	while (temp != nullptr) {
		if (temp->item == key) return &(temp->item);
		temp = temp->next;
	}
	return nullptr;
}
