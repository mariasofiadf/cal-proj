//
// Created by pedro on 25/04/21.
//

#include "GraphViewerLoader.h"
#define SCALE 10
GraphViewerLoader::GraphViewerLoader(GraphViewer *gv) : gv(gv){
}

void GraphViewerLoader::loadGraph(Graph graph) {
    // Set coordinates of window center
    vector<GraphViewer::Node> nodes;

    int Vid = 0;
    for( auto vertex : graph.getVertexSet()){
        // Create node
        vertex->setViewerIndex(Vid);
        GraphViewer::Node &node0 = gv->addNode(Vid++, sf::Vector2f((float) abs(vertex->getPoint().getPosition().getX()*SCALE), (float) abs(vertex->getPoint().getPosition().getY()*SCALE)));
        switch (vertex->getPoint().getPointType()) {
            case COFFE:
                node0.setOutlineColor(GraphViewer::GRAY);
                break;
            case GAS:
                node0.setOutlineColor(GraphViewer::YELLOW);
                break;
            case STORE:
                node0.setOutlineColor(GraphViewer::RED);
                break;
            case PARK:
                node0.setOutlineColor(GraphViewer::BLUE);
                break;
            default:
                node0.setOutlineColor(GraphViewer::BLACK);
                break;
        }
        node0.setColor(GraphViewer::BLACK);
        //node0.setLabel(to_string(vertex->getPoint().getId()));
        //node0.setSize(node0.getSize()*);
        nodes.push_back(node0);
    }
    int Eid=0;
    for(auto vertex : graph.getVertexSet()){
        for(auto edge : vertex->getAdj()){
            GraphViewer::Edge &edge0 = gv->addEdge(Eid++, nodes.at(vertex->getViewerIndex()), nodes.at(edge->getDest()->getViewerIndex()), GraphViewer::Edge::EdgeType::DIRECTED);
            edge0.setColor(GraphViewer::GRAY);
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
        GraphViewer::Node to = gv->getNode(Vto->getPoint().getId()-1);
        GraphViewer::Node from = gv->getNode(Vfrom->getPoint().getId()-1);
        //to.setColor(GraphViewer::GREEN);
        //vector<GraphViewer::Edge *> edges = gv->getEdges();
        for(int x = 0; x < gv->getEdges().size(); x++){
            GraphViewer::Edge e = gv->getEdge(x);
            if(e.getFrom()->getId() == from.getId() && e.getTo()->getId()==to.getId()) {
                e.setColor(GraphViewer::GREEN);
                from.setColor(GraphViewer::GREEN);
                to.setColor(GraphViewer::GREEN);
            }

        }

        Vto = Vfrom;
        Vfrom = Vfrom->getPath();
    } while(Vfrom != NULL);

    free(Vfrom);
    free(Vto);
}
