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
	std::vector<Edge *> adj;
public:
    const vector<Edge *> &getAdj() const;

private:
    // outgoing edges
	double dist = 0;
	Vertex *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue
	int viewerIndex = 0;
public:
    int getViewerIndex() const;

public:
    void setViewerIndex(int viewerIndex);

private:
    bool marked;
	Edge * addEdge(Vertex *dest, double w);
    Edge * addEdge(Edge * e);
public:
	Vertex(Point in);
	bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
	Point getPoint() const;
	double getDist() const;
    const Point &getInfo() const;
    Vertex *getPath() const;
    bool removeEdgeTo(Vertex *d);
    bool removeEdgeFromTo(Vertex *s, Vertex *d);
    bool DFS_visited = false;

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

/********************** Edge  ****************************/





/*************************** Graph  **************************/

class Graph {
    std::vector<Vertex *> vertexSet;    // vertex set

public:
    ~Graph();
	Vertex *findVertex(const Point &in) const;
	bool addVertex(const Point &in);
	bool addEdge(const Point &sourc, const Point &dest, double w);
    bool removeEdge(const Vertex &sourc, const Vertex &dest);
	bool addBidirectionalEdge(const Point &sourc, const Point &dest, double w);
    bool removeBidirectionalEdge(const Vertex &sourc, const Vertex &dest);
    bool disconnects(Edge aresta) ;
    std::vector<Point> handle_euler(std::vector<Point> res , Vertex * vertice, Edge *aresta);
    bool isConnected();
    void DFS(Vertex * v);
    std::vector<Vertex *> getVertexSet() const;

	// Fp07 - minimum spanning tree
    Vertex * initSingleSource(const Point &origin);
    bool relax(Vertex *v, Vertex *w, double weight);
    void dijkstraShortestPath(const Point &origin);
    std::vector<Point> getPath(const Point &origin, const Point &dest) const;
    //Functions for ModifiedDiskstra's
    void markPossibleParks(Point &source);

    vector<Point> getEuler(const Point &origin);

    void delete_lonely_points();

    bool removeVertex(const Point &in);
};


#endif /* GRAPH_H_ */
