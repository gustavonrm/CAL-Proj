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

using namespace std;

template<class T> class Edge;
template<class T> class Graph;
template<class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template<class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
	vector<Edge<T>> getAdj() const; //used on graphviewer api
	friend class Graph<T> ;
};

template<class T>
Vertex<T>::Vertex(T in) :
		info(in) {
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
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
vector<Edge<T>> Vertex<T>::getAdj() const {
	return this->adj;
}

/********************** Edge  ****************************/

template<class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	Vertex<T> * getDest() const; //used on graph viewer api
	friend class Graph<T> ;
	friend class Vertex<T> ;
};

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w) :
		dest(d), weight(w) {
}

template<class T>
Vertex<T> * Edge<T>::getDest() const {
	return this->dest;
}

/*************************** Graph  **************************/

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	Graph<T> dijkstraShortestPath(const T &s);
	Vertex<T> * initSingleSource(const T &orig);
	bool relax(Vertex<T> *v, Vertex<T> *w, double weight);

};

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
		if (v->info == in)
			return v;
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

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2, w);
	return true;
}

/////////////////////////ALGORITHMS//////////////////////

/**
* Initializes single-source shortest path data (path, dist).
* Receives the content of the source vertex and returns a pointer to the source vertex.
* Used by all single-source shortest path algorithms.
*/
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
/**
* Analyzes an edge in single-source shortest path algorithm.
* Returns true if the target vertex was relaxed (dist, path).
* Used by all single-source shortest path algorithms.
*/
template<class T>
bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
if (v->dist + weight < w->dist) {
w->dist = v->dist + weight;
w->path = v;
return true;
}
else
return false;
}

template<class T>
Graph<T> Graph<T>::dijkstraShortestPath(const T &origin) { //adapted from classes
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

#endif
