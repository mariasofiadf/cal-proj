//
// Created by pedro on 25/04/21.
//

#include <gtest/gtest.h>
//#include "../src/Graph.h"
#include "../src/GraphViewerLoader.h"
#include "GraphGenerator.h"
#include "../src/GraphLoader.h"

#define WIDTH 1920
#define HEIGHT 1080
/*

TEST(GraphViewerLoaderTest, load){
    GraphViewer gv;
    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(WIDTH/2, HEIGHT/2));

    GraphViewerLoader gvl(&gv);

    Graph g;

    GraphLoader graphLoader(&g);

    graphLoader.loadMap("../data/porto/porto_full_nodes_xy.txt", "../data/porto/porto_full_edges.txt");

    gvl.loadGraph(g);

    g.dijkstraShortestPath(Point(0,0,1));

    gvl.colorPath(g,Point(0,0,1), Point(0,0,20000));

    g.getPath(Point(0,0,1), Point(0,0, 20000));



    gv.createWindow(WIDTH, HEIGHT);
    // Join viewer thread (blocks till window closed)
    gv.join();
}*/
