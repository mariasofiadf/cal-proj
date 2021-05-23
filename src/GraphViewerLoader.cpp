//
// Created by pedro on 25/04/21.
//

#include "GraphViewerLoader.h"
#define SCALE 20
GraphViewerLoader::GraphViewerLoader(GraphViewer *gv) : gv(gv){
}

void GraphViewerLoader::loadGraph(Graph graph, int scale, int thickness, int nodeSize) {
    // Set coordinates of window center
    vector<GraphViewer::Node> nodes;

    int Vid = 0;
    for( auto vertex : graph.getVertexSet()){
        // Create node
        vertex->setViewerIndex(Vid);
        GraphViewer::Node &node0 = gv->addNode(Vid++, sf::Vector2f((float) abs(vertex->getPoint().getPosition().getX()*scale), (float) abs(vertex->getPoint().getPosition().getY()*scale)));
        switch (vertex->getPoint().getPointType()) {
            case COFFE:
                node0.setColor(GraphViewer::GRAY);
                break;
            case GAS:
                node0.setColor(GraphViewer::YELLOW);
                break;
            case STORE:
                node0.setColor(GraphViewer::ORANGE);
                break;
            case PARK:
                node0.setColor(GraphViewer::BLUE);
                break;
            default:
                node0.setColor(GraphViewer::WHITE);
                break;
        }
        node0.setLabel(to_string(vertex->getPoint().getId()));
        node0.setSize(nodeSize);
        nodes.push_back(node0);
    }
    int Eid=0;
    for(auto vertex : graph.getVertexSet()){
        for(auto edge : vertex->getAdj()){
            if(edge->getOrig()->getPoint().getId()==vertex->getPoint().getId()){
                edge->setViewerIndex(Eid);
                GraphViewer::Edge &edge0 = gv->addEdge(Eid++, nodes.at(vertex->getViewerIndex()), nodes.at(edge->getDest()->getViewerIndex()), GraphViewer::Edge::EdgeType::DIRECTED);
                edge0.setColor(GraphViewer::BLACK);
                edge0.setThickness(thickness);
            }
        }
    }
}

void GraphViewerLoader::colorPath(Graph graph, Point start, Point end) {
    Vertex * Vend = graph.findVertex(end);
    if(!Vend)
        return;

    Vertex * Vto = graph.findVertex(end);
    Vertex * Vfrom = Vto->getPath();
    int i;
    do {
        GraphViewer::Node to = gv->getNode(Vto->getViewerIndex());
        GraphViewer::Node from = gv->getNode(Vfrom->getViewerIndex());
        from.setColor(GraphViewer::GREEN);
        to.setColor(GraphViewer::GREEN);
        /*for(auto edge : Vfrom->getAdj()){
            if(edge->getDest()->getPoint().getId() == Vto->getPoint().getId()){
                GraphViewer::Edge e = gv->getEdge(edge->getViewerIndex());
                if(e.getColor() != GraphViewer::GREEN)
                    e.setColor(GraphViewer::GREEN);
            }
        }
        for(auto edge : Vto->getAdj()){
            if(edge->getDest()->getPoint().getId() == Vfrom->getPoint().getId()){
                GraphViewer::Edge &e = gv->getEdge(edge->getViewerIndex());
                if(e.getColor() != GraphViewer::GREEN)
                    e.setColor(GraphViewer::GREEN);
            }
        }*/

        Vto = Vfrom;
        Vfrom = Vfrom->getPath();
    } while(Vfrom != NULL);

    free(Vfrom);
    free(Vto);
}

void GraphViewerLoader::enableAll() {
    for(auto n : gv->getNodes())
        if(!n->isEnabled())
            n->enable();
    for(auto e : gv->getEdges())
        if(!e->isEnabled())
            e->enable();
}


