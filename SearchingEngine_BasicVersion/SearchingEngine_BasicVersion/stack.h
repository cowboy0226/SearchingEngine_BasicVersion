#pragma once

template<class T>
class Stack {
private:
	int size;
	int num;
	T* arr;
	void resize(int cur, int after);
public:
	Stack():size(1),num(0),arr(new T[size]) {}
	~Stack() { delete[] arr; }
	bool isEmpty() { return num == 0; }
	int getNum() { return num; }
	void push(const T& item);
	bool pop(T& item);
	void clear();
};

template<class T>
void Stack<T>::resize(int cur, int after) {
	T* temp = arr;
	arr = new T[after];
	for (int i = 0; i < cur; ++i) arr[i] = temp[i];
	delete[] temp;
}

template<class T>
void Stack<T>::push(const T& item) {
	if (num >= size) {
		resize(size, 2 * size);
		size *= 2;
	}
	arr[num++] = item;
}

template<class T>
bool Stack<T>::pop(T& item) {
	if (num > 0) {
		item = arr[--num];
		return true;
	}
	else return false;
}

template<class T>
void Stack<T>::clear() {
	num = 0;
	size = 1;
	delete[] arr;
	arr = new T[size];
}