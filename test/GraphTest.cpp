//
// Created by pedro on 08/04/21.
//

#include <gtest/gtest.h>
#include <graphviewer.h>
#include "TestAux.h"
#include "GraphGenerator.h"
#include "../src/GraphViewerLoader.h"
#include "../src/GraphLoader.h"

#define WIDTH 1920
#define HEIGHT 1080

TEST(Graph, dijkstra_4x4) {
    Graph myGraph;

    GraphLoader graphLoader(&myGraph);
    graphLoader.loadMap("../data/GridGraphs/4x4/nodes.txt", "../data/GridGraphs/4x4/edges.txt");
    Point P0(1,0,0);
    Point P7(18,0,0);

    myGraph.dijkstraShortestPath(P0);
    checkAllPaths(myGraph, "0<-|1<-|2<-1|3<-2|4<-3|5<-|6<-1|7<-2|8<-7|9<-8|10<-|11<-6|12<-7|13<-12|14<-13|15<-|16<-11|17<-12|18<-17|19<-18|20<-|21<-16|22<-17|23<-22|24<-23|");
    checkSinglePath(myGraph.getPath(P0, P7), "1 2 7 12 17 18 ");

}

TEST(Graph, matching) {
    Graph myGraph = getTestGraph();

    myGraph.matchingOdd();

    ASSERT_EQ(myGraph.getOddVertices().size(), 0);

    Point P0(0,0,300);
    Point P1(1,300,400);
    Vertex * V0 = myGraph.findVertex(P0);
    Vertex * V1 = myGraph.findVertex(P1);

    bool found = false;
    for(auto e : V0->getAdj()){
        if(e->getDest() == V1)
            found = true;
    }

    ASSERT_TRUE(found);

}

TEST(Graph, getOddVertices) {

    Graph myGraph = getTestGraph();

    vector<Vertex*> vec = myGraph.getOddVertices();

    ASSERT_TRUE(vec.size() == 6);
}

TEST(Graph, prim) {
    Graph myGraph = getTestGraph3();

    float cost = myGraph.primAlgorithm();
    float expectedCost = 10.4 + 11.2+17.5+15.8;
    EXPECT_EQ( expectedCost, cost);

    stringstream ss;
    for(const auto v : myGraph.getVertexSet()) {
        ss << v->getInfo() << "<-";
        if ( v->getPath() != nullptr )
            ss << v->getPath()->getInfo();
        ss << "|";
    }
    cout << ss.str() << endl;

    Point P1(1,0,0);
    Point P4(4,0,0);
    Point P5(5,0,0);

    checkSinglePath(myGraph.getPath(P1, P5), "1 3 2 5 ");
    checkSinglePath(myGraph.getPath(P1, P4), "1 3 4 ");

}
