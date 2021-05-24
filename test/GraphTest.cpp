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
    checkAllPaths(myGraph, "0<-|1<-|2<-1|3<-2|4<-3|5<-|6<-1|7<-2|8<-7|9<-4|10<-|11<-6|12<-7|13<-12|14<-13|15<-|16<-11|17<-16|18<-13|19<-14|20<-|21<-16|22<-17|23<-22|24<-23|");
    checkSinglePath(myGraph.getPath(P0, P7), "1 2 7 12 13 18 ");

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


 TEST(Graph, disconnects) {
    Graph myGraph;

    Point P1(1,0,0);
    Point P2(2,0,0);
    Point P3(3,0,0);
    Point P4(4,0,0);
    Point P5(5,0,0);
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);
    myGraph.addVertex(P4);
    myGraph.addVertex(P5);
    myGraph.addBidirectionalEdge(P1, P3, 1);
    myGraph.addBidirectionalEdge(P2, P3, 1);
    myGraph.addBidirectionalEdge(P3, P4, 1);
    myGraph.addBidirectionalEdge(P4, P5, 1);

    //myGraph.getEuler(P1);
    Vertex * V2 = myGraph.findVertex(P2);
    Edge * aresta = V2->getAdj()[0];


    EXPECT_EQ(myGraph.disconnects(*aresta), true);
}



TEST(Graph, getEuler) {
    Graph myGraph;

    Point P1(1,0,0);
    Point P2(2,0,0);
    Point P3(3,0,0);
    Point P4(4,0,0);
    Point P5(5,0,0);
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);
    myGraph.addVertex(P4);
    myGraph.addVertex(P5);
    myGraph.addBidirectionalEdge(P1, P2, 1);
    myGraph.addBidirectionalEdge(P1, P3, 1);
    myGraph.addBidirectionalEdge(P2, P3, 1);
    myGraph.addBidirectionalEdge(P3, P4, 1);
    myGraph.addBidirectionalEdge(P4, P5, 1);

    vector<Point>res = myGraph.getEuler(P1);
    EXPECT_EQ(1, res[0].getId());
    EXPECT_EQ(2, res[1].getId());
    EXPECT_EQ(3, res[2].getId());
    EXPECT_EQ(4, res[3].getId());
    EXPECT_EQ(5, res[4].getId());

}

TEST(Graph, getEuler2) {
    Graph myGraph;
    Point P1(1,300, 0);
    Point P2(2,700,0);
    Point P3(3,800, 200);

    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);

    myGraph.addBidirectionalEdge(P1, P2, P1.getPosition().distance(P2.getPosition()));
    myGraph.addBidirectionalEdge(P1, P3, P1.getPosition().distance(P3.getPosition()));
    myGraph.addBidirectionalEdge(P2, P3, P2.getPosition().distance(P3.getPosition()));

    vector<Point>res = myGraph.getEuler(P1);

    for(auto i: res){
        cout << i.getId() << "|";
    }
    cout <<endl;

}

TEST(Graph, VertexSetAlterationAfterEuler) {
    Graph myGraph;

    Point P1(1,0,0);
    Point P2(2,0,0);
    Point P3(3,0,0);
    Point P4(4,0,0);
    Point P5(5,0,0);
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);
    myGraph.addVertex(P4);
    myGraph.addVertex(P5);
    myGraph.addBidirectionalEdge(P1, P2, 1);
    myGraph.addBidirectionalEdge(P1, P3, 1);
    myGraph.addBidirectionalEdge(P2, P3, 1);
    myGraph.addBidirectionalEdge(P3, P4, 1);
    myGraph.addBidirectionalEdge(P4, P5, 1);
    vector<Vertex *> original = myGraph.getVertexSet();

    vector<Point>res = myGraph.getEuler(P1);
    vector<Vertex *> after = myGraph.getVertexSet();

    for (int i = 0;i < original.size();i++) {
        EXPECT_EQ(original[i]->getPoint().getId(),after[i]->getPoint().getId());
    }

}

TEST(Graph, cutShort) {
    Graph myGraph = getTestGraph4();
    Point P0(0,0,300);
    Point P1(1,3, 0);
    Point P2(2,7,0);
    Point P3(3,8, 2);
    Point P4(4,10,3);
    Point P5(5,11,1);
    Point P6(6,5,3);
    Point P7(7,6,4);
    Point P8(8,3,3);
    Point P9(9,0,1);

    vector<Point>res = myGraph.getEuler(P1);
    //19867635432
    myGraph.cutShort(&res);

    vector<Point> expected {P1, P9, P8, P6, P7, P3, P5, P4, P2};
    EXPECT_EQ(res, expected);

}

TEST(Graph, getTranspose) {
    Graph myGraph;
    Point P0(0,-10,-10);
    Point P1(1,10,-10);
    Point P2(2,10,10);
    Point P3(3,-10,10);

    myGraph.addVertex(P0);
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);
    myGraph.addEdge(P0, P1, 1);
    myGraph.addEdge(P1, P2, 1);
    myGraph.addEdge(P2, P3, 1);
    myGraph.addEdge(P3, P0, 1);

    Graph transposed = myGraph.getTranspose();

    for(auto v : transposed.getVertexSet()){
        ASSERT_EQ(v->getAdj().size(), 2);
    }

    Vertex * v = transposed.findVertex(P3);
    int i = 3;
    do {
        ASSERT_EQ(v->getPoint().getId(), i);
        i--;
        v = v->getAdj().at(0)->getDest();
    }while(v->getPoint().getId() != 0);

}


TEST(Graph, fillOrder) {
    Graph myGraph;
    Point P0(0,-10,-10);
    Point P1(1,10,-10);
    Point P2(2,10,10);
    Point P3(3,-10,10);

    myGraph.addVertex(P0);
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);
    myGraph.addEdge(P0, P1, 1);
    myGraph.addEdge(P1, P2, 1);
    myGraph.addEdge(P2, P3, 1);
    myGraph.addEdge(P3, P0, 1);

    for(auto v :myGraph.getVertexSet())
    {
        v->visited = false;
    }

    stack<Vertex *>stack;
    myGraph.fillOrder(myGraph.findVertex(P0), stack);

    int i = 0;
    while(!stack.empty()){
        Vertex * v = stack.top(); stack.pop();
        ASSERT_EQ(v->getPoint().getId(), i);
        i++;
    }
}

TEST(Graph, DFSUtil) {
    Graph myGraph;
    Point P0(0, -10, -10);
    Point P1(1, 10, -10);
    Point P2(2, 10, 10);
    Point P3(3, -10, 10);

    myGraph.addVertex(P0);
    myGraph.addVertex(P1);
    myGraph.addVertex(P2);
    myGraph.addVertex(P3);
    myGraph.addEdge(P0, P1, 1);
    myGraph.addEdge(P1, P2, 1);
    myGraph.addEdge(P2, P3, 1);
    myGraph.addEdge(P3, P0, 1);

    for (auto v :myGraph.getVertexSet()) {
        v->visited = false;
    }

    vector<Vertex *> vector;
    myGraph.DFSUtil(myGraph.findVertex(P0), vector);

    int i = 0;
    for (auto v : vector) {
        ASSERT_EQ(v->getPoint().getId(), i);
        i++;
    }
}


TEST(Graph, getSCC) {
    Graph myGraph;
    GraphLoader graphLoader(&myGraph);
    graphLoader.loadMap("../data/GridGraphs/4x4/nodes.txt", "../data/GridGraphs/4x4/edges.txt",1);

    vector<vector<Vertex *>> scc = myGraph.getSCC();
    if(scc.size() == 1 && scc.at(0).size() == myGraph.getVertexSet().size())
        cout << "Strongly connected!!\n";
    for(auto component : scc){
        for(auto vertex : component){
            cout << vertex->getPoint().getId() << " ";
        }
        cout << endl;
    }
}
