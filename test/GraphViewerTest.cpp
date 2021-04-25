//
// Created by pedro on 25/04/21.
//

#include <gtest/gtest.h>
#include <graphviewer.h>

#define WIDTH 1920
#define HEIGHT 1080

//Here, one of the nodes should be blinking
//This is a proof of concept for future Algorithm Visualization
TEST(GraphViewer, blinkingNode){
    GraphViewer gv;
    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(WIDTH/2, HEIGHT/2));

    GraphViewer::Node &node0 = gv.addNode(0, sf::Vector2f(200,300));
    node0.setSize(node0.getSize()*4);
    node0.setColor(GraphViewer::GREEN);
    GraphViewer::Node &node1 = gv.addNode(1, sf::Vector2f(400,500));
    node1.setSize(node1.getSize()*4);

    GraphViewer::Edge &edge0 = gv.addEdge(0, node0, node1);
    gv.createWindow(WIDTH, HEIGHT);
    // Join viewer thread (blocks till window closed)
    for(int i = 0; i < 10; i++){
        if(i%2)
            node0.setColor(GraphViewer::BLUE);
        else
            node0.setColor(GraphViewer::RED);
        sleep(1);
    }
    gv.join();
}