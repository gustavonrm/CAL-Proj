/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>

#include "MutablePriorityQueue.h"
#include "Item.h"

using namespace std;

template<class T> class Edge;
template<class T> class Graph;
template<class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/**
 *Class adapted from pratical classes, with some methods added,
 *Class algorithms used were also adapted in exception to some, explained in further detail on doc
 *
 *
 */

/************************* Vertex  **************************/

template<class T>
class Vertex {
	int index;
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	bool visited1;    		//used in bidirectional
	bool visited2;
	bool discovered;
	double dist = 0;
	double dist1 = 0; //used in bidirectional
	double dist2 = 0;
	Vertex<T> *path = NULL;
	Vertex<T> *path1 = NULL; //used in bidirectional
	Vertex<T> *path2 = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(Vertex<T> *dest, double w, int eId);

public:
	Vertex(T in);
	Vertex(T in, int index);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
	Vertex *getPath1() const;
	Vertex *getPath2() const;
	vector<Edge<T>> getAdj() const; //used on graphviewer api
	void setAdj(vector<Edge<T>> edges);
	friend class Graph<T> ;
	friend class MutablePriorityQueue<Vertex<T>> ;
};

template<class T>
void Vertex<T>::setAdj(vector<Edge<T>> edges) {
	this->adj = edges;
}

template<class T>
Vertex<T>::Vertex(T in) :
		info(in) {
}
template<class T>
Vertex<T>::Vertex(T in, int index) :
		info(in) {
	this->index = index;
}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w, int eId) {
	adj.push_back(Edge<T>(d, w, eId));
}

template<class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template<class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template<class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template<class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}
template<class T>
Vertex<T> *Vertex<T>::getPath1() const {
	return this->path;
}
template<class T>
Vertex<T> *Vertex<T>::getPath2() const {
	return this->path;
}
template<class T>
vector<Edge<T>> Vertex<T>::getAdj() const {
	return this->adj;
}

/********************** Edge  ****************************/

template<class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	int eId;
	Edge(Vertex<T> *d, double w, int eId);
	Vertex<T> * getDest() const; //used on graph viewer api
	friend class Graph<T> ;
	friend class Vertex<T> ;
};

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w, int eId) :
		dest(d), weight(w), eId(eId) {
}

template<class T>
Vertex<T> * Edge<T>::getDest() const {
	return this->dest;
}

/*************************** Graph  **************************/

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
	void dfsVisit(Vertex<T> *v, vector<T> & res) const;
	bool dfsIsDAG(Vertex<T> *v) const;
	double ** W = nullptr; // dist
	int **P = nullptr; // path
	int findVertexIdx(const T &in) const;
public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addVertexNumerated(const T &in, int index); //to convert graph into matrix
	bool addEdge(const T &sourc, const T &dest, double w, int eId);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;
	bool isDAG() const;
	void dijkstraShortestPath(const T &s);
	void dijkstraBidirectionalPath(const T &origin, const T &dest);
	vector<Vertex<T>*> getPath(const T &origin, const T &dest) const;
	vector<Vertex<T>*> getPath1(const T &origin, const T &dest) const;
	vector<Vertex<T>*> getPath2(const T &origin, const T &dest) const;
	Vertex<T> * initSingleSource(const T &orig);
	bool relax(Vertex<T> *v, Vertex<T> *w, double weight);
	void removeEdge(int edgeId);
};

template<class T>
void Graph<T>::removeEdge(int edgeId) {
	vector<Edge<T>> edges;
	for (int j = 0; j < this->vertexSet.size(); j++) {
		edges = this->vertexSet.at(j)->getAdj();
		for (int i = 0; i < edges.size(); i++) {
			if (edges.at(i).eId == edgeId) {
				edges.erase(edges.begin() + i);
			}
		}
		this->vertexSet.at(j)->setAdj(edges);
	}
}

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template<class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in) {
			return v;
		}

	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template<class T>
bool Graph<T>::addVertex(const T &in) {
	if (findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}
template<class T>
bool Graph<T>::addVertexNumerated(const T &in, int index) {
	if (findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in, index));
	return true;
}
/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, int eId) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2, w, eId);
	return true;
}

/////////////////////////ALGORITHMS//////////////////////

/******************  isDAG  ********************/

template<class T>
bool Graph<T>::isDAG() const {
	for (auto v : vertexSet) {
		v->visited = false;
		v->processing = false;
	}
	for (auto v : vertexSet)
		if (!v->visited)
			if (!dfsIsDAG(v))
				return false;
	return true;
}
//aux
template<class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	v->visited = true;
	v->processing = true;
	for (auto & e : v->adj) {
		auto w = e.dest;
		if (w->processing)
			return false;
		if (!w->visited)
			if (!dfsIsDAG(w))
				return false;
	}
	v->processing = false;
	return true;
}

/**************SHORTEST PATH ALGO***********************/
//aux
template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
	for (auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findVertex(origin);
	s->dist = 0;
	return s;
}
//aux
template<class T>
bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	} else
		return false;
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) { //adapted from classes
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);
	while (!q.empty()) {
		auto v = q.extractMin();
		for (auto e : v->adj) {
			auto oldDist = e.dest->dist;
			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
				q.insert(e.dest);
				else
				q.decreaseKey(e.dest);
			}
		}
	}
}

template<class T>
void Graph<T>::dijkstraBidirectionalPath(const T &origin, const T &dest) {
	//reset everything
	for (auto v : vertexSet) {
		v->visited1 = false;
		v->visited2 = false;
		v->dist1 = 0;
		v->dist2 = 0;
		v->path1 = NULL;
		v->path1 = NULL;
	}
	MutablePriorityQueue<Vertex<T>> q1, q2;
	Vertex<T> *v1 = findVertex(origin);
	Vertex<T> *v2 = findVertex(dest);
	q1.insert(v1);
	q2.insert(v2);
	v1->visited = true;
	v2->visited = true;

	while (!q1.empty() || !q2.empty()) {
		v1 = q1.extractMin();
		v2 = q2.extractMin();
		if(v1->getInfo() == v2->getInfo()){
			break;
		}
		for (size_t i = 0; i < v1->adj.size() || i < v2->adj.size(); i++) {
			auto e1 = v1->getAdj().at(i);
			auto e2 = v2->getAdj().at(i);
			auto oldDist1 = e1.dest->dist;
			auto oldDist2 = e2.dest->dist;
			if (relax(v1, e1.dest, e1.weight)) {
				if (oldDist1 == INF)
				q1.insert(e1.dest);
				else
				q1.decreaseKey(e1.dest);
			}
			if (relax(v2, e2.dest, e2.weight)) {
				if (oldDist2 == INF)
				q2.insert(e2.dest);
				else
				q2.decreaseKey(e1.dest);
			}
		}
	}

}

template<class T>
vector<Vertex<T>*> Graph<T>::getPath(const T &origin, const T &dest) const {
	vector<Vertex<T>*> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF) { // missing or disconnected
		cout<<"missing or disconnected\n";
		return res;
	}
	for (; v != nullptr; v = v->path)
		res.push_back(v);
	reverse(res.begin(), res.end());
	for (auto r : res) {
		cout << r->getInfo().getId() << endl;
	}
	return res;
}
template<class T>
vector<Vertex<T>*> Graph<T>::getPath1(const T &origin, const T &dest) const {
	vector<Vertex<T>*> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist1 == INF) { // missing or disconnected
		cout<<"missing or disconnected\n";
		return res;
	}
	for (; v != nullptr; v = v->path1)
		res.push_back(v);
	reverse(res.begin(), res.end());
	for (auto r : res) {
		cout << r->getInfo().getId() << endl;
	}
	return res;
}
template<class T>
vector<Vertex<T>*> Graph<T>::getPath2(const T &origin, const T &dest) const {
	vector<Vertex<T>*> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist2 == INF) { // missing or disconnected
		cout<<"missing or disconnected\n";
		return res;
	}
	for (; v != nullptr; v = v->path2)
		res.push_back(v);
	reverse(res.begin(), res.end());
	for (auto r : res) {
		cout << r->getInfo().getId() << endl;
	}
	return res;
}

#endif
