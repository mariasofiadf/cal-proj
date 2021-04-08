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

TEST(Map, test_dijkstra_simple) {
Graph myGraph;

Point P1(0,1, "P1");
Point P2(2,3, "P2");
Point P3(2,0, "P3");
Point P4(3,2, "P4");
Point P5(4,3, "P5");
Point P6(4,0, "P6");
Point P7(5,1, "P7");

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

checkAllPaths(myGraph, "P1<-|P2<-P1|P3<-P4|P4<-P2|P5<-P4|P6<-P3|P7<-P6|");
checkSinglePath(myGraph.getPath(P1, P7), "P1 P2 P4 P3 P6 P7 ");


myGraph.dijkstraShortestPath(P4);
checkAllPaths(myGraph, "P1<-P2|P2<-P4|P3<-P4|P4<-|P5<-P4|P6<-P3|P7<-P6|");
checkSinglePath(myGraph.getPath(P4, P1), "P4 P2 P1 ");

}