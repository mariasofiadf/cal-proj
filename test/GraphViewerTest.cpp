//
// Created by pedro on 25/04/21.
//

#include <gtest/gtest.h>
#include <graphviewer.h>

#define WIDTH 1920
#define HEIGHT 1080
TEST(GraphViewer, NodesAndEdges){
    GraphViewer gv;
    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(WIDTH/2, HEIGHT/2));

    GraphViewer::Node &node0 = gv.addNode(0, sf::Vector2f(200,300));
    node0.setColor(GraphViewer::GREEN);
    GraphViewer::Node &node1 = gv.addNode(1, sf::Vector2f(400,500));

    GraphViewer::Edge &edge0 = gv.addEdge(0, node0, node1);
    gv.createWindow(WIDTH, HEIGHT);
    // Join viewer thread (blocks till window closed)
    gv.join();
}