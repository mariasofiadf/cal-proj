//
// Created by pedro on 26/04/21.
//

#include <gtest/gtest.h>
#include "../src/GraphLoader.h"

TEST(GraphLoaderTest, load){
    Graph graph;
    GraphLoader graphLoader(graph);
    graphLoader.loadMap("../data/roads.sqlite");
}