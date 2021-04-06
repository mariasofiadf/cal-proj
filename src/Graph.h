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
#include <algorithm>
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...
    Vertex<T> * initSingleSource(const T &origin);
    bool relax(Vertex<T> *v, Vertex<T> *w, double weight);
    bool allVisited();

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
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
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {

    typename std::vector<Vertex<T>*>::iterator itVertex;
    typename std::vector<Edge<T>>::iterator it;
    typename std::queue<Vertex<T>*> queue;
    for(itVertex = vertexSet.begin(); itVertex != vertexSet.end(); itVertex++)
    {
        (*itVertex)->visited= false;
        (*itVertex)->path = NULL;
    }
    Vertex<T>* v = findVertex(orig);
    queue.push(v);
    v->dist = 0;
    v->visited = true;
    while(!queue.empty()){
        v = queue.front(); queue.pop();
        for(it = v->adj.begin(); it != v->adj.end(); it++)
        {
            if(!it->dest->visited){
                it->dest->visited = true;
                queue.push(it->dest);
                it->dest->dist = v->dist + 1;
                it->dest->path = v;
            }
        }
    }
    // TODO implement this
}

template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
    for(auto v : vertexSet) {
        v->dist = INF;
        v->path = NULL;
    }
    auto s = findVertex(origin);
    s->dist = 0;
    return s;
}

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
void Graph<T>::dijkstraShortestPath(const T &origin) {
    auto s = initSingleSource(origin);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        for(auto e : v->adj) {
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

/*
template<class T>
bool Graph<T>::allVisited(){
    typename std::vector<Vertex<T>*>::const_iterator itVertex;
    for(itVertex = vertexSet.begin(); itVertex != vertexSet.end(); itVertex++){
        if(!(*itVertex)->visited)
            return false;
    }
    return true;
}
template<class T>

void Graph<T>::dijkstraShortestPath(const T &origin) {
    typename std::vector<Vertex<T>*>::iterator itV;
    typename std::vector<Edge<T>>::iterator itE;
    MutablePriorityQueue<Vertex<T>> priorityQueue;
    for(itV = vertexSet.begin(); itV != vertexSet.end(); itV++)
    {
        (*itV)->dist = INF;
        (*itV)->path = NULL;
        (*itV)->visited = false;
    }
    Vertex<T>* v = findVertex(origin);
    v->dist = 0;
    v->queueIndex = 0;
    priorityQueue.insert(v);
    double oldDist;
    while(!priorityQueue.empty()) {
        v = priorityQueue.extractMin();

        v->visited = true;
        for (itE = v->adj.begin(); itE != v->adj.end(); itE++) {
            Vertex<T>* vv = (Vertex<T>*) malloc(sizeof (Vertex<T>));
            vv = findVertex(itE->dest->getInfo());
            if (vv->getDist() > v->getDist() + itE->weight) {
                oldDist = vv->getDist();
                vv->dist = v->getDist() + itE->weight;
                vv->path = v;
                vv->queueIndex = priorityQueue.getSize() - 1;
                if (oldDist == INF) {
                    priorityQueue.insert(vv);
                } else
                    priorityQueue.decreaseKey(vv);
            }
        }
    }
    // TODO implement this
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    typename std::vector<Vertex<T>*>::iterator itVertex;
    typename std::vector<Edge<T>>::iterator it;
    MutablePriorityQueue<Vertex<T>> priorityQueue;
    for(itVertex = vertexSet.begin(); itVertex != vertexSet.end(); itVertex++)
    {
        (*itVertex)->dist = (double) 99999;
        (*itVertex)->path = NULL;
    }
    Vertex<T>* v = findVertex(origin);
    v->dist = 0;
    priorityQueue.insert(v);
    double oldDist;
    while(!priorityQueue.empty()){
        v = priorityQueue.extractMin(); priorityQueue.remove(v);
        for(it = v->adj.begin(); it != v->adj.end(); it++)
        {
            if(it->dest->getDist() > v->getDist() + it->weight){
                oldDist = it->dest->getDist();
                it->dest->dist = v->getDist() + it->weight;
                it->dest->path = v;
                if(oldDist == (double) 99999){
                    priorityQueue.insert(it->dest);
                }
                else
                    priorityQueue.decreaseKey(it->dest);
            }
        }
    }
    // TODO implement this
}*/


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    // TODO implement this
}

template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    for (auto v = findVertex(dest); v != NULL; v = v-> path) {
        res.push_back(v->info);
        if (v->info == origin)
            break;
    }
    reverse(res.begin(), res.end());
    return res;
}

/*
template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    T t;
    Vertex<T>* v = findVertex(dest);
    res.push_back(dest);
    do{
        t = v->path->info;
        res.push_back(t);
        v = v->path;
    }while(v->info != origin);

    reverse(res.begin(), res.end());
    // TODO implement this
    return res;
}*/


/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    // TODO implement this
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    std::vector<T> res;
    // TODO implement this
    return res;
}


#endif /* GRAPH_H_ */
