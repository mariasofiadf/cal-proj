//
// Created by pedro on 26/04/21.
//

#include <gtest/gtest.h>
#include "../src/GraphLoader.h"

TEST(GraphLoaderTest, load){
    Graph graph;
    GraphLoader graphLoader(&graph);
    graphLoader.loadMap("../data/GridGraphs/4x4/nodes.txt", "../data/GridGraphs/4x4/edges.txt");
    ASSERT_EQ(graph.getVertexSet().size(), 25);
    Point expected(11, 300,150);
    Vertex * found = graph.findVertex(expected);

    ASSERT_EQ(found->getPoint().getPosition().getX(), expected.getPosition().getX());
    ASSERT_EQ(found->getPoint().getPosition().getY(), expected.getPosition().getY());
}