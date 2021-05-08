//
// Created by pedro on 08/04/21.
//

#include <gtest/gtest.h>
#include <graphviewer.h>
#include "TestAux.h"
#include "GraphGenerator.h"
#include "../src/GraphViewerLoader.h"

#define WIDTH 1920
#define HEIGHT 1080

TEST(Graph, dijkstraShortestPath_2PointsOnly) {
    Graph myGraph;

    Point P1(0,0, 1);
    Point P2(0,0, 2);
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

    TEST(Graph, dijkstraShortestPath_Simple) {
    Graph myGraph;

    Point P1(0,10, 1);
    Point P2(20,30,2);
    Point P3(20,0, 3);
    Point P4(30,20, 4);
    Point P5(40,30, 5);
    Point P6(40,0, 6);
    Point P7(50,10, 7);

    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);
    myGraph.addVertex(P4);
    myGraph.addVertex(P5);
    myGraph.addVertex(P6);
    myGraph.addVertex(P7);

    myGraph.addBidirectionalEdge(P1, P2, 1);
    myGraph.addBidirectionalEdge(P1, P3, 5);
    myGraph.addBidirectionalEdge(P2, P4, 2);
    myGraph.addBidirectionalEdge(P3, P4, 1);
    myGraph.addBidirectionalEdge(P3, P6, 1);
    myGraph.addBidirectionalEdge(P4, P5, 1);
    myGraph.addBidirectionalEdge(P4, P6, 5);
    myGraph.addBidirectionalEdge(P5, P7, 3);
    myGraph.addBidirectionalEdge(P6, P7, 1);

    myGraph.dijkstraShortestPath(P1);
    checkAllPaths(myGraph, "1<-|2<-1|3<-4|4<-2|5<-4|6<-3|7<-6|");
    checkSinglePath(myGraph.getPath(P1, P7), "1 2 4 3 6 7 ");

  /*  myGraph.dijkstraShortestPath(P4);
    checkAllPaths(myGraph, "1<-2|2<-4|3<-4|4<-|5<-4|6<-3|7<-6|");
    checkSinglePath(myGraph.getPath(P4, P1), "4 2 1 ");*/

    GraphViewer graphViewer;

    graphViewer.setCenter(sf::Vector2f(WIDTH/2, HEIGHT/2));

    GraphViewerLoader graphViewerLoader(&graphViewer);

    graphViewerLoader.loadGraph(myGraph);

    graphViewerLoader.colorPath(myGraph, P1, P7);

    graphViewer.createWindow(WIDTH, HEIGHT);
    // Join viewer thread (blocks till window closed)
    graphViewer.join();
}

TEST(Graph, dijkstraShortestPath_DifferentPointTypes) {
Graph myGraph = getTestGraph2();

myGraph.dijkstraShortestPath(Point(0,0, 1));
checkAllPaths(myGraph, "P1<-|PK2<-P1|G3<-C4|C4<-PK2|PK5<-C4|PK6<-G3|P7<-PK6|");
checkSinglePath(myGraph.getPath(Point(0,0, 1), Point(0,0, 7)), "P1 PK2 C4 G3 PK6 P7 ");

myGraph.dijkstraShortestPath(Point(0,0, 4));
checkAllPaths(myGraph, "P1<-PK2|PK2<-C4|G3<-C4|C4<-|PK5<-C4|PK6<-G3|P7<-PK6|");
checkSinglePath(myGraph.getPath(Point(0,0, 4), Point(0,0, 1)), "C4 PK2 P1 ");

}

TEST(Graph, markPossibleParks) {
    Graph myGraph;

    Point P1(0,50, 1);
    PointPark PK2(2,3, 2, 3.0);
    PointGas G3(2,0, 3);
    PointCoffe C4(3,2, 4);
    PointPark PK5(4,3, 5, 2.0);
    PointPark PK6(4000,0, 6, 2.6);
    Point P7(5,1, 7);

    myGraph.addVertex(P1);
    myGraph.addVertex(PK2);
    myGraph.addVertex(G3);
    myGraph.addVertex(C4);
    myGraph.addVertex(PK5);
    myGraph.addVertex(PK6);
    myGraph.addVertex(P7);

    myGraph.markPossibleParks(P1);

    Vertex* V = myGraph.findVertex(P1);
    EXPECT_EQ(V->isMarked(), false);

    V = myGraph.findVertex(G3);
    EXPECT_EQ(V->isMarked(), false);

    V = myGraph.findVertex(C4);
    EXPECT_EQ(V->isMarked(), false);

    V = myGraph.findVertex(PK5);
    EXPECT_EQ(V->isMarked(), true);

    V = myGraph.findVertex(PK6);
    EXPECT_EQ(V->isMarked(), false); //This Park is not marked because it's more than 1km away from P1

    V = myGraph.findVertex(P7);
    EXPECT_EQ(V->isMarked(), false);
}