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
    Graph myGraph;

    Point P0(0,0,300);
    Point P1(1,300,400);
    Point P2(2,300,100);
    Point P3(3,400,100);
    Point P4(4,500,0);
    Point P5(5,500,400);
    Point P6(6,525,225);
    Point P7(7,725,200);
    Point P8(8,800,400);
    myGraph.addVertex(P0);
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);
    myGraph.addVertex(P4);
    myGraph.addVertex(P5);
    myGraph.addVertex(P6);
    myGraph.addVertex(P7);
    myGraph.addVertex(P8);

    myGraph.addBidirectionalEdge(P1,P5,P1.getPosition().distance(P5.getPosition()));

    myGraph.addBidirectionalEdge(P5,P6,P5.getPosition().distance(P6.getPosition()));

    myGraph.addBidirectionalEdge(P6,P7,P6.getPosition().distance(P7.getPosition()));

    myGraph.addBidirectionalEdge(P7,P8,P7.getPosition().distance(P8.getPosition()));

    myGraph.addBidirectionalEdge(P6,P3,P6.getPosition().distance(P3.getPosition()));

    myGraph.addBidirectionalEdge(P3,P4,P3.getPosition().distance(P4.getPosition()));

    myGraph.addBidirectionalEdge(P3,P2,P3.getPosition().distance(P2.getPosition()));

    myGraph.addBidirectionalEdge(P2,P0,P2.getPosition().distance(P0.getPosition()));

    myGraph.matchingOdd();

    GraphViewer graphViewer;
    GraphViewerLoader graphViewerLoader(&graphViewer);
    graphViewerLoader.loadGraph(myGraph);

    graphViewer.setCenter(sf::Vector2f(WIDTH/2, HEIGHT/2));

    graphViewer.createWindow(WIDTH, HEIGHT);
    // Join viewer thread (blocks till window closed)
    graphViewer.join();

}

TEST(Graph, getOddVertices) {

    Graph myGraph;

    Point P0(0,0,300);
    Point P1(1,300,400);
    Point P2(2,300,100);
    Point P3(3,400,100);
    Point P4(4,500,0);
    Point P5(5,500,400);
    Point P6(6,525,225);
    Point P7(7,725,200);
    Point P8(8,800,400);
    myGraph.addVertex(P0);
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);
    myGraph.addVertex(P4);
    myGraph.addVertex(P5);
    myGraph.addVertex(P6);
    myGraph.addVertex(P7);
    myGraph.addVertex(P8);

    myGraph.addBidirectionalEdge(P1,P5,P1.getPosition().distance(P5.getPosition()));

    myGraph.addBidirectionalEdge(P5,P6,P5.getPosition().distance(P6.getPosition()));

    myGraph.addBidirectionalEdge(P6,P7,P6.getPosition().distance(P7.getPosition()));

    myGraph.addBidirectionalEdge(P7,P8,P7.getPosition().distance(P8.getPosition()));

    myGraph.addBidirectionalEdge(P6,P3,P6.getPosition().distance(P3.getPosition()));

    myGraph.addBidirectionalEdge(P3,P4,P3.getPosition().distance(P4.getPosition()));

    myGraph.addBidirectionalEdge(P3,P2,P3.getPosition().distance(P2.getPosition()));

    myGraph.addBidirectionalEdge(P2,P0,P2.getPosition().distance(P0.getPosition()));

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
