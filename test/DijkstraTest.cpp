//
// Created by pedro on 06/04/21.
//

#include "../src/Graph.h"
#include "TestAux.h"



/// TESTS ///
#include <gtest/gtest.h>
#include "string"

TEST(Dijkstra, test_dijkstra) {
Graph<int> myGraph = CreateTestGraph();

myGraph.dijkstraShortestPath(3);
checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");


myGraph.dijkstraShortestPath(1);
checkAllPaths(myGraph, "1<-|2<-1|3<-4|4<-2|5<-4|6<-4|7<-5|");
checkSinglePath(myGraph.getPath(1, 7), "1 2 4 5 7 ");

myGraph.dijkstraShortestPath(5);
checkSinglePath(myGraph.getPath(5, 6), "5 7 6 ");

myGraph.dijkstraShortestPath(7);
checkSinglePath(myGraph.getPath(7, 1), "7 6 4 3 1 ");
}

TEST(Dijkstra, test_dijkstra_map1) {
    Graph<int> myGraph = CreateMap1();

    myGraph.dijkstraShortestPath(1);
    checkAllPaths(myGraph, "1<-|2<-1|3<-4|4<-2|5<-4|6<-3|7<-6|");
    checkSinglePath(myGraph.getPath(1, 7), "1 2 4 3 6 7 ");


    myGraph.dijkstraShortestPath(7);
    checkAllPaths(myGraph, "1<-2|2<-4|3<-6|4<-3|5<-7|6<-7|7<-|");


}