//
// Created by pedro on 08/04/21.
//

#include <gtest/gtest.h>
#include "TestAux.h"
#include "../src/Graph.h"

TEST(Map, test_dijkstra_super_simple) {
    Graph myGraph;

    Point P1(0,0, "P1");
    Point P2(0,0, "P2");
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addBidirectionalEdge(P1, P2, 1);

    myGraph.dijkstraShortestPath(P1);

    checkAllPaths(myGraph, "P1<-|P2<-P1|");
    checkSinglePath(myGraph.getPath(P1, P2), "P1 P2 ");

    myGraph.dijkstraShortestPath(P2);

    checkAllPaths(myGraph, "P1<-P2|P2<-|");
    checkSinglePath(myGraph.getPath(P2, P1), "P2 P1 ");
}