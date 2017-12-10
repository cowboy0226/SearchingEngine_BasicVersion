#pragma once

#include"list.h"

template<class E>
struct Edge {
	int vertexID;
	E value;
	Edge(int id=-1):vertexID(id){}
	Edge(int id,E val):vertexID(id),value(val){}
};

template<class T, class E>
struct Vertex {
	int id;
	T data;
	List<Edge<E> > dst;
	List<Edge<E> > src;
	Vertex(int i=-1):id(i){}
	Vertex(int i, T d): id(i),data(d){}
};

template<class T, class E>
class Graph {
private:
	int sizeOfVertex;
	int sizeOfEdge;
	int Max;
	Vertex<T, E>* vertexSet;
	void resize(int cur, int after);
public:
	Graph(int m = 5) : sizeOfVertex(0), sizeOfEdge(),Max(m) { vertexSet = new Vertex<T,E>[Max]; }
	~Graph() { delete [] vertexSet; }
	int getSizeOfVertex() { return sizeOfVertex; }
	int getSizeOfEdge() { return sizeOfEdge; }
	int getInDegree(int id) { return vertexSet[id].src.getLength(); }
	int getOutDegree(int id) { return vertexSet[id].dst.getLength(); }
	bool addVertex(int id,T value);
	bool addEdge(int srcID, int dstID, E val);
	bool removeVertex(int id);
	bool removeEdge(int srcID, int dstID);
	int getNeighbor(int id);
	int getNext(int id, int cur);
};

template<class E>
bool operator ==(const Edge<E>& e1, const Edge<E>& e2) {
	return e1.vertexID == e2.vertexID;
}

template<class E>
bool operator != (const Edge<E>& e1, const Edge<E>& e2) {
	return !(e1 == e2);
}

template<class T, class E>
void Graph<T, E>::resize(int cur, int after) {
	Vertex<T, E>* temp = vertexSet;
	vertexSet = new Vertex<T, E>[after];
	for (int i = 0; i < cur; ++i) vertexSet[i] = temp[i];
	delete[] temp;
}

template<class T, class E>
bool Graph<T, E>::addVertex(int id, T value) {
	if (id >= Max) {
		resize(Max, 2 * Max);
		Max *= 2;
	}
	if (vertexSet[id].id != -1) return false;
	vertexSet[id].id = id;
	vertexSet[id].data = value;
	++sizeOfVertex;
	return true;
}

template<class T, class E>
bool Graph<T, E>::addEdge(int srcID, int dstID, E val) {
	if (srcID < 0 || srcID >= Max) return false;
	if (dstID < 0 || dstID >= Max) return false;
	if (vertexSet[srcID].id == -1 || vertexSet[dstID].id == -1) return false;
	vertexSet[srcID].dst.add(Edge<E>(dstID, val));
	vertexSet[dstID].src.add(Edge<E>(srcID, val));
	++sizeOfEdge;
	return true;
}

template<class T, class E>
bool Graph<T, E>::removeVertex(int id) {
	if (id < 0 || id >= Max) return false;
	if (vertexSet[id].id == -1) return false;
	while (vertexSet[id].dst.getFirst() != nullptr) {
		Edge<E> temp = vertexSet[id].dst.getFirst()->item;
		int dstid = temp.vertexID;
		temp.vertexID = id;
		vertexSet[dstid].src.removeItem(temp);
		vertexSet[id].dst.delItem(1);
		--sizeOfEdge;
	}
	while (vertexSet[id].src.getFirst() != nullptr) {
		Edge<E> temp = vertexSet[id].src.getFirst()->item;
		int srcid = temp.vertexID;
		temp.vertexID = id;
		vertexSet[srcid].dst.removeItem(temp);
		vertexSet[id].src.delItem(1);
		--sizeOfEdge;
	}
	vertexSet[id].id = -1;
	// vertexSet[id] = vertexSet[sizeOfVertex];
	--sizeOfVertex;
	return true;
}

template<class T, class E>
bool Graph<T, E>::removeEdge(int srcID, int dstID) {
	if (srcID < 0 || srcID >= Max) return false;
	if (dstID < 0 || dstID >= Max) return false;
	if (vertexSet[srcID].id == -1 || vertexSet[dstID].id == -1) return false;
	Edge<E> temp1(dstID);
	Edge<E> temp2(srcID);
	if (vertexSet[srcID].dst.removeItem(temp1) && vertexSet[dstID].src.removeItem(temp2)) {
		--sizeOfEdge;
		return true;
	}
	else return false;
}

template<class T, class E>
int Graph<T, E>::getNeighbor(int id) {
	if (id < 0 || id >= Max) return -1;
	if (vertexSet[id].id == -1) return -1;
	if (vertexSet[id].dst.getLength() == 0) return -1;
	Edge<E> temp = vertexSet[id].dst.getFirst()->item;
	return temp.vertexID;
}

template<class T, class E>
int Graph<T, E>::getNext(int id, int cur) {
	if (id < 0 || id >= Max) return -1;
	if (vertexSet[id].id == -1) return -1;
	if (cur >= vertexSet[id].dst.getLength()) return -1;
	Node<Edge<E> >* temp = vertexSet[id].dst.getFirst();
	for (int i = 0; i < cur; ++i) temp = temp->next;
	Edge<E> tempe = temp->item;
	return tempe.vertexID;
}



