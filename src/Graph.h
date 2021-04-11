/*
 * Graph.h.
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include "MutablePriorityQueue.h"

#include "Point.h"

class Edge;
class Graph;
class Vertex;

#define INF std::numeric_limits<double>::max()

template<typename Base, typename T>
inline bool instanceof(const T*) {
    return is_base_of<Base, T>::value;
}

/************************* Vertex  **************************/

class Vertex {
	Point info;                 // contents
	std::vector<Edge *> adj;  // outgoing edges
	double dist = 0;
	Vertex *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue
    bool marked;
	Edge * addEdge(Vertex *dest, double w);
public:
	Vertex(Point in);
	bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
	Point getPoint() const;
	double getDist() const;
    const Point &getInfo() const;
    Vertex *getPath() const;

    bool isMarked() const;

    friend class Graph;
	friend class MutablePriorityQueue<Vertex>;
};

class Edge {
    Vertex *orig; 		    // Fp07
    Vertex * dest;           // destination vertex
    double weight;              // edge weight
    bool selected = false;      // Fp07
    Edge *reverse = nullptr; // Fp07
public:
    Edge(Vertex *o, Vertex *d, double w);
    friend class Graph;
    friend class Vertex;

    double getWeight() const;
    Vertex *getOrig() const;
    Vertex *getDest() const;
};

Vertex::Vertex(Point in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */

Edge *Vertex::addEdge(Vertex *d, double w) {
	Edge *e = new Edge(this, d, w);
	adj.push_back(e);
	return e;
}

bool Vertex::operator<(Vertex & vertex) const {
	return this->dist < vertex.dist;
}

Point Vertex::getPoint() const {
	return this->info;
}

double Vertex::getDist() const {
	return this->dist;
}

Vertex *Vertex::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/




Edge::Edge(Vertex *o, Vertex *d, double w): orig(o), dest(d), weight(w) {}

double Edge::getWeight() const {
	return weight;
}

Vertex *Edge::getOrig() const {
	return orig;
}

Vertex *Edge::getDest() const {
	return dest;
}

/*************************** Graph  **************************/

class Graph {
    std::vector<Vertex *> vertexSet;    // vertex set

public:
    ~Graph();
	Vertex *findVertex(const Point &in) const;
	bool addVertex(const Point &in);
	bool addEdge(const Point &sourc, const Point &dest, double w);
	bool addBidirectionalEdge(const Point &sourc, const Point &dest, double w);
    std::vector<Vertex *> getVertexSet() const;

	// Fp07 - minimum spanning tree
    Vertex * initSingleSource(const Point &origin);
    bool relax(Vertex *v, Vertex *w, double weight);
    void dijkstraShortestPath(const Point &origin);
    std::vector<Point> getPath(const Point &origin, const Point &dest) const;
    //Functions for ModifiedDiskstra's
    void markPossibleParks(Point &source);
};

const Point &Vertex::getInfo() const {
    return info;
}

bool Vertex::isMarked() const {
    return marked;
}


std::vector<Vertex *> Graph::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const Point &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return nullptr;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const Point &in) {
	if (findVertex(in) != nullptr)
		return false;
	vertexSet.push_back(new Vertex(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const Point &sourc, const Point &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == nullptr || v2 == nullptr)
		return false;
	v1->addEdge(v2, w);
	return true;
}

bool Graph::addBidirectionalEdge(const Point &sourc, const Point &dest, double w) {
	//TODO
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->reverse = e2;
    e2->reverse = e1;
    return true;
}

Graph::~Graph() {

}

Vertex * Graph::initSingleSource(const Point &origin) {
    for(auto v : vertexSet) {
        v->dist = INF;
        v->path = NULL;
    }
    auto s = findVertex(origin);
    s->dist = 0;
    return s;
}


bool Graph::relax(Vertex *v, Vertex *w, double weight) {
    if (v->dist + weight < w->dist) {
        w->dist = v->dist + weight;
        w->path = v;
        return true;
    }
    else
        return false;
}

void Graph::dijkstraShortestPath(const Point &origin) {
    auto s = initSingleSource(origin);
    MutablePriorityQueue<Vertex> q;
    q.insert(s);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        for(auto e : v->adj) {
            auto oldDist = e->dest->dist;
            if (relax(v, e->dest, e->weight)) {
                if (oldDist == INF)
                    q.insert(e->dest);
                else
                    q.decreaseKey(e->dest);
            }
        }
    }
}


/**************** Minimum Spanning Tree  ***************/

#include <iostream>


std::vector<Point> Graph::getPath(const Point &origin, const Point &dest) const{
    std::vector<Point> res;
    for (auto v = findVertex(dest); v != NULL; v = v-> path) {
        res.push_back(v->info);
        if (v->info == origin)
            break;
    }
    reverse(res.begin(), res.end());
    return res;
}

void Graph::markPossibleParks(Point &source) {

    double maxDist = 1000;
    typename std::vector<Vertex *>::iterator it;

    for(it = vertexSet.begin(); it != vertexSet.end(); it++)
        (*it)->marked = false;

    for(it = vertexSet.begin(); it != vertexSet.end(); it++)
    {
        bool validDist = source.getPosition().distance((*it)->getPoint().getPosition()) < maxDist;
        auto point = (*it)->getPoint();
        enum pointType pointType = (*it)->getPoint().getPointType();
        bool isPark = (*it)->getPoint().getPointType() == PARK;
        if(validDist && isPark)
            (*it)->marked = true;
    }
}


#endif /* GRAPH_H_ */
