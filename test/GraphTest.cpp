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
