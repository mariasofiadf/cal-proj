//
// Created by pedro on 26/04/21.
//

#ifndef CAL_PROJ_GRAPHLOADER_H
#define CAL_PROJ_GRAPHLOADER_H



#include "Graph.h"


class GraphLoader {
    Graph * graph;

public:
    GraphLoader(Graph * graph) : graph(graph) {}

    void loadMap(string nodesFilename, string edgesFilename, int loadBidirectional = 0);
    void loadEdges(string edgesFilename, int loadBidirectional = 0);
    void loadNodes(string nodesFilename, float Pnumber = 0.05, float Cnumber = 0.05, float Gnumber = 0.05, float Snumber = 0.05);

    pointType getRandomPointType(int nodes, int &normal, int &park, int &coffee, int &gas, int &store);
};


#endif //CAL_PROJ_GRAPHLOADER_H
