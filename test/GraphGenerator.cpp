//
// Created by pedro on 25/04/21.
//

#include "GraphGenerator.h"

Graph getTestGraph2(){
    Graph myGraph;

    Point P1(0,1, "P1");
    PointPark PK2(2,3, "PK2", 3.0);
    PointGas G3(2,0, "P3");
    PointCoffe C4(3,2, "C4");
    PointPark PK5(4,3, "PK5", 2.0);
    PointPark PK6(4,0, "PK6", 2.6);
    Point P7(5,1, "P7");

    myGraph.addVertex(P1);
    myGraph.addVertex(PK2);
    myGraph.addVertex(G3);
    myGraph.addVertex(C4);
    myGraph.addVertex(PK5);
    myGraph.addVertex(PK6);
    myGraph.addVertex(P7);

    myGraph.addBidirectionalEdge(P1, PK2, 1);
    myGraph.addBidirectionalEdge(P1, G3, 5);
    myGraph.addBidirectionalEdge(PK2, C4, 2);
    myGraph.addBidirectionalEdge(G3, C4, 1);
    myGraph.addBidirectionalEdge(G3, PK6, 1);
    myGraph.addBidirectionalEdge(C4, PK5, 1);
    myGraph.addBidirectionalEdge(C4, PK6, 5);
    myGraph.addBidirectionalEdge(PK5, P7, 3);
    myGraph.addBidirectionalEdge(PK6, P7, 1);

    return myGraph;
}