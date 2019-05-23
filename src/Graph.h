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

/************************* Vertex  **************************/

template<class T>
class Vertex {
	int index;
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	bool discovered;
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	Vertex(T in,int index);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
	vector<Edge<T>> getAdj() const; //used on graphviewer api
	friend class Graph<T> ;
	friend class MutablePriorityQueue<Vertex<T>> ;
};

template<class T>
Vertex<T>::Vertex(T in) :
		info(in) {
}
template<class T>
Vertex<T>::Vertex(T in,int index):info(in) {
	this->index = index;
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
	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addVertexNumerated(const T &in,int index); //to convert graph into matrix
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	void dijkstraShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;
	Vertex<T> * initSingleSource(const T &orig);
	bool relax(Vertex<T> *v, Vertex<T> *w, double weight);
	vector<Vertex<T>*>TSP(Vertex<T> *origin);
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
bool Graph<T>::addVertexNumerated(const T &in,int index){
	if (findVertex(in) != NULL)
			return false;
		vertexSet.push_back(new Vertex<T>(in,index));
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
/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
	vector<T> res;
	for (auto v : vertexSet)
		v->visited = false;
	for (auto v : vertexSet)
	    if (! v->visited)
	    	dfsVisit(v, res);
	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	v->visited = true;
	res.push_back(v->info);
	for (auto & e : v->adj) {
		auto w = e.dest;
	    if ( ! w->visited)
	    	dfsVisit(w, res);
	}
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	vector<T> res;
	auto s = findVertex(source);
	if (s == NULL)
		return res;
	queue<Vertex<T> *> q;
	for (auto v : vertexSet)
		v->visited = false;
	q.push(s);
	s->visited = true;
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		res.push_back(v->info);
		for (auto & e : v->adj) {
			auto w = e.dest;
		    if ( ! w->visited ) {
				q.push(w);
				w->visited = true;
		    }
		}
	}
	return res;
}

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
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const {
	vector<T> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF) { // missing or disconnected
		cout<<"missing or disconnected\n";
		return res;
	}
	for (; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	for (auto r : res) {
		cout << r.getId() << endl;
	}
	return res;
}

template<class T>
vector<Vertex<T>*> Graph<T>::TSP(Vertex<T> *origin){
	vector<Vertex<T>*> res;
	vector<int> vertex_indexes;
	cout<<"ola"<<endl;
	//hamiltonian matrix
	/**
	 *quando uma edge é criada e lhe associado um indice por incremento a 0, esses indices vao ser usados para construir
	 * a matriz do grafo.assim quando o algoritmo é processado gerando os varios indices por ordemdo caminho, sao feitos
	 * os matches dos indices com o vertice respetivo e posteriormente desse vertice com as coordenadas do item
	 *
	 */
	int nodes = vertexSet.size();
	vector<double> v(nodes,0);
	vector<vector <double>> matrix;

	for(int i=0; i<nodes ;i++){
		matrix.push_back(v);
	}
	for(int i=0; i<nodes ;i++){
		for(auto e : vertexSet.at(i)->adj){
			matrix[i][e.dest->index]=e.weight;
		}
	}

	//TSP closest neighbour?


	return res;
}
/**
 * match final com ciclo incrmental a uma variavel dado match ao vertice na posiçºao do vetor
 * hamiltoniana usa incide do vetor vrtice e nao id
 *
 * O(n!)nem pensar
 *  https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/
 *
 *  https://www.sanfoundry.com/cpp-program-implement-nearest-neighbour-algorithm/
 *
 *  http://www.martinbroadhurst.com/nearest-neighbour-algorithm-for-tsp-in-c.html
 */


#endif
