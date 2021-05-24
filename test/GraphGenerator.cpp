//
// Created by pedro on 25/04/21.
//

#include "GraphGenerator.h"

Graph getTestGraph(){
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

    return myGraph;
}

Graph getTestGraph2(){
    Graph myGraph;

    Point P0(0,1, 1);
    PointPark PK1(1,3, 1);
    PointGas G2(2,0, 3);
    PointCoffe C3(3,2, 4);
    PointPark PK4(4,3, 5);
    PointPark PK5(5,0, 6);
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

Graph getTestGraph3(){
    Graph myGraph;

    Point P1(1,0, 0);
    Point P2(2,0,0);
    Point P3(3,0, 0);
    Point P4(4,0,0);
    Point P5(5,0,0);
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);
    myGraph.addVertex(P4);
    myGraph.addVertex(P5);


    myGraph.addBidirectionalEdge(P1, P2, 13.9);
    myGraph.addBidirectionalEdge(P2, P3, 11.2);
    myGraph.addBidirectionalEdge(P1, P3, 10.4);
    myGraph.addBidirectionalEdge(P3, P4,  15.8);
    myGraph.addBidirectionalEdge(P4, P5, 22.4);
    myGraph.addBidirectionalEdge(P5, P2, 17.5);
    myGraph.addBidirectionalEdge(P3, P5, 20.2);

    return myGraph;
}

Graph getTestGraph4(){
    Graph myGraph;

    Point P1(1,300, 0);
    Point P2(2,700,0);
    Point P3(3,800, 200);
    Point P4(4,1000,300);
    Point P5(5,1100,100);
    Point P6(6,500,300);
    Point P7(7,600,400);
    Point P8(8,300,300);
    Point P9(9,0,100);
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);
    myGraph.addVertex(P4);
    myGraph.addVertex(P5);
    myGraph.addVertex(P6);
    myGraph.addVertex(P7);
    myGraph.addVertex(P8);
    myGraph.addVertex(P9);

    myGraph.addBidirectionalEdge(P1, P9, 0);
    myGraph.addBidirectionalEdge(P1, P2, 0);
    myGraph.addBidirectionalEdge(P2, P3, 0);
    myGraph.addBidirectionalEdge(P3, P4,  0);
    myGraph.addBidirectionalEdge(P4, P5, 0);
    myGraph.addBidirectionalEdge(P5, P3, 0);
    myGraph.addBidirectionalEdge(P3, P6, 0);
    myGraph.addBidirectionalEdge(P6, P7, 0);
    myGraph.addBidirectionalEdge(P6, P7, 0);
    myGraph.addBidirectionalEdge(P8, P6, 0);
    myGraph.addBidirectionalEdge(P8, P9, 0);

    return myGraph;
}