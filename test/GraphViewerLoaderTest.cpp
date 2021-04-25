//
// Created by pedro on 25/04/21.
//

#include <gtest/gtest.h>
//#include "../src/Graph.h"
#include "../src/GraphViewerLoader.h"
#include "GraphGenerator.h"

#define WIDTH 1920
#define HEIGHT 1080

TEST(GraphViewerLoaderTest, load){
    GraphViewer gv;
    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(WIDTH/2, HEIGHT/2));

    GraphViewerLoader gvl(&gv);

    Graph g = getTestGraph2();

    gvl.loadGraph(g);

    gv.createWindow(WIDTH, HEIGHT);
    // Join viewer thread (blocks till window closed)
    gv.join();
}