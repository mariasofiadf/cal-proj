//
// Created by pedro on 25/04/21.
//

#include <gtest/gtest.h>
//#include "../src/Graph.h"
#include "../src/GraphViewerLoader.h"
#include "GraphGenerator.h"

TEST(GraphViewerLoaderTest, load){
    GraphViewer gv;
    // Set coordinates of window center
    gv.setCenter(sf::Vector2f(300, 300));

    GraphViewerLoader gvl(gv);

    Graph g = getTestGraph2();

    gvl.loadGraph(g);

    gv.createWindow(600, 600);
    // Join viewer thread (blocks till window closed)
    gv.join();
}