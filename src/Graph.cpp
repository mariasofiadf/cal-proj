//
// Created by pedro on 25/04/21.
//

#include "Graph.h"


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


const Point &Vertex::getInfo() const {
    return info;
}

bool Vertex::isMarked() const {
    return marked;
}

void Vertex::setViewerIndex(int viewerIndex) {
    Vertex::viewerIndex = viewerIndex;
}

int Vertex::getViewerIndex() const {
    return viewerIndex;
}

const vector<Edge *> &Vertex::getAdj() const {
    return adj;
}


std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}


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
bool Graph::addVertex(Point &in) {
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


unsigned int Graph::primAlgorithm() {
    if(vertexSet[0] == NULL) return 0;
    for(auto v: vertexSet){
        v->visited = false;
        v->dist = INF;
        v->path = NULL;
    }
    vertexSet[0]->dist = 0;
    MutablePriorityQueue<Vertex> queue;
    queue.insert(vertexSet[0]);
    while(!queue.empty()) {
        Vertex *vertex = queue.extractMin();
        vertex->visited=true;
        for(Edge * edge:vertex->adj){
            if(!edge->dest->visited) {
                if (edge->dest->dist > edge->weight) {
                    double dist = edge->dest->dist;
                    edge->dest->dist = edge->weight;
                    edge->dest->path = vertex;
                    if (dist == INF) {
                        queue.insert(edge->dest);
                    } else
                        queue.decreaseKey(edge->dest);
                }
            }
        }
    }

    unsigned int total = 0;
    for(auto v: vertexSet) {
        if(v->visited)
            total+=v->dist;
    }
    return total;
}


vector<Vertex*> Graph::getOddVertices(){
    vector<Vertex*> res;
    for(auto v : vertexSet){
        if((v->getAdj().size() % 2)!=0)
            res.push_back(v);
    }
    return res;
}
void Graph::matchingOdd(){
    return;
}