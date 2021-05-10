//
// Created by pedro on 25/04/21.
//

#include "GraphGenerator.h"

Graph getTestGraph2(){
    Graph myGraph;

    Point P0(0,1, 1);
    PointPark PK1(1,3, 1, 3.0);
    PointGas G2(2,0, 3);
    PointCoffe C3(3,2, 4);
    PointPark PK4(4,3, 5, 2.0);
    PointPark PK5(5,0, 6, 2.6);
    Point P6(6,1, 7);

    myGraph.addVertex(P0);
    myGraph.addVertex(PK1);
    myGraph.addVertex(G2);
    myGraph.addVertex(C3);
    myGraph.addVertex(PK4);
    myGraph.addVertex(PK5);
    myGraph.addVertex(P6);

    myGraph.addBidirectionalEdge(P0, PK1, 1);
    myGraph.addBidirectionalEdge(P0, G2, 5);
    myGraph.addBidirectionalEdge(PK1, C3, 2);
    myGraph.addBidirectionalEdge(G2, C3, 1);
    myGraph.addBidirectionalEdge(G2, PK5, 1);
    myGraph.addBidirectionalEdge(C3, PK4, 1);
    myGraph.addBidirectionalEdge(C3, PK5, 5);
    myGraph.addBidirectionalEdge(PK4, P6, 3);
    myGraph.addBidirectionalEdge(PK5, P6, 1);

    return myGraph;
}