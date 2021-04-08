#ifndef TEST_AUX_H_
#define TEST_AUX_H_

#include <gtest/gtest.h>

#include <sstream>
#include <random>
#include <time.h>
#include <chrono>

/**
 * Auxiliary functions to tests...
 *
 */
Graph CreateTestGraph();



void checkAllPaths(Graph &g, std::string expected) {
    std::stringstream ss;
    std::vector<Vertex* > vs = g.getVertexSet();
    for(unsigned int i = 0; i < vs.size(); i++) {
        ss << vs[i]->getInfo() << "<-";
        if ( vs[i]->getPath() != NULL )
            ss << vs[i]->getPath()->getInfo();
        ss << "|";
    }
    EXPECT_EQ(expected, ss.str());
}

void checkSinglePath(std::vector<Point> path, std::string expected) {
    std::stringstream ss;
    for(unsigned int i = 0; i < path.size(); i++)
        ss << path[i] << " ";
    EXPECT_EQ(expected, ss.str());
}

#endif /* TEST_AUX_H_ */
