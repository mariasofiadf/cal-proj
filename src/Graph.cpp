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

bool Graph::removeBidirectionalEdge(const Vertex &sourc, const Vertex &dest) {
    Vertex *sourc_vert = findVertex(sourc.getPoint());
    Vertex *dest_vert = findVertex(dest.getPoint());
    if(sourc_vert && dest_vert){
        dest_vert->removeEdgeFromTo(sourc_vert,dest_vert);
        dest_vert->removeEdgeFromTo(dest_vert,sourc_vert);
        sourc_vert->removeEdgeTo(sourc_vert);
        return sourc_vert->removeEdgeTo(dest_vert);
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
    auto e3 = v2->addEdge(e1);
    auto e4 = v1->addEdge(e2);
    e1->reverse = e2;
    e2->reverse = e1;
    e3->reverse = e4;
    e4->reverse = e3;
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

bool Graph::removeVertex(const Point &in) {
    if (findVertex(in) == nullptr)
        return false;
    vector<Vertex *>::iterator ite;
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getPoint().getId() == in.getId()) {
            ite = it;
        }
    }
    vertexSet.erase(ite);
    return true;
}


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


bool Graph::disconnects(Edge aresta) {
    bool res = true;
    Vertex * vertorig = aresta.getOrig();
    Vertex * vertdest = aresta.getDest();
    removeEdge(*(aresta.getOrig()),*(aresta.getDest()));
    removeEdge(*(aresta.getDest()),*(aresta.getOrig()));
    DFS(*(getVertexSet().begin()));
    for(auto element : vertexSet) {
        if (!(element->DFS_visited)) {res = false;}
    }
    for(auto element : vertexSet) { //reseting DFS values for entire graph
        element->DFS_visited = false;
    }
    addBidirectionalEdge(aresta.getOrig()->getPoint(),(aresta.getDest()->getPoint()),aresta.getWeight());
    return !res;
}

void Graph::delete_lonely_points() {
    vector<Vertex *>::iterator it;
    vector<Vertex *> vetorcopy = getVertexSet();
    for (it = vetorcopy.begin() ; it != vetorcopy.end(); it++) {

        if((*it)->getAdj().size() == 0) {
            break;
        }
    }
    if(it != vetorcopy.end()) {
        this->removeVertex((*it)->getPoint());
    }
}

std::vector<Point>  Graph::handle_euler(std::vector<Point> res , Vertex * vertice, Edge *aresta) {
    res.push_back(vertice->getPoint());
    this->removeBidirectionalEdge(*aresta->getOrig(), *aresta->getDest());
    this->delete_lonely_points();
    return res;

}

std::vector<Point> Graph::getEuler(const Point &origin) {
    std::vector<Point> res;
    Graph grafo = *this;
    Vertex* vertice = this->findVertex(origin);
    bool flag_entered_noBridge = false;

    while (true) {
        flag_entered_noBridge = false;

        for(Edge *aresta : vertice->getAdj()) {
            if(aresta->getOrig() == vertice) {
                Edge aresta1 = *aresta;
                if(!disconnects(aresta1)) {
                    res = this->handle_euler(res,vertice,aresta);
                    vertice = aresta->getDest();
                    flag_entered_noBridge = true;
                    break;
                }
            }
        }
        if(!flag_entered_noBridge) {
            for(Edge *aresta : vertice->getAdj()) {
                if(aresta->getOrig() == vertice) {
                    res = this->handle_euler(res,vertice,aresta);
                    vertice = aresta->getDest();
                    break;
                }
            }
        }
        if(vertice->getAdj().size() == 0) {
            res.push_back(vertice->getPoint());
            break;
        }

    }

    return res;
}

float Graph::primAlgorithm() {
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

    float total = 0;
    for(auto v: vertexSet) {
        if(v->visited)
            total+=v->dist;
    }
    return total;
}


vector<Vertex*> Graph::getOddVertices(){
    vector<Vertex*> res;
    for(auto v : vertexSet){
        if(((v->getAdj().size()/2) % 2)!=0)
            res.push_back(v);
    }
    return res;
}
void Graph::matchingOdd(){
    for(auto v: vertexSet){
        v->visited = false;
    }
    vector<Vertex*> oddSet = getOddVertices();
    Vertex * closest; double minDist = 9999999; double dist;
    for(vector<Vertex*>::iterator it = oddSet.begin(); it != oddSet.end(); it++){
        Vertex v1 = *(*it);
        if((*it)->visited) continue;
        minDist = 9999999;
        for(vector<Vertex*>::iterator it2 = oddSet.begin(); it2 != oddSet.end(); it2++)
        {
            if((*it) == (*it2)) continue;
            Vertex v2 = *(*it2);
            if((*it2)->visited) continue;
            dist = (*it)->getPoint().getPosition().distance((*it2)->getPoint().getPosition());
            if( dist < minDist){
                minDist = dist;
                closest = (*it2);
            }

        }
        addBidirectionalEdge((*it)->getPoint(),closest->getPoint(), minDist);
        (*it)->visited = true; closest->visited = true;
    }
    return;
}

float Graph::cutShort(vector<Point>* path) {
    float pathCost = 0;
    for(auto v: vertexSet)
        v->visited = false;

    Point root = path->front();
    Vertex * v = findVertex(root);
    bool add = true;
    for(vector<Point>::iterator it = path->begin()+1; it != path->end(); it++){
        if(!v->visited){
            pathCost +=  (*v).getAdj().front()->weight;
            v->visited = true;
        }else{
            it = path->erase(it);
        }
        v = findVertex(*it);
    }

    for(auto i: *path){
        cout << i.getId() << "|";
    }
    cout <<endl;
    return pathCost;
}
