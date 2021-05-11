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

Edge *Vertex::addEdge(Edge *e) {
    adj.push_back(e);
    return e;
}


bool Graph::removeEdge(const Vertex &sourc, const Vertex &dest) {
    Vertex *sourc_vert = findVertex(sourc.getPoint());
    Vertex *dest_vert = findVertex(dest.getPoint());
    if(sourc_vert && dest_vert){
        dest_vert->removeEdgeFromTo(sourc_vert,dest_vert);
        return sourc_vert->removeEdgeTo(dest_vert);
    }
    return false;
}


bool Vertex::removeEdgeTo(Vertex *d) {
    for(auto it = adj.begin(); it != adj.end(); ++it){
        if((*it)->dest == d){
            adj.erase(it);
            return true;
        }
    }
    return false;
}

bool Vertex::removeEdgeFromTo(Vertex *s, Vertex *d) {
    for(auto it = adj.begin(); it != adj.end(); ++it){
        if((*it)->dest == d && (*it)->orig == s){
            adj.erase(it);
            return true;
        }
    }
    return false;
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
    Edge *e = new Edge(v1, v2, w);
    v2->addEdge(e);
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

/**************** Euler Circuit  ***************/

void Graph::DFS(Vertex * v)
{
    // Mark the current node as visited and print it
    v->DFS_visited = true;


    // Recur for all the vertices adjacent to
    // this vertex
    for (auto i = v->getAdj().begin(); i != v->getAdj().end(); ++i)
        if (!((*i)->getDest()->DFS_visited))
            DFS((*i)->getDest());
}


bool Graph::disconnects(Graph mod , Edge * aresta) {
    bool res = true;
    mod.removeEdge(*(aresta->getOrig()),*(aresta->getDest()));
    mod.DFS(*(mod.getVertexSet().begin()));
    for(auto element : mod.vertexSet) {
        if (!(element->DFS_visited)) {res = false;}
    }
    for(auto element : mod.vertexSet) { //reseting DFS values for entire graph
        element->DFS_visited = false;
    }
    return !res;
}

std::vector<Point> Graph::getEuler(const Point &origin) {
    std::vector<Point> res;
    Point origvertex = origin;
    Graph mod;
    mod = *this;

    while (mod.getVertexSet().size() > 2) {
        auto ponto = mod.findVertex(origvertex);
        Edge *aresta = ponto->getAdj()[0];

        if (!disconnects(mod, aresta)) {
            res.push_back(aresta->getDest()->getPoint());
            printf("added %s", res.end());
            mod.removeEdge(*aresta->getOrig(), *aresta->getDest());
            std::vector<Vertex *> vetor2;
            for(Vertex * vertice2 : mod.getVertexSet()) {
                if (vertice2->getAdj().size() == 0) {
                    vetor2.push_back(vertice2);
                }
            }
            for (auto elim : vetor2) {
                for (auto it = mod.getVertexSet().begin();it != mod.getVertexSet().end(); it++) {
                    if (elim == (*it)) {mod.getVertexSet().erase(it);}
                }
            }

            origvertex = aresta->getDest()->getPoint();
        }
    }
    return res;
}