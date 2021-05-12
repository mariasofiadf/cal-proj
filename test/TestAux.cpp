#include <gtest/gtest.h>

#include <random>
#include "TestAux.h"

/**
 * Auxiliary functions to tests...
 *
 */
Graph CreateTestGraph() {
    Graph myGraph;

    Point P1(0,0, "P1");
    Point P2(0,0, "P2");
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);

    myGraph.addBidirectionalEdge(P1, P2, 1);

    return myGraph;
}


