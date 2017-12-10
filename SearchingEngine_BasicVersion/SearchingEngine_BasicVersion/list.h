#pragma once

template<class T>
struct Node{
	T item;
	Node<T>* next;
	Node(): next(nullptr) {}
	Node(T ii, Node* nn = nullptr): item(ii), next(nn) {}
};

template<class T>
class List {
private:
	Node<T>* first;
	Node<T>* last;
	int length;
public:
	List() :first(nullptr), last(nullptr), length(0) {}
	~List() { for (int i = 1; i <= length; ++i) delItem(i); }
	int getLength() { return length; }
	Node<T>* getFirst() { return first; }
	Node<T>* getLast() { return last; }
	bool isEmpty() { return length == 0; }
	bool add(const T& item);
	bool insert(int index, const T& item); // insert item just before index
	bool delItem(int index);
	bool removeItem(const T& val);
};

template<class T>
bool List<T>::add(const T& item) {
	if (length == 0) {
		first = new Node<T>(item);
		last = first;
	}
	else {
		Node<T>* newItem = new Node<T>(item);
		last->next = newItem;
		last = newItem;
	}
	++length;
	return true;
}

template<class T>
bool List<T>::insert(int index, const T& item) {
	if (index > length || index <= 0) return false;
	Node<T>* newItem = new Node<T>(item);
	if (index == 1) {
		newItem->next = first;
		first = newItem;
	}
	else {
		Node<T>* current = first;
		int i = 1;
		while (++i < index) current = current->next;
		newItem->next = current->next;
		current->next = newItem;
	}
	++length;
	return true;
}

template<class T>
bool List<T>::delItem(int index) {
	if (index > length || index <= 0) return false;
	if (index == 1) {
		Node<T>* temp = first;
		first = first->next;
		delete temp;
	}
	else {
		Node<T>* current = first;
		int i = 1;
		while (++i < index) current = current->next;
		Node<T>* temp = current->next;
		current->next = temp->next;
		delete temp;
		if (index == length) last = current;
	}
	--length;
	return true;
}

template<class T>
bool  List<T>::removeItem(const T& val) {
	if (length == 0) return false;
	Node<T>* cur = first;
	Node<T>* nxt = cur->next;
	if (first->item == val) {
		first = nxt;
		delete cur;
		--length;
		return true;
	}
	while (nxt->item != val && nxt != nullptr) {
		cur = nxt;
		nxt = nxt->next;
	}
	if (nxt == nullptr) return false;
	cur->next = nxt->next;
	if (nxt == last) last = cur;
	delete nxt;
	--length;
	return true;
}