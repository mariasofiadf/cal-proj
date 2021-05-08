//
// Created by pedro on 26/04/21.
//

#include <gtest/gtest.h>
#include "../src/GraphLoader.h"

TEST(GraphLoaderTest, load){
    Graph graph;
    GraphLoader graphLoader(&graph);
    graphLoader.loadMap("../data/porto/porto_full_nodes_latlng.txt", "../data/porto/porto_full_edges.txt");
    ASSERT_EQ(graph.getVertexSet().size(), 53621);
    Point expected(-8.589981,41.142501,33920);
    Vertex * found = graph.findVertex(expected);

    ASSERT_EQ(found->getPoint().getPosition().getX(), expected.getPosition().getX());
    ASSERT_EQ(found->getPoint().getPosition().getY(), expected.getPosition().getY());
}