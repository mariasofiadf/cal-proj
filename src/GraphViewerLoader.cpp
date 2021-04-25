//
// Created by pedro on 25/04/21.
//

#include "GraphViewerLoader.h"

GraphViewerLoader::GraphViewerLoader(GraphViewer &gv) : gv(&gv){

}

void GraphViewerLoader::loadGraph(Graph graph) {
    // Set coordinates of window center
    gv->setCenter(sf::Vector2f(300, 300));
    int Vid = 0;
    for( auto vertex : graph.getVertexSet()){
        // Create node
        GraphViewer::Node &node0 = gv->addNode(Vid++, sf::Vector2f(vertex->getPoint().getPosition().getX(), vertex->getPoint().getPosition().getY()));
        switch (vertex->getPoint().getPointType()) {
            case COFFE:
                node0.setColor(GraphViewer::BLACK);
                break;
            case GAS:
                node0.setColor(GraphViewer::YELLOW);
                break;
            case STORE:
                node0.setColor(GraphViewer::RED);
                break;
            default:
                node0.setColor(GraphViewer::WHITE);
                break;
        }
    }

}
