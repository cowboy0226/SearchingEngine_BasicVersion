#pragma once
#include<iostream>
#include<istream>
#include<ostream>
#include<cctype>
#include<fstream>

using std::ifstream;
using std::ostream;
using std::istream;

template<class T>
class FlexibleArr {
private:
	int size;
	int length;
	T* arr;
	void resize(int cur, int after);
public:
	FlexibleArr(int s = 5) :size(s), length(0) { arr = new T[size]; };
	FlexibleArr(const FlexibleArr<T>& fa);
	FlexibleArr(const T* ptr, int len);
	~FlexibleArr();
	void clear() { length = 0; }
	bool add(const T& item);
	int getLength() const { return length; }
	T& operator[](int index) { return arr[index]; }
	const T& operator[](int index) const { return arr[index]; }
	FlexibleArr<T>& operator=(const FlexibleArr<T>& fa);
	bool operator==(const FlexibleArr<T>& fa) const;
	bool operator!=(const FlexibleArr<T>& fa)const;
	friend ostream& operator<<(ostream& os, const FlexibleArr<T>& fa);
	friend istream& operator>>(istream& is, FlexibleArr<T>& fa);
};


template<class T>
void FlexibleArr<T>::resize(int cur, int after) {
	T* temp = arr;
	arr = new T[after];
	for (int i = 0; i < cur; ++i)arr[i] = temp[i];
	delete[] temp;
}

template<class T>
FlexibleArr<T>::FlexibleArr(const FlexibleArr<T>& fa) {
	size = fa.size;
	length = fa.length;
	arr = new T[size];
	for (int i = 0; i < length; ++i) arr[i] = fa.arr[i];
}

template<class T>
FlexibleArr<T>::FlexibleArr(const T* ptr, int len) {
	size = len;
	length = len;
	arr = new T[size];
	for (int i = 0; i < len; ++i) arr[i] = ptr[i];
}

template<class T>
FlexibleArr<T>::~FlexibleArr() {
	size = 0;
	length = 0;
	delete[] arr;
}

template<class T>
bool FlexibleArr<T>::add(const T& item) {
	if (length >= size) {
		resize(size, (2 * size));
		size *= 2;
	}

	arr[length] = item;
	length++;
	// cout << "size: " << size << endl;
	return true;
}

template<class T>
FlexibleArr<T>& FlexibleArr<T>::operator=(const FlexibleArr<T>& fa) {
	if (this == &fa) return *this;
	delete[] arr;
	length = fa.length;
	size = fa.size;
	arr = new T[size];
	for (int i = 0; i < length; ++i) arr[i] = fa.arr[i];
	return *this;
}

template<class T>
bool FlexibleArr<T>::operator==(const FlexibleArr<T>& fa)const {
	if (this == &fa) return true;
	if (length != fa.length) return false;
	for (int i = 0; i < length; ++i) if (arr[i] != fa.arr[i]) return false;
	return true;
}

template<class T>
bool FlexibleArr<T>::operator!=(const FlexibleArr<T>& fa)const {
	return !(*this == fa);
}

