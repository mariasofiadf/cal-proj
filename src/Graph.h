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
#include <stack>
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
    // outgoing edges
	double dist = 0;
	Vertex *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue
	int viewerIndex = 0;
    bool marked;
    Edge * addEdge(Vertex *dest, double w);
    Edge * addEdge(Edge * e);
public:
    int getViewerIndex() const;
    void setViewerIndex(int viewerIndex);
	Vertex(Point in);
	bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
	Point getPoint() const;
	double getDist() const;
    const Point &getInfo() const;
    Vertex *getPath() const;
    bool removeEdgeTo(Vertex *d);
    bool removeEdgeFromTo(Vertex *s, Vertex *d);
    bool DFS_visited = false;

    const vector<Edge *> &getAdj() const;


    bool isMarked() const;

    friend class Graph;
	friend class MutablePriorityQueue<Vertex>;

    bool visited;
};

class Edge {
    Vertex *orig; 		    // Fp07
    Vertex * dest;           // destination vertex
    double weight;              // edge weight
    bool selected = false;      // Fp07
    Edge *reverse = nullptr; // Fp07
    int viewerIndex = 0;
public:
    Edge(Vertex *o, Vertex *d, double w);
    friend class Graph;
    friend class Vertex;

    double getWeight() const;
    Vertex *getOrig() const;
    Vertex *getDest() const;

    int getViewerIndex() const;

    void setViewerIndex(int viewerIndex);
};

/********************** Edge  ****************************/





/*************************** Graph  **************************/

class Graph {
    std::vector<Vertex *> vertexSet;// vertex set
    vector<PointPark *> parkSet;

public:
    ~Graph();
	Vertex *findVertex(const Point &in) const;
	bool addVertex(Point &in);
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
    void markPossibleParks(Point *source);

    vector<Point> getEuler(const Point &origin);

    void delete_lonely_points();

    bool removeVertex(const Point &in);
    void matchingOdd();
    vector<Vertex*> getOddVertices();

    float primAlgorithm();

    float cutShort(vector<Point> *eulerPath);

    int numberofelements(vector<Point> res);
    Graph extractMSTfromPath();

    vector<vector<Vertex*>> getSCC();
    void fillOrder(Vertex * v, stack<Vertex*>&stack);
    void DFSUtil(Vertex * v, vector<Vertex*> &vector);
    Graph getTranspose();

    Point * getPark(int optimization, Point * dest ,Point * origin, int timeParked);
    void addPark(PointPark * park);

    Point * getParkByPrice(Point *dest, Point *orig, int timeParked);
    Point * getParkByDistance(Point * dest);

};


#endif /* GRAPH_H_ */
